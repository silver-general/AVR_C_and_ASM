## TERRIBLE ARPEGGIATOR

First try at making sounds using CTC (clear timer on compare, 50% duty cycle, variable frequency wave).  
I am using timer counter 0, OCR0A as output compare register (determines frequency), PB0 as out (same as OC0A, physical pin 5).  
See CTC.c for theory and a bit of code all in a place.


```
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "C:\Users\Agnese\Documents\Atmel Studio\7.0\personal_libraries\my_CTC.c"
#define DELAY 150

void CTC_init();
int CTC_start();
int CTC_stop();
int CTC_set_freq(float freq);

int main (void)
{
	CTC_init();
	CTC_set_freq(110);
		
	while (1)
	{
	CTC_set_freq(110);
	CTC_start();
	_delay_ms(DELAY);
	
	CTC_set_freq(220);
	_delay_ms(DELAY);

	CTC_set_freq(415);
	_delay_ms(DELAY);

	/*CTC_stop();
	_delay_ms(DELAY);
*/
	}
return 0;
}

ISR(TIMER0_COMPA_vect)
{ // update frequency: 
// for now, nothing to do here
}

void CTC_init()
{  // default: usa PB0 
	DDRB |= 1<<PB0; // PB0 (OCA0) as output
	TCCR0A |= 1<<COM0A0; // toggle on match
	TCCR0A |= 1<<WGM01; // CTC selection
	OCR0A = 17; // default note: A4
	TCCR0B |= (1<<CS01 | 1<<CS00); // this prescaler gives a range 30.517Hz-7.8125kHz, that is: 31-7812
	
	TIMSK |= 1<<OCIE0A; // set an interrupt for output compare match
	sei(); // set external interrupts

/* IN CASE YOU NEED TO TEST IT
	TCCR0B |= (1<<CS01 | 1<<CS00); // activate it, test for a sec
	_delay_ms(1000);
	TCCR0B &= ~(1<<CS02|1<<CS01|1<<CS00); // deactivate it
*/	
}


int CTC_start()
{ 
	TCCR0B |= (1<<CS01 | 1<<CS00);
	return 0;
}

int CTC_stop()
{
	TCCR0B &= ~(1<<CS02|1<<CS01|1<<CS00);
	return 0;
}


int CTC_set_freq(float freq) //freq from 31 to 7811 (7812 to make 0 for OCR0A
{ // QUESTION: HOW SLOW IS USING A FLOAT? ALTERNATIVES?
	if (freq>31 && freq < 7812) 
	{
		OCR0A = (7812.5/freq)-1; // NOTE: can't reproduce A4 with a perfect freq==440. it's less, why?
	}
	return 0;
}

```
