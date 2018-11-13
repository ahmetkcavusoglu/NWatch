/*
 * Project: N|Watch
 * Author: Zak Kemble, contact@zakkemble.co.uk
 * Copyright: (C) 2013 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: http://blog.zakkemble.co.uk/diy-digital-wristwatch/
 */

// LED control

#include "common.h"

#ifdef __AVR_ATmega32U4__
#ifndef power_timer4_enable
#define power_timer4_enable()  (PRR1 &= (uint8_t)~(1 << 4)) // PRTIM4
#endif
#ifndef power_timer4_disable
#define power_timer4_disable() (PRR1 |= (uint8_t) (1 << 4)) // PRTIM4
#endif
#endif

// Registers and stuff
#ifdef __AVR_ATmega32U4__
#define RED_CCR    TCCR4C
#define RED_OCR		 OCR4D
#define RED_COM		 COM4D0
#define RED_PIN		 PD7
#define RED_PORT   PORTD
#define GREEN_CCR  TCCR4A
#define GREEN_OCR	 OCR4A
#define GREEN_COM	 COM4A1
#define GREEN_PIN	 PC7
#define GREEN_PORT PORTC
#else
#define RED_CCR    TCCR0A
#define RED_OCR		 OCR0A
#define RED_COM		 COM0A1
#define RED_PIN		 PD6
#define RED_PORT   PORTD
#define GREEN_CCR  TCCR0A
#define GREEN_OCR	 OCR0B
#define GREEN_COM	 COM0B1
#define GREEN_PIN	 PD5
#define GREEN_PORT PORTD
#endif

typedef struct {
	byte flashLen;			// How long to light up for
	millis8_t startTime;	// 
}led_s;

static led_s ledRed;
static led_s ledGreen;

void led_init()
{
	// Setup timers
#ifdef __AVR_ATmega32U4__
	LOAD_BITS(TCCR4A, PWM4A); // PWM4A
	LOAD_BITS(TCCR4B, CS43);  // CK/128
  LOAD_BITS(TCCR4C, PWM4D); // PWM4D
	power_timer4_disable();

	// Setup pins
	pinMode(C7, OUTPUT);
	pinMode(D7, OUTPUT);
	pinWrite(C7, LOW);
	pinWrite(D7, LOW);
#else
	LOAD_BITS(TCCR0A, WGM01, WGM00); // PWM0A
	LOAD_BITS(TCCR0B, CS01, CS00);   // 1/64
	power_timer0_disable();

	// Setup pins
	pinMode(D5, OUTPUT);
	pinMode(D6, OUTPUT);
	pinWrite(D5, LOW);
	pinWrite(D6, LOW);
#endif
}

static void flash(led_s* led, byte len, byte brightness, volatile byte* ccr, volatile byte* ocr, byte com, volatile byte* port, byte pin)
{
  led->flashLen = len;
  led->startTime = millis();

  if(brightness == 255 || brightness == 0)
  {
    *ccr &= ~com;
    brightness == 255 ? (*port |= pin) : (*port &= ~pin);
  }
  else
  {
#ifdef __AVR_ATmega32U4__
    power_timer4_enable();
#else
    power_timer0_enable();
#endif
    *ccr |= com;
    *ocr = brightness;
  }
}

void led_flash(led_t led, byte len, byte brightness)
{
  switch(led)
  {
    case LED_RED:
      flash(&ledRed, len, brightness, &RED_CCR, &RED_OCR, _BV(RED_COM), &RED_PORT, _BV(RED_PIN));
      break;
    case LED_GREEN:
      flash(&ledGreen, len, brightness, &GREEN_CCR, &GREEN_OCR, _BV(GREEN_COM), &GREEN_PORT, _BV(GREEN_PIN));
      break;
    default:
      break;
  }

  pwrmgr_setState(PWR_ACTIVE_LED, PWR_STATE_IDLE);
}

// Is an LED on?
BOOL led_flashing()
{
	return ledRed.flashLen || ledGreen.flashLen;
}

static BOOL update(led_s* led, volatile byte* ccr, byte com, volatile byte* port, byte pin)
{
	if(led->flashLen && (millis8_t)(millis() - led->startTime) >= led->flashLen)
	{
    *ccr &= ~com;
		*port &= ~pin;
		led->flashLen = 0;
	}

	return led->flashLen;
}

void led_update()
{
	BOOL red = update(&ledRed, &RED_CCR, _BV(RED_COM), &RED_PORT, _BV(RED_PIN));
	BOOL green = update(&ledGreen, &GREEN_CCR, _BV(GREEN_COM), &GREEN_PORT, _BV(GREEN_PIN));

	if(!red && !green)
	{
		// Timer no longer in use, disable
#ifdef __AVR_ATmega32U4__
    power_timer4_disable();
#else
		power_timer0_disable();
#endif
		pwrmgr_setState(PWR_ACTIVE_LED, PWR_STATE_NONE);
	}
}

// Turn off LEDs
void led_stop()
{
	led_flash(LED_GREEN, 0, 0);
	led_flash(LED_RED, 0, 0);
	led_update();
}
