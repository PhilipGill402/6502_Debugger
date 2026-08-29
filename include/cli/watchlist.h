#ifndef INCLUDE_CLI_WATCHLIST_H_
#define INCLUDE_CLI_WATCHLIST_H_

#include <stdint.h>

#define MAX_WATCH_POINTS 64

typedef struct {
    uint16_t addr;
    uint8_t found;
    uint8_t active;
} watch_point_t;

void watch_point_add(uint16_t addr);
void watch_point_remove(uint16_t addr);
void watch_point_activate(uint16_t addr);
void watch_point_reset(uint16_t addr);
int32_t watch_point_is_active();

extern watch_point_t watch_point_list[MAX_WATCH_POINTS];

#endif
