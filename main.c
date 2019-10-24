
#include "initialization_fun.h"

int main(){
/*
 * Initialization Functions :
 * 1- using Timer0 compare mode
 * 2- Adjust Port and enable Global Interrupt
 * 3- Initialization of Interrupt 0 and Interrupt 1
 * Interrupt 0 is used as reset
 * Interrupt 1 is used as stop
 *
 * */
	timer0_init_CTC_mode();
	port_init();
	Interrupt0_init ();
	Interrupt1_init ();

	while(1){

		if(reset_flag ==1){
			reset_timer();
		}

		 display_sec();
		 display_min();
		 display_hours();
	}

}

