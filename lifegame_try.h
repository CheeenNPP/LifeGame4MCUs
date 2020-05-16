/* CODE BEGIN Header */
/* CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LIFEGAME_TRY_H
#define __LIFEGAME_TRY_H

/* Includes ------------------------------------------------------------------*/
// MCU related head file
#include "main.h"

// STD head file
#include "stdint.h"

/* Definations ---------------------------------------------------------------*/
// Define the rules to use
#ifndef USE_RULE_0
#define USE_RULE_0
#endif

#if defined(USE_RULE_0)
#define LG_BORN 3 
#define LG_LESS 2
#define LG_MORE 3
#endif

// Define the map size of this game
// Due to the adaptation of the screen, here we sets the map size the same as
// the display buffer size
#define LG_MAPSIZE_X 128
#define LG_MAPSIZE_Y 64
#if (LG_MAPSIZE_Y % 8) != 0
#warning "Wrong Y size! "
#endif
#define LG_MAPBUFSIZE (LG_MAPSIZE_X * LG_MAPSIZE_Y / 8)

/* Typedefs ------------------------------------------------------------------*/
typedef uint16_t LG_DataType;
typedef uint16_t LG_Position;
typedef enum {
    LG_DEAD = 0,
    LG_ALIVE = 1,
    LG_BUSY = 2,
    LG_READY = 3,
    LG_ERROR = 4
} LG_Status;

/* Function prototypes -------------------------------------------------------*/
LG_Status LG_CheckStatus(LG_Position X, LG_Position Y);
LG_Status LG_SetStatus(LG_Position X, LG_Position Y, LG_Status Status);
LG_DataType LG_CountNeighbour(LG_Position X, LG_Position Y);
LG_Status LG_CalcNextStatus(LG_Position X, LG_Position Y);
LG_Status LG_CalcAllMap(void);
LG_Status LG_CalcAllMap_Fast(void);
LG_Status LG_RefreshMap(void);

#endif
