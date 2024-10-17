#include "navigation_switch.h"
#include "navswitch.h"

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