		AREA | .text|,CODE,READONLY,ALIGN=2 
		THUMB 
	    EXTERN current_thread 		;current_thread = &current_tcb 	
		EXPORT SysTick_Handler 	
		EXPORT Kernel_Launch_scheduler
		

SysTick_Handler 					; Saves R0-R3 , R12 , LR ,PC & PSR Register -> EXCEPTION Stack Frame 
		
	; Save Previous Context
	
	CPSID 		I 					; Change Processor State -> Disable Interrupts
	PUSH 	 {R4-R11}				; Push registers on the stack except the stack frame registers
	LDR 	 R0,=current_thread		; R0 = &current_thread, Points to current thread's TCB, whose quanta has exhausted, so we are saving the context 
	LDR      R1,[R0] 				; R1 = current_thread
	STR 	 SP,[R1]				; *current_thread/StackPtr = SP => Saves Stack Pointer value at current_thread addr which is StackPtr 
	
	; Load next thread & it's stack 
	
	LDR 	 R1,[R1,#4]				; R1 = current_thread -> nextpt ;  navigates to 2nd entry of tcb which is *next_thread
	STR 	 R1,[R0]				; current_thread = R1 ; Store next_thread in current_thread , current_thread = next_thread  
									; above two mean => current_thread = current_thread -> next_thread ; dencing thru Linked list
	
	LDR 	 SP,[R1]				; SP = current_thread -> stackptr ; 
	
	; Load New Context
	
	POP 	{R4-R11}
	CPSIE      I					; Change Processor State -> Enable Interrupts
	BX 		  LR				 	; Restores the new thread's registers , including PC , enabling new thread's execution
	

Kernel_Launch_scheduler

	; set SP to SP of first thread 
		
	LDR 	R0,=current_thread 		
	LDR 	R2,[R0] 				; R2 = current_thread
	LDR 	SP,[R2]					; SP = current_thread -> StackPtr
	POP    {R4-R11}
	POP    {R0-R3}
	POP    {R12}
	ADD 	SP,SP,#4 				; ignore LR 
	POP 	{LR}					; POP PC into LR 
	ADD 	SP,SP,#4 				; ignore xPSR
	CPSIE	  I
	BX		LR
	
AlIGN 
	END
	
	