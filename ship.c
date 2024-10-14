/** @file   ship.c
 *  @author Corey Hines, Ethan Field
 *  @date   14 October 2024
 *  @brief  This file defines the structures and functions for 
 *          handling ship creation, manipulation, and destruction in the game.
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
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
static void ship_calculate_bottom_coords(
    Orientation_t orientation, 
    ShipType_t ship_type,
    uint8_t x_top,
    uint8_t y_top,
    uint8_t* x_bottom,
    uint8_t* y_bottom)
{
    if (orientation == ORIENTATION_HORIZONTAL)
    {
        *x_bottom = x_top + ship_type - 1;  // Adjust for 0-based index
        *y_bottom = y_top;
    }
    else
    {
        *x_bottom = x_top;
        *y_bottom = y_top + ship_type - 1;  // Adjust for 0-based index
    }
}

/**
 * @brief Creates and returns the points of a ship based on its type and coordinates.
 * @param ship_type The type of the ship, representing its length.
 * @param x_top The x-coordinate of the top of the ship.
 * @param y_top The y-coordinate of the top of the ship.
 * @param orientation The orientation of the ship.
 * @return A dynamically allocated array of ShipPoint_t representing the ship's points.
 */
static ShipPoint_t* ship_create_points(ShipType_t ship_type, uint8_t x_top, uint8_t y_top, Orientation_t orientation)
{
    ShipPoint_t* ship_points = malloc(ship_type * sizeof(ShipPoint_t));
    for (uint8_t i = 0; i < ship_type; i++)
    {
        if (orientation == ORIENTATION_HORIZONTAL)
        {
            ship_points[i].x_coord = x_top + i;
            ship_points[i].y_coord = y_top;
        }
        else
        {
            ship_points[i].x_coord = x_top;
            ship_points[i].y_coord = y_top + i;
        }
    }

    return ship_points;
}

/**
 * @brief  Creates a ship object with the specified parameters.
 * @param  orientation The orientation of the ship (horizontal or vertical).
 * @param  type The type of the ship, which determines its length (either SMALL or LARGE).
 * @param  x_top The x-coordinate of the topmost (or leftmost) part of the ship.
 * @param  y_top The y-coordinate of the topmost (or leftmost) part of the ship.
 * @return A dynamically allocated Ship_t object with initialized attributes.
 */
Ship_t* ship_create(Orientation_t orientation, ShipType_t type, uint8_t x_top, uint8_t y_top)
{
    uint8_t x_bottom, y_bottom;
    ship_calculate_bottom_coords(orientation, type, x_top, y_top, &x_bottom, &y_bottom);

    ShipPoint_t* points = ship_create_points(type, x_top, y_top, orientation);
    Ship_t* ship = malloc(sizeof(Ship_t));
    ship->orientation = orientation;
    ship->type = type;
    ship->points = points;
    return ship;
}

/**
 * @brief Removes a ship object with the specified parameters.
 * @param ship The Ship_t object to be removed.
 */
void ship_remove(Ship_t* ship)
{
    if (ship != NULL) {
        free(ship->points);
        free(ship);
    }
}

/**
 * @brief  Checks if a ship has been completely sunk.
 * @param  ship A pointer to the Ship_t object to check.
 * @return true if all points of the ship have been hit (ship is sunk), false otherwise.
 */
bool ship_sunk(Ship_t* ship)
{
    ShipPoint_t* points = ship->points;
    for (uint8_t i = 0; i < ship->type; i++)
    {
        if (!points[i].hit) {
            return false;
        }
    }
    return true;
}