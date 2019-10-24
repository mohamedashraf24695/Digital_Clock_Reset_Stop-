
#ifndef INITIAL_FUN_H

#define  INITIAL_FUN_H

#include "Common_macros.h"
#include "micro_config.h"
#include "std_types.h"



extern uint8 g_tick;
extern uint8 g_seconds ;
extern uint8 g_minutes ;
extern uint8 g_hours ;
extern uint8 reset_flag ;
extern uint8 stop_flag ;


void display_sec(void);
void display_min(void);
void display_hours(void);
void timer0_init_CTC_mode(void);
void port_init(void);
void reset_timer(void);
void Interrupt0_init (void);
void Interrupt1_init (void);


#endif
