/*
 * mySPI.h
 *
 *  Created on: Mar 28, 2025
 *      Author: miros
 */

#ifndef SPI_MYSPI_H_
#define SPI_MYSPI_H_

void SPI_Init (void);
void SPI_Enable (SPI_TypeDef* hspi);
void SPI_Disable (SPI_TypeDef* hspi);
void SPI_Transmit (SPI_TypeDef* hspi, uint8_t* data, int size);
void SPI_Receive (SPI_TypeDef* hspi, uint8_t* data, int size);
void SPI_Transmit_Receive (SPI_TypeDef* hspi, const uint8_t* tx_data, uint8_t* rx_data, int size);

#endif /* SPI_MYSPI_H_ */
