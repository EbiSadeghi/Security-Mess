#ifndef OPAQUE_PREDICATES_HPP
#define OPAQUE_PREDICATES_HPP

#include <cmath>
#include <ctime>
#include <cstdint>

/**
 * @brief Collection of opaque predicate functions used for demonstration and
 *        obfuscation examples.
 *
 * The OpaquePredicates class groups several functions that evaluate to
 * constant boolean outcomes while appearing nontrivial.  Each method
 * demonstrates a different technique for creating an opaque predicate:
 * arithmetic identity, bitwise trick, hashed comparison, floating-point
 * identity, loop-accumulation, and environment-derived value.
 *
 * @note These functions are intended for educational/obfuscation examples.
 *       They reduce readability and can be simplified by optimizers or by
 *       static analysis. Do not use them in production logic.
 */
class OpaquePredicates {
public:
    /**
     * @brief Opaque predicate using an arithmetic identity.
     *
     * Returns true by comparing two algebraically equal expressions:
     * (x*x + 2*x + 1) and (x+1)*(x+1).
     *
     * @param x Integer input (any value).
     * @return true Always true for all integer x.
     */
    static bool opaque_true_arith(int x);


    /**
     * @brief Opaque predicate using bitwise operations that is always false.
     *
     * The first conjunct ((n | ~n) == 0xFFFFFFFFu) holds for 32-bit unsigned n,
     * but the second conjunct ((n & ~n) == 1u) is never true, so the whole
     * expression always evaluates to false.
     *
     * @param n Unsigned integer input.
     * @return false Always false for all unsigned n.
     */
    static bool opaque_false_bits(unsigned n);


    /**
     * @brief Opaque predicate that compares a precomputed hash to a string hash.
     *
     * Uses simple_hash("hello") and compares it to a precomputed constant.
     * If the constant matches the computed hash, this predicate is always true.
     *
     * @return true Always true if the precomputed constant equals the computed hash.
     */
    static bool opaque_true_hash();


    /**
     * @brief Opaque predicate relying on a floating-point identity.
     *
     * If x is finite, (x - x) yields +0.0, so comparing to 0.0 is true.
     * NaN or infinite inputs are excluded by std::isfinite.
     *
     * @param x Floating-point input.
     * @return true True for all finite x; false for NaN or infinities.
     */
    static bool opaque_true_fp(double x);


    /**
     * @brief Opaque predicate using a loop that accumulates zero.
     *
     * Uses a volatile accumulator and a loop that adds (i - i) each iteration,
     * which is always zero; the function returns true because the accumulator
     * remains zero regardless of n.
     *
     * @param n Number of loop iterations.
     * @return true Always true; volatile reduces some compiler optimizations.
     */
    static bool opaque_true_loop(int n);


    /**
     * @brief Opaque predicate based on the current time.
     *
     * Since any integer time value modulo 1 equals 0, the expression (t % 1) == 0
     * is always true for valid time_t values.
     *
     * @return true Always true for any valid time returned by std::time(nullptr).
     */
    static bool opaque_env_time();


    /**
     * @brief Run a loop starting at `start` and call `body(ii)` each iteration.
     *
     * This overload accepts any callable `body` and ignores its return value.
     * If `body` does not itself break/throw/return, the loop will continue
     * indefinitely (since the predicate is always true).
     *
     * Note on forwarding and invocation:
     * // std::forward<Fn>(body) performs perfect forwarding of the callable.
     * // std::forward<Fn>(body)(ii) invokes the callable with argument ii.
     * // If body is an rvalue (temporary), forwarding preserves that and
     * // avoids unnecessary copies/moves. If it's an lvalue, forwarding calls it as-is.
     */
    template<typename Fn>
    static void forever_arith_loop_ignore_return(int start, Fn&& body) {
        for (int ii = start; opaque_true_arith(ii); ++ii) {
            // invoke the forwarded callable; return value (if any) is ignored
            std::forward<Fn>(body)(ii);
        }
    }


    // convenience with default start = 0
    template<typename Fn>
    static void forever_arith_loop_ignore_return(Fn&& body) {
        forever_arith_loop_ignore_return(0, std::forward<Fn>(body));
    }


    /**
     * @brief Run a loop starting at `start` where `body(ii)` returns bool to continue.
     *
     * This overload expects `body` to return something convertible to bool:
     * - return true  => continue loop
     * - return false => break out of loop
     *
     * If `body` does not return a bool-convertible value, this will be a compile error.
     *
     * Notes on forwarding and invocation:
     * // std::forward<Fn>(body) performs perfect forwarding of the callable.
     * // std::forward<Fn>(body)(ii) invokes the callable with argument ii.
     * // The expression if (!std::forward<Fn>(body)(ii)) break; calls the callable
     * // once per iteration and breaks when the callable returns false.
     */
    template<typename Fn>
    static void forever_arith_loop_until(int start, Fn&& body) {
        for (int ii = start; opaque_true_arith(ii); ++ii) {
            // call once; if it returns false, break
            if (!std::forward<Fn>(body)(ii)) break;
        }
    }


    // convenience with default start = 0
    template<typename Fn>
    static void forever_arith_loop_until(Fn&& body) {
        forever_arith_loop_until(0, std::forward<Fn>(body));
    }


private:
    /**
     * @brief Simple FNV-1a hash of a null-terminated string.
     *
     * Produces a 32-bit hash for the given C string using the FNV-1a algorithm. 
     * - FNV-1a is a common, simple non-cryptographic hash.
     *
     * @param s Null-terminated input string.
     * @return 32-bit hash value.
     */
    static uint32_t simple_hash(const char* s);
};

#endif // OPAQUE_PREDICATES_HPP