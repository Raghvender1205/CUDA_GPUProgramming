#include "Util.hpp"


namespace AI {
    namespace Util {
        /// XORShift 32bit
        uint32_t xorshift32() {
            static uint32_t y = 2463534242UL;
			y ^= (y << 13);
			y ^= (y >> 17);
			y ^= (y << 15);
			return y;
        }

        /// Random Number between 0 and 2^32
        int randint() {
            return xorshift32();
        }

        /// Random Number between 0 and 1
        float randf() {
            return (double)xorshift32() / (double)UINT_MAX;
        }

        /// Random Number in range (mean - deviation) to (mean + deviation)
        double Gaussian(const double mean, const double deviation) {
            return (mean - deviation) + randf() * deviation * 2.f;
        }
    } // namespace Util
} //  namespace AI
