/*!
    \file  main.c
    \brief running led
    
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

#include "gd32vf103.h"
#include "main.h"
#include "systick.h"
#include "lcd/lcd.h"
#include "fatfs/tf_card.h"
#include <string.h>
#include <stdio.h>

unsigned char image[1600];
unsigned char wav1[900];
unsigned char wav2[900];
unsigned char wav12 = 1;
FATFS fs;

unsigned int wavCount = 0;
unsigned char flag = 0;

void init_uart0(void)
{
	/* enable GPIO clock */
    rcu_periph_clock_enable(RCU_GPIOA);
    /* enable USART clock */
    rcu_periph_clock_enable(RCU_USART0);

    /* connect port to USARTx_Tx */
    gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
    /* connect port to USARTx_Rx */
    gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_10);

	/* USART configure */
    usart_deinit(USART0);
    usart_baudrate_set(USART0, 115200U);
    usart_word_length_set(USART0, USART_WL_8BIT);
    usart_stop_bit_set(USART0, USART_STB_1BIT);
    usart_parity_config(USART0, USART_PM_NONE);
    usart_hardware_flow_rts_config(USART0, USART_RTS_DISABLE);
    usart_hardware_flow_cts_config(USART0, USART_CTS_DISABLE);
    usart_receive_config(USART0, USART_RECEIVE_ENABLE);
    usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
    usart_enable(USART0);

    usart_interrupt_enable(USART0, USART_INT_RBNE);
}


void timer1_Init(void)
{
	eclic_global_interrupt_enable();//使能全局中断
	eclic_set_nlbits(ECLIC_GROUP_LEVEL3_PRIO1);//分组
	eclic_irq_enable(TIMER1_IRQn, 1 ,0);//使能TIMER1中断请求,设置优先级

	rcu_periph_clock_enable(RCU_TIMER1);//使能TIMER1时钟
	timer_deinit(TIMER1);//重置TIMER1
	timer_parameter_struct timer1;//定义结构体
	timer1.prescaler = 44;//预装载值
	timer1.alignedmode = TIMER_COUNTER_EDGE;//边沿对齐模式
	timer1.counterdirection = TIMER_COUNTER_UP;//向上计数
	timer1.period = 99;//周期
	timer1.clockdivision = TIMER_CKDIV_DIV1;//时钟分频
	timer1.repetitioncounter = 0;//重复值，一般赋值为0
	timer_init(TIMER1, &timer1);//初始化TIMER01
	timer_interrupt_enable(TIMER1, TIMER_INT_UP);//启用TIMER1中断
	timer_enable(TIMER1);//使能TIMER1
}

void DAC0_Init(void)
{
	rcu_periph_clock_enable(RCU_GPIOA);
	rcu_periph_clock_enable(RCU_DAC);

	/* once enabled the DAC, the corresponding GPIO pin
	is connected to the DAC converter automatically */
	gpio_init(GPIOA, GPIO_MODE_AIN, GPIO_OSPEED_50MHZ, GPIO_PIN_4);
	dac_deinit();

	dac_trigger_disable(DAC0);
	dac_wave_mode_config(DAC0, DAC_WAVE_DISABLE);
	dac_output_buffer_enable(DAC0);

	dac_enable(DAC0);
	//dac_data_set(DAC0, DAC_ALIGN_12B_L, DAC0_OUT_VAL);
	DAC0_R8DH = 0x80;
}



int main(void)
{
    uint8_t mount_is_ok = 1; /* 0: mount successful ; 1: mount failed */
    FIL fil;
    FRESULT fr;     /* FatFs return code */
    UINT br;

    SystemInit();			//初始化时钟为108M
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOC);
    gpio_init(GPIOC, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_13);
    gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_1|GPIO_PIN_2);

    init_uart0();
    timer1_Init();			//定时器用于dac输出，采样率是24000，定时时间108000000/24000
    DAC0_Init();

    Lcd_Init();			// init OLED
    LCD_Clear(WHITE);
    BACK_COLOR=WHITE;

    LEDR(1);
    LEDG(1);
    LEDB(1);

    fr = f_mount(&fs, "", 1);
    if (fr == 0)
        mount_is_ok = 0;
    else
        mount_is_ok = 1;

    if (mount_is_ok == 0)
    {
        while(1)
        {
            fr = f_open(&fil, "badapple.bin", FA_READ);			//文件时图片和音频交叉拼接出来的
            if (fr) printf("open error: %d!\n\r", (int)fr);

            f_read(&fil, image, sizeof(image), &br);	//读图 1600字节
			if(wav12 == 1)								//读音频 800字节
			{
				f_read(&fil, wav2, 800, &br);
				wav12 = 2;
			}
			else
			{
				f_read(&fil, wav1, 800, &br);
				wav12 = 1;
			}
            wavCount = 0;
            for (int i=0; i<6566;i++)
            {
            	LCD_ShowBmp(image);
                while(flag == 0){LEDB_TOG;}
                flag = 0;
                f_read(&fil, image, sizeof(image), &br);	//读图
				if(wav12 == 1)								//读音频
				{
					f_read(&fil, wav2, 800, &br);
					wav12 = 2;
				}
				else
				{
					f_read(&fil, wav1, 800, &br);
					wav12 = 1;
				}
            }
            /* Close the file*/
            f_close(&fil);
        }
    }
    else
    {
        LCD_ShowString(24,  0, (u8 *)("no card found!"), BLACK);
        LCD_ShowString(24, 16, (u8 *)("no card found!"), BLUE);
        LCD_ShowString(24, 32, (u8 *)("no card found!"), BRED);
        LCD_ShowString(24, 48, (u8 *)("no card found!"), GBLUE);
        LCD_ShowString(24, 64, (u8 *)("no card found!"), RED);
        while (1)
        {
            LEDR_TOG;
            delay_1ms(200);
            LEDG_TOG;
            delay_1ms(200);
            LEDB_TOG;
            delay_1ms(200);
        }
    }
}
//定时器1中断入口函数
void TIMER1_IRQHandler(void)
{
    if(SET == timer_interrupt_flag_get(TIMER1, TIMER_INT_FLAG_UP))//判断是否产生中断
    {
    	timer_interrupt_flag_clear(TIMER1, TIMER_INT_FLAG_UP);//清除中断标志位
        wavCount++;
        if(wavCount > 799 )
        {
			flag = 1;
			wavCount = 0;
		}
        if(wav12 == 1)
        	DAC0_R8DH = wav1[wavCount];
        else
        	DAC0_R8DH = wav2[wavCount];
    }
}


int _put_char(int ch)
{
    usart_data_transmit(USART0, (uint8_t) ch );
    while ( usart_flag_get(USART0, USART_FLAG_TBE)== RESET){
    }
    return ch;
}
