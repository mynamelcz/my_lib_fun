/*
 * spi_driver.h
 *
 *  Created on: 2019年6月15日
 *      Author: youyou
 */

#ifndef SPI_DRIVER_H_
#define SPI_DRIVER_H_


typedef enum __SPI_TYPE{
	CPOL0_CPHA0,		// CLK  LOW,  1 age
	CPOL0_CPHA1,		// CLK  LOW,  2 age
	CPOL1_CPHA0,
	CPOL1_CPHA1,
}SPI_TYPE_E;

typedef struct _soft_spi_io {
	SPI_TYPE_E type;
	u8  (*MISO)(void);
	void (*MOSI)(u8 en);
	void (*CLK)(u8 en);
}Soft_SPI_hd;




#endif /* SPI_DRIVER_H_ */
