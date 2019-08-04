#include "kernel.h" 

/****************************************************************************
* PRTOS  Pran Real-time Operating System 
* Round version 1.0 
* 
*	Specifications : 
* 					1. Round Robin Scheduler (Pre-emptive)
*					2. SysTick handles Scheduling 
* 					3. No Priority based Scheduling
*					4. Pre-defined Quanta in ms
*					5. No dynamic task creation
*						
*
* Copyright (C) 2019 Pran Labs. All Rights Reserved.
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <https://www.gnu.org/licenses/>.
*
****************************************************************************/

/* Kernel must include 
	
	1. Scheduler 
	2. Thread Control Block 
	3. Stack for thread context 
*/ 
#define SYSPRI3 *((volatile uint32_t *) 0xE000ED20) 
#define TOTAL_THREADS 3 
#define Stacksize 100 

uint32_t ms_prescalar ; 

void Kernel_Launch_scheduler(void) ;  
/**********************THREAD CONTROL BLOCK************************/ 

struct tcb{

		int32_t *stackptr ; 
		struct tcb *next_thread ; 

} ; 

typedef struct tcb tcbTypedef ; 

tcbTypedef thread[TOTAL_THREADS] ; 
tcbTypedef *current_thread ; 

/********************END OF TCB ROUTINE **************************/

/********************STACK INITIALIZATIONS************************/

int32_t tcb_stack[TOTAL_THREADS][Stacksize] ; 


void kernel_init_stack(int thread_num)
{
	thread[thread_num].stackptr = &tcb_stack[thread_num][Stacksize-16] ; 
	
	tcb_stack[thread_num][Stacksize - 1] = 0x01000000 ; 																// xPSR |= (1<<24) ; -> xPSR is at the highest mem. addr. ie. at bottom of stack    
}

/********************END OF ROUTINE******************************/

/*******************Task Creation Routine**********************/

uint8_t	kernel_create_task (void (*task0)(void), void (*task1)(void),	void (*task2)(void)) 
{	
		__disable_irq() ; 
		
		thread[0].next_thread = &thread[1] ; 
		thread[1].next_thread = &thread[2] ;
		thread[2].next_thread = &thread[0] ;

		kernel_init_stack(0) ; 
		tcb_stack[0][Stacksize-2] = (int32_t)task0 ; 																	// Assign address of task0 to PC 
		
		kernel_init_stack(1) ; 
		tcb_stack[1][Stacksize-2] = (int32_t)task1 ; 																	// Assign address of task0 to PC 
		
		kernel_init_stack(2) ; 
		tcb_stack[2][Stacksize-2] = (int32_t)task2 ; 																	// Assign address of task0 to PC 
		
		current_thread = &thread[0] ; 
	
		__enable_irq() ; 
	
		return 1 ; 
}	
														
/*********************END OF ROUTINE**********************/


void init_kernel(void) 
{
		__disable_irq() ;
	
		ms_prescalar = SystemCoreClock/1000U ; 
}

void launch_kernel(uint32_t quanta)
{
	
	SysTick -> CTRL = 0 ; 
	SysTick -> VAL = 0 ; 
	
	SYSPRI3 = (SYSPRI3&0x00FFFFFF) | (0xE0000000) ; 															// Set Systick priority to lowest, ie 7 => (1<<29)|(1<<30)|(1<<31) ;  
	
	SysTick -> LOAD = (quanta*ms_prescalar) - 1 ; 																  // Scale Quanta to ms 
	SysTick -> CTRL = 0x00000007 ; 																						 // Enable SysTick with Interrupts , (1<<2) indicated to use CPU CLK  
	Kernel_Launch_scheduler() ;  
	
}

