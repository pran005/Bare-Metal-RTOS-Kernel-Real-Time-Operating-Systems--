#ifndef _kernel_h
#define _kernel_h

#include <stdint.h> 
#include <tm4c123gh6pm.h> 

/* 
The basic functions of the kernel (only routines accessible by main) :  	

	 1. Launch the Kernel 
	 2. init Kernel
	 3. Add threads to the Kernel */ 

void launch_kernel(uint32_t quanta) ; 

void init_kernel(void) ; 

uint8_t	kernel_create_task (void (*task0)(void),
														void (*task1)(void),
														void (*task2)(void)	) ; 
	
#endif 	


														
 
   														