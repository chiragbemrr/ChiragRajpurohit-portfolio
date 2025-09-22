/*
 * I2C1.c
 *
 *  Created on: Sep 7, 2025
 *      Author: Chiku
 */
#include "I2C.h"
#include "main.h"
uint16_t calculate_ccr(uint16_t freq_mhz, uint32_t speed_hz);
uint8_t I2C_TxE(I2C_TypeDef* i2c){
	return (i2c->SR1 & (1U<<7));
}
uint8_t I2C_RxE(I2C_TypeDef* i2c){
	return (i2c->SR1 & (1U<<6));
}

//i2c_err_t M_I2C_WRITE(uint8_t *data,I2C_TypeDef* i2c,uint8_t address){
//
//	i2c->CR1 |= START_EN |(1U << 10); //start generation
//	while(!(i2c->SR1 & (1U<<0)));//wait for SB bit set
//	i2c->DR = (address << 1) | 0; //send the address
//	if(!(i2c->SR1 & (1U << 1))){
//		return I2C_ADDRESS_NOT_MATCHED;
//	}else if(i2c->SR1 & (1U << 10)){
//		i2c->SR1 &= ~(1U << 10); //clear the ack failure bit
//		i2c->CR1  |= STOP_EN ; //stop generation
//		return I2C_ACK_FAILURE;
//	}
//	i2c->SR1 &= ~(1U << 1); //clear the address bit
//	while(!I2C_TxE(i2c)); //wait while data reg is not empty
//	while(*(data)){//send the data
//		i2c->DR = *(data++);
//	}
//	i2c->CR1 |= STOP_EN ; //stop generation
//	return I2C_OK;
//}
i2c_err_t M_I2C_WRITE(uint8_t *data, I2C_TypeDef* i2c, uint8_t address) {
    // Start
    i2c->CR1 |= START_EN;
    while (!(i2c->SR1 & (1U << 0))); // wait SB=1

    // Send address (write mode)
    i2c->DR = (address << 1);

    // After writing address
    while (!(i2c->SR1 & (1U << 1))) {
        if (i2c->SR1 & (1U << 10)) {
            // AF set -> NACK received
            i2c->SR1 &= ~(1U << 10);  // clear AF
            i2c->CR1 |= STOP_EN;
            return I2C_ACK_FAILURE;
        }
    }

    // Wait for ADDR=1
    while (!(i2c->SR1 & (1U << 1)));

    // Clear ADDR by reading SR1 and SR2
    (void)i2c->SR1;
    (void)i2c->SR2;

    // Send data
    while (*data) {
        while (!(i2c->SR1 & (1U << 7))); // wait TXE
        i2c->DR = *data++;
    }

    // Wait BTF before STOP
    while (!(i2c->SR1 & (1U << 2))); // BTF

    // Generate STOP
    i2c->CR1 |= STOP_EN;

    return I2C_OK;
}
void M_I2C_READ(uint8_t *data,I2C_TypeDef* i2c,uint8_t address){
	i2c->CR1 |= START_EN ; //start generation
	while(!(i2c->SR1 & (1U<<0)));//wait for SB bit set
	i2c->DR = address; //send the address
	i2c->SR1 &= ~(1U << 1); //clear the address bit
	while(!I2C_RxE(i2c)); //wait while data reg is not empty
	*(data) = i2c->DR ;
	i2c->CR1 |= STOP_EN ; //start generation
}

void S_I2C_WRITE(uint8_t *data,I2C_TypeDef* i2c,uint8_t address){
	i2c->CR1 |= START_EN ; //start generation
	while(!(i2c->SR1 & (1U<<0)));//wait for SB bit set
	i2c->DR = address; //send the address
	i2c->SR1 &= ~(1U << 1); //clear the address bit
	while(!I2C_TxE(i2c)); //wait while data reg is not empty
	while(*(data)){//send the data
		i2c->DR = *(data++);
	}
	i2c->CR1 |= STOP_EN ; //start generation
}
void S_I2C_READ(uint8_t *data,I2C_TypeDef* i2c,uint8_t address){
	i2c->CR1 |= START_EN ; //start generation
	while(!(i2c->SR1 & (1U<<0)));//wait for SB bit set
	i2c->DR = address; //send the address
	i2c->SR1 &= ~(1U << 1); //clear the address bit
	while(!I2C_RxE(i2c)); //wait while data reg is not empty
	*(data) = i2c->DR ;
	i2c->CR1 |= STOP_EN ; //start generation
}

i2c_err_t M_get_addr(I2C_TypeDef* i2c,uint8_t* addr){
	uint8_t cmd='c';
	for(int i=0;i<127;i++){
		i2c_err_t Status = M_I2C_WRITE(&cmd,i2c,i);
		if(Status == I2C_OK){
			*addr=i;
			return I2C_OK;
		}
	}
	return I2C_NO_ACTIVE_DEVICE;
}

uint16_t calculate_ccr(uint16_t freq_mhz, uint32_t speed_hz){
    uint32_t pclk_hz = freq_mhz * 1000000UL;
    return (uint16_t)(pclk_hz / (2 * speed_hz));
}

//
//void I2C1_INIT(struct i2ctypedef I2C_config){
//	I2C_config.intance->CR1 |= SWRST;
//	I2C_config.intance->CR1 &= ~SWRST;   // clear reset
//
//	I2C_config.intance->CR2   = I2C_config.frequency;                 // Peripheral clock freq in MHz
//	I2C_config.intance->CCR   = calculate_ccr(I2C_config.frequency, 100); // Clock control (100kHz)
//	I2C_config.intance->TRISE = I2C_config.frequency + 1;             // TRISE register
//	I2C_config.intance->CR1  |= PE_EN;                                // Enable peripheral
//
//}
void I2C1_INIT(struct i2ctypedef *I2C_config){
    // Reset
    I2C_config->intance->CR1 |= SWRST;
    I2C_config->intance->CR1 &= ~SWRST;

    // Clock freq (MHz)
    I2C_config->intance->CR2 = I2C_config->frequency;

    // CCR for 100kHz
    I2C_config->intance->CCR = calculate_ccr(I2C_config->frequency, 100000);

    // TRISE
    I2C_config->intance->TRISE = I2C_config->frequency + 1;
    I2C_config->intance->CR1 |= (1U << 10);//for ack
    I2C_config->intance->CR2 |= (1U << 9);
    I2C_config->intance->CR1 |= PE_EN;
}
#define I2C_CR1_SWRST (1U << 15)
void I2C1_Slave_Init(uint8_t own_address,I2C_TypeDef* I2C1___) {
    // Reset
	I2C1___->CR1 |= I2C_CR1_SWRST;
	I2C1___->CR1 &= ~I2C_CR1_SWRST;

    // Enable ACK
//	I2C1___->CR1 |=(1U << 10);
	I2C1___->CR2 |= (1U << 9);
    // Peripheral clock frequency (must be set even in slave)
	I2C1___->CR2 = 42;   // if APB1=42 MHz

    // Own address
	I2C1___->OAR1 = (own_address << 1);
	I2C1___->OAR1 |= (1 << 14);   // required for 7-bit mode



    // Enable peripheral
    I2C1___->CR1 = 1025;
}
#define I2C_SR1_ADDR (40005414UL)
void I2C1_Slave_Loop(I2C_TypeDef* I2cxx) {
    while (1) {
        // Wait for address match
        while (!(I2cxx->SR1 & I2C_SR1_ADDR));
        (void)I2cxx->SR1;
        (void)I2cxx->SR2;

        // Wait for data (master write)
        while (!(I2cxx->SR1 & (1U<<6)));
        uint8_t rx = I2cxx->DR;

        // Prepare response (master read)
        while (!(I2cxx->SR1 & (1U<<7)));
        I2cxx->DR = rx + 1;  // echo +1 back
    }
}


