/**
 * Entry point of ESP32 series processors
 *
 * Copyright (C) 2022 Shizhi Huang <main.shizhi@gmail.com>
 *
 * This file may be distributed under the terms of the GNU GPLv3 license.
 */

#include <stddef.h>
#include "sched.h"

/**
 * @brief entry point of app, ran after bootloader
 */
int main(void) {
    sched_main();
    return 0;
}
