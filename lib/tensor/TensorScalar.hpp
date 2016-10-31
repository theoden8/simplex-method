#pragma once


template <>
class Tensor<0> {
public:
	typedef real_t tensor_t;
protected:
	tensor_t grid_;
public:
	Tensor();
	Tensor(tensor_t val);
	virtual ~Tensor();

	virtual size_t Size() const;
	virtual const tensor_t &GetGrid() const;

	virtual operator tensor_t() ;
	virtual const operator tensor_t() const;

	void
		operator +=(real_t val),
		operator -=(real_t val),
		operator *=(real_t val),
		operator /=(real_t val);
};
