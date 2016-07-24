#include "Vector.hpp"

#include <functional>
#include <thread>

#define VTR_NOTHREADS 8

/* static void paralellize(size_t size, std::function <void, (size_t, size_t)> &worker) { */
#define PARALLEL(SIZE, FUNC) { \
	std::vector <std::thread> threads(VTR_NOTHREADS); \
	const size_t per_thread = SIZE / VTR_NOTHREADS; \
 \
	size_t start_idx = 0; \
	for(size_t i = 0; i < threads.size() - 1; ++i) { \
		threads[i] = std::thread(FUNC, start_idx, start_idx + per_thread); \
		start_idx += per_thread; \
	} \
 \
	threads.back() = std::thread(FUNC, start_idx, SIZE); \
 \
	for(auto &&it : threads) \
		it.join(); \
}

Vector Vector::Map(mapfunc_t &map_lambda) const {
	Vector vec = *this;

	const auto &worker = [&](size_t init, size_t fin) {
		for(size_t i = init; i < fin; ++i)
			vec[i] = map_lambda(vec[i]);
	};
	PARALLEL(vec.Size(), worker);

	return vec;
}

Vector Vector::Map(const Vector &a, const Vector &b, mapfunc_2_t &map_lambda) {
	ASSERT_DOMAIN(a.Size() == b.Size());
	Vector vec(a.Size(), 0.);

	const auto &worker = [&](size_t init, size_t fin) {
		for(size_t i = init; i < fin; ++i)
			vec[i] = map_lambda(a[i], b[i]);
	};
	PARALLEL(vec.Size(), worker);

	return vec;
}


static real_t reduce(const Vector::line_t &vec, Vector::mapfunc_2_t &func, const size_t start_id, const size_t fin_id) {
	if(start_id + 1 == fin_id)
		return vec[start_id];
	else return func(
		reduce(vec, func, start_id, (start_id + fin_id - 1) >> 1),
		reduce(vec, func, (start_id + fin_id + 1) >> 1, fin_id)
	);
}

real_t Vector::Reduce(const std::function <real_t (real_t, real_t)> &map_lambda) const {
	return reduce(line_, map_lambda, 0, Size());
}
