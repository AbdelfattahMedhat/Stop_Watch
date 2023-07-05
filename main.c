#define F_CPU 8000000
#include <util/delay.h>
#include "STDTYPES.h"
#include "mem_map.h"
#include "Utils.h"
#include "seven_segment_interface.h"
#include "Stop_Watch_interface.h"

int main(void)
{
	Stop_watchinit();
	u8 mode=MOD;
    while (1) 
    {
		Stop_WatchRunnable(mode);
    }
}

