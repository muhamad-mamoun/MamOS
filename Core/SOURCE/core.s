;======================================================================================================================
; Author       : Mamoun
; Module       : Core
; File Name    : core.s
; Date Created : Oct 6, 2024
; Description  : Assembly file for the MamOS Core Module.
;======================================================================================================================


;======================================================================================================================
; [Details]    : This file hosts the implementation of the PendSV and SVC handlers that manage task context switching
;                and system calls in MamOS. It handles saving and restoring task contexts during switches.
;======================================================================================================================

    AREA      |.text|, CODE, READONLY, ALIGN=2
    IMPORT    MamOS_forceTaskTransition             ; Extern a C function for task switching.
    EXTERN    G_kernelControlPanel                  ; Extern the kernel control panel.
	EXPORT	  PendSV_Handler                        ; Export PendSV handler.
	EXPORT	  SVC_Handler                           ; Export SVC handler.

;======================================================================================================================
; [Function Name] : PendSV_Handler
; [Description]   : The exception service routine for PendSV.
; [Arguments]     : The function Takes no arguments.
; [return]        : The function returns void.
;======================================================================================================================
PendSV_Handler
                                                    ; Enter a critical section.
    CPSID     I                                     ; Disable interrupts during context switch.

                                                    ; Save the stack frame [manual part] of the current task.
    MRS       R1, PSP                               ; Get the stack pointer of the current task.
    STMDB     R1!, {R4-R11}                         ; Save the values of R4-R11 in the current task stack.

                                                    ; Save the current PSP value in the TCB of the current task.
    LDR       R2, =G_kernelControlPanel             ; Load address of kernel control panel.
    LDR       R2, [R2, #8]                          ; Move to the address of the active task TCB.
    STR       R1, [R2, #8]                          ; Save the stack pointer value in the TCB.

                                                    ; Update active task with standby task.
    LDR       R0, =G_kernelControlPanel             ; Load address of kernel control panel.
    LDR       R3, =G_kernelControlPanel             ; Load address of kernel control panel.
    LDR       R3, [R3, #12]                         ; Move to the address of the standby task TCB.
    STR       R3, [R0, #8]                          ; Update active task with standby task.

                                                    ; Load the stack pointer value of the new active task.
    LDR       R2, =G_kernelControlPanel             ; Load address of kernel control panel.
    LDR       R2, [R2, #8]                          ; Move to the address of the new active task TCB.
    LDR       R2, [R2, #8]                          ; Load the stack pointer value of the new active task.

                                                    ; Load the stack frame [manual part] of the new task.
    LDMIA     R2!, {R4-R11}                         ; Restore the values of R4-R11 from the new task stack.
    MSR       PSP, R2                               ; Update PSP to the stack pointer of the new task.

    CPSIE     I                                     ; Re-enable interrupts after context switch [critical section end].
    BX        LR                                    ; Return from exception to the new task.

;======================================================================================================================
; [Function Name] : SVC_Handler
; [Description]   : The exception service routine for SVC.
; [Arguments]     : The function Takes no arguments.
; [return]        : The function returns void.
;======================================================================================================================
SVC_Handler
                                                    ; Extract stack frame starting address.
    TST       LR, #4                                ; Test the second bit of EXC_RETURN.
    ITE       EQ                                    ; If-Then-Else block.
    MRSEQ     R0, MSP                               ; If bit 2 clear, Load the current MSP value.
    MRSNE     R0, PSP                               ; If bit 2 set, Load the current PSP value.

    LDR       R0, [R0, #24]                         ; Load the PC value from stack frame.
    LDRB      R0, [R0, #-2]                         ; Extract the SVC number from PC.

    CMP       R0, #0                                ; Check if the SVC number is 0 [Task Transition Request].
    BNE       SVC_END                               ; If the SVC number is not 0, exit.

    PUSH      {LR}                                  ; Save the current return address before branching.
    BL        MamOS_forceTaskTransition             ; Call a C function for task switching.
    POP       {LR}                                  ; Restore saved return address.

    BX        LR                                    ; Return from exception.

SVC_END                                             ; End of SVC handler.