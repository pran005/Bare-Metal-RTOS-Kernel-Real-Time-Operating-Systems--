#ifndef _kernel_h
#define _kernel_h

/****************************************************************************
* PRTOS  Pran Real-time Operating System 
* Round version 2.3
* 
*	Updated : 
* 					1. Co-operative Scheduler 	(if enabled) 
*						2. PendSV handles Scheduler (earlier Systick) 
*						3. Dynamic Task Creation 		(User program) 
*						4. User defined Stacks     	
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

#include <stdint.h> 
#include <tm4c123gh6pm.h> 

struct tcb{

		int32_t *stackptr ; 
		struct tcb *next_thread ; 
		uint32_t timeout ;
		uint8_t thread_ID ; 
} ; 

typedef struct tcb tcbTypedef ; 
	

void launch_kernel(uint32_t quanta) ; 

void init_kernel(void) ; 
void kernel_yield_processor(void) ; 

uint8_t	kernel_create_task (void (*task0)(void),
														void (*task1)(void),
														void (*task2)(void)	) ; 
													
void kernel_add_thread(void (*task0)(void) , tcbTypedef *new , int32_t * stack, uint32_t size ) ; 			
														
														
#endif 	


														
 


	
														