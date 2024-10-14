#include <stdint.h>
#include <stdbool.h>
#include "ship.h"

static void calculate_bottom_coords(
    Orientation_t orientation, 
    ShipType_t ship_type,
    uint8_t x_top,
    uint8_t y_top,
    uint8_t* x_bottom,
    uint8_t* y_bottom)
{
    if (orientation == ORIENTATION_HORIZONTAL)
    {
        *x_bottom = x_top + ship_type;
        *y_bottom = y_top;
    }
    else
    {
        *x_bottom = x_top;
        *y_bottom = y_top + ship_type;
    }
}

Ship_t ship_create(Orientation_t orientation, ShipType_t length, uint8_t x_top, uint8_t y_top)
{
    uint8_t x_bottom, y_bottom;
    calculate_bottom_coords(orientation, length, x_top, y_top, &x_bottom, &y_bottom);

    Ship_t ship = {
        .orientation = orientation,
        .length = length,
        .x_top = x_top,
        .x_bottom = x_bottom,
        .y_top = y_top,
        .y_bottom = y_bottom,
        .sunk = false
    };
    return ship;
}
