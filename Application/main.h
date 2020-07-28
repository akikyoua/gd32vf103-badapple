/*!
    \file  main.h
    \brief the header file of main 
    
    \version 2019-6-5, V1.0.0, firmware for GD32VF103
*/

/*
    Copyright (c) 2019, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/

#ifndef __MAIN_H
#define __MAIN_H


#include "gd32vf103_libopt.h"
#include <stdio.h>

#define PA_OUT(n,s)                                         \
({  if (s%2)        gpio_bit_set(GPIOA, GPIO_PIN_##n);      \
    else            gpio_bit_reset(GPIOA, GPIO_PIN_##n);   })
#define PA_IN(n)    gpio_input_bit_get(GPIOA, GPIO_PIN_##n)

#define PB_OUT(n,s)                                         \
({  if (s%2)        gpio_bit_set(GPIOB, GPIO_PIN_##n);      \
    else            gpio_bit_reset(GPIOB, GPIO_PIN_##n);   })
#define PB_IN(n)    gpio_input_bit_get(GPIOB, GPIO_PIN_##n)

#define PC_OUT(n,s)                                         \
({  if (s%2)        gpio_bit_set(GPIOC, GPIO_PIN_##n);      \
    else            gpio_bit_reset(GPIOC, GPIO_PIN_##n);   })
#define PC_IN(n)    gpio_input_bit_get(GPIOC, GPIO_PIN_##n)

#define LEDR_TOG    gpio_bit_write(GPIOC, GPIO_PIN_13, (bit_status)(1-gpio_input_bit_get(GPIOC, GPIO_PIN_13)))
#define LEDR(s)     PC_OUT(13, s)
#define LEDG_TOG    gpio_bit_write(GPIOA, GPIO_PIN_1, (bit_status)(1-gpio_input_bit_get(GPIOA, GPIO_PIN_1)))
#define LEDG(s)     PA_OUT(1, s)
#define LEDB_TOG    gpio_bit_write(GPIOA, GPIO_PIN_2, (bit_status)(1-gpio_input_bit_get(GPIOA, GPIO_PIN_2)))
#define LEDB(s)     PA_OUT(2, s)

/* led spark function */
void led_spark(void);

#endif /* __MAIN_H */
