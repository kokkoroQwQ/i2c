/**
  ******************************************************************************
  * @file    main_slave_MW.c
  * @author  Ye Qinghua
  * @version V1.0.0
  * @date    04-Aug-2020
  * @brief   entry for i2c slave device while master write.
  ******************************************************************************
 	* @attention
  *
  * (C) COPYRIGHT 2020 Ye Qinghua,All rights reserved.
  ******************************************************************************
  */

#include "typedef.h"
#include "i2c.h"
#include "str.h"

#define READ_MODE   1
#define WRITE_MODE  0

// 0b010-1010
#define SLAVE_ADDR_7BITS  0x2a 
// 0b01-0101-0101
#define SLAVE_ADDR_10BITS 0x155

void user_interrupt(void){}

int main(void){
  int data = 0x76;
  while(1){

    i2c_debug("\n----I2C MASTER WRITE----\n");

    /* I2C slave init */
    i2c_slave_init();
    i2c_debug("\n0. Slave init.\n");

    /* wait for START signal */
    if(!i2c_slave_wait_start()){
      i2c_debug("1. Slave has captured START signal.\n");
    }else{
      continue;
    }

    /* capture address and R/W bit then ack or nack*/
    data = i2c_slave_read_byte(1, SLAVE_ADDR_7BITS);
    if(data != 2){
      i2c_debug("2. Slave address fits. ");
      if(data == 0){
        i2c_debug("Master write.\n");
      }else{
        i2c_debug("Master read.\n");
      }
    }else{
      i2c_debug("2. Slave address doesn't fit\n");
    }

    #if 0 // 10-bit address
    /* capture address and R/W bit then ack or nack*/
    data = i2c_slave_read_11bits(SLAVE_ADDR_10BITS);
    if(data != 2){
      i2c_debug("2. Slave address fits. ");
      if(data == 1){
        i2c_debug("Master write.\n");
      }else{
        i2c_debug("Master read.\n");
      }
    }else{
      i2c_debug("2. Slave address doesn't fit\n");
    }
    #endif
    
    /* read a byte from master */
    data = i2c_slave_read_byte(0, 0);
    i2c_debug("3. Slave read a byte('");
    putch(data);
    i2c_debug("') from master successfully.\n");

    /* read a byte from master */
    data = i2c_slave_read_byte(0, 0);
    i2c_debug("4. Slave read a byte('");
    putch(data);
    i2c_debug("') from master successfully.\n");

    /* read a byte from master */
    data = i2c_slave_read_byte(0, 0);
    i2c_debug("5. Slave read a byte('");
    putch(data);
    i2c_debug("') from master successfully.\n");

    /* wait for STOP signal */
    i2c_slave_wait_stop();
    i2c_debug("6. Slave has captured STOP signal.\n");

    break;
  }
  while(1);
  
  return 0;
}

/******************* (C) COPYRIGHT 2020 Ye Qinghua,All rights reserved. *******************/
/******************* END OF FILE *******************/
