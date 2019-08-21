#include<avr/io.h>
#include<util/delay.h>

#define pad PORTD

void check1(void);
void check2(void);
void check3(void);
void check4(void);

#define LCD_DATA PORTA

#define ctrl PORTB
#define en PB2
#define rw PB1
#define rs PB0

void LCD_cmd(unsigned char cmd);
void init_LCD(void);
void LCD_write(unsigned char data);
char custom_hex1[] = {0x00,0x0A,0x00,0x11,0x0E,0x00,0x00,0x00};

unsigned int press;

char arr1[3][3];
int  arr2[3][3];
char commands[]={0x80,0xc0,0x94};
int change=0;
char mode='0';
int count1=0;


void printData()
{
	for(int i=0;i<3;i++)
	{
		LCD_cmd(commands[i]);
		if(i==0 || i==1)
		{
			LCD_write_string("      ");
		}
		else
		{
			LCD_write_string("  ");
		}
		for(int j=0;j<3;j++)
		{
			LCD_write(arr1[i][j]);
			LCD_write(' ');
		}
		LCD_write_string("\n");
	}
	
}

void init()
{
	init_LCD();
	LCD_cmd(0x80);
	LCD_write_string("  SELECT LEVEL   ");
	LCD_cmd(0xc0);
	LCD_write_string(" *EASY    #HARD  ");
	while(mode=='0')
	{
		PORTD=0xF0;
		char value1=PIND;
		
		_delay_us(100);
		if(value1!=0xf0)
		{
			check1();
			check2();
			check3();
			check4();
		}
	}
	
	if(mode=='*')
	{
		LCD_cmd(0xc0);
		LCD_write_string(" ");
		LCD_write(255);
	}
	else
	{
		LCD_cmd(0xc0);
		LCD_write_string(" *EASY    ");
		LCD_write(255);
		LCD_write_string("HARD");
	}
	_delay_ms(2000);
	mode='0';
	init_LCD();
	count1++;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			arr2[i][j]=2;
		}
	}
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<7;j++)
		{
			arr1[i][j]=255;
		}
	}
	LCD_cmd(0x94);
	LCD_write_string("                  ");
	printData();
	if(count1%2==0)
	{
		if(arr2[1][1]==2)
		{
			arr1[1][1]='0';
			arr2[1][1]=3;
			printData();
		}
	}
	arr2[0][0]=2;
}


void matchDraw()
{
	printData();
	_delay_ms(1000);
	LCD_cmd(0xD4);
	LCD_write_string("...................");
	LCD_cmd(0xD4);
	LCD_write_string("OHH!...............");
	
	LCD_cmd(0x80);
	LCD_write_string("MATCH DRAW.............");
	LCD_cmd(0xc0);
	LCD_write_string("new Match in 5s.....");
	LCD_cmd(0x94);
	LCD_write_string("...............");
	_delay_ms(5000);
	LCD_cmd(0x80);
	LCD_write_string("                        ");
	LCD_cmd(0xc0);
	LCD_write_string("                        ");
	init();
}

void nextStep()
{
	int r1=arr2[0][0]*arr2[0][1]*arr2[0][2];
	int r2=arr2[1][0]*arr2[1][1]*arr2[1][2];
	int r3=arr2[2][0]*arr2[2][1]*arr2[2][2];
	
	int c1=arr2[0][0]*arr2[1][0]*arr2[2][0];
	int c2=arr2[0][1]*arr2[1][1]*arr2[2][1];
	int c3=arr2[0][2]*arr2[1][2]*arr2[2][2];
	
	int dig1=arr2[0][0]*arr2[1][1]*arr2[2][2];
	int dig2=arr2[0][2]*arr2[1][1]*arr2[2][0];
	
	if(arr2[1][1]==2)
	{
		arr1[1][1]='0';
		arr2[1][1]=3;
	}
	else if(r1==125 || r2==125 || r3==125 || c1==125 || c2==125 || c3==125 || dig1==125 || dig2==125)
	{
		printData();
		_delay_ms(1000);
		LCD_cmd(0xD4);
		LCD_write_string("...................");
		LCD_cmd(0xD4);
		LCD_write_string("You won............");
		
		LCD_cmd(0x80);
		LCD_write_string("Congratulation.........");
		LCD_cmd(0xc0);
		LCD_write_string("new Match in 5s.....");
		LCD_cmd(0x94);
		LCD_write_string("...............");
		_delay_ms(5000);
		LCD_cmd(0x80);
		LCD_write_string("                        ");
		LCD_cmd(0xc0);
		LCD_write_string("                        ");
		init();
	}
	else
	{
		LCD_cmd(0xD4);
		LCD_write_string("...................");
		LCD_cmd(0xD4);
		LCD_write_string("Machine's turn.....");
		_delay_ms(1000);
		
		if(r1==18 || r2==18 || r3==18 || c1==18 || c2==18 || c3==18 || dig1==18 || dig2==18)
		{
			
			if(r1==18)
			{
				for(int i=0;i<3;i++)
				{
					if(arr2[0][i]==2)
					{
						arr2[0][i]=3;
						arr1[0][i]='0';
					}
				}
			}
			else if(r2==18)
			{
				for(int i=0;i<3;i++)
				{
					if(arr2[1][i]==2)
					{
						arr2[1][i]=3;
						arr1[1][i]='0';
					}
				}
			}
			else if(r3==18)
			{
				for(int i=0;i<3;i++)
				{
					if(arr2[2][i]==2)
					{
						arr2[2][i]=3;
						arr1[2][i]='0';
					}
				}
			}
			else if(c1==18)
			{
				for(int i=0;i<3;i++)
				{
					if(arr2[i][0]==2)
					{
						arr2[i][0]=3;
						arr1[i][0]='0';
					}
				}
			}
			else if(c2==18)
			{
				for(int i=0;i<3;i++)
				{
					if(arr2[i][1]==2)
					{
						arr2[i][1]=3;
						arr1[i][1]='0';
					}
				}
			}
			else if(c3==18)
			{
				for(int i=0;i<3;i++)
				{
					if(arr2[i][2]==2)
					{
						arr2[i][2]=3;
						arr1[i][2]='0';
					}
				}
			}
			else if(dig1==18)
			{
				if(arr2[0][0]==2)
				{
					arr2[0][0]=3;
					arr1[0][0]='0';
				}
				else if(arr2[1][1]==2)
				{
					arr2[1][1]=3;
					arr1[1][1]='0';
				}
				else if(arr2[2][2]==2)
				{
					arr2[2][2]=3;
					arr1[2][2]='0';
				}
			}
			else if(dig2==18)
			{
				if(arr2[0][2]==2)
				{
					arr2[0][2]=3;
					arr1[0][2]='0';
				}
				else if(arr2[1][1]==2)
				{
					arr2[1][1]=3;
					arr1[1][1]='0';
				}
				else if(arr2[2][0]==2)
				{
					arr2[2][0]=3;
					arr1[2][0]='0';
				}
			}
			printData();
			_delay_ms(1000);
			LCD_cmd(0xD4);
			LCD_write_string("...................");
			LCD_cmd(0xD4);
			LCD_write_string("    You lost...........");
			
			LCD_cmd(0x80);
			LCD_write_string("    Bad Luck...........");
			LCD_cmd(0xc0);
			LCD_write_string("new Match in 5s.....");
			LCD_cmd(0x94);
			LCD_write_string("...............");
			_delay_ms(5000);
			LCD_cmd(0x80);
			LCD_write_string("                        ");
			LCD_cmd(0xc0);
			LCD_write_string("                        ");
			init();
		}
		else if(r1==50 || r2==50 || r3==50 || c1==50 || c2==50 || c3==50 || dig1==50 || dig2==50)
		{
			if(r1==50)
			{
				for(int i=0;i<3;i++)
				{
					if(arr2[0][i]==2)
					{
						arr2[0][i]=3;
						arr1[0][i]='0';
					}
				}
			}
			else if(r2==50)
			{
				for(int i=0;i<3;i++)
				{
					if(arr2[1][i]==2)
					{
						arr2[1][i]=3;
						arr1[1][i]='0';
					}
				}
			}
			else if(r3==50)
			{
				for(int i=0;i<3;i++)
				{
					if(arr2[2][i]==2)
					{
						arr2[2][i]=3;
						arr1[2][i]='0';
					}
				}
			}
			else if(c1==50)
			{
				for(int i=0;i<3;i++)
				{
					if(arr2[i][0]==2)
					{
						arr2[i][0]=3;
						arr1[i][0]='0';
					}
				}
			}
			else if(c2==50)
			{
				for(int i=0;i<3;i++)
				{
					if(arr2[i][1]==2)
					{
						arr2[i][1]=3;
						arr1[i][1]='0';
					}
				}
			}
			else if(c3==50)
			{
				for(int i=0;i<3;i++)
				{
					if(arr2[i][2]==2)
					{
						arr2[i][2]=3;
						arr1[i][2]='0';
					}
				}
			}
			else if(dig1==50)
			{
				if(arr2[0][0]==2)
				{
					arr2[0][0]=3;
					arr1[0][0]='0';
				}
				else if(arr2[1][1]==2)
				{
					arr2[1][1]=3;
					arr1[1][1]='0';
				}
				else if(arr2[2][2]==2)
				{
					arr2[2][2]=3;
					arr1[2][2]='0';
				}
			}
			else if(dig2==50)
			{
				if(arr2[0][2]==2)
				{
					arr2[0][2]=3;
					arr1[0][2]='0';
				}
				else if(arr2[1][1]==2)
				{
					arr2[1][1]=3;
					arr1[1][1]='0';
				}
				else if(arr2[2][0]==2)
				{
					arr2[2][0]=3;
					arr1[2][0]='0';
				}
			}
			printData();
			LCD_cmd(0xD4);
			LCD_write_string("...................");
			LCD_cmd(0xD4);
			LCD_write_string("YOUR TURN..........");
		}
		else if(mode=='#' && (r1==12 || r2==12 || r3==12 || c1==12 || c2==12 || c3==12 || dig1==12 || dig2==12))
		{
			if(dig1==12)
			{
				if(arr2[0][0]==2)
				{
					arr2[0][0]=3;
					arr1[0][0]='0';
				}
				else if(arr2[1][1]==2)
				{
					arr2[1][1]=3;
					arr1[1][1]='0';
				}
				else if(arr2[2][2]==2)
				{
					arr2[2][2]=3;
					arr1[2][2]='0';
				}
			}
			else if(dig2==12)
			{
				if(arr2[0][2]==2)
				{
					arr2[0][2]=3;
					arr1[0][2]='0';
				}
				else if(arr2[1][1]==2)
				{
					arr2[1][1]=3;
					arr1[1][1]='0';
				}
				else if(arr2[2][0]==2)
				{
					arr2[2][0]=3;
					arr1[2][0]='0';
				}
			}
			else if(r1==12)
			{
				for(int i=0;i<3;i++)
				{
					if(arr2[0][i]==2)
					{
						arr2[0][i]=3;
						arr1[0][i]='0';
						break;
					}
				}
			}
			else if(r2==12)
			{
				for(int i=0;i<3;i++)
				{
					if(arr2[1][i]==2)
					{
						arr2[1][i]=3;
						arr1[1][i]='0';
						break;
					}
				}
			}
			else if(r3==12)
			{
				for(int i=0;i<3;i++)
				{
					if(arr2[2][i]==2)
					{
						arr2[2][i]=3;
						arr1[2][i]='0';
						break;
					}
				}
			}
			else if(c1==12)
			{
				for(int i=0;i<3;i++)
				{
					if(arr2[i][0]==2)
					{
						arr2[i][0]=3;
						arr1[i][0]='0';
						break;
					}
				}
			}
			else if(c2==12)
			{
				for(int i=0;i<3;i++)
				{
					if(arr2[i][1]==2)
					{
						arr2[i][1]=3;
						arr1[i][1]='0';
						break;
					}
				}
			}
			else if(c3==12)
			{
				for(int i=0;i<3;i++)
				{
					if(arr2[i][2]==2)
					{
						arr2[i][2]=3;
						arr1[i][2]='0';
						break;
					}
				}
			}
		}
		
		else
		{
			int flag=0;
			for(int i=0;i<3;i++)
			{
				for(int j=0;j<3;j++)
				{
					if(arr2[i][j]==2 && flag==0)
					{
						flag=1;
						arr2[i][j]=3;
						arr1[i][j]='0';
					}
				}
			}
			
			if(flag==0)
			{
				matchDraw();
			}
		}
		int flag2=0;
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				if(arr2[i][j]==2 && flag2==0)
				{
					flag2=1;
				}
			}
		}
		
		if(flag2==0)
		{
			matchDraw();
		}
		else
		{
			LCD_cmd(0xD4);
			LCD_write_string("...................");
			LCD_write_string("Done...............");
		}
	}
}


int main()
{
	unsigned char value;
	DDRA=0xff;
	DDRB=0x07;
	DDRD=0x0F;
	pad=0xf0;
	init_LCD();
	init();
	while(1)
	{
		PORTD=0xF0;
		value=PIND;
		
		_delay_us(100);
		if(value!=0xf0)
		{
			check1();
			check2();
			check3();
			check4();
			if(change==1)
			{
				change=0;
				printData();
				_delay_ms(1000);
				
				nextStep();
				printData();
				_delay_ms(100);
				LCD_cmd(0xD4);
				LCD_write_string("...................");
				LCD_cmd(0xD4);
				LCD_write_string("Your Turn.....");
			}
		}
	}
	return 0;
}



void check1(void)
{
	
	pad =0b11111110;
	
	_delay_us(100);
	char chr1=PIND;
	if(chr1==0b10111110)
	{
		if(arr2[0][2]==2)
		{
			arr1[0][2]='X';
			arr2[0][2]=5;
			change=1;
			LCD_cmd(0xD4);
			LCD_write_string("...................");
			LCD_cmd(0xD4);
			LCD_write_string("ADDED..............");
		}
		else
		{
			LCD_cmd(0xD4);
			LCD_write_string("...................");
			LCD_cmd(0xD4);
			LCD_write_string("ALREADY TAKEN");
		}
	}
	else if(chr1==0b11011110)
	{
		if(arr2[0][1]==2)
		{
			arr1[0][1]='X';
			arr2[0][1]=5;
			change=1;
			LCD_cmd(0xD4);
			LCD_write_string("...................");
			LCD_cmd(0xD4);
			LCD_write_string("ADDED..............");
		}
		else
		{
			LCD_cmd(0xD4);
			LCD_write_string("...................");
			LCD_cmd(0xD4);
			LCD_write_string("ALREADY TAKEN");
		}
	}
	else if(chr1==0b11101110)
	{
		if(arr2[0][0]==2)
		{
			arr1[0][0]='X';
			arr2[0][0]=5;
			change=1;
			LCD_cmd(0xD4);
			LCD_write_string("...................");
			LCD_cmd(0xD4);
			LCD_write_string("ADDED..............");
		}
		else
		{
			LCD_cmd(0xD4);
			LCD_write_string("...................");
			LCD_cmd(0xD4);
			LCD_write_string("ALREADY TAKEN");
		}
	}
	
}

void check2(void)
{
	pad=0b11111101;
	_delay_us(100);
	char chr1=PIND;
	if(chr1==0b10111101)
	{
		if(arr2[1][2]==2)
		{
			arr1[1][2]='X';
			arr2[1][2]=5;
			change=1;
			LCD_cmd(0xD4);
			LCD_write_string("...................");
			LCD_cmd(0xD4);
			LCD_write_string("ADDED..............");
		}
		else
		{
			LCD_cmd(0xD4);
			LCD_write_string("...................");
			LCD_cmd(0xD4);
			LCD_write_string("ALREADY TAKEN");
		}
	}
	else if(chr1==0b11011101)
	{
		if(arr2[1][1]==2)
		{
			arr1[1][1]='X';
			arr2[1][1]=5;
			LCD_cmd(0xD4);
			change=1;
			LCD_write_string("...................");
			LCD_cmd(0xD4);
			LCD_write_string("ADDED..............");
			LCD_cmd(0xD4);
		}
		else
		{
			LCD_cmd(0xD4);
			LCD_write_string("...................");
			LCD_cmd(0xD4);
			LCD_write_string("ALREADY TAKEN");
		}
	}
	else if(chr1==0b11101101)
	{
		if(arr2[1][0]==2)
		{
			arr1[1][0]='X';
			arr2[1][0]=5;
			LCD_cmd(0xD4);
			change=1;
			LCD_write_string("...................");
			LCD_cmd(0xD4);
			LCD_write_string("ADDED..............");
		}
		else
		{
			LCD_cmd(0xD4);
			LCD_write_string("...................");
			LCD_cmd(0xD4);
			LCD_write_string("ALREADY TAKEN");
		}
	}
	
	
}

void check3(void)
{
	pad=0b11111011;
	_delay_us(100);
	char chr1=PIND;
	if(chr1==0b10111011)
	{
		if(arr2[2][2]==2)
		{
			arr1[2][2]='X';
			arr2[2][2]=5;
			LCD_cmd(0xD4);
			change=1;
			LCD_write_string("...................");
			LCD_cmd(0xD4);
			LCD_write_string("ADDED..............");
		}
		else
		{
			LCD_cmd(0xD4);
			LCD_write_string("...................");
			LCD_cmd(0xD4);
			LCD_write_string("ALREADY TAKEN");
		}
	}
	else if(chr1==0b11011011)
	{
		if(arr2[2][1]==2)
		{
			arr1[2][1]='X';
			arr2[2][1]=5;
			LCD_cmd(0xD4);
			change=1;
			LCD_write_string("...................");
			LCD_cmd(0xD4);
			LCD_write_string("ADDED..............");
		}
		else
		{
			LCD_cmd(0xD4);
			LCD_write_string("...................");
			LCD_cmd(0xD4);
			LCD_write_string("ALREADY TAKEN");
		}
	}
	else if(chr1==0b11101011)
	{
		if(arr2[2][0]==2)
		{
			arr1[2][0]='X';
			arr2[2][0]=5;
			LCD_cmd(0xD4);
			change=1;
			LCD_write_string("...................");
			LCD_cmd(0xD4);
			LCD_write_string("ADDED..............");
		}
		else
		{
			LCD_cmd(0xD4);
			LCD_write_string("...................");
			LCD_cmd(0xD4);
			LCD_write_string("ALREADY TAKEN");
		}
	}
	
	
}

void check4(void)
{
	pad =0b11110111;
	_delay_us(100);
	
	char chr1=PIND;
	if(chr1==0b10110111)
	{
		mode='#';
	}
	else if(chr1==0b11100111)
	{
		mode='*';
	}
}

void init_LCD(void)
{
	
	LCD_cmd(0x38);
	_delay_ms(1);
	
	LCD_cmd(0x01);
	_delay_ms(1);
	
	LCD_cmd(0x0E);
	_delay_ms(1);
	
	LCD_cmd(0x80);
	_delay_ms(1);
	return;
}

void LCD_cmd(unsigned char cmd)
{
	LCD_DATA=cmd;
	ctrl =(0<<rs)|(0<<rw)|(1<<en);
	_delay_ms(1);
	ctrl =(0<<rs)|(0<<rw)|(0<<en);
	_delay_ms(10);
	return;
}

void LCD_write(unsigned char data)
{
	LCD_DATA= data;
	ctrl = (1<<rs)|(0<<rw)|(1<<en);
	_delay_ms(10);
	ctrl = (1<<rs)|(0<<rw)|(0<<en);
	_delay_ms(10);
	return ;
}

void LCD_write_string(unsigned char *str)
{
	int i=0;
	while(str[i]!='\0')
	{
		LCD_write(str[i]);
		i++;
	}
	return;
}

