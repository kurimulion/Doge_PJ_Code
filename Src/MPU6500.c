#include "MPU6500.h"
extern SPI_HandleTypeDef hspi1;
void SPI_Configuration(u32 BaudRatePrescaler);

int MPU6500_delay_EN=ENABLE;
void MPU6500_Configuration(){
	__HAL_SPI_ENABLE(&hspi1);
	/***************************************
	Resrt device , Sleep mode disable
	use internal 20MHz oscillator
	****************************************/
	MPU6500_write(MPU6500_PWR_MGMT_1,0x80); 
	HAL_Delay(100);
	/***************************************
	Resrt digital signal path
	****************************************/
	MPU6500_write(MPU6500_SIGNAL_PATH_RESET,0x07); 
	HAL_Delay(100);
	
	MPU6500_write(MPU6500_PWR_MGMT_2,0x00); //0x3F disable Gyro,ACC
	
	/***************************************
	Resrt  DMP , FIFO , I2C_MST , SIG_COND
	Set SPI interface only
	****************************************/
	MPU6500_write(MPU6500_USER_CTRL,0x1D); 

	//check communication 
	while(MPU6500_read(MPU6500_WHOAMI)!=0x0070){
		printf("communication fail\r\n");
	}
		
	/***************************************
	Set Gyro 3600hz bandwidth, 8khz Fs
	****************************************/
	MPU6500_write(MPU6500_Config,0x07); 
		
	/***************************************
  Set FCHOICE_B=0, Gyro Full Scale +-2000dps , Gyro self-test off
	****************************************/
	MPU6500_write(MPU6500_Gyro_Config,MPU6500_GYRO_FS_2000 ); //option : MPU6500_self_test
		
	/***************************************
	Set ACC 460Hz bandwidth, 1khz Fs
	****************************************/
	MPU6500_write(MPU6500_Acc_Config_2,0x00); 
		
	/***************************************
  Set Accel Full Scale +-16g , Accel self-test off
	****************************************/
	MPU6500_write(MPU6500_Acc_Config,MPU6500_ACCEL_FS_16);  //option : MPU6500_self_test
		
	/***************************************
  Set six Axis offset to 32767(0x7FFF)
	****************************************/
	MPU6500_write( 0x1300, 0x7F ); 
	MPU6500_write( 0x1400, 0xFF ); 
	MPU6500_write( 0x1500, 0x7F ); 
	MPU6500_write( 0x1600, 0xFF ); 
	MPU6500_write( 0x1700, 0x7F ); 
	MPU6500_write( 0x1800, 0xFF ); 

	SPI_Configuration(SPI_BAUDRATEPRESCALER_4);	//Set PCLK1 = 84Mhz / 8 = 10.5Mhz
	__HAL_SPI_ENABLE(&hspi1);
	
	MPU6500_delay_EN=DISABLE;
}

void MPU6500_write(u16 address , u8 CMD){
	int count_delay=0;
	CS_L;
	while(!(hspi1.Instance->SR&SPI_FLAG_TXE));
	hspi1.Instance->DR = (address | CMD);
	while(!(hspi1.Instance->SR&SPI_FLAG_RXNE));
	hspi1.Instance->DR;
	CS_H;
	if(MPU6500_delay_EN==ENABLE) for(;count_delay<10;count_delay++){}
}
u16 MPU6500_read(u16 address){
	int count_delay=0;
	CS_L;
	while(!(hspi1.Instance->SR&SPI_FLAG_TXE));
	hspi1.Instance->DR =  (0x8000 | address);
	while(!(hspi1.Instance->SR&SPI_FLAG_RXNE));
	CS_H;
	if(MPU6500_delay_EN==ENABLE) for(;count_delay<10;count_delay++){}
	return (0x00FF & hspi1.Instance->DR);	
}
void SPI_Configuration(u32 BaudRatePrescaler)
{
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_16BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = BaudRatePrescaler;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLED;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
  HAL_SPI_Init(&hspi1);
}

