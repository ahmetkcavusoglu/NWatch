/*
 * Project: N|Watch
 * Author: Zak Kemble, contact@zakkemble.co.uk
 * Copyright: (C) 2013 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: http://blog.zakkemble.co.uk/diy-digital-wristwatch/
 */

// SPI driver

#include "common.h"

#ifdef __AVR_ATmega32U4__
#define MISO	B3
#define MOSI	B2
#define SCK		B1
#define SS		B0
#else
#define MISO	B4
#define MOSI	B3
#define SCK		B5
#define SS		B2
#endif

static void init(void)
{
  SPCR = _BV(SPE)|_BV(MSTR);
  SPSR = _BV(SPI2X);
}

void spi_init()
{
	pinMode(SS, OUTPUT);
	pinMode(MOSI, OUTPUT);
	pinMode(SCK, OUTPUT);
	pinPullup(MISO, PU_EN);
	pinWrite(SS, HIGH);

	init();
	
	spi_disable();
}

void spi_enable()
{
	power_spi_enable();
	init(); // Datasheet says to re-initialize after waking up
}

void spi_disable()
{
	power_spi_disable();
}

byte spi_transfer(byte data)
{
  SPDR = data;
  loop_until_bit_is_set(SPSR, SPIF);
  return SPDR;
}

void spi_transfer_nr(byte data)
{
  SPDR = data;
  loop_until_bit_is_set(SPSR, SPIF);
}
