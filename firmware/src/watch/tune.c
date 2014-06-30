/*
 * Project: N|Watch
 * Author: Zak Kemble, contact@zakkemble.co.uk
 * Copyright: (C) 2014 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: http://blog.zakkemble.co.uk/diy-digital-wristwatch/
 */

#include "common.h"

#warning "dont forget me"
#include "apps/screenshot.h"

#if TUNEMEM_TYPE == TUNEMEM_PROGMEM
#define tune_read(x) (pgm_read_word(&x))
#elif TUNEMEM_TYPE == TUNEMEM_EEPROM
#define tune_read(x) (eeprom_read_word((const uint16_t*)&x))
#else
#define tune_read(x) (x)
#endif

static byte idx;
static const tune_t* tune;
static vol_t vol;
static tonePrio_t prio;

static void next(void);

void tune_play(const tune_t* _tune, vol_t _vol, tonePrio_t _prio)
{
#if COMPILE_SCREENSHOT
	screenshot_do();
#endif

	if(_prio < prio)
		return;
	prio = _prio;
	tune = _tune;
	vol = _vol;
	idx = 0;
	next();
}

void tune_stop(tonePrio_t _prio)
{
	buzzer_buzz(0, TONE_STOP, VOL_OTHER, _prio, NULL);
	prio = PRIO_MIN;
}

static void next()
{
	uint data = tune_read(tune[idx++]);
	byte len = data;
	if(len != TONE_REPEAT)
	{
		buzzer_buzz(len, (tone_t)(data>>8), vol, prio, next);
		if(len == TONE_STOP)
			prio = PRIO_MIN;
	}
	else
	{
		idx = 0;
		next();
	}
}