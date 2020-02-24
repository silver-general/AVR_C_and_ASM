## super cool guide
https://ccrma.stanford.edu/wiki/AVR_Programming#C_Syntax

## REGISTERS
* attiny85 has 8bit registers.
* for input/output, there are two ports: port A and B
* each port has 3 registers. let's take port A: PORTA, PINA, DDRA

### DDRx Register
* Data Direction Register. each bit of DDRx has a corresponding PINx bit whose direction they specify.
** EG: PORTA is a MACRO that holds the address of the register PORTA.
* instructions to use to set/clear a bit: 
** sbi(reg,bit);
** cli(reg,bit);
** outb(reg,byte); this sets the entire byte of the port.
** DDRB = 0x0f this is a classic assignment in C that sets 00001111

### PORTx Register
* if a pin is an output, its corresponding bit in PORTx controls the value of that output (0 or 1)
~~~
DDRC = 0xFF;  //Set all Port C pins to output
PORTC = 0xF0; //Set first 4 pins of Port C low and next 4 pins high
~~~
* if a pin is an input, its corresponding bit in PORTx is the PULLUP RESISTOR! by default, it is activated (vaue 1), so that the default value is Vcc
** the input value is received in PINx!
~~~
DDRC = 0x00; //Set all Port C pins to input
PORTC = 0xFF; //Set pull-up resistors on Port C
~~~

### PINx Register
* if a pin is set in PORTx as an INPUT: it's pin in PINx contains the value applied to it. the THRESHOLD is 2.5V (also for the tiny??)
* functions:
** inb(reg); returns the byte of the register
~~~
u08 foo;  // declare an 8-bit variable
DDRD = 0x00;   // set port D pins to input
PORTD = 0xFF;  // set pull-ups on port D
foo = PIND;    // read the value of the port D pins
               // and store in the variable foo
~~~
** bit_is_set(reg,bit); returns 1 if set, 0 is not
~~~
u08 bar;  // declare an 8-bit variable
     DDRD = 0x00;    // set port D pins to input
     PORTD = 0xFF;   // set pull-ups on port D
     bar = bit_is_set(PIND,1);
                     // bar now contains the logic value at Port D pin 2
~~~

