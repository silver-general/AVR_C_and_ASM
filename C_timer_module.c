/*
LET'S INITIALIZE THE TIMER 0 AND COMMENT EVERYTHING WITH DATASHEET INFO
*/

// SELECT WAVEFORM GENERATION (tab 11.5 for all modes)
	//	WGM02 (TCCR0B),	WGM01 (TCCR0A),	WGM00 (TCCR0A),	MODE,	TOP,	update OCRx,	TOV flag set,
	//	0				0				0				normal
	// ...
	// MODES: normal; PWM phase correct, CTC, fast PWM, reserved,PWM phase correct, reserved, fastPWM
	// -> fast PWM with OCRx at TOP (so that OCR0A determines the duty cycle): 1,1,1 
	TCCR0B |= 1<<WGM02;
	TCCR0A |= 1<<WGM01 | 1<<WGM00;
	
	// DUTY CYCLE SELECT: OCR0A (see pinout) (CAN I USE OCR0B????)--------------------???
	// -> set OCR0A, the output compare register as a fraction of TOP value.
	OCR0A = (duty/100)*255;	
	
	// SELECT TOGGLE MODE FOR OCR0A in TCCR0A (tab11.2) 
	//	COM0A1/COM0B1	COM0A0/COM0B0	description
	//	0				0				disconnected	
	//									toggle COM0xn on compare match
	//									clear
	//									set	
	TCCR0A |= (1<<COM0A1); // "toggle"
	
	
	// SELECT FAST PWM OUTPUT PIN 
	// avaiable pins: see pinout. OC0A (or OC0B???) -----------------------------???
	DDRB |= (1 << PB0);	// sets PB0 (pin 0 of PINB register) as output, that is also the pin for OC0A

	
	// INTERRUPTS
	
	// activate the inturrupt. it will happen when timer counter 0 overflows
	TIMSK |= 1<<TOIE0;
	// set external interrupts (BEFORE THE PRESCALER. reason: see datasheet)
	sei();
	
	
	// PRESCALER SELECTION
	
	// frequency of fast PWM: f = clk / 256*N, with clk = 1MHz for attiny85 with default fuse
	//see table 11.6
	// 7 modes, ascending number. 5 for internal clok (see below), 2 for external	
	// CS00, CS01, CS02 in TCCR0B	:	N, frequency=clk/(256*N), period=1/frequency
		// 0,0,0 :	N=0, stop timer
		// 0,0,1 :	N=1, 3.91kHz, 0.256ms
		//			N=8, 488Hz, 2.05ms
		//			N=64, 61.0Hz, 16.3ms		-> good for fost servos (50Hz and duty 1-2ms, neutral 1.5ms)
		//			N=256 15.2Hz, 65.5ms
		//			N=1024 1024, 3.81Hz, 262
		//			external clk on T0 pin. clock on falling edge
		//			external clk on T0 pin. clock on rising edge.
	TCCR0B &= ~(1<<CS00 |1<<CS01 | 1<<CS02); // 0,0,0 stops everything
	
	while (1)
	{
		duty += 10; if (duty>100) { duty=10; }
		_delay_ms(100);
	}

	return 1;
}


// do something during the interrupt. does this work with attiny85?
ISR(TIMER0_OVF_vect)
{
	OCR0A = (duty/100)*255;
}
