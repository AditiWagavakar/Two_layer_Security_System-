#include<p18f4520.h>

void UART_init(void);
void trans(unsigned char);
unsigned char receive(void);
void lcd_init(void);
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_string(unsigned char *);
void delay(void);

#define r0 PORTBbits.RB5
#define r1 PORTBbits.RB6
#define r2 PORTBbits.RB7
#define c0 PORTBbits.RB1
#define c1 PORTBbits.RB2
#define c2 PORTBbits.RB3
#define c3 PORTBbits.RB4

#define RS PORTCbits.RC1
#define RW PORTCbits.RC0
#define EN PORTCbits.RC2
#define data_line PORTD


void main()
{
	unsigned char tag[12];
	unsigned char tag1[12]="090016004C53" ;
	unsigned char tag2[12]="09001600041B" ;
	unsigned char x;
	int i; 
	
	UART_init();
	lcd_init();
	
	
	while(1)
	{
		lcd_string("Welcome")
		delay();
		lcd_sting("Scan Your Card");
		delay();
		
		for(i=0;i<12;i++)
		{
		tag[i]=receive();
		trans(tag[i]);
		}
		
		if(tag[0]==tag1[0]&&tag[1]==tag1[1]&&tag[2]==tag1[2]&&tag[3]==tag1[3]&&tag[4]==tag1[4]&&tag[5]==tag1[5]
		&&tag[6]==tag1[6]&tag[7]==tag1[7]&tag[8]==tag1[8]&tag[9]==tag1[9]&tag[10]==tag1[10]&tag[11]==tag1[11])
		{
			lcd_string("Enter PIN")	
		}
		else
		{
			lcd_string("Invalid Card")
		}
		
	
}

void UART_init(void)
{
	TRISC=0x80;
	TXSTA=0x24;
	RCSTA=0x90;
	SPBRG=0x81;
}

void trans(unsigned char x )
{
	TXREG=x;
	while(TXSTAbits.TRMT==0);
}

unsigned char receive(void)
{
	while(PIR1bits.RCIF==0);  //use RCIF bit for PIR1 to indcate data is received
	return RCREG;
}

void lcd_init(void)
{
	TRISD=0x00;
	TRISC=0x00;
	lcd_cmd(0x30);
	lcd_cmd(0x38);
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_cmd(0x0F);
}
void lcd_cmd(unsigned char c)
{
	data_line=c;
	RS=0;
	RW=0;
            EN=1;
	delay(20);
	EN=0;
}

void lcd_data(unsigned char d)
{
	data_line=d;
	RS=1;
	RW=0;
            EN=1;
	delay(20);
	EN=0;
}
void lcd_string(unsigned char *P)
{
  while(*P!='\0')
	{
		lcd_data(*P);
		P++;
  }
}

void delay(int t)
{
	int i,j;
	for(i=0;i<t;i++)
	{
		for(j=0;j<300;j++);
	}
  
}