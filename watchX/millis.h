/*
 * Project: Lightweight millisecond tracking library
 * Author: Zak Kemble, contact@zakkemble.co.uk
 * Copyright: (C) 2013 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: http://blog.zakkemble.co.uk/millisecond-tracking-library-for-avr/
 */

#ifndef MILLIS_H_
#define MILLIS_H_

typedef unsigned char millis8_t;
typedef unsigned int  millis_t;

#define millis() millis_get()

millis_t millis_get(void);

#ifdef ARDUINO
#define millis_init()
#else
void millis_init(void);
#endif

#endif /* MILLIS_H_ */
