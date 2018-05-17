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

#include "mbed_assert.h"
#include "pinmap.h"
#include "PortNames.h"
#include "mbed_error.h"

/**
 * Custom
 */

typedef struct _PinMask
{
    int MSK;
    int ALT_MSK;
    int ALT2_MSK;
    int ALT3_MSK;
    int ALT4_MSK;
} PinMask;

typedef struct _GPIOPinDescription
{
    PinName pin;
    PinMask msk;
} GPIOPinDescription;

typedef struct _PeripheralDescription
{
    int mod;
    PinMask msk;
} PeripheralDescription;
//*** PinMask ***

//*** PinMap Mask ***
const PeripheralDescription Peripheral_Desc[] = {
    /** ADC **/
    {PA0_ADC0, {SYS_GPA_MFP_PA0_ADC0, NULL, NULL, NULL, NULL}},
    {PA1_ADC1, {SYS_GPA_MFP_PA1_ADC1, NULL, NULL, NULL, NULL}},
    {PA2_ADC2, {SYS_GPA_MFP_PA2_ADC2, NULL, NULL, NULL, NULL}},
    {PA3_ADC3, {SYS_GPA_MFP_PA3_ADC3, NULL, NULL, NULL, NULL}},
    {PA4_ADC4, {SYS_GPA_MFP_PA4_ADC4, NULL, NULL, NULL, NULL}},
    {PA5_ADC5, {SYS_GPA_MFP_PA5_ADC5, NULL, NULL, NULL, NULL}},
    {PA6_ADC6, {SYS_GPA_MFP_PA6_ADC6, NULL, NULL, NULL, NULL}},
    /** I2C_SDA **/
    {PA1_I2C1_SDA, {SYS_GPA_MFP_PA1_I2C1_SDA, NULL, NULL, SYS_ALT_MFP3_PA1_I2C1_SDA, SYS_ALT_MFP4_PA1_I2C1_SDA}},
    {PA8_I2C0_SDA, {SYS_GPA_MFP_PA8_I2C0_SDA, NULL, NULL, NULL, SYS_ALT_MFP4_PA8_I2C0_SDA}},
    {PA10_I2C1_SDA, {SYS_GPA_MFP_PA10_I2C1_SDA, NULL, NULL, SYS_ALT_MFP3_PA10_I2C1_SDA, NULL}},
    {PC6_I2C0_SDA, {SYS_GPC_MFP_PC6_I2C0_SDA, NULL, NULL, SYS_ALT_MFP3_PC6_I2C0_SDA, SYS_ALT_MFP4_PC6_I2C0_SDA}},
    {PF4_I2C0_SDA, {SYS_GPF_MFP_PF4_I2C0_SDA, NULL, NULL, SYS_ALT_MFP3_PF4_I2C0_SDA, NULL}},
    /** I2C SCL **/
    {PA0_I2C1_SCL, {SYS_GPA_MFP_PA0_I2C1_SCL, NULL, NULL, SYS_ALT_MFP3_PA0_I2C1_SCL, NULL}},
    {PA9_I2C0_SCL, {SYS_GPA_MFP_PA9_I2C0_SCL, NULL, NULL, NULL, SYS_ALT_MFP4_PA9_I2C0_SCL}},
    {PA11_I2C1_SCL, {SYS_GPA_MFP_PA11_I2C1_SCL, NULL, NULL, SYS_ALT_MFP3_PA11_I2C1_SCL, NULL}},
    {PC7_I2C0_SCL, {SYS_GPC_MFP_PC7_I2C0_SCL, NULL, NULL, SYS_ALT_MFP3_PC7_I2C0_SCL, SYS_ALT_MFP4_PC7_I2C0_SCL}},
    {PF5_I2C0_SCL, {SYS_GPF_MFP_PF5_I2C0_SCL, NULL, NULL, SYS_ALT_MFP3_PF5_I2C0_SCL, NULL}},
    /** PWM **/
    {PA0_PWM0_CH4, {SYS_GPA_MFP_PA0_PWM0_CH4,  NULL, NULL, SYS_ALT_MFP3_PA0_PWM0_CH4,  SYS_ALT_MFP4_PA0_PWM0_CH4}},
    {PA1_PWM0_CH5, {SYS_GPA_MFP_PA1_PWM0_CH5,  NULL, NULL, SYS_ALT_MFP3_PA1_PWM0_CH5,  SYS_ALT_MFP4_PA1_PWM0_CH5}},
    {PA2_PWM1_CH0, {SYS_GPA_MFP_PA2_PWM1_CH0,  NULL, NULL, SYS_ALT_MFP3_PA2_PWM1_CH0,  SYS_ALT_MFP4_PA2_PWM1_CH0}},
    {PA3_PWM1_CH1, {SYS_GPA_MFP_PA3_PWM1_CH1,  NULL, NULL, SYS_ALT_MFP3_PA3_PWM1_CH1,  SYS_ALT_MFP4_PA3_PWM1_CH1}},
    {PA10_PWM1_CH2, {SYS_GPA_MFP_PA10_PWM1_CH2, NULL, NULL, SYS_ALT_MFP3_PA10_PWM1_CH2, NULL}},
    {PA11_PWM1_CH3, {SYS_GPA_MFP_PA11_PWM1_CH3, NULL, NULL, SYS_ALT_MFP3_PA11_PWM1_CH3, NULL}},
    {PA12_PWM0_CH0, {SYS_GPA_MFP_PA12_PWM0_CH0, NULL, NULL, NULL, SYS_ALT_MFP4_PA12_PWM0_CH0}},
    {PA13_PWM0_CH1, {SYS_GPA_MFP_PA13_PWM0_CH1, NULL, NULL, NULL, SYS_ALT_MFP4_PA13_PWM0_CH1}},
    {PA14_PWM0_CH2, {SYS_GPA_MFP_PA14_PWM0_CH2, NULL, NULL, NULL, NULL}},
    {PA15_PWM0_CH3, {SYS_GPA_MFP_PA15_PWM0_CH3, NULL, NULL, NULL, NULL}},
    {PB11_PWM0_CH4, {SYS_GPB_MFP_PB11_PWM0_CH4, NULL, NULL, SYS_ALT_MFP3_PB11_PWM0_CH4, NULL}},
    {PE5_PWM0_CH5, {SYS_GPE_MFP_PE5_PWM0_CH5, SYS_ALT_MFP_PE5_PWM0_CH5, SYS_ALT_MFP2_PE5_PWM0_CH5, NULL, NULL}},
    {PF4_PWM1_CH4, {SYS_GPF_MFP_PF4_PWM1_CH4,  NULL, NULL, SYS_ALT_MFP3_PF4_PWM1_CH4,  NULL}},
    {PF5_PWM1_CH5, {SYS_GPF_MFP_PF5_PWM1_CH5,  NULL, NULL, SYS_ALT_MFP3_PF5_PWM1_CH5,  NULL}},
    /** UART TX **/
    {PA0_UART5_TXD, {SYS_GPA_MFP_PA0_UART5_TXD, NULL, NULL, SYS_ALT_MFP3_PA0_UART5_TXD, SYS_ALT_MFP4_PA0_UART5_TXD}},
    {PA2_UART3_TXD, {SYS_GPA_MFP_PA2_UART3_TXD, NULL, NULL, SYS_ALT_MFP3_PA2_UART3_TXD, SYS_ALT_MFP4_PA2_UART3_TXD}},
    {PA6_UART3_TXD, {SYS_GPA_MFP_PA6_UART3_TXD, NULL, NULL, NULL, SYS_ALT_MFP4_PA6_UART3_TXD}},
    {PA13_UART5_TXD, {SYS_GPA_MFP_PA13_UART5_TXD, NULL, NULL, NULL, SYS_ALT_MFP4_PA13_UART5_TXD}},
    {PB1_UART0_TXD, {SYS_GPB_MFP_PB1_UART0_TXD, NULL, NULL, NULL, NULL}},
    {PB5_UART1_TXD, {SYS_GPB_MFP_PB5_UART1_TXD, NULL, NULL, NULL, NULL}},
    {PC6_UART4_TXD, {SYS_GPC_MFP_PC6_UART4_TXD, NULL, NULL, SYS_ALT_MFP3_PC6_UART4_TXD, SYS_ALT_MFP4_PC6_UART4_TXD}},
    {PD15_UART2_TXD, {SYS_GPD_MFP_PD15_UART2_TXD, NULL, NULL, SYS_ALT_MFP3_PD15_UART2_TXD, NULL}},
    /** UART_RX **/
    {PA1_UART5_RXD, {SYS_ALT_MFP3_PA1_UART5_RXD, NULL, NULL, SYS_ALT_MFP3_PA1_UART5_RXD, SYS_ALT_MFP4_PA1_UART5_RXD}},
    {PA3_UART3_RXD, {SYS_GPA_MFP_PA3_UART3_RXD, NULL, NULL, SYS_ALT_MFP3_PA3_UART3_RXD, SYS_ALT_MFP4_PA3_UART3_RXD}},
    {PA5_UART3_RXD, {SYS_GPA_MFP_PA5_UART3_RXD, NULL, NULL, NULL, SYS_ALT_MFP4_PA5_UART3_RXD}},
    {PA12_UART5_RXD, {SYS_GPA_MFP_PA12_UART5_RXD, NULL, NULL, NULL, SYS_ALT_MFP4_PA12_UART5_RXD}},
    {PB0_UART0_RXD, {SYS_GPB_MFP_PB0_UART0_RXD, NULL, NULL, NULL, NULL}},
    {PB4_UART1_RXD, {SYS_GPB_MFP_PB4_UART1_RXD, NULL, NULL, NULL, NULL}},
    {PC7_UART4_RXD, {SYS_GPC_MFP_PC7_UART4_RXD, NULL, NULL, SYS_ALT_MFP3_PC7_UART4_RXD, SYS_ALT_MFP4_PC7_UART4_RXD}},
    {PD14_UART2_RXD, {SYS_GPD_MFP_PD14_UART2_RXD, NULL, NULL, SYS_ALT_MFP3_PD14_UART2_RXD, NULL}},
    /** UART_RTS **/
    {PB2_UART0_nRTS, {SYS_GPB_MFP_PB2_UART0_nRTS, SYS_ALT_MFP_PB2_UART0_nRTS, SYS_ALT_MFP2_PB2_UART0_nRTS, SYS_ALT_MFP3_PB2_UART0_nRTS, NULL}},
    {PA8_UART1_nRTS, {SYS_GPA_MFP_PA8_UART1_nRTS, NULL, NULL, NULL, SYS_ALT_MFP4_PA8_UART1_nRTS}},
    {PB6_UART1_nRTS, {SYS_GPB_MFP_PB6_UART1_nRTS, NULL, NULL, NULL, NULL}},
    /** UART_CTS **/
    {PB3_UART0_nCTS, {SYS_GPB_MFP_PB3_UART0_nCTS, SYS_ALT_MFP_PB3_UART0_nCTS, SYS_ALT_MFP2_PB3_UART0_nCTS, SYS_ALT_MFP3_PB3_UART0_nCTS, NULL}},
    {PA9_UART1_nCTS, {SYS_GPA_MFP_PA9_UART1_nCTS, NULL, NULL, NULL, SYS_ALT_MFP4_PA9_UART1_nCTS}},
    {PB7_UART1_nCTS, {SYS_GPB_MFP_PB7_UART1_nCTS, NULL, NULL, NULL, NULL}},
    /** MOSI **/
    {PC3_SPI0_MOSI0, {SYS_GPC_MFP_PC3_SPI0_MOSI0, NULL, NULL, NULL, NULL}},
    /** MISO **/
    {PC2_SPI0_MISO0, {SYS_GPC_MFP_PC2_SPI0_MISO0, NULL, NULL, NULL, NULL}},
    /** SCLK **/
    {PC1_SPI0_CLK, {SYS_GPC_MFP_PC1_SPI0_CLK,   NULL, NULL, NULL, NULL}},
    /** SSEL **/
    {PC0_SPI0_SS0, {SYS_GPC_MFP_PC0_SPI0_SS0,   NULL, NULL, NULL, NULL}},
    {NC, {NULL, NULL, NULL, NULL, NULL}},
};

const GPIOPinDescription GPIO_Desc[] = {
    {NOT_A_PIN, {NULL, NULL, NULL, NULL, NULL}},                                                                  // 0
    {PB_12, {SYS_GPB_MFP_PB12_Msk, NULL, NULL, NULL, NULL}},                  // 1
    {PF_5, {SYS_GPF_MFP_PF5_Msk, NULL, NULL, SYS_ALT_MFP3_PF5_Msk, NULL}},     // 2
    {PF_4, {SYS_GPF_MFP_PF4_Msk, NULL, NULL, SYS_ALT_MFP3_PF4_Msk, NULL}},     // 3
    {PA_11, {SYS_GPA_MFP_PA11_Msk, NULL, NULL, SYS_ALT_MFP3_PA11_Msk, NULL}}, // 4
    {PA_10, {SYS_GPA_MFP_PA10_Msk, NULL, NULL, SYS_ALT_MFP3_PA10_Msk, NULL}}, // 5
    {PA_9, {SYS_GPA_MFP_PA9_Msk, NULL, NULL, NULL, NULL}},                     // 6
    {PA_8, {SYS_GPA_MFP_PA8_Msk, NULL, NULL, NULL, NULL}},                     // 7
    {PB_4, {SYS_GPB_MFP_PB4_Msk, NULL, NULL, NULL, NULL}},                     // 8
    {PB_5, {SYS_GPB_MFP_PB5_Msk, NULL, NULL, NULL, NULL}},                     // 9
    {NOT_A_PIN, {NULL, NULL, NULL, NULL, NULL}},                                                                  // 10
    {NOT_A_PIN, {NULL, NULL, NULL, NULL, NULL}},                                                                  // 11
    {NOT_A_PIN, {NULL, NULL, NULL, NULL, NULL}},                                                                  // 12
    {PB_0, {SYS_GPB_MFP_PB0_Msk, NULL, NULL, NULL, NULL}},                     // 13
    {PB_1, {SYS_GPB_MFP_PB1_Msk, NULL, NULL, NULL, NULL}},                     // 14
    {PB_2, {SYS_GPB_MFP_PB2_Msk, NULL, NULL, NULL, NULL}},                     // 15
    {PB_3, {SYS_GPB_MFP_PB3_Msk, NULL, NULL, NULL, NULL}},                     // 16
    {PD_6, {SYS_GPD_MFP_PD6_Msk, NULL, NULL, SYS_ALT_MFP3_PD6_Msk, NULL}},     // 17
    {PD_7, {SYS_GPD_MFP_PD7_Msk, NULL, NULL, SYS_ALT_MFP3_PD7_Msk, NULL}},     // 18
    {PD_14, {SYS_GPD_MFP_PD14_Msk, NULL, NULL, SYS_ALT_MFP3_PD14_Msk, NULL}}, // 19
    {PD_15, {SYS_GPD_MFP_PD15_Msk, NULL, NULL, SYS_ALT_MFP3_PD15_Msk, NULL}}, // 20
    {PC_3, {SYS_GPC_MFP_PC3_Msk, NULL, NULL, NULL, NULL}},                     // 21
    {PC_2, {SYS_GPC_MFP_PC2_Msk, NULL, NULL, NULL, NULL}},                     // 22
    {PC_1, {SYS_GPC_MFP_PC1_Msk, NULL, NULL, NULL, NULL}},                     // 23
    {PC_0, {SYS_GPC_MFP_PC0_Msk, NULL, NULL, NULL, NULL}},                     // 24
    {PA_15, {SYS_GPA_MFP_PA15_Msk, NULL, NULL, NULL, NULL}},                              // 25
    {PA_14, {SYS_GPA_MFP_PA14_Msk, NULL, NULL, NULL, NULL}},                              // 26
    {PA_13, {SYS_GPA_MFP_PA13_Msk, NULL, NULL, NULL, SYS_ALT_MFP4_PA13_Msk}},             // 27
    {PA_12, {SYS_GPA_MFP_PA12_Msk, NULL, NULL, NULL, SYS_ALT_MFP4_PA12_Msk}},             // 28
    {PF_7, {SYS_GPF_MFP_PF7_Msk, NULL, NULL, NULL, NULL}},                                 // 29
    {PF_6, {SYS_GPF_MFP_PF6_Msk, NULL, NULL, NULL, NULL}},                                 // 30
    {NOT_A_PIN, {NULL, NULL, NULL, NULL, NULL}},                                                                              // 31
    {PA_0, {SYS_GPA_MFP_PA0_Msk, NULL, NULL, SYS_ALT_MFP3_PA0_Msk, SYS_ALT_MFP4_PA0_Msk}}, // 32
    {PA_1, {SYS_GPA_MFP_PA1_Msk, NULL, NULL, SYS_ALT_MFP3_PA1_Msk, SYS_ALT_MFP4_PA1_Msk}}, // 33
    {PA_2, {SYS_GPA_MFP_PA2_Msk, NULL, NULL, SYS_ALT_MFP3_PA2_Msk, SYS_ALT_MFP4_PA2_Msk}}, // 34
    {PA_3, {SYS_GPA_MFP_PA3_Msk, NULL, NULL, SYS_ALT_MFP3_PA3_Msk, SYS_ALT_MFP4_PA3_Msk}}, // 35
    {PA_4, {SYS_GPA_MFP_PA4_Msk, NULL, NULL, NULL, NULL}},                                 // 36
    {PA_5, {SYS_GPA_MFP_PA5_Msk, NULL, NULL, NULL, SYS_ALT_MFP4_PA5_Msk}},                 // 37
    {PA_6, {SYS_GPA_MFP_PA6_Msk, NULL, NULL, NULL, SYS_ALT_MFP4_PA6_Msk}},                 // 38
    {PA_7, {SYS_GPA_MFP_PA7_Msk, NULL, NULL, NULL, NULL}},                                 // 39
    {NOT_A_PIN, {NULL, NULL, NULL, NULL, NULL}},                                                                              // 40
    {PC_7, {SYS_GPC_MFP_PC7_Msk, NULL, NULL, SYS_ALT_MFP3_PC7_Msk, SYS_ALT_MFP4_PC7_Msk}}, // 41
    {PC_6, {SYS_GPC_MFP_PC6_Msk, NULL, NULL, SYS_ALT_MFP3_PC6_Msk, SYS_ALT_MFP4_PC6_Msk}}, // 42
    {PB_15, {SYS_GPB_MFP_PB15_Msk, NULL, NULL, NULL, NULL}},                              // 43
    {PF_0, {SYS_GPF_MFP_PF0_Msk, NULL, NULL, NULL, NULL}},                                 // 44
    {PF_1, {SYS_GPF_MFP_PF1_Msk, NULL, NULL, NULL, NULL}},                                 // 45
    {NOT_A_PIN, {NULL, NULL, NULL, NULL, NULL}},                                                                              // 46
    {PF_8, {SYS_GPF_MFP_PF8_Msk, NULL, NULL, NULL, NULL}},                                 // 47
    {PB_8, {SYS_GPB_MFP_PB8_Msk, NULL, NULL, NULL, NULL}},                                 // 48
    {NC, {NULL, NULL, NULL, NULL, NULL}}
};

void pin_set_gpio_mask(PinName pin, const GPIOPinDescription* map) {
    
    MBED_ASSERT(pin != (PinName)NC);
    uint32_t port_index = NU_PINNAME_TO_PORT(pin);
    
    PinMask msk = {NULL, NULL, NULL, NULL, NULL};
    while (map->pin != NC) {
        if (map->pin == pin) {
            msk = map->msk;
            break;
        }
        map++;
    }

    if(msk.MSK == NULL) return;

    __IO uint32_t *GPx_MFP = ((__IO uint32_t *) &SYS->GPA_MFP) + port_index;
    
    *GPx_MFP  = (*GPx_MFP & ~(msk.MSK));
    outp32(&SYS->ALT_MFP, inp32(&SYS->ALT_MFP) & ~(msk.ALT_MSK));
    outp32(&SYS->ALT_MFP2, inp32(&SYS->ALT_MFP2) & ~(msk.ALT2_MSK));
    outp32(&SYS->ALT_MFP3, inp32(&SYS->ALT_MFP3) & ~(msk.ALT3_MSK));
    outp32(&SYS->ALT_MFP4, inp32(&SYS->ALT_MFP4) & ~(msk.ALT4_MSK));
}

void pin_set_peripheral_mask(PinName pin, int data, const PeripheralDescription* map) {

    MBED_ASSERT(pin != (PinName)NC);
    if(data == GPIO_CONFIG) return;

    uint32_t port_index = NU_PINNAME_TO_PORT(pin);
    PinMask msk = {NULL, NULL, NULL, NULL, NULL};
    while (map->mod != NC) {
        if (map->mod == data) {
            msk = map->msk;
            break;
        }
        map++;
    }
    if(msk.MSK == NULL) return;

    __IO uint32_t *GPx_MFP = ((__IO uint32_t *) &SYS->GPA_MFP) + port_index;
    
    *GPx_MFP  = (*GPx_MFP | (msk.MSK));
    if(msk.ALT_MSK != NULL) outp32(&SYS->ALT_MFP, inp32(&SYS->ALT_MFP) | (msk.ALT_MSK));
    if(msk.ALT2_MSK != NULL) outp32(&SYS->ALT_MFP2, inp32(&SYS->ALT_MFP2) | (msk.ALT2_MSK));
    if(msk.ALT3_MSK != NULL) outp32(&SYS->ALT_MFP3, inp32(&SYS->ALT_MFP3) | (msk.ALT3_MSK));
    if(msk.ALT4_MSK != NULL) outp32(&SYS->ALT_MFP4, inp32(&SYS->ALT_MFP4) | (msk.ALT4_MSK));
}

/**
 * Configure pin multi-function
 */
void pin_function(PinName pin, int data)
{
    // MBED_ASSERT(pin != (PinName)NC);
    // uint32_t pin_index = NU_PINNAME_TO_PIN(pin);
    // uint32_t port_index = NU_PINNAME_TO_PORT(pin);
    //__IO uint32_t *GPx_MFP = ((__IO uint32_t *) &SYS->GPA_MFP) + port_index * 2 + (pin_index / 8);
    //uint32_t MFP_Msk = NU_MFP_MSK(pin_index);
    
    // E.g.: SYS->GPA_MFP  = (SYS->GPA_MFP & (~SYS_GPA_MFP_PA0__Msk) ) | SYS_GPA_MFP_PA0_GPIO  ;
    //*GPx_MFP  = (*GPx_MFP & (~MFP_Msk)) | data;
    pin_set_gpio_mask(pin, GPIO_Desc);
    pin_set_peripheral_mask(pin, data, Peripheral_Desc);
}

/**
 * Configure pin pull-up/pull-down
 */
void pin_mode(PinName pin, PinMode mode)
{
    MBED_ASSERT(pin != (PinName)NC);
    uint32_t pin_index = NU_PINNAME_TO_PIN(pin);
    uint32_t port_index = NU_PINNAME_TO_PORT(pin);
    GPIO_T *gpio_base = NU_PORT_BASE(port_index);
    
    uint32_t mode_intern = GPIO_PMD_INPUT;
    
    switch (mode) {
        case PullUp:
            mode_intern = GPIO_PMD_INPUT;
            break;
            
        case PullDown:
        case PullNone:
            // NOTE: Not support
            return;
        
        case PushPull:
            mode_intern = GPIO_PMD_OUTPUT;
            break;
            
        case OpenDrain:
            mode_intern = GPIO_PMD_OPEN_DRAIN;
            break;
            
        case Quasi:
            mode_intern = GPIO_PMD_QUASI;
            break;
    }
    
    GPIO_SetMode(gpio_base, 1 << pin_index, mode_intern);
}
