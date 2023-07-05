
#include "STDTYPES.h"
#include "DIO_Interface.h"
#include "seven_segment_interface.h"
#include "Stop_Watch_interface.h"
#include "sev_seg_cfg.h"

u8 S_W_NUMBER=INIT;
u8 RESET_NUMBER=0;
u8 Pause_Resume_flag=0;
void Stop_watchinit(void)
{
	DIO_Init();
	DIO_WritePort(SEV_SEG_PORT,~sev_seg_Display_hex(INIT)<<PORT_SHIFT);
	DIO_WritePin(F_D,HIGH);
	DIO_WritePin(S_D,HIGH);
}

void Stop_WatchRunnable(u8 mode)
{
	while(mode==MOD)
	{
		if(DIO_ReadPin(IN_F_B)==LOW)
		{
			Increase_digit(DIG1);
			if(S_W_NUMBER%10==MIN)
			{
				S_W_NUMBER=S_W_NUMBER-MAX;
			}
			
		}
		if(DIO_ReadPin(IN_S_B)==LOW)
		{
			Increase_digit(DIG2);
			if(S_W_NUMBER/10==MAX)
			{
				S_W_NUMBER=S_W_NUMBER%MAX;
			}
			
		}
		sev_seg_display_multi(S_W_NUMBER);
		if(DIO_ReadPin(MODE_B)==LOW)
		{
			mode=RUN;
			RESET_NUMBER=S_W_NUMBER;
			break;
		}
	}
	while(mode==RUN)
	{
			while(Pause_Resume_flag==HIGH)
			{
				sev_seg_display_multi(S_W_NUMBER);
				if(S_W_NUMBER==MIN)
				{
					Stop_Watch_buzzer();
					while(DIO_ReadPin(RESET_B)==HIGH)
					{
						sev_seg_display_multi(S_W_NUMBER);
						if(DIO_ReadPin(MODE_B)==LOW)
						{
							mode=MOD;
							Pause_Resume_flag=LOW;
							break;
						}
					}
				}
				S_W_NUMBER--;
				while(DIO_ReadPin(PAUSE_RESUME_B)==LOW)
				{
					Pause_Resume_flag=LOW;
					sev_seg_display_multi(S_W_NUMBER);
				}
				stop_watch_reset();
				if(DIO_ReadPin(MODE_B)==LOW)
				{
					while(DIO_ReadPin(MODE_B)==LOW)
					{
						sev_seg_display_multi(S_W_NUMBER);
						mode=MOD;
					}
					Pause_Resume_flag=LOW;
					break;
				}
			}
			while(Pause_Resume_flag==LOW)
			{
				stop_watch_reset();
				sev_seg_display_multi(S_W_NUMBER);
				while(DIO_ReadPin(PAUSE_RESUME_B)==LOW)
				{
					Pause_Resume_flag=HIGH;
					sev_seg_display_multi(S_W_NUMBER);
				}
				
				if(DIO_ReadPin(MODE_B)==LOW)
				{
					while(DIO_ReadPin(MODE_B)==LOW)
					{
						sev_seg_display_multi(S_W_NUMBER);
						mode=MOD;
					}
					break;
				}
			}
			
		
	}
}

void Increase_digit(Digit_number dig)
{
	if(dig==DIG1)
	{
		S_W_NUMBER++;
	}
	else
	{
	    S_W_NUMBER+=MAX;	
	}
	
}


void Stop_Watch_buzzer(void)
{
	DIO_WritePin(BUZZER,HIGH);
}

void stop_watch_reset(void)
{
	if(DIO_ReadPin(RESET_B)==LOW)
	{
		S_W_NUMBER=RESET_NUMBER;
		Pause_Resume_flag=LOW;
	}
}