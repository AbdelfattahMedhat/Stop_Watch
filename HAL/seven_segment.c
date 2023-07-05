#define F_CPU 8000000
#include <util/delay.h>
#include "STDTYPES.h"
#include "DIO_Interface.h"
#define SEVEN_SEGMENT_ARRAY
#include "seven_segment_private.h"
#include "seven_segment_interface.h"
#include "sev_seg_cfg.h"

u8 sev_seg_Display_hex(u8 n)
{
	return seven_segment[n];	
}

void sev_seg_display_multi(u8 number)
{
	u8 F_dig=number%10;
	u8 S_dig=number/10;
	for(u8 i=0;i<20;i++)
	{
		DIO_WritePin(F_D,HIGH);
		DIO_WritePort(SEV_SEG_PORT,~sev_seg_Display_hex(F_dig)<<(PORT_SHIFT));
		_delay_ms(DELAY);
		DIO_WritePin(F_D,LOW);
		DIO_WritePin(S_D,HIGH);
		DIO_WritePort(SEV_SEG_PORT,~sev_seg_Display_hex(S_dig)<<(PORT_SHIFT));
		_delay_ms(DELAY);
		DIO_WritePin(S_D,LOW);
	}
	
}