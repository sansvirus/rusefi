/**
 * @file	mpu_util.h
 *
 * @date Jul 27, 2014
 * @author Andrey Belomutskiy, (c) 2012-2020
 * @author andreika <prometheus.pcb@gmail.com>
 */

#pragma once

// This is the radical departure from STM32
#define PORT_SIZE 18

// todo: stm32 ticks are based on 4MHz timer I wonder if these STM32_SYSCLK-based clocks are broken here?!
#define US_TO_NT_MULTIPLIER (STM32_SYSCLK / 1000000)

// Scheduler queue GPT device
#define GPTDEVICE GPTD1

typedef enum {
	BOR_Level_None = 0,
	BOR_Level_1 = 1,
	BOR_Level_2 = 2,
	BOR_Level_3 = 3
} BOR_Level_t;

#ifndef ADC_CR2_SWSTART
#define ADC_CR2_SWSTART ((uint32_t)0x40000000)
#endif

#define SPI_CR1_8BIT_MODE 0
#define SPI_CR2_8BIT_MODE 0

#define SPI_CR1_16BIT_MODE SPI_CR1_DFF
#define SPI_CR2_16BIT_MODE 0

// TODO
#define SPI_CR1_24BIT_MODE 0
#define SPI_CR2_24BIT_MODE 0

#define ADC_MAX_VALUE 4095
