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
#ifndef MBED_PINNAMES_H
#define MBED_PINNAMES_H

#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NU_PININDEX_Pos                             0
#define NU_PININDEX_Msk                             (0xFFul << NU_PININDEX_Pos)
#define NU_PINPORT_Pos                              8
#define NU_PINPORT_Msk                              (0xFul << NU_PINPORT_Pos)
#define NU_PIN_MODINDEX_Pos                         12
#define NU_PIN_MODINDEX_Msk                         (0xFul << NU_PIN_MODINDEX_Pos)
#define NU_PIN_BIND_Pos                             16
#define NU_PIN_BIND_Msk                             (0x1ul << NU_PIN_BIND_Pos)

#define NU_PININDEX(PINNAME)                        (((unsigned int)(PINNAME) & NU_PININDEX_Msk) >> NU_PININDEX_Pos)
#define NU_PINPORT(PINNAME)                         (((unsigned int)(PINNAME) & NU_PINPORT_Msk) >> NU_PINPORT_Pos)
#define NU_PIN_BIND(PINNAME)                        (((unsigned int)(PINNAME) & NU_PIN_BIND_Msk) >> NU_PIN_BIND_Pos)
#define NU_PIN_MODINDEX(PINNAME)                    (((unsigned int)(PINNAME) & NU_PIN_MODINDEX_Msk) >> NU_PIN_MODINDEX_Pos)
#define NU_PINNAME(PORT, PIN)                       ((((unsigned int) (PORT)) << (NU_PINPORT_Pos)) | (((unsigned int) (PIN)) << NU_PININDEX_Pos))
#define NU_PINNAME_BIND(PINNAME, modname)           NU_PINNAME_BIND_(NU_PINPORT(PINNAME), NU_PININDEX(PINNAME), modname)
#define NU_PINNAME_BIND_(PORT, PIN, modname)        ((((unsigned int)(PORT)) << NU_PINPORT_Pos) | (((unsigned int)(PIN)) << NU_PININDEX_Pos) | (NU_MODINDEX(modname) << NU_PIN_MODINDEX_Pos) | NU_PIN_BIND_Msk)

#define NU_PORT_BASE(port)                          ((GPIO_T *)(((uint32_t) PA_BASE) + 0x40 * port))
#define NU_MFP_POS(pin)                             ((pin % 8) * 4)
#define NU_MFP_MSK(pin)                             (0xful << NU_MFP_POS(pin))

// LEGACY
#define NU_PINNAME_TO_PIN(PINNAME)                  NU_PININDEX(PINNAME)
#define NU_PINNAME_TO_PORT(PINNAME)                 NU_PINPORT(PINNAME)
#define NU_PINNAME_TO_MODSUBINDEX(PINNAME)          NU_PIN_MODINDEX(PINNAME)
#define NU_PORT_N_PIN_TO_PINNAME(PORT, PIN)         NU_PINNAME((PORT), (PIN))

typedef enum {
    PIN_INPUT,
    PIN_OUTPUT
} PinDirection;

typedef enum {
    PullNone = 0,
    PullDown,
    PullUp,
    
    PushPull,
    OpenDrain,
    Quasi,
    
    PullDefault = PullUp,
} PinMode;

typedef enum {
    // Not connected
    NC = (int)0xFFFFFFFF,
    
    // Generic naming
    PA_0    = NU_PORT_N_PIN_TO_PINNAME(0, 0), PA_1, PA_2, PA_3, PA_4, PA_5, PA_6, PA_7, PA_8, PA_9, PA_10, PA_11, PA_12, PA_13, PA_14, PA_15,
    PB_0    = NU_PORT_N_PIN_TO_PINNAME(1, 0), PB_1, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7, PB_8, PB_9, PB_10, PB_11, PB_12, PB_13, PB_14, PB_15,
    PC_0    = NU_PORT_N_PIN_TO_PINNAME(2, 0), PC_1, PC_2, PC_3, PC_4, PC_5, PC_6, PC_7, PC_8, PC_9, PC_10, PC_11, PC_12, PC_13, PC_14, PC_15,
    PD_0    = NU_PORT_N_PIN_TO_PINNAME(3, 0), PD_1, PD_2, PD_3, PD_4, PD_5, PD_6, PD_7, PD_8, PD_9, PD_10, PD_11, PD_12, PD_13, PD_14, PD_15,
    PE_0    = NU_PORT_N_PIN_TO_PINNAME(4, 0), PE_1, PE_2, PE_3, PE_4, PE_5, PE_6, PE_7, PE_8, PE_9, PE_10, PE_11, PE_12, PE_13, PE_14, PE_15,
    PF_0    = NU_PORT_N_PIN_TO_PINNAME(5, 0), PF_1, PF_2, PF_3, PF_4, PF_5, PF_6, PF_7, PF_8,
    NOT_A_PIN,
    
    // Arduino UNO naming
    A0 = PA_0,
    A1 = PA_1,
    A2 = PA_2,
    A3 = PA_3,
    A4 = PA_5,
    A5 = PA_6,

    D0 = PB_0,
    D1 = PB_1,
    D2 = PF_5,
    D3 = PF_4,
    D4 = PA_11,
    D5 = PA_10,
    D6 = PD_6,
    D7 = PD_7,
    D8 = PD_14,
    D9 = PD_15,
    D10 = PA_12,
    D11 = PA_13,
    D12 = PA_15,
    D13 = PA_14,
    D14 = PC_6,
    D15 = PC_7,

    I2C_SCL = D15,
    I2C_SDA = D14,
        
    // NOTE: other board-specific naming
    // UART naming
    USBTX = PB_1,
    USBRX = PB_0,
    STDIO_UART_TX   = USBTX,
    STDIO_UART_RX   = USBRX,
    SERIAL_TX = USBTX,
    SERIAL_RX = USBRX,    
    // LED naming
    LED1 = D13,
    LED2 = D0,
    LED3 = D1,
    LED4 = LED1,
    LED_RED = LED3,
    LED_GREEN = LED1,
    LED_YELLOW = LED2,
    
} PinName;

typedef enum {
    /*** ADC ***/
    PA0_ADC0 = 0, PA1_ADC1, PA2_ADC2, PA3_ADC3, PA4_ADC4, PA5_ADC5, PA6_ADC6,
    /*** I2C SDA ***/
    PA1_I2C1_SDA, PA8_I2C0_SDA, PA10_I2C1_SDA, PC6_I2C0_SDA, PF4_I2C0_SDA,
    /*** I2C SCL ***/
    PA0_I2C1_SCL, PA9_I2C0_SCL, PA11_I2C1_SCL, PC7_I2C0_SCL, PF5_I2C0_SCL,
    /*** PWM ***/
    PA0_PWM0_CH4, PA1_PWM0_CH5, PA2_PWM1_CH0, PA3_PWM1_CH1, PA10_PWM1_CH2,
    PA11_PWM1_CH3, PA12_PWM0_CH0, PA13_PWM0_CH1, PA14_PWM0_CH2, PA15_PWM0_CH3,
    PB11_PWM0_CH4, PE5_PWM0_CH5, PF4_PWM1_CH4, PF5_PWM1_CH5,
    /*** UART TX ***/
    PA0_UART5_TXD, PA2_UART3_TXD, PA6_UART3_TXD, PA13_UART5_TXD, PB1_UART0_TXD,
    PB5_UART1_TXD, PC6_UART4_TXD, PD15_UART2_TXD,
    /*** UART RX ***/
    PA1_UART5_RXD, PA3_UART3_RXD, PA5_UART3_RXD, PA12_UART5_RXD, PB0_UART0_RXD,
    PB4_UART1_RXD, PC7_UART4_RXD, PD14_UART2_RXD,
    /*** UART RTS ***/
    PB2_UART0_nRTS, PA8_UART1_nRTS, PB6_UART1_nRTS,
    /*** UART CTS ***/
    PB3_UART0_nCTS, PA9_UART1_nCTS, PB7_UART1_nCTS,
    /*** SPI MOSI ***/
    PC3_SPI0_MOSI0,
    /*** SPI MISO ***/
    PC2_SPI0_MISO0,
    /*** SPI SCLK ***/
    PC1_SPI0_CLK,
    /*** SPI SS ***/
    PC0_SPI0_SS0,
    /** General GPIO config **/
    GPIO_CONFIG,

} PeripheralIdx;

#ifdef __cplusplus
}
#endif

#endif // MBED_PINNAMES_H
