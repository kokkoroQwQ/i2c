/**
  ******************************************************************************
  * @file    i2c.c
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
#include "i2c.h"

/**
  * @brief  I2C master device initializes.
  * @param  None
  * @retval 0
  */
int i2c_master_init(void){
  SET_SDA_OUT;
  SET_SDA_HIGH;
  SET_SCL_OUT;
  SET_SCL_HIGH;
  return 0;
}

/**
  * @brief  I2C master device START signal control.
  * @param  None
  * @retval 0
  */
int i2c_master_start(void){
  SET_SDA_OUT;
  SET_SDA_HIGH;
  SET_SCL_OUT;
  SET_SCL_HIGH;

  udelay(4*I2C_DELAY);    /* 1T */

  SET_SDA_LOW;
  udelay(2*I2C_DELAY);
  SET_SCL_LOW;
  udelay(2*I2C_DELAY);

  return 0;
}

/**
  * @brief  I2C master device STOP signal control.
  * @param  None
  * @retval 0
  */
int i2c_master_stop(void){
  SET_SCL_LOW;
  SET_SDA_OUT;
  SET_SDA_LOW;
  udelay(I2C_DELAY);
  SET_SCL_HIGH;
  udelay(I2C_DELAY);
  SET_SDA_HIGH;
  return 0;
}

/**
  * @brief  I2C master device write a bit to slave device.
  * @param  bit: integer, 0 or 1.
  * @retval 0
  */
int i2c_master_write_bit(int bit){
  SET_SDA_OUT;
  SET_SCL_LOW;
  if(bit == 0){
    SET_SDA_LOW;
  }else if(bit > 0){
    SET_SDA_HIGH;
  }
  udelay(I2C_DELAY);
  SET_SCL_HIGH;
  udelay(2*I2C_DELAY);
  SET_SCL_LOW;
  udelay(I2C_DELAY);
  return 0;
}

/**
  * @brief  I2C master device write a byte to slave device.
  * @param  byte: uint8_t(unsigned char), 0x00 ~ 0xff.
  * @retval 0: if master device receives an ack.
  *         1: if master device receives a nack.
  */
int i2c_master_write_byte(uint8_t byte){
  int i = 0;
  int mask = (1 << (BYTE_LENGTH-1));
  SET_SDA_OUT;
  SET_SCL_LOW;
  for(i = 0; i < BYTE_LENGTH; i++){
    i2c_master_write_bit(byte & mask);
    byte <<= 1;
  }
  SET_SDA_HIGH;
  SET_SDA_IN;
  udelay(I2C_DELAY);
  SET_SCL_HIGH;
  i = 0;
  while(GET_SDA_VAL && i < 4){
    udelay(I2C_DELAY/2);
    i++;
  }
  udelay((4-i) * I2C_DELAY/2);
  SET_SCL_LOW;
  udelay(I2C_DELAY);
  if(i >= 4){
    return 1;
  }else{
    return 0;
  }
}

/**
  * @brief  I2C master device write a 11-bit word to slave device.
  * @param  data: uint16_t(unsigned int), 0x000 ~ 0x7ff.
  * @retval 0: if master device receives an ack.
  *         1: if master device receives a nack.
  */
int i2c_master_write_11bits(uint16_t data){
  int i = 0;
  int mask = (1 << 10);
  SET_SDA_OUT;
  SET_SCL_LOW;
  for(i = 0; i < 11; i++){
    i2c_master_write_bit(data & mask);
    data <<= 1;
  }
  SET_SDA_HIGH;
  SET_SDA_IN;
  udelay(I2C_DELAY);
  SET_SCL_HIGH;
  i = 0;
  while(GET_SDA_VAL && i < 4){
    udelay(I2C_DELAY/2);
    i++;
  }
  udelay((4-i) * I2C_DELAY);
  SET_SCL_LOW;
  if(i >= 4){
    return 1;
  }else{
    return 0;
  }
}

/**
  * @brief  I2C master device read a bit from slave device.
  * @param  None
  * @retval 0: if master device read 0.
  *         1: if master device read 1.
  */
int i2c_master_read_bit(void){
  int bit = 0;
  SET_SDA_IN;
  SET_SCL_LOW;
  udelay(I2C_DELAY);
  SET_SCL_HIGH;
  udelay(I2C_DELAY);
  if(GET_SDA_VAL){
    bit = 1;
  }else{
    bit = 0;
  }
  udelay(I2C_DELAY);
  SET_SCL_LOW;
  udelay(I2C_DELAY);

  return bit;
}

/**
  * @brief  I2C master device write a byte to slave device.
  * @param  None
  * @retval byte: uint8_t(unsigned char), the byte master device has read from slave device
  */
uint8_t i2c_master_read_byte(void){
  uint8_t byte = 0;
  int i = 0;
  SET_SDA_IN;
  SET_SCL_LOW;

  for(i = 0; i < BYTE_LENGTH; i++){
    byte <<= 1;
    byte |= i2c_master_read_bit();
  }

  /* send ack to slave */
  SET_SDA_OUT;
  SET_SDA_LOW;
  udelay(I2C_DELAY);
  SET_SCL_HIGH;
  udelay(2*I2C_DELAY);
  SET_SCL_LOW;
  udelay(I2C_DELAY);

  return byte;
}






/**
  * @brief  I2C slave device initializes.
  * @param  None
  * @retval 0
  */
int i2c_slave_init(void){
  SET_SCL_IN;
  SET_SDA_IN;
  return 0;
}

/**
  * @brief  I2C slave device waits for START signal. 
  * @param  None
  * @retval 0: if slave device captures a START signal.
  *         1: error.
  */
int i2c_slave_wait_start(void){
  SET_SDA_IN;
  while(!GET_SCL_VAL);
  while(!GET_SDA_VAL);
  while(GET_SDA_VAL);
  if (GET_SCL_VAL){
    return 0;
  }
  return 1;
}

/**
  * @brief  I2C slave device waits for STOP signal. 
  * @param  None
  * @retval 0: if slave device captures a STOP signal.
  *         1: error.
  */
int i2c_slave_wait_stop(void){
  int SDA_level = 0;
  int SCL_level = 0;
  SET_SDA_IN;
  while(GET_SDA_VAL);
  while(GET_SCL_VAL);
  while(!GET_SCL_VAL);
  SDA_level = GET_SDA_VAL;
  while(!GET_SDA_VAL);
  SCL_level = GET_SCL_VAL;
  while(!GET_SCL_VAL);
  while(!GET_SDA_VAL);
  if(SDA_level == 0 && SCL_level == 1){
    return 0;
  }else{
    return 1;
  }
}

/**
  * @brief  I2C slave device writes a bit to master device.
  * @param  bit: integer, 0 or 1.
  * @retval 0
  */
int i2c_slave_write_bit(int bit){
  while(GET_SCL_VAL);
  SET_SDA_OUT;
  if(bit == 0){
    SET_SDA_LOW;
  }else{
    SET_SDA_HIGH;
  }
  while(!GET_SCL_VAL);
  while(GET_SCL_VAL);
  //SET_SDA_LOW;
  return 0;
}

/**
  * @brief  I2C slave device writes a byte to master device.
  * @param  byte: uint8_t(unsigned char), 0x00 ~ 0xff.
  * @retval 0: if slave device receives an ack.
  *         1: if slave device receives a nack.
  */
int i2c_slave_write_byte(uint8_t byte){
  int i = 0;
  int mask = (1 << (BYTE_LENGTH-1));
  for(i = 0; i < BYTE_LENGTH; i++){
    i2c_slave_write_bit(byte & mask);
    byte <<= 1;
  }

  /* waiting ack signal */
  while(GET_SCL_VAL);
  SET_SDA_IN;
  while(!GET_SCL_VAL);
  if(GET_SDA_VAL){
    return 1;
  }else{
    return 0;
  }
}

/**
  * @brief  I2C slave device read a bit from master device.
  * @param  None
  * @retval bit
  */
int i2c_slave_read_bit(void){
  int bit = 0;
  while(GET_SCL_VAL);
  while(!GET_SCL_VAL);
  if(GET_SDA_VAL){
    bit = 1;
  }
  while(GET_SCL_VAL);
  return bit;
}

/**
  * @brief  I2C slave device read a byte from master device while method = 0,
  *         proccess address and R/W bit while method = 1.
  * @param  method: optional
  *                 0 while reading a common byte.
  *                 1 while reading a special byte with address and R/W bit.
  *         addr:   neccessary while method = 1. The slave device address.
  * @retval byte:   while method = 0.
  *         status: R/W bit(R for 1, W for 0) while address fits.
  *                 2 while address doesn't fit.
  */
uint8_t i2c_slave_read_byte(int method, uint8_t addr){
  uint8_t byte = 0;
  int i = 0;
  SET_SDA_IN;
  SET_SCL_IN;
  for(i = 0; i < BYTE_LENGTH; i++){
    byte <<= 1;
    byte |= (uint8_t)i2c_slave_read_bit();
  }

  /* send ack signal while method = 1 and addr fit*/
  if((method == 1) && ((byte >> 1) == addr)){
    while(GET_SCL_VAL);
    while(!GET_SDA_VAL); // wait for master release SDA
    SET_SDA_OUT;
    SET_SDA_LOW;
    while(!GET_SCL_VAL);
    while(GET_SCL_VAL);
    SET_SDA_HIGH;
    SET_SDA_IN;
    return (uint8_t)(byte & 1);  // R/W bit
  }

  /* send nack signal while method = 1 and addr not fit*/
  else if((method == 1) && ((byte >> 1) != addr)){
    while(GET_SCL_VAL);
    while(!GET_SDA_VAL); // wait for master release SDA
    SET_SDA_OUT;
    SET_SDA_HIGH;
    while(!GET_SCL_VAL);
    while(GET_SCL_VAL);
    SET_SDA_HIGH;
    SET_SDA_IN;
    return (uint8_t)2;
  }

  /* send ack signal while method = 0*/
  else if(method == 0){
    while(GET_SCL_VAL);
    while(!GET_SDA_VAL); // wait for master release SDA
    SET_SDA_OUT;
    SET_SDA_LOW;
    while(!GET_SCL_VAL);
    while(GET_SCL_VAL);
    SET_SDA_HIGH;
    SET_SDA_IN;
    return byte;
  }
}

/**
  * @brief  I2C slave device read a 11-bit word from master device.
  * @param  None
  * @retval data
  */
uint16_t i2c_slave_read_11bits(uint16_t addr){
  uint16_t data = 0;
  int i = 0;
  SET_SDA_IN;
  SET_SCL_IN;
  for(i = 0; i < 11; i++){
    data <<= 1;
    data |= i2c_slave_read_bit();
  }

  /* send ack signal while method = 1 and addr fit*/
  if((data >> 1) == addr){
    while(GET_SCL_VAL);
    while(!GET_SDA_VAL); // wait for master release SDA
    SET_SDA_OUT;
    SET_SDA_LOW;
    while(!GET_SCL_VAL);
    while(GET_SCL_VAL);
    SET_SDA_HIGH;
    SET_SDA_IN;
    return (uint16_t)(data & 1);  // R/W bit
  }

  /* send nack signal while method = 1 and addr not fit*/
  else if((data >> 1) != addr){
    while(GET_SCL_VAL);
    while(!GET_SDA_VAL); // wait for master release SDA
    SET_SDA_OUT;
    SET_SDA_HIGH;
    while(!GET_SCL_VAL);
    while(GET_SCL_VAL);
    SET_SDA_HIGH;
    SET_SDA_IN;
    return (uint16_t)2;
  }
}

/******************* (C) COPYRIGHT 2020 Ye Qinghua,All rights reserved. *******************/
/******************* END OF FILE *******************/
