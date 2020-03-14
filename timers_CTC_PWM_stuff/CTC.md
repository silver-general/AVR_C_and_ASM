## STUFF YOU NEED TO SET
I took notes while programming, that's why there are comment symbols.  
The idea is to set it up to play sounds from 30 to 7.8kHz.  
I still have to figure out how precisely floats are handled, I need to study a bit more of assembly.

// CTC: STUFF YOU NEED TO SET

// output pin: set pin PBn in DDRB
// -> DDRB |= 1<<PB0; (PB0 is the one where OC0A is located. physically: pin 5)

// compare match mode (tab 11.2)
// in TCCR0A set bits COM01A/COM01B, COM0A0/COM0B0
// 0,0 normal, 0,1 toggle, 1,0 clear, 11 set -> use toggle for CTC sounds
TCCR0A |= 1<<COM0A0;

// WAVEFORM GENERATION (tab 11.5)
// in TCCR0B set WGM02, in TCCR0A set WGM01, WGM00
// normal, phase correct PWM, CTC, fast PWM, reserved, phase correct PWM, reserved, fast PWM NOTE: some have OCR0A as TOP, some have 0xFF
// -> obviously CTC
TCCR0A |= 1<<WGM01;

// COMPARE THRENHOLD OCR0n: frequency can be up to half max value (keeping 50% duty cycle)
// to have a frequency f: OCR0A = clk/(2*N*f) - 1
OCR0A = 17;// actually: 16.7556... for default: 440Hz, A4

// CLOCK PRESCALER SELECT
// in TCCRB set CS02,CS01,CS00 
// waveform frequency = clk / (2*N*(1+OCRnx))
// -> max frex at OCRnx = 0, min freq at OCRnx = 255
// N = 1,8,64,256,1024 the f_min and f_max are: (N,fmin,fmax) = (1,500kHz,1.95kHz),(8,62.5kHz,244Hz),(64,7.81kHz,30Hz),(256,1.95kHz,7.63Hz),(1024,488Hz,1.91Hz)
// -> for human audible sounds: N=64	
TCCR0B |= (1<<CS01 | 1<<CS00); // activate it, test for a sec
_delay_ms(1000);
TCCR0B &= ~(1<<CS02|1<<CS01|1<<CS00); // deactivate it

// INTERRUPTS
// set the output compare A interrupt
// handle interrupts with ISR(TIMER0_COMPA_vect) { do stuff }
TIMSK |= 1<<OCIE0A;
// set external interrupts (BEFORE THE PRESCALER?!?!?!?)
sei();
