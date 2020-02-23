## GUIDES AND REFERENCES

### PWM on attiny85
https://www.electroschematics.com/attiny85-pwm-primer-tutorial-using-arduino/

attiny85 has 2 timers. the timer counter 0 is used for the delay function (how??), so better use the timer counter 1.

## Timer/Counter0
* general purpose 8-bit 
* 2 independent output compare units
* PWM

### registers
* TCNT0
* OCR0A, OCR0B
* TIFR

### constant definitions
* BOTTOM 0x00
* MAX 0xFF (decimal 255)
* TOP (set by user in OCR0A register. default is decimal 255)

### prescaler and clock sources
* TCCR0B timer/counter0 control register has "clock select bits" that can be set to select clock source. NOTE: the fuses are set to prescale 8MHz/8=1MHz the internal clock, but the timer counter can be set differently!
* external clock: another time.

### 11.4 counter unit, page 64
note: timer counter overflow flag TOV0/TOV1 generate interrupts when counter0/counter1 overflow (reach beyond 255, the time is scaled with the frequency scaling. if the count uses the clock, after 255ns. if the clock is scaled clk/1024, every tick is 1024ns, and an overflow occurs after 255 ticks = 261120ns = 261ms

### 11.5 output compare unit
* set output goals with the output compare registers OCR0A and OCR0B
* when TCNT0 equals one of the two, the comparator signals a match with a flag, Output Compare Flag OCF0A or OCF0B at the next timer clock cycle
* if the corresponding interrupt is enabled: interruption!
* ... more about comparisons

## 11.7 MODES
* default: normal mode
* modes are set by setting bits in the registers Waveform Generation Mode WGM0[2:0] (does not affect counting sequece) and Compare Output mode COM0x[1:0] (affects the counting mode)
* SEE DIAGRAMS ON PAGE 76

### 11.7.1 Normal Mode
it's the default.
* counts up to TOP (the one set by user, default 255), then overflows (TOV0 is set in the same clock cycle of the overflow), and if enabled an interrupt occurs

### 11.7.2 Clear Timer on Compare (CTC) mode
the register OCR0A (output compare register A) is used to manupulate the counter resolution
* when timer counter register TCNT0 matches the output compare register0 OCR0A, timer counter is reset to zero. 
* is the interrupt is enabled, OCF0A Flag is set when TCNT0 matches TOP. 
* during the interrupt, the TOP can be updated. this creates a waveform!
** waveform max frequency: page 72
QUESTION: why use OCR0A and OCR0B? why two of them fir timer counter 0?

### 11.7.3 fast PWM
* "fast" because it uses a single slope operation: ?????
* this creates a frequency twice as high as the normal 2-sloped PWM
* high frequences are useful for power regulation, rectification, DAC applications. they also allow small sized components (coils, capacitors) because ..... ????? SOMETHING ABOUT CONTINUITY OF CURENT, LOOK IT UP!
* timer counter TCNT0 increases until it matches OCR0A/OCR0B
* the timer/counter0 overflow flag TOV0 is set when TCNT0 reaches TOP. if interrupts are enabled, the TOP can be updated.
* in fast PWM, a PWM is generated in OC0x pins (OC0A or OC0B, output compare units)
** non inverted PWM: set .... page 73
** inverted: ... page 73

* the actual PWM is seen on OC0x port pin is it's set as output.
* PWM frequency: page 74

### 11.7.4 phase correct PWM
* Dual slope PWM
* set with ... page 74


## 11.9 REGISTERS

### 11.9.1 GTCCR General Timer/Counter Control Register


## timer counter 2

DA FARE: CONTROLLA COME USARE PWM PER TIMER COUNTER 1, DAT ìO CHE TIMER COUNTER 0 SI USA PER LA FUNZIONE DELAY!
DA FARE: schematizza https://www.youtube.com/watch?v=O_Yqf_cugwE
