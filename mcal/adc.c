/*
 * adc.c
 *
 *  Created on: May 24, 2022
 *      Author: DELL
 */
#include "avr/io.h" /* To use the ADC Registers */
#include "adc.h"
#include "common_macros.h" /* To use the macros like SET_BIT */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void ADC_init(const ADC_ConfigType * Config_Ptr)
{
	/* ADMUX Register Bits Description:
	 * REFS1:0 = 00 to choose to connect external reference voltage by input this voltage through AREF pin
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	 */
	switch(Config_Ptr->ref_volt)
	{
	default:
	case AREF:
		ADMUX = 0;
		break;
	case AVCC:
		ADMUX =(1<<REFS0);
		break;
	case INTERNAL_2_56:
		ADMUX =(1<<REFS0)|(1<<REFS1);
		break;
	}



	/* ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 0 Disable ADC Interrupt
	 * ADATE   = 0 Disable Auto Trigger
	 * ADPS2:0 = ADC must operate in range 50-200Khz
	 */
	switch(Config_Ptr->prescaler)
		{
		default:
		case 2:
			ADCSRA = (1<<ADEN)  | (1<<ADPS0);
			break;
		case 4:
			ADCSRA = (1<<ADEN) | (1<<ADPS1) ;
			break;
		case 8:
			ADCSRA = (1<<ADEN) | (1<<ADPS1) | (1<<ADPS0);
			break;
		case 16:
			ADCSRA = (1<<ADEN) | (1<<ADPS2) ;
			break;
		case 32:
			ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS0);
			break;
		case 64:
			ADCSRA = (1<<ADEN) | (1<<ADPS1) | (1<<ADPS2);
			break;
		case 128:
			ADCSRA = (1<<ADEN) | (1<<ADPS1) | (1<<ADPS0)| (1<<ADPS2);
			break;

		}

}

uint16 ADC_readChannel(uint8 channel_num)
{
	channel_num &= 0x07; /* Input channel number must be from 0 --> 7 */
	ADMUX &= 0xE0; /* Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
	ADMUX = ADMUX | channel_num; /* Choose the correct channel by setting the channel number in MUX4:0 bits */
	SET_BIT(ADCSRA,ADSC); /* Start conversion write '1' to ADSC */
	while(BIT_IS_CLEAR(ADCSRA,ADIF)); /* Wait for conversion to complete, ADIF becomes '1' */
	SET_BIT(ADCSRA,ADIF); /* Clear ADIF by write '1' to it :) */
	return ADC; /* Read the digital value from the data register */
}
