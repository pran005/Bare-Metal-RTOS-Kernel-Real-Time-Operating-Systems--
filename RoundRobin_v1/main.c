#include "kernel.h"

#define quanta 10 

#define RED (1<<1) 
#define BLUE (1<<2) 
#define GREEN (1<<3) 


uint32_t count0,count1,count2 ; 
void Task0(void) 
{
	while(1) 
	{
		count0++ ;
		GPIOF -> DATA = 0  ;
		GPIOF -> DATA |= RED ;	
		for(int i = 0 ; i<200 ; i++) ; 
		GPIOF -> DATA &= ~RED ;
	}

}
void Task1(void) 
{
	while(1) 
	{
		count1++ ; 
		GPIOF -> DATA = 0  ;
		GPIOF -> DATA |= BLUE ;
		for(int i = 0 ; i<200 ; i++) ;
		GPIOF -> DATA &= ~BLUE ;		
	}
}
void Task2(void) 
{
	while(1) 
	{
		count2++ ; 
		GPIOF -> DATA = 0  ;
		GPIOF -> DATA |= GREEN ;
		for(int i = 0 ; i<200 ; i++) ;
		GPIOF -> DATA &= ~GREEN ;
	}

}


int main(void) 
{
	
	SYSCTL -> RCGCGPIO = 0x20 ; 
	GPIOF -> DIR |= RED | GREEN | BLUE ; 
	GPIOF -> DEN |= RED | GREEN | BLUE ; 
	
	init_kernel() ; 
	kernel_create_task(&Task0,&Task1,&Task2) ; 
	launch_kernel(quanta) ; 
	
}

