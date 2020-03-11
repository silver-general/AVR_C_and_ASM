### guide 1
http://maxembedded.com/2011/06/the-adc-of-the-avr/

### 
https://maker.pro/custom/tutorial/how-to-take-analog-readings-with-an-avr-microcontroller

```
/*	SETTINGS FOR ADC	*/	

// voltage reference: bits REFS[2:0] in ADMUX
	ADMUX &= ~(1<<REFS0 | 1<<REFS1 | 1<<REFS2); //default: 0,0,0, Vcc
// select analogue input and differential gain: bits MUX[3:0] in ADMUX
	// this is for single ended conversion, value is Vin*1024/Vref
	ADMUX &= ~(1<<MUX0 | 1<< MUX1 |1<<MUX2); //ADC0, or PB0, physical pin 1: 0,0,0	
// enable ADC
	ADCSRA |= 1<< ADEN;
// left adjustment if needed: set ADLAR in ADMUC
	ADMUX &= ~(1<<ADLAR); // let's keep it right 

// START SINGLE CONVERSION, OR START AUTOTRIGGERING CONVERSIONS (I'll do it later)
//	ADCSRA |= 1<<ADSC;

// AUTO TRIGGER CONVERSION
// enable auto trigger
	ADCSRA |= 1<<ADATE;
// select trigger signal: bits ADTS[2:0] in ADCSRB. default: free running, 0,0,0
	ADCSRB &= ~(1<<ADTS0 | 1<<ADTS1 | 1<<ADTS2); 	

//prescaler
	// first conversion: 25ADCclk. following conversions: 13ADCclk
	// if clk=1Mhz, N= 128 (set to 1,1,1) -> ADCclk=7812tick/s -> 600 conversions/s
	ADCSRA |= (1<<ADPS2 | 1<<ADPS1 | 1<<ADPS0);

// repetition: start free running mode
ADCSRA |= 1<<ADSC;
```

### acquire a value via ADC
read values from ADCL and ADCH.  
NOTE: you can read just ADCH, or if you read ADCL you then must read ADCH, or the next conversion won't be made. this is done to avoid mixing conversions
