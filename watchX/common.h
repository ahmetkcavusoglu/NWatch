/*
 * Project: N|Watch
 * Author: Zak Kemble, contact@zakkemble.co.uk
 * Copyright: (C) 2013 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: http://blog.zakkemble.co.uk/diy-digital-wristwatch/
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <avr/io.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <util/twi.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "config.h"
#include "util.h"
#include "typedefs.h"
#include "debug.h"

#include "wdt.h"
#include "spi.h"
#include "i2c.h"
#include "rtc.h"
#include "adc.h"
#include "oled.h"
#include "buttons.h"
#include "battery.h"
#include "buzzer.h"
#include "led.h"
#include "ds3231.h"
#include "millis.h"
#include "functions.h"
#include "alarms.h"
#include "diag.h"
#include "m_display.h"
#include "games.h"
#include "timedate.h"
#include "settings.h"
#include "sleep.h"
#include "sound.h"
#include "m_main.h"
#include "game1.h"
#include "game2.h"
#include "stopwatch.h"
#include "torch.h"
#include "screenshot.h"
#include "normal.h"
#include "lowbatt.h"
#include "ui.h"

#include "system.h"
#include "global.h"
#include "display.h"
#include "time.h"
#include "alarm.h"
#include "pwrmgr.h"
#include "appconfig.h"
#include "disco.h"
#include "tune.h"
#include "animation.h"
#include "draw.h"
#include "menu.h"

#include "lang.h"
#include "tunes.h"
#include "discos.h"
#include "resources.h"

#endif /* COMMON_H_ */
