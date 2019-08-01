#include "kernel.h"

#define quanta 1
#define RED (1<<1) 
#define BLUE (1<<2) 
#define GREEN (1<<3) 


uint32_t count0,count1,count2,count3 ; 
void Task0(void) 
{
	while(1) 
	{
		count0++ ;
		//kernel_yield_processor() ; 
		/*GPIOF -> DATA = 0  ;
		GPIOF -> DATA |= RED ;	
		for(int i = 0 ; i<200 ; i++) ; 
		GPIOF -> DATA &= ~RED ;
	*/}

}
void Task1(void) 
{
	while(1) 
	{
		count1++ ; 
		//kernel_yield_processor() ; 
		/*GPIOF -> DATA = 0  ;
		GPIOF -> DATA |= BLUE ;
		for(int i = 0 ; i<200 ; i++) ;
		GPIOF -> DATA &= ~BLUE ;		
	*/}
}
void Task2(void) 
{
	while(1) 
	{
		count2++ ;
		//kernel_yield_processor() ; 
		/*
		GPIOF -> DATA = 0  ;
		GPIOF -> DATA |= GREEN ;
		for(int i = 0 ; i<200 ; i++) ;
		GPIOF -> DATA &= ~GREEN ;
		*/
	}

}

void Task3(void) 
{
	while(1) 
	{
		count3++ ;
		//kernel_yield_processor() ; 
		/*GPIOF -> DATA = 0  ;
		GPIOF -> DATA |= RED ;	
		for(int i = 0 ; i<200 ; i++) ; 
		GPIOF -> DATA &= ~RED ;
	*/}

}



int main(void) 
{
	
	SYSCTL -> RCGCGPIO = 0x20 ; 
	GPIOF -> DIR |= RED | GREEN | BLUE ; 
	GPIOF -> DEN |= RED | GREEN | BLUE ; 
	

	//kernel_create_task(&Task0,&Task1,&Task2) ; 
			
	 tcbTypedef new1,task0,task1,task2 ;
			
		
				
			int32_t stack0[40] ; 
	  	kernel_add_thread(&Task0 , &task0 , stack0 , sizeof(stack0)) ; 
			
			int32_t stack2[40] ; 
			kernel_add_thread(&Task3 , &new1 , stack2 , sizeof(stack2)) ; 
				
	
			int32_t stack1[40] ; 
			kernel_add_thread(&Task1 , &task1 , stack1 , sizeof(stack1)) ;
	
			int32_t stack3[40] ; 
			kernel_add_thread(&Task2 , &task2 , stack3, sizeof(stack3)) ;
			
			
			init_kernel() ; 
			launch_kernel(quanta) ; 
	
}

