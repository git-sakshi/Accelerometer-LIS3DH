#include "lis3dh.h"

u_lis3dh_reg_t lis3dh_reg_t;
extern I2C_HandleTypeDef hi2c1;

void config_lis3dh_reg1(void)
{
	lis3dh_reg_t.lis3dh_byte 		= 0x07;			/* Default */
//	lis3dh_reg_t.cfg_reg_1.x_enable 	= 1;
//	lis3dh_reg_t.cfg_reg_1.y_enable 	= 1;
//	lis3dh_reg_t.cfg_reg_1.z_enable 	= 1;
//	lis3dh_reg_t.cfg_reg_1.lp_enable 	= 0;
	lis3dh_reg_t.cfg_reg_1.odr 		= LIS3DH_1Hz;
}

void config_lis3dh_reg2(void)
{
	lis3dh_reg_t.lis3dh_byte 		= 0x00;			/* Default */
	lis3dh_reg_t.cfg_reg_2.hp_ia1 		= 1;
//	lis3dh_reg_t.cfg_reg_2.hp_ia2 		= 0;	
//	lis3dh_reg_t.cfg_reg_2.hpclick 		= 0;
//	lis3dh_reg_t.cfg_reg_2.fds		= 0;	
//	lis3dh_reg_t.cfg_reg_2.hp_cutoff 	= 0;
//  	lis3dh_reg_t.cfg_reg_2.hp_mode 		= HP_NORMAL_RESET_MODE;
}

void config_lis3dh_reg3(void)
{
	lis3dh_reg_t.lis3dh_byte = 0x00;				/* Default */
//	lis3dh_reg_t.cfg_reg_3.not_used_01	= 0;
//	lis3dh_reg_t.cfg_reg_3.i1_overrun	= 0;
//	lis3dh_reg_t.cfg_reg_3.i1_wtm		= 0;
//	lis3dh_reg_t.cfg_reg_3.i1_321da	    	= 0;
//	lis3dh_reg_t.cfg_reg_3.i1_zyxda	    	= 0;
//	lis3dh_reg_t.cfg_reg_3.i1_ia2		= 0;
	lis3dh_reg_t.cfg_reg_3.i1_ia1		= 1;
//	lis3dh_reg_t.cfg_reg_3.i1_click	    	= 0;
}

void config_lis3dh_reg4(void)
{
	lis3dh_reg_t.lis3dh_byte = 0x00;				/* Default */
//	lis3dh_reg_t.cfg_reg_4.spi_mode	  	= 0;
//	lis3dh_reg_t.cfg_reg_4.self_test	= ST_NORMAL_MODE;
	lis3dh_reg_t.cfg_reg_4.hr_mode		= 1;
//	lis3dh_reg_t.cfg_reg_4.full_scale	= FS_2G;
//	lis3dh_reg_t.cfg_reg_4.ble		= 0;
	lis3dh_reg_t.cfg_reg_4.bdu		= 1;
}

void config_lis3dh_reg5(void)
{
	lis3dh_reg_t.lis3dh_byte 		= 0x00;			/* Default */
//	lis3dh_reg_t.cfg_reg_5.d4d_int2		= 0;
//	lis3dh_reg_t.cfg_reg_5.lir_int2		= 0;
//	lis3dh_reg_t.cfg_reg_5.d4d_int1		= 0;
	lis3dh_reg_t.cfg_reg_5.lir_int1		= 1;
//	lis3dh_reg_t.cfg_reg_5.na1		= 0;
//	lis3dh_reg_t.cfg_reg_5.na2		= 0;
//	lis3dh_reg_t.cfg_reg_5.fifo_enable	= 0;
	lis3dh_reg_t.cfg_reg_5.boot		= 1;
}

void config_lis3dh_reg6(void)
{	
	lis3dh_reg_t.lis3dh_byte 		= 0x00;			/* Default */
	lis3dh_reg_t.cfg_reg_6.na1		= 0;
	lis3dh_reg_t.cfg_reg_6.int_pol		= 0;
	lis3dh_reg_t.cfg_reg_6.na2		= 0;
	lis3dh_reg_t.cfg_reg_6.i2_act		= 0;
	lis3dh_reg_t.cfg_reg_6.i2_boot		= 0;
	lis3dh_reg_t.cfg_reg_6.i2_ia2		= 0;
	lis3dh_reg_t.cfg_reg_6.i2_ia1		= 0;
	lis3dh_reg_t.cfg_reg_6.i2_click		= 0;
}

void config_lis3dh_int1ths(void)
{	
	lis3dh_reg_t.lis3dh_byte 		= 0x00;			/* Default */
	lis3dh_reg_t.cfg_reg_int1ths.ths 	= 0x08;
}

void config_lis3dh_int1dur(void)
{
	lis3dh_reg_t.lis3dh_byte 		= 0x00;			/* Default */
	lis3dh_reg_t.cfg_reg_int1dur.dur 	= 0x3C;			/* 1 minute - 0x3C */
}

void config_lis3dh_int1cfg(void)
{
	lis3dh_reg_t.lis3dh_byte 		= 0x00;			/* Default */
	lis3dh_reg_t.cfg_reg_int1cfg.xlie	= 1;
//	lis3dh_reg_t.cfg_reg_int1cfg.xhlie	= 0;
	lis3dh_reg_t.cfg_reg_int1cfg.ylie	= 1;
//	lis3dh_reg_t.cfg_reg_int1cfg.yhlie	= 0;
	lis3dh_reg_t.cfg_reg_int1cfg.zlie	= 1;
//	lis3dh_reg_t.cfg_reg_int1cfg.zhile	= 0;
	lis3dh_reg_t.cfg_reg_int1cfg.aoi_6d	= AND_COMB_INT;
}

void init_lis3dh_no_motion(void)
{
	// reg1- 0x17 ODR-1HZ, Enable all axes
	config_lis3dh_reg1();
	HAL_I2C_Mem_Write(&hi2c1, LIS3DH_Write_Address_V, LIS3DH_REG_CTRL1, I2C_MEMADD_SIZE_8BIT, &lis3dh_reg_t.lis3dh_byte, 1, 100);
	
	// reg2 - 0x01 - HPF enabled for INT1
	config_lis3dh_reg2();
	HAL_I2C_Mem_Write(&hi2c1, LIS3DH_Write_Address_V, LIS3DH_REG_CTRL2, I2C_MEMADD_SIZE_8BIT, &lis3dh_reg_t.lis3dh_byte, 1, 100);
	
	// reg3 - 0x40 - Enable INT1
	config_lis3dh_reg3();
	HAL_I2C_Mem_Write(&hi2c1, LIS3DH_Write_Address_V, LIS3DH_REG_CTRL3, I2C_MEMADD_SIZE_8BIT, &lis3dh_reg_t.lis3dh_byte, 1, 100);
	
	// reg4 0x88 - Block data update and HR Mode
	config_lis3dh_reg4();
	HAL_I2C_Mem_Write(&hi2c1, LIS3DH_Write_Address_V, LIS3DH_REG_CTRL4, I2C_MEMADD_SIZE_8BIT, &lis3dh_reg_t.lis3dh_byte, 1, 100);
		
	// int_ths - 0x08
	config_lis3dh_int1ths();
	HAL_I2C_Mem_Write(&hi2c1, LIS3DH_Write_Address_V, LIS3DH_REG_INT1THS, I2C_MEMADD_SIZE_8BIT, &lis3dh_reg_t.lis3dh_byte, 1, 100);
	
	/*  reg5 - 0x88 - Latched INT & Boot */
	config_lis3dh_reg5();
	HAL_I2C_Mem_Write(&hi2c1, LIS3DH_Write_Address_V, LIS3DH_REG_CTRL5, I2C_MEMADD_SIZE_8BIT, &lis3dh_reg_t.lis3dh_byte, 1, 100);
	
	// int_dur - 0x0A 
	config_lis3dh_int1dur();
 	HAL_I2C_Mem_Write(&hi2c1, LIS3DH_Write_Address_V, LIS3DH_REG_INT1DUR, I2C_MEMADD_SIZE_8BIT, &lis3dh_reg_t.lis3dh_byte, 1, 100);
	
	// int_cfg - 0x95
	config_lis3dh_int1cfg();
	HAL_I2C_Mem_Write(&hi2c1, LIS3DH_Write_Address_V, LIS3DH_REG_INT1CFG, I2C_MEMADD_SIZE_8BIT, &lis3dh_reg_t.lis3dh_byte, 1, 100);
}

void reconfigure_no_motion(void)
{
	config_lis3dh_reg5();
	HAL_I2C_Mem_Write(&hi2c1, LIS3DH_Write_Address_V, LIS3DH_REG_CTRL5, I2C_MEMADD_SIZE_8BIT, &lis3dh_reg_t.lis3dh_byte, 1, 100);
	config_lis3dh_int1ths();
	HAL_I2C_Mem_Write(&hi2c1, LIS3DH_Write_Address_V, LIS3DH_REG_INT1THS, I2C_MEMADD_SIZE_8BIT, &lis3dh_reg_t.lis3dh_byte, 1, 100);
	config_lis3dh_int1cfg();
	HAL_I2C_Mem_Write(&hi2c1, LIS3DH_Write_Address_V, LIS3DH_REG_INT1CFG, I2C_MEMADD_SIZE_8BIT, &lis3dh_reg_t.lis3dh_byte, 1, 100);
	config_lis3dh_int1dur();
	HAL_I2C_Mem_Write(&hi2c1, LIS3DH_Write_Address_V, LIS3DH_REG_INT1DUR, I2C_MEMADD_SIZE_8BIT, &lis3dh_reg_t.lis3dh_byte, 1, 100);
}
