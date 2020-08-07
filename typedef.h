/*
 * @description: defined some registers, data_type, and memory operation functions		 
 * @file: i2c.h
 * @author: Ye Qinghua
 * @date: 2020/07/30  last edit
 */


#ifndef TYPEDEF_H
#define	TYPEDEF_H

/* integer type definition */
#define uint8_t		unsigned char	// unsigned char 	8bits
#define uint16_t	unsigned int 	// unsigned int  	16bits
#define uint32_t	unsigned long	// unsigned long	32bits

#define SYS_IOCTL_REG	0x1f800704
#define SYS_GPIO0_REG	0x1f800705
#define SYS_GPIO1_REG	0x1f800706
#define EXINT_CTL0_REG	0x1f800500
#define EXINT_READ_REG	0x1f800501
#define EXINT_SET_REG	0x1f800502
#define EXINT_CLR_REG	0x1f800503


#define MemoryRead32(A) (*(volatile unsigned long*)(A))
#define MemoryWrite32(A,V) *(volatile unsigned long*)(A)=(V)
#define MemoryOr32(A,V) (*(volatile unsigned long*)(A)|=(V))
#define MemoryAnd32(A,V) (*(volatile unsigned long*)(A)&=(V))



#endif	// TYPEDEF_H

