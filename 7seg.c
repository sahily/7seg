/*
 * 7seg.c
 *
 * Created: 4/5/2019 9:35:06 PM
 * Author : Sahil S. Mahajan
 * Description: Driver for 7 segment display
 *
 */
 
#include <REG51F.H>

void init(void);
void delay(unsigned int k);
void display(void);

sbit sl1 = P2^3;
sbit sl2 = P2^2;
sbit sl3 = P2^1;
sbit sl4 = P2^0;

unsigned int numbersToDisplay[4] = {6,8,0,3};   //enter 4 numbers here

unsigned int numberList[10] = {
                                  0xFC,   //0         
                                  0x60,   //1
                                  0xDA,   //2 
                                  0xF2,   //3
                                  0x66,   //4
                                  0xB6,   //5
                                  0xBE,   //6
                                  0xE0,   //7
                                  0xFE,   //8
                                  0xF6    //9
                              };
                            
unsigned int digitSelector[4][4] = {
                                      0,1,1,1,   //select 1st digit on 7seg display
                                      1,0,1,1,   //select 2nd digit on 7seg display
                                      1,1,0,1,   //select 3rd digit on 7seg display
                                      1,1,1,0    //select 4th digit on 7seg display
                                   };
                    
void main()
{           
   init();
   while(1)
   {
      display();
   }
    
}
  

/* -----------------
 * Function: init
 * -----------------
 *
 * resets Port 0
 *
 */

void init(void)
{
   P0 = 0x00;
}


/* -----------------
 * Function: delay
 * -----------------
 *
 * creates delay for a specificed number of milliseconds
 *
 * k: number of milliseconds (approximate)
 *
 */

void delay(unsigned int k)
{
   unsigned int i,j;
    
   for(i=0; i<k;i++)
   {
      for(j=0;j<120;j++); 
   }

}

/* -----------------
 * Function: display
 * -----------------
 *
 * selects one digit on the 7-segment display at a time and displays a number on the selected digit
 *
 */

void display(void)
{
   unsigned char x;

   for(x=0;x<4;x++)
   {
      sl1 = digitSelector[x][0];
      sl2 = digitSelector[x][1];
      sl3 = digitSelector[x][2];
      sl4 = digitSelector[x][3];   /* Digit is selected when its pin is reset.        */ 
                                   /* Only one of these is selected in each iteration */

      P0 = numberList[numbersToDisplay[x]];

      delay(4);                    /* 4 milliseconds seems about the right amount of time */
                                   /* for a smooth transition to the next digit/number.   */
   }
}
