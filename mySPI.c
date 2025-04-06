/*
 * mySPI.c
 *
 *  Created on: Mar 28, 2025
 *      Author: miros
 */

#include "stm32g474xx.h"
#include "stm32g4xx_hal.h"
#include "mySPI.h"

void SPI_Transmit (SPI_TypeDef* hspi, uint8_t* data, int size)
{
	if (size == 0) return;

	int i = 0;
	while (i<size)
	{
		while(!(hspi->SR&SPI_SR_TXE)) {};
		*(volatile uint8_t *)&hspi->DR = data[i];
	    i++;
	}

	while(!(hspi->SR&SPI_SR_TXE)) {};
	while((hspi->SR)&SPI_SR_BSY) {};
}

void SPI_Receive (SPI_TypeDef* hspi, uint8_t* data, int size)
{
	if (size == 0) return;

	while (size > 0)
	{
		while((hspi->SR)&SPI_SR_BSY) {};
		*(volatile uint8_t *)&hspi->DR = 0xFF;
		while(!(hspi->SR&SPI_SR_RXNE)) {};
		*data++ = (uint8_t)hspi->DR;
		size--;
	}

	while(!(hspi->SR&SPI_SR_TXE)) {};
	while((hspi->SR)&SPI_SR_BSY) {};
}

void SPI_Enable (SPI_TypeDef* hspi)
{
	hspi->CR1|=SPI_CR1_SPE;
}

void SPI_Disable (SPI_TypeDef* hspi)
{
	while(!(hspi->SR&SPI_SR_TXE)) {}
	while(hspi->SR&SPI_SR_BSY) {}
	hspi->CR1&=~SPI_CR1_SPE;
}

void SPI_Transmit_Receive (SPI_TypeDef* hspi, const uint8_t* tx_data, uint8_t* rx_data, int size)
{
	if (size == 0) return;

	while (size > 0)
	{
		while(!(hspi->SR&SPI_SR_TXE)) {}
		*(volatile uint8_t *)&hspi->DR = *(tx_data++);

		while(!(hspi->SR&SPI_SR_RXNE)) {}
		*(rx_data++) = (uint8_t)hspi->DR;

		size--;
	}

	while(!(hspi->SR&SPI_SR_TXE)) {};
	while((hspi->SR)&SPI_SR_BSY) {};
}
