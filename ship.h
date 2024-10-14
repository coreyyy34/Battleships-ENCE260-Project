#include <stdint.h>
#include <stdbool.h>

#define ORIENTATION_HORIZONTAL 0
#define ORIENTATION_VERTICAL 1
#define SMALL_SHIP_LENGTH 2
#define LARGE_SHIP_LENGTH 3

typedef uint8_t Orientation_t;

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

typedef enum 
{
    SMALL = SMALL_SHIP_LENGTH,
    LARGE = LARGE_SHIP_LENGTH
} ShipType_t;

Ship_t ship_create(Orientation_t orientation, ShipType_t length, uint8_t x_top,  uint8_t y_top);
