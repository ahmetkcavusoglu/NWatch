/*
 * Project: N|Watch
 * Author: Zak Kemble, contact@zakkemble.co.uk
 * Copyright: (C) 2013 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: http://blog.zakkemble.co.uk/diy-digital-wristwatch/
 */

#ifndef SPI_H_
#define SPI_H_

void spi_init(void);
void spi_enable(void);
void spi_disable(void);

void spi_transfer_nr(byte data);
byte spi_transfer(byte data);


#endif /* SPI_H_ */
