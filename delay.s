###########################################################
# @file			delay.s
# @author		Ye Qinghua
# @version	V1.0.0
# @date:		06-Aug-2020  last edit
# @brief		define a delay function "void udelay(uint32_t)"
###########################################################
# @attention
# 
# (C) COPYRIGHT 2020 Ye Qinghua,All rights reserved.
###########################################################
.text
	.align	4
	.globl	udelay
	.ent	udelay
	.set	noreorder
	.set	noat
udelay:
	nop
_loop_:
	beq $a0, $zero, _end_
	nop
	nop
	addi $a0, $a0, -1
	j _loop_
	nop
_end_:
	nop
	jr	$ra
	nop

.set	reorder
.end	udelay

##################### (C) COPYRIGHT 2020 Ye Qinghua,All rights reserved. #####################
##################### END OF FILE #####################
