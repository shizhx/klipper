/**
 * Serial port support on ESP32 series processors
 *
 * Copyright (C) 2022 Shizhi Huang <main.shizhi@gmail.com>
 *
 * This file may be distributed under the terms of the GNU GPLv3 license.
 */

#include "board/serial_irq.h"
// #include "hal/interrupt_controller_hal.h"
#include "hal/uart_hal.h"
#include "sched.h"

#define UART_INTR_CONFIG_FLAG                                                  \
    ((UART_INTR_RXFIFO_FULL) | (UART_INTR_RXFIFO_TOUT) |                       \
     (UART_INTR_RXFIFO_OVF) | (UART_INTR_BRK_DET) | (UART_INTR_PARITY_ERR))

static uart_hal_context_t s_uart_ctx = {
    .dev = &UART0,
};

// callback provided by board specific code
void serial_enable_tx_irq(void)
{
}

void serial_init(void)
{
    uart_hal_disable_intr_mask(&s_uart_ctx, UART_LL_INTR_MASK);
    uart_hal_clr_intsts_mask(&s_uart_ctx, UART_LL_INTR_MASK);
    uart_hal_set_rx_timeout(&s_uart_ctx, 0);
    uart_hal_ena_intr_mask(&s_uart_ctx, UART_INTR_CONFIG_FLAG);
    uart_hal_init(&s_uart_ctx, 0);
    uart_hal_set_sclk(&s_uart_ctx, UART_SCLK_DEFAULT);
    uart_hal_set_baudrate(&s_uart_ctx, 115200);
    uart_hal_set_parity(&s_uart_ctx, UART_PARITY_DISABLE);
    uart_hal_set_data_bit_num(&s_uart_ctx, UART_DATA_8_BITS);
    uart_hal_set_stop_bits(&s_uart_ctx, UART_STOP_BITS_1);
    uart_hal_set_tx_idle_num(&s_uart_ctx, 0);
    uart_hal_rxfifo_rst(&s_uart_ctx);
    uart_hal_txfifo_rst(&s_uart_ctx);

    // set irq handler
}

DECL_INIT(serial_init);
