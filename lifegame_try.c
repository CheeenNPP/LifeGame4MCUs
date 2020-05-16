#include "lifegame_try.h"

static const int8_t CHECK_SQNC_X[8] = {-1, 0 , 1, -1, 1, -1, 0, 1};
static const int8_t CHECK_SQNC_Y[8] = {-1, -1 , -1, 0, 0, 1, 1, 1};

uint8_t LG_MAPBUF_NOW[LG_MAPBUFSIZE];
uint8_t LG_MAPBUF_NEXT[LG_MAPBUFSIZE];

LG_Status LG_CheckStatus(LG_Position X, LG_Position Y) {
    LG_Status state;
    LG_Position addr;
    uint8_t mask, temp;
    addr = X + (Y / 8) * LG_MAPSIZE_X;
    mask = (1 << (Y % 8));
    temp = LG_MAPBUF_NOW[addr] & mask;
    if (temp == mask) {
        state = LG_ALIVE;
    } else {
        state = LG_DEAD;
    }
    return state;
}

LG_Status LG_SetStatus(LG_Position X, LG_Position Y, LG_Status Status) {
    if (Status == LG_ALIVE) {
        LG_MAPBUF_NEXT[X + (Y / 8) * LG_MAPSIZE_X] |= (1 << (Y % 8));
    } else if (Status == LG_DEAD) {
        LG_MAPBUF_NEXT[X + (Y / 8) * LG_MAPSIZE_X] &= ~(1 << (Y % 8));
    } else {
        return LG_ERROR;
    }
    return LG_READY;
}

LG_DataType LG_CountNeighbour(LG_Position X, LG_Position Y) {
    LG_DataType num = 0;
    LG_Position tempx, tempy;
    uint8_t i;
    for (i = 0; i < 8; i++) {
        tempx = (uint8_t)(X + CHECK_SQNC_X[i]) % LG_MAPSIZE_X;
        tempy = (uint8_t)(Y + CHECK_SQNC_Y[i]) % LG_MAPSIZE_Y;
        if (LG_CheckStatus(tempx, tempy) == LG_ALIVE) {
            num += 1;
        } else {
            num += 0;
        }
    }
    return num;
}

LG_Status LG_CalcNextStatus(LG_Position X, LG_Position Y) {
    LG_DataType num = LG_CountNeighbour(X, Y);
    LG_Status status = LG_CheckStatus(X, Y);
    if (status == LG_DEAD && num == LG_BORN) {
        LG_SetStatus(X, Y, LG_ALIVE);
    } else if (status == LG_ALIVE && num > LG_MORE) {
        LG_SetStatus(X, Y, LG_DEAD);
    } else if (status == LG_ALIVE && num < LG_LESS) {
        LG_SetStatus(X, Y, LG_DEAD);
    } else {
        return LG_READY;
    }
    return LG_READY;
}

LG_Status LG_CalcAllMap(void) {
    LG_Position i, j;
    for (i = 0; i < LG_MAPSIZE_X; i++) {
        for (j = 0; j < LG_MAPSIZE_Y; j++ ) {
            LG_CalcNextStatus(i, j);
        }
    }
    return LG_READY;
}

LG_Status LG_CalcAllMap_Fast(void) {
    return LG_READY;
}

LG_Status LG_RefreshMap(void) {
    uint16_t i;
    for (i = 0; i < LG_MAPBUFSIZE; i++) {
        LG_MAPBUF_NOW[i] = LG_MAPBUF_NEXT[i];
    }
    return LG_READY;
}
