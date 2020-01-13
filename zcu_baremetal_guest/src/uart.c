/**
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#include <stdio.h>

#include "uart.h"
#include "zynq_uart.h"

Xil_Uart *uart  = (void*) 0xFF010000;

void uart_init(void)
{
    xil_uart_init(uart);
    xil_uart_enable(uart);

    return;
}

void uart_putc(char c)
{
    xil_uart_putc(uart, c);
}

char uart_getchar(void)
{
    return xil_uart_getc(uart);
}

void uart_enable_rxirq(){
    xil_uart_enable_irq(uart, UART_ISR_EN_RTRIG);
}

void uart_clear_irqs(){
    xil_uart_clear_rxbuf(uart);
    xil_uart_clear_irq(uart, 0xFFFFFFFF);
}