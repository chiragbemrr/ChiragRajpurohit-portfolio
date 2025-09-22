/*
 * main.h
 *
 *  Created on: Sep 7, 2025
 *      Author: Chiku
 */

#ifndef MAIN_H_
#define MAIN_H_
#include <stdint.h>
#include "I2C.h"
#include <stdint.h>

#define I2C1_EN 	(1U << 21) // enables i2c1
//#define AFEN
#define GPIOA_EN 	(1U << 0)
#define GPIOB_EN 	(1U << 1)
#define _PP ~(3U)
#define _PU ~(2U)
#define _PD (3U)

#define _INPUT (0x00U)
#define _OUTPUT (0x01U)
#define _AF (2U)


//
//#define _INPUT ~(1U)
//#define _OUTPUT (1U)
//#define _AF (3U)

#define PRE_AHB 	(0 << 4)  //AHB prescaler
#define PRE_APB1 	(5U<<10)  //APB1 precaler
#define PRE_APB2 	(4U << 13) //APB2 prescaler
#define MAIN_PRE 	(PRE_AHB | PRE_APB1 | PRE_APB2)

#define CLOCK_SWITCH 	(3U << 0)
#define PLL_AS_MAIN 	(2U << 0)
#define SWITCH_STATUS 	(3U << 2)

//RCC CR flags
#define PLLRDY 	(1U << 25) //set when main pll is ready
#define PLLON 	(1U << 24) //enables main pll
#define HSERDY 	(1U << 17) //sets when high speed clock is ready
#define HSEON 	(1U << 16) //enables external high speed clock

#define PLLM 	(8 << 0)
#define PLLN 	(336 << 6)
#define PLLP 	(0 << 16)
#define PLLSRC 	(1U<<22)
#define PLLQ 	(7 << 24)

#define PWR_CLK (1U <<28)

#define ICEN    (1U << 9)
#define DCEN 	(1U << 10)
#define PRFTEN 	(1U << 8)
#define LATENCY (5U << 0)

#define GPIO_PIN_0 (1U<<0)
#define GPIO_PIN_1 (1U<<1)
#define GPIO_PIN_2 (1U<<2)
#define GPIO_PIN_3 (1U<<3)
#define GPIO_PIN_4 (1U<<4)
#define GPIO_PIN_5 (1U<<5)
#define GPIO_PIN_6 (1U<<6)
#define GPIO_PIN_7 (1U<<7)
#define GPIO_PIN_8 (1U<<8)
#define GPIO_PIN_9 (1U<<9)
#define GPIO_PIN_10 (1U<<10)
#define GPIO_PIN_11 (1U<<11)
#define GPIO_PIN_12 (1U<<12)
#define GPIO_PIN_13 (1U<<13)
#define GPIO_PIN_14 (1U<<14)
#define GPIO_PIN_15 (1U<<15)

// Struct definition (no initializers here)
typedef struct RCC_ {
	volatile uint32_t CR;            // 0x00
	  volatile uint32_t PLLCFGR;       // 0x04
	  volatile uint32_t CFGR;          // 0x08
	  volatile uint32_t CIR;           // 0x0C
	  volatile uint32_t AHB1RSTR;      // 0x10
	  volatile uint32_t AHB2RSTR;      // 0x14
	  volatile uint32_t AHB3RSTR;      // 0x18
	  uint32_t RESERVED0;              // 0x1C
	  volatile uint32_t APB1RSTR;      // 0x20
	  volatile uint32_t APB2RSTR;      // 0x24
	  uint32_t RESERVED1[2];           // 0x28–0x2C
	  volatile uint32_t AHB1ENR;       // 0x30
	  volatile uint32_t AHB2ENR;       // 0x34
	  volatile uint32_t AHB3ENR;       // 0x38
	  uint32_t RESERVED2;              // 0x3C
	  volatile uint32_t APB1ENR;       // 0x40
	  volatile uint32_t APB2ENR;       // 0x44
	  uint32_t RESERVED3[2];           // 0x48–0x4C
	  volatile uint32_t AHB1LPENR;     // 0x50
	  volatile uint32_t AHB2LPENR;     // 0x54
	  volatile uint32_t AHB3LPENR;     // 0x58
	  uint32_t RESERVED4;              // 0x5C
	  volatile uint32_t APB1LPENR;     // 0x60
	  volatile uint32_t APB2LPENR;     // 0x64
	  uint32_t RESERVED5[2];           // 0x68–0x6C
	  volatile uint32_t BDCR;          // 0x70
	  volatile uint32_t CSR;           // 0x74
	  uint32_t RESERVED6[2];           // 0x78–0x7C
	  volatile uint32_t SSCGR;         // 0x80
	  volatile uint32_t PLLI2SCFGR;    // 0x84
}Rcc_typedef;


struct FLASH_{
	 volatile uint32_t* ACR;
//	 volatile uint32_t* KEYR;
//	 volatile uint32_t* OPTKEYR;
//	 volatile uint32_t* SR;
//	 volatile uint32_t* CR;
//	 volatile uint32_t* OPTCR;
};


struct PWR_{
	 volatile uint32_t* CR;
	 volatile uint32_t* CSR;
};

struct SYSCFG_ {
	volatile uint32_t* MEMRM;
	volatile uint32_t* PMC;
	volatile uint32_t* EXTICR1;
    volatile uint32_t* EXTICR2;
    volatile uint32_t* EXTICR3;
    volatile uint32_t* EXTICR4;
    volatile uint32_t* CMPCR;
};

typedef struct {
    volatile uint32_t MODER;    // GPIO Port Mode Register
    volatile uint32_t OTYPER;   // GPIO Port Output Type Register
    volatile uint32_t OSPEEDR;  // GPIO Port Output Speed Register
    volatile uint32_t PUPDR;    // GPIO Port Pull-up/Pull-down Register
    volatile uint32_t IDR;      // GPIO Port Input Data Register
    volatile uint32_t ODR;      // GPIO Port Output Data Register
    volatile uint32_t BSRR;     // GPIO Port Bit Set/Reset Register
    volatile uint32_t LCKR;     // GPIO Port Configuration Lock Register
    volatile uint32_t AFR[2];   // GPIO Alternate Function Registers (AFR[0] and AFR[1])
} GPIO_TypeDef;

#define GPIOA_BASE_ADDR 0x40020000UL // Example base address for GPIOA
#define GPIOA ((GPIO_TypeDef *) GPIOA_BASE_ADDR)

#define GPIOB_BASE_ADDR 0x40020400UL // Example base address for GPIOA
#define GPIOB ((GPIO_TypeDef *) GPIOB_BASE_ADDR)

#define RCC_BASE_ADDR 0x40023800UL // Example base address for GPIOA
#define RCC ((Rcc_typedef*) RCC_BASE_ADDR)

enum _mode {
	INPUT_NOPULL,
	OUTPUT_NOPULL,
	AF_PP,
	OUTPUT_PU,
	INPUT_PU
};
#define LED_PIN GPIO_PIN_9
#define LED_PORT GPIOA

#define I2C1_SDA GPIO_PIN_7
#define I2C1_SCL GPIO_PIN_6
#define I2C1_PORT GPIOB
//struct NVIC{
//
//};

#endif /* MAIN_H_ */
