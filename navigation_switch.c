/** 
 * @file   navigation_switch.c
 * @brief  Implementation of navigation switch functions.
 *
 * This file contains the implementation of functions for handling the navigation switch.
 * It includes functionality to detect and return the current direction or state of the
 * navigation switch, based on its input events.
 *
 * @date   17/10/2024
 * @author Corey Hines
 */

#include "navigation_switch.h"
#include "navswitch.h"

/**
 * @brief Get the current direction of the navigation switch.
 *
 * This function updates the state of the navigation switch and returns the current
 * direction or state based on the input events. It checks if the navigation switch
 * is pushed in any direction or pressed, and returns the corresponding direction enum.
 *
 * @return Direction_t The current direction of the navigation switch.
 */
Direction_t navigation_switch_get(void)
{
    navswitch_update();
    if (navswitch_push_event_p(NAVSWITCH_NORTH))      /* up */
    {
        return DIR_NORTH;
    }
    else if (navswitch_push_event_p(NAVSWITCH_SOUTH)) /* down */
    {
        return DIR_SOUTH;
    }
    else if (navswitch_push_event_p(NAVSWITCH_WEST))  /* left */
    {
        return DIR_WEST;
    }
    else if (navswitch_push_event_p(NAVSWITCH_EAST))  /* right */
    {
        return DIR_EAST;
    }
    else if (navswitch_push_event_p(NAVSWITCH_PUSH))  /* down */
    {
        return DIR_PUSHED;
    }
    return DIR_NONE;
}