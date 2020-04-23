#include <string.h>
#include <stdint.h>
#include <math.h>
#include "hw.h"
#include "stm32l0xx_hal_def.h"

/*=========================================================================
    I2C ADDRESS/BITS
    -----------------------------------------------------------------------*/
	/* Address Pad Ground */
#define LIS3DH_Write_Address_G	    0x0030
#define LIS3DH_Read_Address_G	    0x0031	    

	/* Address Pad Connected to Vdd */
#define LIS3DH_Write_Address_V 	    0x0032
#define LIS3DH_Read_Address_V	    0x0033

/*=========================================================================*/

/* LIS3DH_REGISTER_ADDRESSES */
#define LIS3DH_REG_STATUS1       0x07
#define LIS3DH_REG_OUTADC1_L     0x08
#define LIS3DH_REG_OUTADC1_H     0x09
#define LIS3DH_REG_OUTADC2_L     0x0A
#define LIS3DH_REG_OUTADC2_H     0x0B
#define LIS3DH_REG_OUTADC3_L     0x0C
#define LIS3DH_REG_OUTADC3_H     0x0D
#define LIS3DH_REG_INTCOUNT      0x0E
#define LIS3DH_REG_WHOAMI        0x0F
#define LIS3DH_REG_TEMPCFG       0x1F
#define LIS3DH_REG_CTRL1         0x20
#define LIS3DH_REG_CTRL2         0x21
#define LIS3DH_REG_CTRL3         0x22
#define LIS3DH_REG_CTRL4         0x23
#define LIS3DH_REG_CTRL5         0x24
#define LIS3DH_REG_CTRL6         0x25
#define LIS3DH_REG_REFERENCE     0x26
#define LIS3DH_REG_STATUS2       0x27
#define LIS3DH_REG_OUT_X_L       0x28
#define LIS3DH_REG_OUT_X_H       0x29
#define LIS3DH_REG_OUT_Y_L       0x2A
#define LIS3DH_REG_OUT_Y_H       0x2B
#define LIS3DH_REG_OUT_Z_L       0x2C
#define LIS3DH_REG_OUT_Z_H       0x2D
#define LIS3DH_REG_FIFOCTRL      0x2E
#define LIS3DH_REG_FIFOSRC       0x2F
#define LIS3DH_REG_INT1CFG       0x30
#define LIS3DH_REG_INT1SRC       0x31
#define LIS3DH_REG_INT1THS       0x32
#define LIS3DH_REG_INT1DUR       0x33
#define LIS3DH_REG_CLICKCFG      0x38
#define LIS3DH_REG_CLICKSRC      0x39
#define LIS3DH_REG_CLICKTHS      0x3A
#define LIS3DH_REG_TIMELIMIT     0x3B
#define LIS3DH_REG_TIMELATENCY   0x3C
#define LIS3DH_REG_TIMEWINDOW    0x3D
#define LIS3DH_REG_ACTTHS        0x3E
#define LIS3DH_REG_ACTDUR        0x3F

/* REG_1 */
typedef enum {
	LIS3DH_POWERDOWN,
    	LIS3DH_1Hz,	   	
	LIS3DH_10Hz,		
	LIS3DH_25Hz,		
	LIS3DH_50Hz,		
	LIS3DH_100Hz,		
	LIS3DH_200Hz,	
	LIS3DH_400Hz,		
	LIS3DH_1600Hz,		
	LIS3DH_1344HZ,		
	LIS3DH_5376HZ,	
}e_lis3dh_odr_t;

typedef struct {
	uint8_t x_enable	:1;
	uint8_t y_enable	:1;
	uint8_t z_enable	:1;
	uint8_t lp_enable	:1;
	uint8_t odr		:4; 		/* Define ODR in macro @LIS3DH_REG1 */
}lis3dh_reg1_t;

/* REG_2 */
typedef enum{
	HP_NORMAL_RESET_MODE,
	HP_REFERENCE_MODE,	
	HP_NORMAL_MODE,		
	HP_AUTORESET,		
}e_lis3dh_hp_cutoff_t;

typedef struct {
	uint8_t hp_ia1		:1;
	uint8_t hp_ia2		:1;
	uint8_t hpclick		:1;
	uint8_t fds		:1;
	uint8_t hp_cutoff	:2;			/* Refer Datasheet and application note */
	uint8_t hp_mode		:2;			/* Mode defined in macro @LIS3DH_REG2 */
}lis3dh_reg2_t;

/* REG_3 */
typedef	struct {
	uint8_t not_used_01	:1;
	uint8_t	i1_overrun	:1;		
	uint8_t	i1_wtm		:1;
	uint8_t i1_321da	:1;
	uint8_t	i1_zyxda	:1;
	uint8_t	i1_ia2		:1;
	uint8_t	i1_ia1		:1;
	uint8_t i1_click	:1;
}lis3dh_reg3_t;

/* REG_4 */
typedef enum {
	FS_2G,
	FS_4G,
	FS_8G,
	FS_16G,
}e_lis3dh_full_scale_t;

typedef enum{
	ST_NORMAL_MODE,	
	ST_0,			
	ST_1,			
	NA,			
}e_lis3dh_self_test_t;

typedef	struct {
	uint8_t	spi_mode	:1;
	uint8_t	self_test	:2;
	uint8_t	hr_mode		:1;
	uint8_t	full_scale	:2;
	uint8_t	ble		:1;
	uint8_t	bdu		:1;
}lis3dh_reg4_t;

/* REG_5 */
typedef	struct {
	uint8_t d4d_int2	:1;
	uint8_t	lir_int2	:1;
	uint8_t	d4d_int1	:1;
	uint8_t	lir_int1	:1;
	uint8_t	na1		:1;
	uint8_t	na2		:1;
	uint8_t	fifo_enable	:1;
	uint8_t	boot		:1;
}lis3dh_reg5_t;

/* REG_6 */
typedef	struct {
	uint8_t	na1		:1;
	uint8_t	int_pol		:1;
	uint8_t	na2		:1;
	uint8_t	i2_act		:1;
	uint8_t	i2_boot		:1;
	uint8_t	i2_ia2		:1;
	uint8_t	i2_ia1		:1;
	uint8_t	i2_click	:1;
}lis3dh_reg6_t;

/* INT1_CFG */
typedef enum{
	OR_COMB_INT,	
	DIR_MOV_RECO,
	AND_COMB_INT,
	DIR_POS_RECO,
}e_lis3dh_and_or_int_t;

typedef	struct {
	uint8_t	xlie		:1;
	uint8_t	xhlie		:1;
	uint8_t	ylie		:1;
	uint8_t	yhlie		:1;
	uint8_t	zlie		:1;
	uint8_t	zhile		:1;
	uint8_t	aoi_6d		:2;
}lis3dh_int1cfg_t;

/* INT1_THS */
typedef	struct {
	uint8_t	ths		:7;
	uint8_t	not_used_01 	:1;
}lis3dh_int1ths_t;

/* INT1_DUR */
typedef struct{
	uint8_t	dur		:7;
	uint8_t	not_used_02 	:1;
}lis3dh_int1dur_t;

/* LIS3DH union */
typedef union {
	lis3dh_reg1_t		cfg_reg_1;
	lis3dh_reg2_t		cfg_reg_2;
	lis3dh_reg3_t		cfg_reg_3;
	lis3dh_reg4_t		cfg_reg_4;
	lis3dh_reg5_t		cfg_reg_5;
	lis3dh_reg6_t		cfg_reg_6;
	lis3dh_int1cfg_t	cfg_reg_int1cfg;
	lis3dh_int1ths_t	cfg_reg_int1ths;
	lis3dh_int1dur_t    	cfg_reg_int1dur;
    	uint8_t             	lis3dh_byte;
}u_lis3dh_reg_t;

/* User defined functions */
void config_lis3dh_reg1(void);
void config_lis3dh_reg2(void);
void config_lis3dh_reg3(void);
void config_lis3dh_reg4(void);
void config_lis3dh_reg5(void);
void config_lis3dh_reg6(void);
void config_lis3dh_int1ths(void);
void config_lis3dh_int1dur(void);
void config_lis3dh_int1cfg(void);

void init_lis3dh_no_motion(void);
void reconfigure_no_motion(void);
