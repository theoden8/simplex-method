#include "Vector.hpp"

#include <functional>
#include <thread>

#define VF_THREADS 8

void Vector::Map(const std::function <real_t (real_t)> &map_lambda) {
	const auto &worker = [&](line_t::iterator begin, line_t::iterator end) {
		for(auto it = begin; it != end; ++it)
			*it = map_lambda(*it);
	};

	std::vector <std::thread> threads(VF_THREADS);
	const size_t grain_size = Size() / VF_THREADS;

	auto work_iter = std::begin(line_);
	for(auto it = std::begin(threads); it != std::end(threads) - 1; ++it) {
		*it = std::thread(worker, work_iter, work_iter + grain_size);
		work_iter += grain_size;
	}

	threads.back() = std::thread(worker, work_iter, std::end(line_));

	for(auto&& it : threads)
		it.join();
}
