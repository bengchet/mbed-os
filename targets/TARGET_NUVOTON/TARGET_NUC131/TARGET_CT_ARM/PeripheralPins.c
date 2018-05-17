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

#include "PeripheralPins.h"

//*** ADC ***

const PinMap PinMap_ADC[] = {
    {PA_0, ADC_0_0, PA0_ADC0},
    {PA_1, ADC_0_1, PA1_ADC1},
    {PA_2, ADC_0_2, PA2_ADC2},
    {PA_3, ADC_0_3, PA3_ADC3},
    {PA_4, ADC_0_4, PA4_ADC4},
    {PA_5, ADC_0_5, PA5_ADC5},
    {PA_6, ADC_0_6, PA6_ADC6},

    {NC, NC, 0}
};

//*** I2C ***

const PinMap PinMap_I2C_SDA[] = {
    {PA_1, I2C_1, PA1_I2C1_SDA},
    {PA_8, I2C_0, PA8_I2C0_SDA},
    {PA_10, I2C_1, PA10_I2C1_SDA},
    {PC_6, I2C_0, PC6_I2C0_SDA},
    {PF_4, I2C_0, PF4_I2C0_SDA},

    {NC, NC, 0}
};

const PinMap PinMap_I2C_SCL[] = {
    {PA_0, I2C_1, PA0_I2C1_SCL},
    {PA_9, I2C_0, PA9_I2C0_SCL},
    {PA_11, I2C_1, PA11_I2C1_SCL},
    {PC_7, I2C_0, PC7_I2C0_SCL},
    {PF_5, I2C_0, PF5_I2C0_SCL},

    {NC, NC, 0}
};

//*** PWM ***

const PinMap PinMap_PWM[] = {
    {PA_0, PWM_0_4, PA0_PWM0_CH4},
    {PA_1, PWM_0_5, PA1_PWM0_CH5},
    {PA_2, PWM_1_0, PA2_PWM1_CH0},
    {PA_3, PWM_1_1, PA3_PWM1_CH1},
    {PA_10, PWM_1_2, PA10_PWM1_CH2},
    {PA_11, PWM_1_3, PA11_PWM1_CH3},
    {PA_12, PWM_0_0, PA12_PWM0_CH0},
    {PA_13, PWM_0_1, PA13_PWM0_CH1},
    {PA_14, PWM_0_2, PA14_PWM0_CH2},
    {PA_15, PWM_0_3, PA15_PWM0_CH3},
    {PB_11, PWM_0_4, PB11_PWM0_CH4},
    {PE_5, PWM_0_5, PE5_PWM0_CH5},
    {PF_4, PWM_1_4, PF4_PWM1_CH4},
    {PF_5, PWM_1_5, PF5_PWM1_CH5},

    {NC, NC, 0}
};

//*** SERIAL ***

const PinMap PinMap_UART_TX[] = {
    {PA_0, UART_5, PA0_UART5_TXD},
    {PA_2, UART_3, PA2_UART3_TXD},
    {PA_6, UART_3, PA6_UART3_TXD},
    {PA_13, UART_5, PA13_UART5_TXD},
    {PB_1, UART_0, PB1_UART0_TXD},
    {PB_5, UART_1, PB5_UART1_TXD},
    {PC_6, UART_4, PC6_UART4_TXD},
    {PD_15, UART_2, PD15_UART2_TXD},

    {NC, NC, 0}
};

const PinMap PinMap_UART_RX[] = {
    {PA_1, UART_5, PA1_UART5_RXD},
    {PA_3, UART_3, PA3_UART3_RXD},
    {PA_5, UART_3, PA5_UART3_RXD},
    {PA_12, UART_5, PA12_UART5_RXD},
    {PB_0, UART_0, PB0_UART0_RXD},
    {PB_4, UART_1, PB4_UART1_RXD},
    {PC_7, UART_4, PC7_UART4_RXD},
    {PD_14, UART_2, PD14_UART2_RXD},

    {NC, NC, 0}
};


#ifdef DEVICE_SERIAL_FC
const PinMap PinMap_UART_RTS[] = {
    {PB_2, UART_0, PB2_UART0_nRTS},
    {PA_8, UART_1, PA8_UART1_nRTS},
    {PB_6, UART_1, PB6_UART1_nRTS},

    {NC, NC, 0}};

const PinMap PinMap_UART_CTS[] = {
    {PB_3, UART_0, PB3_UART0_nCTS},
    {PA_9, UART_1, PA9_UART1_nCTS},
    {PB_7, UART_1, PB7_UART1_nCTS},

    {NC, NC, 0}};
#endif

//*** SPI ***

const PinMap PinMap_SPI_MOSI[] = {
    {PC_3, SPI_0, PC3_SPI0_MOSI0},

    {NC, NC, 0}
};

const PinMap PinMap_SPI_MISO[] = {
    {PC_2, SPI_0, PC2_SPI0_MISO0},

    {NC, NC, 0}
};

const PinMap PinMap_SPI_SCLK[] = {
    {PC_1, SPI_0, PC1_SPI0_CLK},

    {NC, NC, 0}
};

const PinMap PinMap_SPI_SSEL[] = {
    {PC_0, SPI_0, PC0_SPI0_SS0},

    {NC, NC, 0}
};

