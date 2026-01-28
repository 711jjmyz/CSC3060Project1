#ifndef DATA_LAB_HPP
#define DATA_LAB_HPP

#include <cstdint>
namespace data_lab {

/**
 * @brief Adds two 32-bit signed integers.
 *
 * @param a The first operand
 * @param b The second operand
 * @return int32_t The sum of a and b
 */
int32_t add(int32_t a, int32_t b);

/**
 * @brief Subtracts the second integer from the first.
 *
 * @param a The minuend
 * @param b The subtrahend
 * @return int32_t The difference (a - b)
 */
int32_t subtract(int32_t a, int32_t b);

/**
 * @brief Multiplies two 32-bit signed integers.
 *
 * @param a The first factor
 * @param b The second factor
 * @return int32_t The product of a and b
 */
int32_t multiply(int32_t a, int32_t b);

/**
 * @brief Divides the first integer by the second.
 *
 * @param a The dividend
 * @param b The divisor
 * @return int32_t The quotient (a / b)
 * @note Division by zero behavior is undefined
 */
int32_t divide(int32_t a, int32_t b);

/**
 * @brief Computes the modulo (remainder) of integer division.
 *
 * @param a The dividend
 * @param b The divisor
 * @return int32_t The remainder of a divided by b
 * @note Modulo by zero behavior is undefined
 */
int32_t modulo(int32_t a, int32_t b);

}  // namespace data_lab

#endif  // DATA_LAB_HPP
