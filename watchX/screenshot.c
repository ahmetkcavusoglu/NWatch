/*
 * Project: N|Watch
 * Author: Zak Kemble, contact@zakkemble.co.uk
 * Copyright: (C) 2014 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: http://blog.zakkemble.co.uk/diy-digital-wristwatch/
 */

#include "common.h"

#if COMPILE_SCREENSHOT

void screenshot_send()
{
//	byte b;
//	if(!uart_get_nb(&b) || (char)b != 's')
//		return;

	for(uint i=0;i<FRAME_BUFFER_SIZE;i++)
		uart_put(oledBuffer[i]);
}

#endif
