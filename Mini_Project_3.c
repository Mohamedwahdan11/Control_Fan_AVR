/*
 * Mini_Project_3.c
 *
 *  Created on: May 24, 2022
 *      Author: DELL
 */

#include "pwm.h"
#include "lcd.h"
#include "adc.h"
#include "lm35_sensor.h"
#include "dc_motor.h"





void main(void)
{

	/*Function to initialize the LCD*/
	LCD_init();

	/*Structure of type ADC_Confitype contain the ADC configurations  */
	ADC_ConfigType ADC_Con={INTERNAL_2_56,8};

	/*Function to initialize the ADC*/
	ADC_init(&ADC_Con);



	/*Function to initialize the DC-motorr*/
	DcMotor_Init();

	uint8 temp; // variable that holds the current temperature


	/* Initialize the LCD screen*/
	LCD_moveCursor(0,4);
	LCD_displayString("Fan Is Off");
	LCD_moveCursor(1,4);
	LCD_displayString("Temp = 0  C");


	while(1)
	{
		/*Read the current temperature by the sensor*/
		temp = LM35_getTemperature();

		/*Display the current temp on the LCD*/
		LCD_moveCursor(1,11);
		LCD_intgerToString(temp);
		LCD_displayCharacter(' ');
		LCD_displayCharacter('C');
		LCD_displayCharacter(' ');

		/*if condition to check the the current temp and turn on the fan with its
		 * suitable speed and the display the fan state if it is on or off*/


		if(temp<30)
		{
			DcMotor_Rotate(OFF,0);
			LCD_moveCursor(0,4);
			LCD_displayString("Fan Is Off");

		}
		else if((temp>=30)&&(temp<60))
		{
			DcMotor_Rotate(CLK_WISE,25);
			LCD_moveCursor(0,4);
			LCD_displayString("Fan Is On");
			LCD_displayCharacter(' ');
		}
		else if((temp>=60)&&(temp<90))
		{
			DcMotor_Rotate(CLK_WISE,50);
			LCD_moveCursor(0,4);
			LCD_displayString("Fan Is On");
			LCD_displayCharacter(' ');
		}
		else if((temp>=90)&&(temp<120))
		{
			DcMotor_Rotate(CLK_WISE,75);
			LCD_moveCursor(0,4);
			LCD_displayString("Fan Is On");
			LCD_displayCharacter(' ');
		}
		else if(temp>=120)
		{
			DcMotor_Rotate(CLK_WISE,100);
			LCD_moveCursor(0,4);
			LCD_displayString("Fan Is On");
			LCD_displayCharacter(' ');
		}







	}
}
