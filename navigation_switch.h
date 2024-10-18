/** 
 * @file   navigation_switch.h
 * @brief  Header of navigation switch functions.
 * @author Corey Hines
 * @date   17/10/2024
 */

#ifndef NAVIGATION_SWITCH_H
#define NAVIGATION_SWITCH_H

/**
 * @enum  Direction_t
 * @brief Enum representing possible directions of the navigation switch.
 */
typedef enum 
{
    DIR_NONE,  /**< No direction is selected. */
    DIR_NORTH, /**< Navigation switched is pushed to the north direction. */
    DIR_EAST,  /**< Navigation switched is pushed to the east direction. */
    DIR_SOUTH, /**< Navigation switched is pushed to the south direction. */
    DIR_WEST,  /**< Navigation switched is pushed to the west direction. */
    DIR_PUSHED /**< Navigation switched is pressed/pushed. */
} Direction_t;

/**
 * @brief Get the current direction of the navigation switch.
 * @return Direction_t The current direction of the navigation switch.
 */
Direction_t navigation_switch_get(void);

#endif /* NAVIGATION_SWITCH_H */
