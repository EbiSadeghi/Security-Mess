#include "OpaquePredicates.hpp"

uint32_t OpaquePredicates::simple_hash(const char* s) {
        uint32_t h = 2166136261u;
        while (*s) {
            h ^= static_cast<unsigned char>(*s++);
            h *= 16777619u;
        }
        return h;
    }


bool OpaquePredicates::opaque_true_arith(int x) {
    // Always true: (x*x + 2*x + 1) == (x+1)*(x+1)
    return (x*x + 2*x + 1) == (x+1)*(x+1);
}


bool OpaquePredicates::opaque_false_bits(unsigned n) {
    // For 32-bit unsigned, (n | ~n) == ~0 always, compare to a different value to get false
    return ((n | ~n) == 0xFFFFFFFFu) && ((n & ~n) == 1u);
}


bool OpaquePredicates::opaque_true_hash() {
    // Precomputed hash for "hello"
    return simple_hash("hello") == 1335831723u; // Precomputed value for hello
}


bool OpaquePredicates::opaque_true_fp(double x) {
    // If x is finite, (x - x) is 0.0; comparing with +0.0 yields true
    return std::isfinite(x) && ((x - x) == 0.0);
}


bool OpaquePredicates::opaque_true_loop(int n) {
    volatile int s = 0;
    for (int i = 0; i < n; ++i) s += i - i; // always adds 0
    return s == 0;
}


bool OpaquePredicates::opaque_env_time() {
    std::time_t t = std::time(nullptr);
    // For any valid time, t % 1 == 0, so compare to 0 to get true
    return (t % 1) == 0;
}