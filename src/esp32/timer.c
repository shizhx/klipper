/**
 * timer support on ESP32 series processors except ESP32
 *
 * Copyright (C) 2022 Shizhi Huang <main.shizhi@gmail.com>
 *
 * This file may be distributed under the terms of the GNU GPLv3 license.
 */

#include "board/irq.h"
#include "board/misc.h"

/**
 * @brief return true if time1 is before timer2.
 *
 * @param time1
 * @param time2
 * @return uint8_t
 */
uint8_t timer_is_before(uint32_t time1, uint32_t time2)
{
    return (int32_t)(time1 - time2) < 0;
}

void timer_kick(void)
{
}

// Disable hardware interrupts
void irq_disable(void)
{
}

// Enable hardware interrupts
void irq_enable(void)
{
}

// Disable hardware interrupts in not already disabled
irqstatus_t irq_save(void)
{
    return 0;
}

// Restore hardware interrupts to state from flag returned by irq_save()
void irq_restore(irqstatus_t flag)
{
}

// Atomically enable hardware interrupts and sleep processor until next irq
void irq_wait(void)
{
}

// Check if an interrupt is active (used only on architectures that do
// not have hardware interrupts)
void irq_poll(void)
{
}
