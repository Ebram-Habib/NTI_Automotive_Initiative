/*
 * SPI_config.h
 *
 *  Created on: Oct 30, 2023
 *      Author: Ebram Habib
 */

#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

typedef enum{
	SPI_MSB_FIRST,SPI_LSB_FIRST
}SPI_DATA_ORDER;

typedef enum{
	SPI_SLAVE,SPI_MASTER
}SPI_MASTER_SLAVE_SELECT;

typedef enum{
	SPI_IDLE_LOW,SPI_IDLE_HIGH
}SPI_CLOCK_POLARITY;

typedef enum{
	SPI_SAMPLE_FIRST,SPI_SETUP_FIRST
}SPI_CLOCK_PHASE;

typedef enum{
	SPI_NORMAL_SPEED_MODE,SPI_DOUBLE_SPEED_MODE
}SPI_SPEED_MODE;

typedef enum{
	SPI_NORMAL_SPEED_FCPU_DIVIDED_BY_4,
	SPI_NORMAL_SPEED_FCPU_DIVIDED_BY_16,
	SPI_NORMAL_SPEED_FCPU_DIVIDED_BY_64,
	SPI_NORMAL_SPEED_FCPU_DIVIDED_BY_128,
	SPI_DOUBLE_SPEED_FCPU_DIVIDED_BY_2,
	SPI_DOUBLE_SPEED_FCPU_DIVIDED_BY_8,
	SPI_DOUBLE_SPEED_FCPU_DIVIDED_BY_32,
	SPI_DOUBLE_SPEED_FCPU_DIVIDED_BY_64
}SPI_CLOCK_RATE_SELECT;


typedef struct{
	SPI_DATA_ORDER						spi_data_order;
	SPI_MASTER_SLAVE_SELECT				spi_master_slave_select;
	SPI_CLOCK_POLARITY 					spi_clock_polarity;
	SPI_CLOCK_PHASE 					spi_clock_phase;
	SPI_SPEED_MODE						spi_speed_mode;
	SPI_CLOCK_RATE_SELECT 				spi_clock_rate_select;
}SPI_INIT_CONFIG;

#define SPI_ENABLE	1
#define SPI_DISABLE	0


#endif /* SPI_CONFIG_H_ */
