/*
 * Project: N|Watch
 * Author: Zak Kemble, contact@zakkemble.co.uk
 * Copyright: (C) 2013 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: http://blog.zakkemble.co.uk/diy-digital-wristwatch/
 */
#include "common.h"

static void resetError(void)
{
#if WDT_ENABLE && WDT_DEBUG
  while(1)
  {
    wdt_update();
    buzzer_buzzb(200,TONE_5KHZ, VOL_UI);
    buzzer_buzzb(200,TONE_2_5KHZ, VOL_UI);
    buzzer_buzzb(200,TONE_3KHZ, VOL_UI);
  }
#endif
}

void c_setup()
{
  // OSCCAL = 71;

#if CPU_DIV != clock_div_1
  clock_prescale_set(CPU_DIV);
#endif

  // power_twi_disable();
  // power_usart0_disable();
  // power_timer0_disable();
  // power_timer1_disable();
  // power_timer2_disable();
  // power_adc_disable();

#if PIN_DEBUG != PIN_DEBUG_NONE
  pinMode(PIN_DEBUG_PIN, OUTPUT);
#endif

  // Everything else
  global_init();
  spi_init();
  i2c_init();
  adc_init();
  appconfig_init();
  led_init();
  buzzer_init();
  battery_init();
  buttons_init();
  millis_init();
  rtc_init();
  pwrmgr_init();
  time_init();
  alarm_init();
  oled_init();

	if(wdt_wasReset())
    resetError();
	//else if(!appconfig_check())
	//  configError();

	// Startup buzz and flash
	buzzer_buzz(200, TONE_4KHZ, VOL_UI, PRIO_UI, NULL);
	led_flash(LED_GREEN, 50, 255);

	// Set watchface
	display_set(watchface_normal);
	display_load();
}

void c_loop()
{
  time_update();
  if(pwrmgr_userActive())
  {
    battery_update();
    buttons_update();
  }

  buzzer_update();
  led_update();
#if COMPILE_STOPWATCH
  stopwatch_update();
#endif
  global_update();

  if(pwrmgr_userActive())
  {
    alarm_update();
    display_update();
  }

  // freeRAM();
  wdt_update();

  pwrmgr_update();
}

