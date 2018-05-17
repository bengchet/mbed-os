/* mbed Microcontroller Library
 * Copyright (c) 2015-2017 Nuvoton
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "serial_api.h"

#if DEVICE_SERIAL

#include <string.h>
#include "cmsis.h"
#include "mbed_error.h"
#include "mbed_assert.h"
#include "PeripheralPins.h"
#include "nu_modutil.h"
#include "nu_bitutil.h"

struct nu_uart_var {
    uint32_t    ref_cnt;                // Reference count of the H/W module
    serial_t *  obj;
    uint32_t    fifo_size_tx;
    uint32_t    fifo_size_rx;
    void        (*vec)(void);
};

void UART02_IRQHandler(void);
void UART1_IRQHandler(void);
void UART3_IRQHandler(void);
void UART4_IRQHandler(void);
void UART5_IRQHandler(void);
static void uart_irq(serial_t *obj);
static void serial_enable_interrupt(serial_t *obj, SerialIrq irq, uint32_t enable);

static struct nu_uart_var uart0_var = {
    .ref_cnt            =   0,
    .obj                =   NULL,
    .fifo_size_tx       =   16,
    .fifo_size_rx       =   16,
    .vec                =   UART02_IRQHandler,
};
static struct nu_uart_var uart1_var = {
    .ref_cnt            =   0,
    .obj                =   NULL,
    .fifo_size_tx       =   16,
    .fifo_size_rx       =   16,
    .vec                =   UART1_IRQHandler,
};
static struct nu_uart_var uart2_var = {
    .ref_cnt            =   0,
    .obj                =   NULL,
    .fifo_size_tx       =   16,
    .fifo_size_rx       =   16,
    .vec                =   UART02_IRQHandler,
};
static struct nu_uart_var uart3_var = {
    .ref_cnt            =   0,
    .obj                =   NULL,
    .fifo_size_tx       =   16,
    .fifo_size_rx       =   16,
    .vec                =   UART3_IRQHandler,
};
static struct nu_uart_var uart4_var = {
    .ref_cnt            =   0,
    .obj                =   NULL,
    .fifo_size_tx       =   16,
    .fifo_size_rx       =   16,
    .vec                =   UART4_IRQHandler,
};
static struct nu_uart_var uart5_var = {
    .ref_cnt            =   0,
    .obj                =   NULL,
    .fifo_size_tx       =   16,
    .fifo_size_rx       =   16,
    .vec                =   UART5_IRQHandler,
};


int stdio_uart_inited = 0;
serial_t stdio_uart;
static uint32_t uart_modinit_mask = 0;

static const struct nu_modinit_s uart_modinit_tab[] = {
    {UART_0, UART0_MODULE, CLK_CLKSEL1_UART_S_HXT, CLK_CLKDIV_UART(1), UART0_RST, UART02_IRQn, &uart0_var},
    {UART_1, UART1_MODULE, CLK_CLKSEL1_UART_S_HXT, CLK_CLKDIV_UART(1), UART1_RST, UART1_IRQn, &uart1_var},
    {UART_2, UART2_MODULE, CLK_CLKSEL1_UART_S_HXT, CLK_CLKDIV_UART(1), UART2_RST, UART02_IRQn, &uart2_var},
    {UART_3, UART3_MODULE, CLK_CLKSEL1_UART_S_HXT, CLK_CLKDIV_UART(1), UART3_RST, UART3_IRQn, &uart3_var},
    {UART_4, UART4_MODULE, CLK_CLKSEL1_UART_S_HXT, CLK_CLKDIV_UART(1), UART4_RST, UART4_IRQn, &uart4_var},
    {UART_5, UART5_MODULE, CLK_CLKSEL1_UART_S_HXT, CLK_CLKDIV_UART(1), UART5_RST, UART5_IRQn, &uart5_var},
    {NC, 0, 0, 0, 0, (IRQn_Type) 0, NULL}
};

extern void mbed_sdk_init(void);

void serial_init(serial_t *obj, PinName tx, PinName rx)
{
    // NOTE: With armcc, serial_init() gets called from _sys_open() timing of which is before main()/mbed_sdk_init().
    mbed_sdk_init();
    
    // Determine which UART_x the pins are used for
    uint32_t uart_tx = pinmap_peripheral(tx, PinMap_UART_TX);
    uint32_t uart_rx = pinmap_peripheral(rx, PinMap_UART_RX);
    // Get the peripheral name (UART_x) from the pins and assign it to the object
    obj->uart = (UARTName) pinmap_merge(uart_tx, uart_rx);
    MBED_ASSERT((int)obj->uart != NC);

    const struct nu_modinit_s *modinit = get_modinit(obj->uart, uart_modinit_tab);
    MBED_ASSERT(modinit != NULL);
    MBED_ASSERT(modinit->modname == (int) obj->uart);
    
    struct nu_uart_var *var = (struct nu_uart_var *) modinit->var;
    
    if (! var->ref_cnt) {
        // Reset this module
        SYS_ResetModule(modinit->rsetidx);
    
        // Select IP clock source
        CLK_SetModuleClock(modinit->clkidx, modinit->clksrc, modinit->clkdiv);
        // Enable IP clock
        CLK_EnableModuleClock(modinit->clkidx);

        pinmap_pinout(tx, PinMap_UART_TX);
        pinmap_pinout(rx, PinMap_UART_RX);
    
        obj->pin_tx = tx;
        obj->pin_rx = rx;
    }
    var->ref_cnt ++;
    
    // Configure the UART module and set its baudrate
    serial_baud(obj, 9600);
    // Configure data bits, parity, and stop bits
    serial_format(obj, 8, ParityNone, 1);
    
    obj->vec = var->vec;
    obj->irq_en = 0;
    
    // For stdio management
    if (obj->uart == STDIO_UART) {
        stdio_uart_inited = 1;
        memcpy(&stdio_uart, obj, sizeof(serial_t));
    }
    
    if (var->ref_cnt) {
        // Mark this module to be inited.
        int i = modinit - uart_modinit_tab;
        uart_modinit_mask |= 1 << i;
    }
}

void serial_free(serial_t *obj)
{
    const struct nu_modinit_s *modinit = get_modinit(obj->uart, uart_modinit_tab);
    MBED_ASSERT(modinit != NULL);
    MBED_ASSERT(modinit->modname == (int) obj->uart);
    
    struct nu_uart_var *var = (struct nu_uart_var *) modinit->var;
    
    var->ref_cnt --;
    if (! var->ref_cnt) {
        UART_Close((UART_T *) NU_MODBASE(obj->uart));
    
        UART_DISABLE_INT(((UART_T *) NU_MODBASE(obj->uart)), UART_IER_RDA_IEN_Msk);
        NVIC_DisableIRQ(modinit->irq_n);
    
        // Disable IP clock
        CLK_DisableModuleClock(modinit->clkidx);
    }
    
    if (var->obj == obj) {
        var->obj = NULL;
    }
    
    if (obj->uart == STDIO_UART) {
        stdio_uart_inited = 0;
    }
    
    if (! var->ref_cnt) {
        // Mark this module to be deinited.
        int i = modinit - uart_modinit_tab;
        uart_modinit_mask &= ~(1 << i);
    }
}

void serial_baud(serial_t *obj, int baudrate) {
    // Flush Tx FIFO. Otherwise, output data may get lost on this change.
    while (! UART_IS_TX_EMPTY(((UART_T *) NU_MODBASE(obj->uart))));
    
    obj->baudrate = baudrate;
    UART_Open((UART_T *) NU_MODBASE(obj->uart), baudrate);
}

void serial_format(serial_t *obj, int data_bits, SerialParity parity, int stop_bits) {
    // Flush Tx FIFO. Otherwise, output data may get lost on this change.
    while (! UART_IS_TX_EMPTY(((UART_T *) NU_MODBASE(obj->uart))));
    
    // TODO: Assert for not supported parity and data bits
    obj->databits = data_bits;
    obj->parity = parity;
    obj->stopbits = stop_bits;
    
    uint32_t databits_intern = (data_bits == 5) ? UART_WORD_LEN_5 :
        (data_bits == 6) ? UART_WORD_LEN_6 :
        (data_bits == 7) ? UART_WORD_LEN_7 : 
        UART_WORD_LEN_8;
    uint32_t parity_intern = (parity == ParityOdd || parity == ParityForced1) ? UART_PARITY_ODD :
        (parity == ParityEven || parity == ParityForced0) ? UART_PARITY_EVEN :
        UART_PARITY_NONE;
    uint32_t stopbits_intern = (stop_bits == 2) ? UART_STOP_BIT_2 : UART_STOP_BIT_1;
    UART_SetLine_Config((UART_T *) NU_MODBASE(obj->uart), 
        0,  // Don't change baudrate 
        databits_intern, 
        parity_intern, 
        stopbits_intern);
}

void serial_irq_handler(serial_t *obj, uart_irq_handler handler, uint32_t id)
{
    // Flush Tx FIFO. Otherwise, output data may get lost on this change.
    while (! UART_IS_TX_EMPTY(((UART_T *) NU_MODBASE(obj->uart))));
    
    const struct nu_modinit_s *modinit = get_modinit(obj->uart, uart_modinit_tab);
    MBED_ASSERT(modinit != NULL);
    MBED_ASSERT(modinit->modname == (int) obj->uart);
    
    obj->irq_handler = (uint32_t) handler;
    obj->irq_id = id;
}

void serial_irq_set(serial_t *obj, SerialIrq irq, uint32_t enable)
{
    obj->irq_en = enable;
    serial_enable_interrupt(obj, irq, enable);
}

static void serial_enable_interrupt(serial_t *obj, SerialIrq irq, uint32_t enable)
{
    if (enable) {
        const struct nu_modinit_s *modinit = get_modinit(obj->uart, uart_modinit_tab);
        MBED_ASSERT(modinit != NULL);
        MBED_ASSERT(modinit->modname == (int) obj->uart);
    
        NVIC_SetVector(modinit->irq_n, (uint32_t) obj->vec);
        NVIC_EnableIRQ(modinit->irq_n);
        
        struct nu_uart_var *var = (struct nu_uart_var *) modinit->var;
        // Multiple serial S/W objects for single UART H/W module possibly.
        // Bind serial S/W object to UART H/W module as interrupt is enabled.
        var->obj = obj;
        
        switch (irq) {
            // NOTE: Setting ier_msk first to avoid race condition
            case RxIrq:
                obj->ier_msk = obj->ier_msk | UART_IER_RDA_IEN_Msk;
                UART_ENABLE_INT(((UART_T *) NU_MODBASE(obj->uart)), UART_IER_RDA_IEN_Msk);
                break;
            case TxIrq:
                obj->ier_msk = obj->ier_msk | UART_IER_THRE_IEN_Msk;
                UART_ENABLE_INT(((UART_T *) NU_MODBASE(obj->uart)), UART_IER_THRE_IEN_Msk);
                break;
        }
    }
    else { // disable
        switch (irq) {
            case RxIrq:
                UART_DISABLE_INT(((UART_T *) NU_MODBASE(obj->uart)), UART_IER_RDA_IEN_Msk);
                obj->ier_msk = obj->ier_msk & ~UART_IER_RDA_IEN_Msk;
                break;
            case TxIrq:
                UART_DISABLE_INT(((UART_T *) NU_MODBASE(obj->uart)), UART_IER_THRE_IEN_Msk);
                obj->ier_msk = obj->ier_msk & ~UART_IER_THRE_IEN_Msk;
                break;
        }
    }
}

int serial_getc(serial_t *obj)
{
    while (! serial_readable(obj));
    int c = UART_READ(((UART_T *) NU_MODBASE(obj->uart)));
    return c;
}

void serial_putc(serial_t *obj, int c)
{
    while (! serial_writable(obj));
    UART_WRITE(((UART_T *) NU_MODBASE(obj->uart)), c);
}

int serial_readable(serial_t *obj)
{
    return ! UART_GET_RX_EMPTY(((UART_T *) NU_MODBASE(obj->uart)));
}

int serial_writable(serial_t *obj)
{
    return ! UART_IS_TX_FULL(((UART_T *) NU_MODBASE(obj->uart)));
}

void serial_pinout_tx(PinName tx)
{
    pinmap_pinout(tx, PinMap_UART_TX);
}

void serial_break_set(serial_t *obj)
{
}

void serial_break_clear(serial_t *obj)
{
}

void UART02_IRQHandler(void)
{
    uart_irq(uart2_var.obj);
    uart_irq(uart0_var.obj);
}

void UART1_IRQHandler(void)
{
    uart_irq(uart1_var.obj);
}

void UART3_IRQHandler(void)
{
    uart_irq(uart3_var.obj);
}

void UART4_IRQHandler(void)
{
    uart_irq(uart4_var.obj);
}

void UART5_IRQHandler(void)
{
    uart_irq(uart5_var.obj);
}

static void uart_irq(serial_t *obj)
{
    UART_T *uart_base = (UART_T *) NU_MODBASE(obj->uart);

    if (uart_base->ISR & UART_ISR_RDA_INT_Msk) {
        if (obj->irq_handler) {
            ((uart_irq_handler) obj->irq_handler)(obj->irq_id, RxIrq);
        }
    }
    
    if (uart_base->ISR & UART_ISR_THRE_INT_Msk) {
        if (obj->irq_handler) {
            ((uart_irq_handler) obj->irq_handler)(obj->irq_id, TxIrq);
        }
    }
    
    // NOTE: Ignore all other interrupt flags. Clear them. Otherwise, program will get stuck in interrupt.
    uart_base->ISR = uart_base->ISR;
    uart_base->FSR = uart_base->FSR;
}
#endif  // #if DEVICE_SERIAL
