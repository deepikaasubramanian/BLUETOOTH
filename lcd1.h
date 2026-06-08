 #include<LPC21xx.h>
#define lcd_d 0xf<<14
#define rs 1<<12
//#define rw 1<<18
#define e 1<<13
typedef unsigned int U32;
typedef unsigned char U8;
typedef signed char S8;
//void setup(U8);
//void UART0_TX(U8);
//void UART0_CONFIG(void);
//U8 UART0_RX(void);
										 
void delay_ms(U32 milliseconds)
{
	//T0CTCR=0X00;
	T0PR = 15000-1;
	T0TCR = 0X01;
	while(T0TC<milliseconds);
	T0TCR = 0x03;
	T0TCR = 0x00;
}

void lcd_cmd(U8 d)
{
	IOCLR0=lcd_d;
	IOSET0 = (d&0xf0)<<10;
	IOCLR0 = rs;
	//IOCLR0 = rw;
	IOSET0 =e;
	delay_ms(2);
	IOCLR0 =e;

	IOCLR0=lcd_d;
	IOSET0 = (d&0x0f)<<14;
	IOCLR0 = rs;
	//IOCLR0 = rw;
	IOSET0 =e;
	delay_ms(2);
	IOCLR0 =e;
}

void lcd_data(U8 d)
{
	IOCLR0=lcd_d;
	IOSET0 = (d&0xf0)<<10;
	IOSET0 = rs;
	//IOCLR0 = rw;
	IOSET0 =e;
	delay_ms(2);
	IOCLR0 =e;

	IOCLR0=lcd_d;
	IOSET0 = (d&0x0f)<<14;
	IOSET0 = rs;
	//IOCLR0 = rw;
	IOSET0 =e;
	delay_ms(2);
	IOCLR0 =e;
}

void lcd_init(void)
{
	IODIR0 |= lcd_d|rs|e;
	lcd_cmd(0x01);
	lcd_cmd(0x02);
	lcd_cmd(0x0c);
	lcd_cmd(0x28);
	lcd_cmd(0x80);
}

void str(U8 *s)
{
	while(*s)
		lcd_data(*s++);
}
void lcd_integer(int n)
{
 unsigned  char a[10];
 signed char i=0;
 if(n==0)
 lcd_data('0');
 else
 {
 if(n<0)
 {
 lcd_data('-');
 n=-n;
 }
 while(n>0)
 {
 a[i++]=n%10;
 n/=10;
 }
 for(i=i-1;i>=0;i--)
 lcd_data(a[i]+48);
 }
}

