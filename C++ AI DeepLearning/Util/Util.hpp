#ifndef UTIL_HPP
#define UTIL_HPP

#include <math.h>
#include <random>
#include <limits.h>

namespace AI {
    namespace Util {
        /// XORShift 32bit
        uint32_t xorshift32();

        /// Random Number between 0 and 2^32
        int randint();

        /// Random Number between 0 and 1
        float randf();

        /// Random Number in range (mean - deviation) to (mean + deviation)
        double Gaussian(const double mean, const double deviation);
    }; // namespace Util
} // namespace AI
#endif // UTIL_HPP
