/*
 * Stop_Watch_interface.h
 *
 * Created: 3/30/2023 4:28:07 PM
 *  Author: abdo
 */ 


#ifndef STOP_WATCH_INTERFACE_H_
#define STOP_WATCH_INTERFACE_H_

#define MODE_B PIND4
#define PAUSE_RESUME_B PIND2
#define RESET_B PIND3

#define IN_F_B PIND2
#define IN_S_B PIND3

#define INIT 0
#define MAX 10
#define MIN 0
#define BUZZER PINC5
typedef enum{
	MOD,
	RUN
}Stop_Watch_status;

typedef enum{
	DIG1,
	DIG2,
	TOTAL_DIG
	}Digit_number;

void Stop_watchinit(void);
void Stop_WatchRunnable(u8 mode);
void Increase_digit(Digit_number dig);
void Stop_Watch_buzzer(void);
void stop_watch_reset(void);
#endif /* STOP_WATCH_INTERFACE_H_ */