/**
  ******************************************************************************
  * @file    i2c.h
  * @author  Ye Qinghua
  * @version V1.0.0
  * @date    04-Aug-2020
  * @brief   
  ******************************************************************************
 	* @attention
  *
  * (C) COPYRIGHT 2020 Ye Qinghua,All rights reserved.
  ******************************************************************************
  */

#ifndef	__I2C_H
#define	__I2C_H

#include "typedef.h"
#include "mcu.h"
#include "str.h"
#include "delay.h"

/* define SDA, SCL PIN */
#define	SCL_GPIO_PIN	0
#define SDA_GPIO_PIN	1

/* define delay time */
#define I2C_DELAY			685 /* optimal 1/4 T of SCL   685*/

/* define length of a byte */
#define BYTE_LENGTH		8

/* use to print debug information to UART0 */
#define i2c_debug(x)	puts(x)

/* operations about SDA and SCL */
#define SET_SCL_IN		MemoryAnd32	(SYS_IOCTL_REG, ~(1<<(SCL_GPIO_PIN)))
#define SET_SCL_OUT		MemoryOr32	(SYS_IOCTL_REG,  (1<<(SCL_GPIO_PIN)))
#define SET_SCL_HIGH	MemoryOr32	(SYS_GPIO0_REG,  (1<<(SCL_GPIO_PIN)))
#define SET_SCL_LOW		MemoryAnd32	(SYS_GPIO0_REG, ~(1<<(SCL_GPIO_PIN)))

#define SET_SDA_IN		MemoryAnd32	(SYS_IOCTL_REG, ~(1<<(SDA_GPIO_PIN)))
#define SET_SDA_OUT		MemoryOr32	(SYS_IOCTL_REG,  (1<<(SDA_GPIO_PIN)))
#define SET_SDA_HIGH	MemoryOr32	(SYS_GPIO0_REG,  (1<<(SDA_GPIO_PIN)))
#define SET_SDA_LOW		MemoryAnd32	(SYS_GPIO0_REG, ~(1<<(SDA_GPIO_PIN)))

#define GET_SCL_VAL		(MemoryRead32(SYS_GPIO1_REG) & (1<<(SCL_GPIO_PIN)))
#define GET_SDA_VAL		(MemoryRead32(SYS_GPIO1_REG) & (1<<(SDA_GPIO_PIN)))

/* functions for master device */
int i2c_master_init(void);
int i2c_master_start(void);
int i2c_master_stop(void);
int i2c_master_write_bit(int bit);
int i2c_master_write_byte(uint8_t data);
int i2c_master_write_11bits(uint16_t data);
int i2c_master_read_bit(void);
uint8_t i2c_master_read_byte(void);

/* functions for slave device */
int i2c_slave_init(void);
int i2c_slave_wait_start(void);
int i2c_slave_wait_stop(void);
int i2c_slave_write_bit(int bit);
int i2c_slave_write_byte(uint8_t data);
int i2c_slave_read_bit(void);
uint8_t i2c_slave_read_byte(int method, uint8_t addr);
uint16_t i2c_slave_read_11bits(uint16_t addr);

#endif /* __I2C_H */

/******************* (C) COPYRIGHT 2020 Ye Qinghua,All rights reserved. *******************/
/******************* END OF FILE *******************/
