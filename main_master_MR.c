/**
  ******************************************************************************
  * @file    main_master_MR.c
  * @author  Ye Qinghua
  * @version V1.0.0
  * @date    06-Aug-2020 
  * @brief   entry for i2c master device while master read.
  ******************************************************************************
 	* @attention
  *
  * (C) COPYRIGHT 2020 Ye Qinghua,All rights reserved.
  ******************************************************************************
  */
#include "typedef.h"
#include "i2c.h"

#define READ_MODE   1
#define WRITE_MODE  0

#define R_W_MODE    (WRITE_MODE)

#define SLAVE_ADDR_7BITS  0x2a // 0b010-1010
#define SLAVE_ADDR_10BITS 0x155 // 0b01-0101-0101

void user_interrupt(void){}

int main(void){
  int i = 0;
  int addr_rw = 0;
  uint8_t data = 0;
  while(1){

    i2c_debug("\n----I2C MASTER READ----\n");

    addr_rw = ((SLAVE_ADDR_7BITS << 1) | READ_MODE);

    /* I2C master init */
    i2c_master_init();
    i2c_debug("\n0. Master init.\n");

    /* send START signal */
    i2c_master_start();
    i2c_debug("1. Master has sent START signal.\n");
    
    /* send address and R/W bit */
    if(!i2c_master_write_byte(addr_rw)){
      i2c_debug("2. Target slave has replied.\n");
    }else{
      i2c_debug("2. No slave replies.\n");
    }

    udelay(7*I2C_DELAY);
    /* read a byte from slave */
    data = i2c_master_read_byte();
    i2c_debug("3. Master read a byte('");
    putch(data);
    i2c_debug("') from slave successfully.\n");

    udelay(5*I2C_DELAY);
    /* read a byte from slave */
    data = i2c_master_read_byte();
    i2c_debug("4. Master read a byte('");
    putch(data);
    i2c_debug("') from slave successfully.\n");

    udelay(5*I2C_DELAY);
    /* read a byte from slave */
    data = i2c_master_read_byte();
    i2c_debug("5. Master read a byte('");
    putch(data);
    i2c_debug("') from slave successfully.\n");

    /* send STOP signal */
    i2c_master_stop();
    i2c_debug("6. Master has sent STOP signal.\n");

    break;
  }
  while(1);

  return 0;
}

/******************* (C) COPYRIGHT 2020 Ye Qinghua,All rights reserved. *******************/
/******************* END OF FILE *******************/
