/** @file   ship.h
 *  @author Corey Hines, Ethan Field
 *  @date   14 October 2024
 *  @brief  This file defines the structures and functions for 
 *          handling ship creation, manipulation, and destruction in the game.
 */

#ifndef SHIP_H
#define SHIP_H

#include <stdint.h>
#include <stdbool.h>

#define ORIENTATION_HORIZONTAL 0  /** Defines a horizontal ship orientation. */
#define ORIENTATION_VERTICAL 1    /** Defines a vertical ship orientation. */
#define SMALL_SHIP_LENGTH 2       /** Defines the length of a small ship. */
#define LARGE_SHIP_LENGTH 3       /** Defines the length of a large ship. */

/**
 * @typedef Orientation_t
 * @brief   Type definition for representing ship orientation (horizontal or vertical).
 */
typedef uint8_t Orientation_t;

/**
 * @struct ShipPoint_t
 * @brief  Represents a point on a ship.
 */
typedef struct
{
    uint8_t x_coord;
    uint8_t y_coord;
    bool hit;
} ShipPoint_t;

/**
 * @enum  ShipType_t
 * @brief Enumeration for ship types.
 */
typedef enum 
{
    SMALL = SMALL_SHIP_LENGTH,
    LARGE = LARGE_SHIP_LENGTH
} ShipType_t;

/**
 * @struct Ship_t
 * @brief  Represents a ship with a set orientation, type, and its points on the grid.
 */
typedef struct
{
    Orientation_t orientation;
    ShipType_t type;
    ShipPoint_t* points;
} Ship_t;

/**
 * @brief  Creates a ship object with the specified parameters.
 * @param  orientation The orientation of the ship (horizontal or vertical).
 * @param  type The type of the ship, which determines its length (either SMALL or LARGE).
 * @param  x_top The x-coordinate of the topmost (or leftmost) part of the ship.
 * @param  y_top The y-coordinate of the topmost (or leftmost) part of the ship.
 * @return A dynamically allocated Ship_t object with initialized attributes.
 */
Ship_t* ship_create(Orientation_t orientation, ShipType_t type, uint8_t x_top,  uint8_t y_top);

/**
 * @brief Removes a ship object with the specified parameters.
 * @param ship The Ship_t object to be removed.
 */
void ship_remove(Ship_t* ship);

/**
 * @brief  Checks if a ship has been completely sunk.
 * @param  ship A pointer to the Ship_t object to check.
 * @return true if all points of the ship have been hit (ship is sunk), false otherwise.
 */
bool ship_sunk(Ship_t* ship);

#endif /* SHIP_H */