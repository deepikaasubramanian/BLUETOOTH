#include<LPC21xx.h>
#define led 1<<9
#define motor 1<<8
#include "lcd1.h"
int main()
{
    U8 ch;
	IODIR0|=led|motor;
	IOSET0=led;
	IOCLR0=motor;
	lcd_init();
	str("HOME AUTOMATION");
	delay_ms(100);
		UART0_CONFIG();

	
	while(1)
	{
	    ch=UART0_RX();
            UART_TX(ch);
		setup(ch); 
	}
}
void UART0_CONFIG(void)
{
PINSEL0=0X00000005;
U0LCR=0X83;
U0DLL=97;
U0LCR=0X03;
}
void UART0_TX(unsigned U38)
{
while(U0LSR&(1<<5))=0);
U0THR=d;
}
U8 UART0_RX(void)
{
  while((U0LSR &(1<<0))==0);
  return U0RBR;
 }
void  setup(U8 p)
{
  if(p=='A')
   {
      lcd_cmd(0X01);
      IOCLR0=led;
	  lcd_cmd(0xC0);
	  str("LED ON");
	}
   else if(p=='B')
   {
      lcd_cmd(0X01);
      IOSET0=led;
	  lcd_cmd(0xC0);
	  str("LED OFF");
   }
   else if(p=='C')
   {
      lcd_cmd(0X01);
      IOSET0=motor;
	  lcd_cmd(0xC0);
	  str("MOTOR ON");
   }
   else if(p=='D')
   {
      lcd_cmd(0X01);
      IOCLR0=motor;
	  lcd_cmd(0xC0);
	  str("MOTOR OFF");
}
   //else
   //str("INVALID OPTION");
}
