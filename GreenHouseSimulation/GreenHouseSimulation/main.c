/*
 * GreenHouseSimulation.c
 *
 * Created: 05/12/2021 2:35:04
 * Author : Jesus Borobia, Teodor Cosma, Radu Balc,Valentin Cristea
 */ 

/* Defines -----------------------------------------------------------*/
#ifndef F_CPU
#define F_CPU 16000000
#endif
#define LED_WINDOW PB5
#define LED_PUMP PB4
#define LED_FAN PB3
#define LED_LIGHT PB2


/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include <stdlib.h>         // C library. Needed for conversion function
#include "timer.h"          // Timer library for AVR-GCC
#include "uart.h"           // Peter Fleury's UART library
#include "twi.h"            // TWI library for AVR-GCC
#include "lcd.h"			// LCD library for AVR-GCC
#include "gpio.h"			// GPIO library	for AVR-GCC


/* Variables ---------------------------------------------------------*/
// Variable declaration type for FSM 
typedef enum {              
	STATE_IDLE = 1,	//IDLE STATE
	STATE_SEND1,	//SEND INFO TO 1ST SENSOR
	STATE_REC1,		//RECEIVE INFO FROM 1ST SENSOR
	STATE_SEND2,	//SEND INFO TO 2ND SENSOR
	STATE_REC2,	    //RECEIVE INFO FROM 2ND SENSOR
	STATE_REC3,	    //SEND INFO TO 3RD SENSOR
	STATE_SEND3		//RECEIVE INFO FROM 3RD SENSOR AND INCREASE COUNTER FOR MOVING THROUGH RAM
} state_t;



/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose: Initialize every process we will need to display info.
			Setup of TIM1 every 262ms
 * Returns:  none
 **********************************************************************/
int main(void)
{
	 //Configure LEDS as output and initialize with low value.
	 GPIO_config_output(&DDRB, LED_WINDOW);
	 GPIO_write_low(&PORTB, LED_WINDOW);
	 GPIO_config_output(&DDRB, LED_PUMP);
	 GPIO_write_low(&PORTB, LED_PUMP);
	 GPIO_config_output(&DDRB, LED_FAN);
	 GPIO_write_low(&PORTB, LED_FAN);
	 GPIO_config_output(&DDRB, LED_LIGHT);
	 GPIO_write_low(&PORTB, LED_LIGHT);
	
	 //Configure ADC to convert PC0[A0] analog value
	 //Set ADC reference to AVcc
	 ADMUX |=(1<<REFS0);
	 
	 // Set input channel to ADC0
	 ADMUX &= ~((1<MUX3) | (1<<MUX2)|| (1<<MUX1)| (1<<MUX0) );

	 // Enable ADC module
	 ADCSRA |= (1<<ADEN);

	 // Enable conversion complete interrupt
	 ADCSRA |= (1<<ADIE);
	 
	 // Set clock prescaler to 128
	 
	 ADCSRA |= (1<<ADPS2) | (1<<ADPS1) |(1<<ADPS0) ;
	  
	//Initialize LCD display 
	lcd_init(LCD_DISP_ON);
	
    // Initialize I2C (TWI)
    twi_init();

    // Initialize UART to asynchronous, 8N1, 9600
    uart_init(UART_BAUD_SELECT(9600, F_CPU));
	
	// Put strings to ringbuffer for transmitting via UART
	uart_puts("\r\nStarting service...\r\n");

    // Configure 16-bit Timer/Counter1 to update FSM
    // Enable interrupt and set the overflow prescaler to 262ms
    TIM1_overflow_262ms();
    TIM1_overflow_interrupt_enable();
    
	// Enables interrupts by setting the global interrupt mask
    sei();

  	
	//Infinite loop
    while (1) 
    {
		/* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines ISRs */
    }
	
	// Will never reach this
	return 0;
}


/* Interrupt service routines ----------------------------------------*/
/**********************************************************************
 * Function: Timer/Counter1 overflow interrupt
 * Purpose:  Update Finite State Machine and take the info through different 
 * I2C sensors and display it via UART or LCD screen.
 **********************************************************************/
ISR(TIMER1_OVF_vect)
{	 
	//Variable declaration
	 static state_t state = STATE_IDLE;		 // Current state
	 static uint8_t temphumid_addr = 0x5c;   // I2C slave address for measuring temperature and humidity
	 static uint8_t light_addr=0x23;		 // I2C slave address for measuring light
	 static uint8_t soil_addr=0x20;			 // I2C slave address for measuring soil 
	 char uart_string[8] = "00";			 // String for converting numbers by itoa()
	 uint8_t result=1;						 //Temperature variable
	 static uint8_t counter = 0x00;			 //Counter for moving through I2C RAM registers
	 
	 // Start ADC conversion
	 ADCSRA |= (1<<ADSC);
	
//SENSORS ---------------------
    // FSM
    switch (state)
    {
		
	case STATE_IDLE:
	
		state=STATE_SEND1;   

    break;
      
    case STATE_SEND1:
	
       //Starts i2c with 1st addr-->wanting to write
       twi_start((temphumid_addr<<1) + TWI_WRITE);
       //Writing 0x0 to the sensor with addr
       twi_write(counter);
       //Nothing else has to be sent
       twi_stop();   
	   state=STATE_REC1; 
	  
	break;
        
    case STATE_REC1:
      
	  //After giving the order to the slave we want to read
      twi_start((temphumid_addr<<1) + TWI_READ);
      //Read the temperature integer part
      result=twi_read_nack();
	  //End communication
	  twi_stop();
	  
	  //Integer to ASCII for displaying in UART and LCD
      itoa(result,uart_string,10);
      //Display in UART	  
	  uart_puts("TEMPERATURE:");
      uart_puts(uart_string);
	  uart_puts("\n");
	  
      //Display in LCD
 	  lcd_gotoxy(0,0);
      lcd_puts("Temp:");
	  lcd_gotoxy(5,0);
	  lcd_puts(uart_string);
	  lcd_gotoxy(7,0);
	  lcd_puts("C");
		
	  //Condition for turning on LED_WINDOW (open/close window in real life)	
	  if((int)result>20){
		  GPIO_write_high(&PORTB, LED_WINDOW);
	  }
		
	  if((int)result<=20){
		  GPIO_write_low(&PORTB, LED_WINDOW);
	  }	
	  
	  //Next state		
      state = STATE_SEND2;
		
    break;
	
	case STATE_SEND2:
		
	  //Starts i2c with 1st addr-->wanting to write
	  twi_start((light_addr<<1) + TWI_WRITE);
	  //Writing 0x0 to the sensor with addr
	  twi_write(counter);
	  //Nothing else has to be sent
	  twi_stop();
	 
	  //Next state	
	  state=STATE_REC2;
	  
	break;
		
	case STATE_REC2:
	   //After giving the	order to the slave we want to read
	   twi_start((light_addr<<1) + TWI_READ);
	   //Read the temperature integer part
	   result=twi_read_nack();
	   itoa(result,uart_string,10);
	   twi_stop();
	   
	   //Display in UART	
	   uart_puts("HUMID:");
	   uart_puts(uart_string);  
	   uart_puts("\n");
	   
	   //Display in LCD
	   lcd_gotoxy(0,1);
	   lcd_puts("Humid:"); 
	   lcd_gotoxy(6,1);
	   lcd_puts(uart_string);
	   lcd_gotoxy(8,1);
	   lcd_puts("%");
	   
	   //Condition for turning on LED_FANS (turn on/off fans in real life)
	   if((int)result>20){
		 GPIO_write_high(&PORTB, LED_FAN);
	   }
	 
	   if((int)result<=20){
		 GPIO_write_low(&PORTB, LED_FAN);
	   }
		 
	 state = STATE_SEND3;
	 break;
	 
	 case STATE_SEND3:
	   //Starts i2c with 1st addr-->wanting to write
	   twi_start((soil_addr<<1) + TWI_WRITE);
	   //Writing 0x0 to the sensor with addr
	   twi_write(counter);
	   //Nothing else has to be sent
	   twi_stop();
	   //Increase the counter for moving through RAM memories
	   counter=counter+(uint8_t)1;
	 
	   state=STATE_REC3;
	 
	 break;
	 
	 case STATE_REC3:
	 
	   //After giving the order to the slave we want to read
	   twi_start((soil_addr<<1) + TWI_READ);
	   //Read the temperature integer part
	   result=twi_read_nack();
	   itoa(result,uart_string,10);
	   twi_stop();
	   
	   //Display in UART
	   uart_puts("SOIL:");
	   uart_puts(uart_string);
	   uart_puts("\n");
	   
	   //Condition for turning on LED_PUMP (turn on/off water pump in real life) 
	   if((int)result>20){
		   GPIO_write_high(&PORTB, LED_PUMP);
	   }
	 
	   if((int)result<=20){
		   GPIO_write_low(&PORTB, LED_PUMP);
	   }
	
	   state = STATE_IDLE;
	
	 break;
	 
	 //If something unexpected happens then move to IDLE
     default:
	 
        state = STATE_IDLE;
		
     break;
    }

}
		
/**********************************************************************
 * Function: ADC complete interrupt
 * Purpose:  Display value on LCD and send it to UART. Decide if turn on/off windows
 **********************************************************************/	
ISR(ADC_vect){
	
		//Variable declaration
		char lcd_string[4] = "0000";
		uint16_t value = 0;	
		uint16_t real_value = 0;
		
		//Receive the digital value from the AD converter		
		value=ADC;
		
		//Calculate the real value (we want a number between 0 and 5 to measure light)
		real_value=value/204;
		//Integer to ASCII for sending to UART
		itoa(real_value,lcd_string,10);
		//Display in UART
		uart_puts("LIGHT:");
		uart_puts(lcd_string);
		uart_puts("\n");
		
		//Condition for turning on	LED_LIGHT (turn on/off lightbulbs in real life)
		if(real_value<2){
			GPIO_write_high(&PORTB, LED_LIGHT);
		}
		else{
			GPIO_write_low(&PORTB, LED_LIGHT);
		}
			
		
		
}		

