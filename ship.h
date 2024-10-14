/** @file   ship.h
 *  @author Corey Hines, Ethan Field
 *  @date   14 October 2024
 *  @brief   This file defines the structures and functions for 
 *           handling ship creation and manipulation.
 */

#include <stdint.h>
#include <stdbool.h>

#define ORIENTATION_HORIZONTAL 0  /** Defines a horizontal ship orientation. */
#define ORIENTATION_VERTICAL 1    /** Defines a vertical ship orientation. */
#define SMALL_SHIP_LENGTH 2       /** Defines the length of a small ship. */
#define LARGE_SHIP_LENGTH 3       /** Defines the length of a large ship. */

/**
 * @typedef Orientation_t
 * @brief   Type definition for representing ship orientation.
 */
typedef uint8_t Orientation_t;

/**
 * @struct Ship_t
 * @brief  Represents a ship with its attributes.
 */
typedef struct
{
    Orientation_t orientation;
    uint8_t length;
    uint8_t x_top;
    uint8_t x_bottom;
    uint8_t y_top;
    uint8_t y_bottom;
    bool sunk;
} Ship_t;

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
 * @brief Creates a ship object with the specified parameters.
 * @param orientation The orientation of the ship (horizontal or vertical).
 * @param length The length/type of the ship.
 * @param x_top The x-coordinate of the top of the ship.
 * @param y_top The y-coordinate of the top of the ship.
 * @return A Ship_t object with its attributes initialized.
 */
Ship_t ship_create(Orientation_t orientation, ShipType_t length, uint8_t x_top,  uint8_t y_top);
