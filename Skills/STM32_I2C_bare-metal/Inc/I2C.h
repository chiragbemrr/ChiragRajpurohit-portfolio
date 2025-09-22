/*
 * I2C.h
 *
 *  Created on: Sep 9, 2025
 *      Author: Chiku
 */

#ifndef I2C_H_
#define I2C_H_


#include "main.h"

#define I2C_CR1_OFFSET 		(0x40005400UL)
#define I2C_CR2_OFFSET 		(0x40005404UL)
#define I2C_OAR1_OFFSET		(0x40005408UL)
#define I2C_OAR2_OFFSET		(0x4000540CUL)
#define I2C_DR_OFFSET		(0x40005410UL)
#define I2C_SR1_OFFSET		(0x40005414UL)
#define I2C_SR2_OFFSET		(0x40005418UL)
#define I2C_CCR_OFFSET		(0x4000541CUL)
#define I2C_TRISE_OFFSET	(0x40005420UL)

typedef struct {
    volatile uint32_t CR1;    // GPIO Port Mode Register
    volatile uint32_t CR2;   // GPIO Port Output Type Register
    volatile uint32_t OAR1;  // GPIO Port Output Speed Register
    volatile uint32_t OAR2;    // GPIO Port Pull-up/Pull-down Register
    volatile uint32_t DR;      // GPIO Port Input Data Register
    volatile uint32_t SR1;      // GPIO Port Output Data Register
    volatile uint32_t SR2;     // GPIO Port Bit Set/Reset Register
    volatile uint32_t CCR;     // GPIO Port Configuration Lock Register
    volatile uint32_t TRISE;   // GPIO Alternate Function Registers (AFR[0] and AFR[1])
} I2C_TypeDef;



//PB7 - I2C1_SDA
//PB6 - I2C1_SCL

#define PE_EN (1U << 0)
#define START_EN (1U << 8)
#define STOP_EN (1U << 9)
#define SWRST (1u << 15)

typedef enum i2c_mode{
	I2C_MASTER,
	I2C_SLAVE
}i2c_mode;

typedef enum i2c_err{
	I2C_OK,
	I2C_ADDRESS_NOT_MATCHED,
	I2C_ACK_FAILURE,
	I2C_NO_ACTIVE_DEVICE
}i2c_err_t;

struct i2ctypedef {
	I2C_TypeDef* intance;
	i2c_mode mode;
	uint16_t frequency; //frequency in mhz(2-60)

};

uint8_t I2C_RxE(I2C_TypeDef* i2c);
uint8_t I2C_TxE(I2C_TypeDef* i2c);
i2c_err_t M_I2C_WRITE(uint8_t *data,I2C_TypeDef* i2c,uint8_t address);
void M_I2C_READ(uint8_t *data,I2C_TypeDef* i2c,uint8_t address);
i2c_err_t M_get_addr(I2C_TypeDef* i2c,uint8_t* addr);
void I2C1_Slave_Init(uint8_t own_address,I2C_TypeDef* I2C1);
void I2C1_INIT(struct i2ctypedef *I2C_config);
void I2C1_Slave_Loop(I2C_TypeDef* I2cxx);



#endif /* I2C_H_ */
