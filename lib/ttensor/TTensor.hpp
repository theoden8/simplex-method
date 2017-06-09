#pragma once

#include <cstdlib> // size_t
#include <type_traits> // std::enable_if and similar
#include <utility> // sequences etc

// constant
template <auto X> struct constant_struct { static constexpr const auto value = X; using type = decltype(X); };
template <auto X>
using constant = constant_struct<X>;

// issame
template <class A, class B> static constexpr const bool issame = std::is_same<A, B>::value;

// tensor
template <class... Ts> struct tensor_sequence{};
template <class... Ts> using to_tensor = tensor_sequence<Ts...>;
template <auto... Xs> using to_vector = to_tensor<constant<Xs>...>;

// sfinae check for value/tensor
template <class T> class is_tensor_struct {
  template <typename U> static char test(decltype(U::value)*);
  template <typename U> static short test(...);
public:
  static const constexpr bool value = sizeof(test<T>(0)) != sizeof(char);
};
template <class T> static const constexpr bool is_tensor = is_tensor_struct<T>::value;

// len
template <class T> struct len_struct;
template <class T> const constexpr size_t len = len_struct<T>::value;
template <class F, class... Ts> struct len_struct<to_tensor<F, Ts...>>{static constexpr const auto value = 1 + len<to_tensor<Ts...>>;};
template <> struct len_struct<to_tensor<>>{static constexpr const auto value = 0;};

// head
template <class T> struct head_struct;
template <class T> using head = typename head_struct<T>::type;
template <class F, class... Ts> struct head_struct <to_tensor<F, Ts...>> { using type = F; };
template <> struct head_struct <to_tensor<>> { using type = void; };

// last
template <class T> struct last_struct;
template <class T> using last = typename last_struct<T>::type;
template <class Tf, class... Ts> struct last_struct <to_tensor<Tf, Ts...>> { using type = last<to_tensor<Ts...>>; };
template <class Tf> struct last_struct <to_tensor<Tf>> { using type = Tf; };

// concat
template <class T, class U> struct concat_struct;
template <class T, class U> using concat = typename concat_struct<T, U>::type;
template <class... Ts, class... Us> struct concat_struct<to_tensor<Ts...>, to_tensor<Us...>> {
  using type = to_tensor<Ts..., Us...>;
};

// append, insert
template <class T, class S> using append = concat<T, to_tensor<S>>;
template <class T, class S> using insert = concat<to_tensor<T>, S>;

// tail
template <class T> struct tail_struct;
template <class T> using tail = typename tail_struct<T>::type;
template <class F, class... Ts> struct tail_struct<to_tensor<F, Ts...>> { using type = to_tensor<Ts...>; };
template <> struct tail_struct<to_tensor<>> { using type = void; };

// init
template <class T> struct init_struct;
template <class T> using init = typename init_struct<T>::type;
template <class Tf, class... Ts> struct init_struct <to_tensor<Tf, Ts...>> { using type = concat<to_tensor<Tf>,init<to_tensor<Ts...>>>; };
template <class Tf> struct init_struct<to_tensor<Tf> > { using type = to_tensor<>; };
template <> struct init_struct <to_tensor<> > { using type = to_tensor<>; };

// rev
template <class T> struct rev_struct;
template <class T> using rev = typename rev_struct<T>::type;
template <class Tf, class... Ts>
struct rev_struct <to_tensor<Tf, Ts...> > {
	using type = concat<rev<to_tensor<Ts...> >, to_tensor<Tf> >;
};
template <>
struct rev_struct <to_tensor<> > {
	using type = to_tensor<>;
};

// take
template <size_t N, class T> struct take_struct;
template <size_t N, class T> using take = typename take_struct<N,T>::type;
template <size_t N, class Tf, class... Ts> struct take_struct <N, to_tensor<Tf, Ts...>> { using type = concat<to_tensor<Tf>, take<N - 1,to_tensor<Ts...>>>; };
template <size_t N> struct take_struct <N, to_tensor<> > { using type = to_tensor<>; };
template <class Tf, class... Ts> struct take_struct <0, to_tensor<Tf, Ts...> > { using type = to_tensor<>; };
template <> struct take_struct<0, to_tensor<> > { using type = to_tensor<>; };

// drop
template <size_t N, class T> struct drop_struct;
template <size_t N, class T> using drop = typename drop_struct<N, T>::type;
template <size_t N, class Tf, class... Ts>
struct drop_struct<N, to_tensor<Tf, Ts...> > { using type = drop<N - 1, to_tensor<Ts...> >; };
template <size_t N> struct drop_struct<N, to_tensor<> > { using type = to_tensor<>; };
template <class Tf, class... Ts> struct drop_struct<0, to_tensor<Tf, Ts...>> { using type = to_tensor<Tf, Ts...>; };

// dim
template <class T, bool istensor = is_tensor<T>> struct dim_struct;
template <class T> struct dim_struct <T, true> { static const constexpr size_t value = 1 + dim_struct<head<T>>::value; };
template <class T> struct dim_struct <T, false> { static const constexpr size_t value = 0; };
template <bool whatever> struct dim_struct <to_tensor<>, whatever> { static const constexpr size_t value = 0; };
template <class T> const constexpr size_t dim = dim_struct<T>::value;

template <class T> const constexpr bool is_num = (dim<T> == 0);

// index
template <class T, size_t... Is> struct tget_struct;
template <class T, size_t... Is> using tget = typename tget_struct<T, Is...>::type;
template <class... Ts> struct tget_struct<to_tensor<Ts...>, 0> {
  using type = head<to_tensor<Ts...>>;
};
template <class... Ts, size_t I> struct tget_struct<to_tensor<Ts...>, I> {
  using T = to_tensor<Ts...>; static void check() { static_assert(len<T> > I); }
  using type = tget<tail<T>, I - 1>;
};
template <class... Ts, size_t I, size_t J, size_t... Is> struct tget_struct<to_tensor<Ts...>, I, J, Is...> {
  using T = to_tensor<Ts...>;
  using type = tget<tget<T, I>, J, Is...>;
};
template <class... Ts> struct tget_struct<to_tensor<Ts...>> { using type = to_tensor<Ts...>; };

// mapf
template <class T, template <typename A> class F, bool apply = is_tensor<T>> struct mapf_struct;
template <class T, template <typename A> class F> using mapf = typename mapf_struct<T, F>::type;

template <class T, template <typename A> typename F> struct mapf_struct <T, F, false> { using type = typename F<T>::type; };
template <class Tf, class... Ts, template <typename A> typename F> struct mapf_struct <to_tensor<Tf, Ts...>, F, true> {
  using type = concat<to_tensor<mapf<Tf, F>>, mapf<to_tensor<Ts...>, F>>;
};
template <template <typename A> typename F> struct mapf_struct <to_tensor<>, F> { using type = to_tensor<>; };

// positive
template <class T> struct pos_struct;
template <class T> using pos = mapf<T, pos_struct>;
template <auto X> struct pos_struct <constant<X>> { using type = constant<+X>; };
// negative
template <class T> struct neg_struct;
template <class T> using neg = mapf<T, neg_struct>;
template <auto X> struct neg_struct <constant<X>> { using type = constant<-X>; };

// zipwith
template <class T, class U, template <typename A, typename B> typename F, bool apply=is_tensor<T>> struct zipwith_struct;
template <class T, class U, template <class A, class B> class F> using zipWith = typename zipwith_struct<T, U, F>::type;
template <class T, class U, template <class A, class B> class F> struct zipwith_struct <T, U, F, false> {
  static void check() { static_assert(len<T> == len<U> && dim<T> == dim<U>); }
  using type = typename F<T, U>::type;
};
template <class Tf, class... Ts, class Uf, class... Us, template <typename A, typename B> typename F>
struct zipwith_struct <to_tensor<Tf, Ts...>, to_tensor<Uf, Us...>, F, true> {
  using T = to_tensor<Tf, Ts...>; using U = to_tensor<Uf, Us...>;
  static void check() { static_assert(len<T> == len<U> && dim<T> == dim<U>); }
  using type = concat<to_tensor<zipWith<Tf, Uf, F>>, zipWith<to_tensor<Ts...>,to_tensor<Us...>, F>>;
};
template <template <class A, class B> class F> struct zipwith_struct <to_tensor<>, to_tensor<>, F> { using type = to_tensor<>; };

// fold
template <class T, template <class A, class B> class F, class N, bool apply = is_tensor<T>> struct fold_struct;
template <class T, template <class A, class B> class F, class N> using fold = typename fold_struct<T, F, N>::type;
template <class Tf, class... Ts, template <class A, class B> class F, class N> struct fold_struct <to_tensor<Tf, Ts...>, F, N, true> {
  using T = to_tensor<Tf, Ts...>;
  using type = typename F<fold<head<T>, F, N>, fold<tail<T>, F, N>>::type;
};
template <class T, template <class A, class B> class F, class N> struct fold_struct <T, F, N, false> {
  using type = T;
};
template <template <class A, class B> class F, class N, bool apply> struct fold_struct <to_tensor<>, F, N, apply> {
  using type = N;
};

// add, sum
template <class A, class B> struct add_struct;
template <auto X, auto Y> struct add_struct <constant<X>, constant<Y>> { using type = constant<X + Y>; };
template <class A, class B> using addf = zipWith<A, B, add_struct>;
template <class A, class B> using subf = zipWith<A, neg<B>, add_struct>;
template <class A> using sumf = fold<A, add_struct, constant<0>>;
// mul
template <class A, class B> struct mul_struct;
template <class A, class B> using mulf = zipWith<A, B, mul_struct>;
template <class A> using prdf = fold<A, mul_struct, constant<1>>;
template <auto X, auto Y> struct mul_struct <constant<X>, constant<Y>> { using type = constant<X * Y>; };

// TENSOR

// 0-size tensor
template <size_t N> struct tensor_empty_struct;
template <size_t N> using tensor_empty = typename tensor_empty_struct<N>::type;
template <size_t N> struct tensor_empty_struct { using type = to_tensor<tensor_empty<N - 1>>; };
template <> struct tensor_empty_struct <1> { using type = to_vector<>; };

// generate from a functor
template <class V, template <class I, class A> class F, class T, class ACC> struct gen_struct;
template <class V, template <class I, class A> class F, class T = to_vector<>, class ACC = to_vector<>>
using gen = typename gen_struct<V, F, T, ACC>::type;

template <size_t D, size_t... Ds, template <class I, class T> class F, class T, class ACC>
struct gen_struct <to_vector<D, Ds...>, F, T, ACC> {
  using inner_sizes = to_vector<Ds...>;
  using type = to_tensor<
    concat<
      gen<insert<constant<1>, inner_sizes>, F, T, ACC>,
      gen<insert<constant<D - 1>, inner_sizes>, F, T, ACC>
    >
  >;
};
template </* 1 ,*/size_t... Ds, template <class I, class A> class F, class T, class ACC>
struct gen_struct <to_vector<1, Ds...>, F, T, ACC> {
  using inner_sizes = to_vector<Ds...>;
  using type = to_tensor<gen<inner_sizes, F, T, append<ACC, constant<1>>>>;
};
template </* 0 ,*/size_t... Ds, template <class I, class A> class F, class T, class ACC>
struct gen_struct <to_vector<0, Ds...>, F, T, ACC> { using type = tensor_empty<len<to_vector<Ds...>>>; };
template <template <class I, class A> class F, class T, class ACC>
struct gen_struct<to_vector<>, F, T, ACC> { using type = typename F<ACC, T>::type; };

// VECTOR
template <class T> const constexpr bool is_vec = (dim<T> == 1);
template <class T> using if_vector = std::enable_if_t<is_vec<T>, T>;

// dot
template <class A, class B> using dotf = sumf<mulf<if_vector<A>, if_vector<B>>>;

// cross product
template <class A, class B, size_t L = len<A>> struct crossf_struct;
template <class A, class B> struct crossf_struct <A, B, 3> {
private:
  static const constexpr decltype(head<A>::value) a[3] = { tget<A,0>::value, tget<A,1>::value, tget<A,2>::value, };
  static const constexpr decltype(head<B>::value) b[3] = { tget<B,0>::value, tget<B,1>::value, tget<B,2>::value, };
public:
  using type = std::enable_if_t<(is_vec<A> && len<A> == 3) && (is_vec<B> && len<B> == 3), to_vector<
    a[1]*b[2] - a[2]*b[1],
    a[2]*b[0] - a[0]*b[2],
    a[0]*b[1] - a[1]*b[0]
  >>;
};
template <class A, class B> using crossf = typename crossf_struct<A, B>::type;

// generators
// 1, 2, ...
template <size_t N, class V> struct vec_ord_struct;
template <size_t N, class V = int> using vec_ord = typename vec_ord_struct<N, V>::type;
template <size_t N, class V> struct vec_ord_struct { using type = concat<vec_ord<N-1, V>, to_vector<V(N)-1>>; };
template <class V> struct vec_ord_struct <0, V> { using type = to_tensor<>; };

// MATRIX

// is matrix
template <class T> const constexpr bool is_mat = (dim<T> == 2);
template <class M> using if_matrix = std::enable_if_t<is_mat<M>, M>;

// is square
template <class M> const constexpr bool is_sqr = (len<M> == 0 || len<head<M>> == len<M>);
template <class M> using if_sqr_matrix = std::enable_if_t<is_sqr<M>, if_matrix<M>>;

// identity
/* template <class I, class A> struct identity_functor; */
/* template <size_t N> using id_mat = gen<to_vector<N, N>, identity_functor>; */
/* template <size_t Y, size_t X, class A> struct identity_functor<to_vector<Y, X>, A> { */
/*   using type = constant<(Y == X) ? 1 : 0>; */
/* }; */

// transpose
/* template <class I, class M> struct transpose_functor; */
/* template <class M> using transpose = gen<to_vector<len<head<M>>, len<M>>, transpose_functor>; */
/* template <size_t Y, size_t X, class M> struct transpose_functor <to_vector<Y, X>, M> { */
/*   using type = tget<if_matrix<M>, X, Y>; */
/* }; */


/* template <class T> struct Tensor { */
/*   using type = T; */

/*   static constexpr const size_t Len = len<type>; */
/*   static constexpr const size_t Dim = dim<type>; */

/*   using Head = head<type>; */
/*   using Last = last<type>; */
/*   using Init = init<type>; */
/*   using Tail = tail<type>; */
/*   using Rev = rev<type>; */

/*   template <class U> using Add = addf<T, U>; */
/*   template <class U> using Sub = subf<T, U>; */
/*   template <class U> using Mul = mulf<T, U>; */

/*   // constant */
/*   static constexpr bool IsConstant = !is_tensor<type>; */

/*   // vector */
/*   static constexpr bool IsVector = is_vec<type>; */
/*   template <class U> using Dot = dotf<if_vector<T>, if_vector<U>>; */
/*   template <class U> using Cross = crossf<if_vector<T>, if_vector<U>>; */

/*   // matrix */
/*   static constexpr bool IsMatrix = is_mat<type>; */
/*   static constexpr bool IsSquare = is_sqr<if_matrix<type>>; */
/*   using Transpose = transpose<T>; */

/*   // tensor */
/*   static constexpr bool IsTensor = is_tensor<type>; */
/* }; */

void test_tensor() {
  using num = constant<10>;
  static_assert(!is_tensor<num>);
  static_assert(is_num<num>);
  static_assert(issame<num::type, int>);

  using vec = to_vector<10, 20>;
  static_assert(is_tensor<vec>);
  static_assert(issame<constant<10>, head<vec>>);
  static_assert(is_vec<vec>);
  static_assert(issame<vec,pos<vec>>);
  static_assert(issame<neg<neg<vec>>,pos<vec>>);
  static_assert(issame<addf<vec,vec>,to_vector<20,40>>);
  static_assert(issame<sumf<to_vector<>>, constant<0>>);
  static_assert(issame<sumf<vec>, constant<30>>);
  static_assert(issame<prdf<to_tensor<>>, constant<1>>);
  static_assert(issame<prdf<vec>, constant<200>>);
  static_assert(issame<dotf<vec,vec>, constant<500>>);
  static_assert(issame<vec_ord<0>, to_vector<>>);
  static_assert(issame<vec_ord<1>, to_vector<0>>);
  static_assert(issame<vec_ord<2>, to_vector<0,1>>);
  static_assert(issame<crossf<tail<vec_ord<4>>, tail<vec_ord<4>>>, to_vector<0, 0, 0>>);

  using mat = to_tensor<to_vector<1, 0>, to_vector<0, 1>>;
  static_assert(is_tensor<mat>);
  static_assert(issame<constant<1>, head<head<mat>>>);
  static_assert(is_mat<mat>);
  static_assert(issame<tget<mat, 0>, to_vector<1, 0>>);
  static_assert(issame<tget<mat, 0, 1>, constant<0>>);
  static_assert(issame<mat,pos<mat>>);
  static_assert(issame<tget<neg<mat>, 0, 0>, constant<-1>>);
  static_assert(issame<addf<mat, mat>, to_tensor<to_vector<2,0>,to_vector<0,2>>>);
  static_assert(issame<sumf<mat>, constant<2>>);
  /* static_assert(issame<id_mat<2>, to_tensor<to_vector<1, 0>, to_vector<0, 1>>>); */
  /* transpose<tensor_empty<2>>; */
  /* static_assert(issame< */
  /*   transpose< */
  /*     to_tensor< */
  /*         to_vector<1, 2>, */
  /*         to_vector<3, 4> */
  /*     > */
  /*   >, */
  /*     to_tensor< */
  /*       to_vector<1, 3>, */
  /*       to_vector<2, 4> */
  /*     > */
  /*   > */
  /* ); */
}
