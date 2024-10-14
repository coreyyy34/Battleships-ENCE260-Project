/** @file   ship.c
 *  @author Corey Hines, Ethan Field
 *  @date   14 October 2024
 */

#include <stdint.h>
#include <stdbool.h>
#include "ship.h"

/**
 * @brief Calculates the bottom coordinates of a ship based on its orientation and type.
 * @param orientation The orientation of the ship (horizontal or vertical).
 * @param ship_type The type of the ship, representing its length.
 * @param x_top The x-coordinate of the top of the ship.
 * @param y_top The y-coordinate of the top of the ship.
 * @param x_bottom A pointer to store the calculated x-coordinate of the bottom of the ship.
 * @param y_bottom A pointer to store the calculated y-coordinate of the bottom of the ship.
 */
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

/**
 * @brief Creates a ship object with the specified parameters.
 * @param orientation The orientation of the ship (horizontal or vertical).
 * @param length The length/type of the ship.
 * @param x_top The x-coordinate of the top of the ship.
 * @param y_top The y-coordinate of the top of the ship.
 * @return A Ship_t object with its attributes initialized.
 */
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
