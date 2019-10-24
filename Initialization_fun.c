#include "Common_macros.h"
#include "micro_config.h"
#include "std_types.h"

#define observation_delay 2


uint8 g_seconds ;
uint8 g_minutes ;
uint8 g_hours ;
uint8 g_tick ;
uint8 reset_flag ;
uint8 stop_flag =0 ;



ISR(TIMER0_COMP_vect)
{
	if(stop_flag ==0 ){
	g_tick++;
	}

}


void port_init(void){

	 SET_BIT(SREG,7);
	 SET_PORT(DDRC,0x0F);
	 SET_PORT(DDRA,0x3F);
}
void timer0_init_CTC_mode(void)
{
	TCNT0 = 0; //timer initial value
	OCR0  = 250; //compare value
	 //enable compare interrupt
	/* Configure timer0 control register
	 * 1. Non PWM mode FOC0=1
	 * 2. CTC Mode WGM01=1 & WGM00=0
	 * 3. No need for OC0 in this example so COM00=0 & COM01=0
	 * 4. clock = F_CPU/1024 CS00=1 CS01=0 CS02=1
	 */
	SET_BIT(TIMSK,OCIE0);
	SET_BIT(TCCR0,FOC0);
	SET_BIT(TCCR0,WGM01);
	SET_BIT(TCCR0,CS02);
	SET_BIT(TCCR0,CS00);
}





void display_sec(void){

	if(g_tick==4){
				g_seconds ++ ;
				g_tick = 0;
			}
	if(g_seconds == 60){
					g_seconds = 0 ;
					g_minutes ++ ;
				}
	else{
		    SET_PORT(PORTA,1) ;
		    SET_PORT(PORTC , (g_seconds%10));
			_delay_ms(observation_delay);
			SET_PORT(PORTA,2) ;
			SET_PORT(PORTC , (g_seconds/10));
			_delay_ms(observation_delay);

			}
		}


void display_min(void){

	if(g_minutes == 60){
						g_minutes = 0 ;
						g_hours ++ ;
					}
		else{

				SET_PORT(PORTA,4) ;
				SET_PORT(PORTC , (g_minutes %10));
				_delay_ms(observation_delay);
				SET_PORT(PORTA,8) ;
				SET_PORT(PORTC, (g_minutes/10));
				_delay_ms(observation_delay);

				}
	}

void display_hours(void){

	if(g_hours == 24){
                        g_seconds = 0 ;
						g_minutes = 0 ;
						g_hours = 0 ;
					}
		else{

				SET_PORT(PORTA,16) ;
				SET_PORT(PORTC , (g_hours %10));
				_delay_ms(observation_delay);
				SET_PORT(PORTA,32) ;
				SET_PORT(PORTC,(g_hours/10));
				_delay_ms(observation_delay);

				}
	}


void reset_timer(void){

	g_seconds =0 ;
	g_minutes =0;
	g_hours =0;
	g_tick =0;
	reset_flag =0 ;

}


void Interrupt0_init (void){

	/* Make the pin as input and activate internal pull_up resistor */

	CLEAR_BIT(DDRD,2);
	SET_BIT(PORTD,2);
	/* Set interrupt0 bits as Falling edge  */

	SET_BIT(SREG,7);
	SET_BIT(GICR,6);
	SET_BIT(MCUCR, ISC01);
	CLEAR_BIT(MCUCR, ISC00);

}

void Interrupt1_init (void){

	/* Make the pin as input and activate internal pull_up resistor */

	CLEAR_BIT(DDRD,3);
	SET_BIT(PORTD,3);
	/* Set interrupt1 bits as Falling edge */

	SET_BIT(SREG,7);
	SET_BIT(GICR,7);
	SET_BIT(MCUCR, ISC11);
		CLEAR_BIT(MCUCR, ISC10);

}



ISR(INT0_vect){

	reset_flag=1 ;

}
ISR(INT1_vect){

	if(stop_flag==0){
		stop_flag=1 ;
	}
	else{
		stop_flag=0;
	}

}
