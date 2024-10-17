/** @file   utils.h
 *  @author Corey Hines
 *  @date   17/10/2024
 */

#ifndef UTIL_H
#define UTIL_H

/**
 * @brief Returns the minimum of two values.
 * @param a The first value to compare.
 * @param b The second value to compare.
 * @return The smaller of a and b.
 */
#define MIN(a,b) (((a)<(b))?(a):(b))

/**
 * @brief Returns the maximum of two values.
 * @param a The first value to compare.
 * @param b The second value to compare.
 * @return The larger of a and b.
 */
#define MAX(a,b) (((a)>(b))?(a):(b))

#endif /* UTIL_H */