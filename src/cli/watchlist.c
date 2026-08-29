#include "cli/watchlist.h"
#include <string.h>

watch_point_t watch_point_list[MAX_WATCH_POINTS] = { 0 };

void watch_point_add(uint16_t addr) {
    for (uint8_t i = 0; i < MAX_WATCH_POINTS; ++i) {
        if (!watch_point_list[i].active) {
            watch_point_list[i].active = 1;
            watch_point_list[i].addr = addr;
            return;
        }
    }
}

void watch_point_remove(uint16_t addr) {
    for (uint8_t i = 0; i < MAX_WATCH_POINTS; ++i) {
        if (watch_point_list[i].addr == addr) {
            memset(&watch_point_list[i], 0, sizeof(watch_point_t));
            return;
        }
    }
}

void watch_point_activate(uint16_t addr) {
    for (uint8_t i = 0; i < MAX_WATCH_POINTS; ++i) {
        if (watch_point_list[i].addr == addr) {
            watch_point_list[i].found = 1;
            return;
        }
    }
}

void watch_point_reset(uint16_t addr) {
    for (uint8_t i = 0; i < MAX_WATCH_POINTS; ++i) {
        if (watch_point_list[i].addr == addr) {
            watch_point_list[i].found = 0; 
            return;
        }
    }
}

int32_t watch_point_is_active() {
    for (uint8_t i = 0; i < MAX_WATCH_POINTS; ++i) {
        if (watch_point_list[i].found)
            return watch_point_list[i].addr;
    }

    return -1;
}
