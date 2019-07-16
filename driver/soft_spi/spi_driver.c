/*
 * spi_driver.c
 *
 *  Created on: 2019年6月15日
 *      Author: youyou
 */

#include "spi_driver.h"


static unsigned char soft_spi_tx_rx_byte(Soft_SPI_hd *hd, unsigned char s_dat);
static void soft_spi_send_buf(Soft_SPI_hd *hd, const unsigned char *buf, unsigned int len);
static void soft_spi_read_buf(Soft_SPI_hd *hd, unsigned char *buf, unsigned int len);

static volatile unsigned int delay_cnt_g = 0;
static void soft_spi_delay(unsigned int delay)
{
	unsigned int tmp = delay;
	while(delay--);
	delay_cnt_g = tmp;
}
static unsigned char soft_spi_tx_rx_byte(Soft_SPI_hd *hd, unsigned char s_dat)
{
	unsigned char i = 0;
	unsigned char r_dat = 0;
	if(hd->type == CPOL0_CPHA0){
		hd->CLK(0);
		soft_spi_delay(delay_cnt_g);
		for(;i<8;i++){
			if(s_dat & (0x80 >> i)){
				hd->MOSI(1);
			}else{
				hd->MOSI(0);
			}
			soft_spi_delay(delay_cnt_g);
			hd->CLK(1);
			soft_spi_delay(delay_cnt_g);

			r_dat <<= 1;
			if(hd->MISO()) r_dat++;

			hd->CLK(0);
			soft_spi_delay(delay_cnt_g);
		}
	}
	if(hd->type == CPOL0_CPHA1){
		hd->CLK(0);
		soft_spi_delay(delay_cnt_g);
		for(;i<8;i++){
			hd->CLK(1);
			soft_spi_delay(delay_cnt_g);
			if(s_dat & (0x80 >> i)){
				hd->MOSI(1);
			}else{
				hd->MOSI(0);
			}
			soft_spi_delay(delay_cnt_g);
			hd->CLK(0);
			r_dat <<= 1;
			if(hd->MISO()) r_dat++;
			soft_spi_delay(delay_cnt_g);
		}
	}
	if(hd->type == CPOL1_CPHA0){
		hd->CLK(1);
		soft_spi_delay(delay_cnt_g);
		for(;i<8;i++){
			if(s_dat & (0x80 >> i)){
				hd->MOSI(1);
			}else{
				hd->MOSI(0);
			}
			soft_spi_delay(delay_cnt_g);
			hd->CLK(0);
			soft_spi_delay(delay_cnt_g);
			r_dat <<= 1;
			if(hd->MISO()) r_dat++;
			hd->CLK(1);
			soft_spi_delay(delay_cnt_g);
		}
	}
	if(hd->type == CPOL1_CPHA1){
		hd->CLK(1);
		soft_spi_delay(delay_cnt_g);
		for(;i<8;i++){
			hd->CLK(0);
			soft_spi_delay(delay_cnt_g);
			if(s_dat & (0x80 >> i)){
				hd->MOSI(1);
			}else{
				hd->MOSI(0);
			}
			soft_spi_delay(delay_cnt_g);
			hd->CLK(1);
			r_dat <<= 1;
			if(hd->MISO()) r_dat++;
			soft_spi_delay(delay_cnt_g);
		}
	}
	return r_dat;
}

static void soft_spi_send_buf(Soft_SPI_hd *hd, const unsigned char *buf, unsigned int len)
{

	const unsigned char *ptr = buf;
	if(len == 0) return;
	while(len--){
		soft_spi_tx_rx_byte(hd,*ptr++);
	}
}
static void soft_spi_read_buf(Soft_SPI_hd *hd, unsigned char *buf, unsigned int len)
{

	unsigned char *ptr = buf;
	if(len == 0) return;
	while(len--){
		*ptr++ = soft_spi_tx_rx_byte(hd, 0xFF);
	}
}










