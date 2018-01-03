#include "stm32f4xx_hal.h"
#include "short_type.h"

#define CS_L HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_RESET)
#define CS_H HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_SET)
;
#define MPU6500_PWR_MGMT_1 				0x6B00
#define MPU6500_PWR_MGMT_2 				0x6C00
#define MPU6500_SIGNAL_PATH_RESET 0x6800
#define MPU6500_USER_CTRL 				0x6A00
#define MPU6500_WHOAMI 					 	0x7500
#define MPU6500_Config						0x1A00
#define MPU6500_FIFO_Enable				0x2300
#define MPU6500_Gyro_Config				0x1B00
#define MPU6500_Acc_Config				0x1C00
#define MPU6500_Acc_Config_2			0x1D00

#define MPU6500_FIFO_EN_TEMP 		0x80
#define MPU6500_FIFO_EN_GYROX		0x40
#define MPU6500_FIFO_EN_GYROY 	0x20
#define MPU6500_FIFO_EN_GYROZ		0x10
#define MPU6500_FIFO_EN_GYRO 		0x70
#define MPU6500_FIFO_EN_ACC 		0x08

#define MPU6500_ACCEL_FS_2	 		0x00
#define MPU6500_ACCEL_FS_4	 		0x08
#define MPU6500_ACCEL_FS_8	 		0x10
#define MPU6500_ACCEL_FS_16	 		0x18

#define MPU6500_GYRO_FS_250 		0x00
#define MPU6500_GYRO_FS_500 		0x08
#define MPU6500_GYRO_FS_1000 		0x10
#define MPU6500_GYRO_FS_2000 		0x18

#define MPU6500_self_test				0xE0

void MPU6500_Configuration(void);
void MPU6500_write(u16 address , u8 CMD);
u16 MPU6500_read(u16 address);
