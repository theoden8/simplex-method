#include "VectorTests.hpp"

TEST_F(VectorTest, VectorMapTest) {
	Vector
		empty,
		longvector(100, [](const size_t idx) {return (real_t)idx * (real_t)idx;});
	ASSERT_NO_THROW(empty.Map([](real_t val) {return val / 0;}));

	Vector cpvector(longvector);

	for(size_t i = 0; i < cpvector.Size(); ++i)
		cpvector[i] *= cpvector[i];
	longvector.Map([](real_t val) {return val * val;});
	ASSERT_TRUE(cmp_vec_double(longvector, cpvector));

	for(size_t i = 0; i < cpvector.Size(); ++i)
		cpvector[i] = log(cpvector[i]);
	longvector.Map([](real_t val) {return log(val);});
	ASSERT_TRUE(cmp_vec_double(longvector, cpvector));
}
