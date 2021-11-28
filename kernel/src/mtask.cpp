#include "mtask.h"
#include <cstddef>
#include "BasicRenderer.h"
#include "cstr.h"

int IRQ_disable_counter = 0;
task* first_ready_to_run_task = first_ready_to_run_task->next;
task* current_task_TCB;
task* terminated_task_list = NULL;

task* task2;
Multiprocessing* mp;

#define KERNEL_STACK_SIZE 0x1000

void lock_scheduler(void) {
#ifndef SMP
    asm("cli");
    IRQ_disable_counter++;
#endif
}
 
void unlock_scheduler(void) {
#ifndef SMP
    IRQ_disable_counter--;
    if(IRQ_disable_counter == 0) {
        asm("sti");
    }
#endif
}


void schedule(void) {
    mp->currentProcess++;
    if(first_ready_to_run_task != NULL) {
        task* processTask = first_ready_to_run_task;
    }
    GlobalRenderer->Print(to_string((float)task2->id));
    GlobalRenderer->ClearChar();
    GlobalRenderer->ClearChar();
    GlobalRenderer->ClearChar();
    GlobalRenderer->Print(":");
    GlobalRenderer->Print("Started!");
}

void block_task(int reason) {
    lock_scheduler();
    current_task_TCB->state = reason;
    GlobalRenderer->Print(get_error_code(current_task_TCB->state));
    GlobalRenderer->Next();
    schedule();
    unlock_scheduler();
}

void unblock_task(task* task2) {
    lock_scheduler();
    if(first_ready_to_run_task == NULL) {
 
    } else {
        task* last_ready_to_run_task;
        last_ready_to_run_task->next = task2;
        last_ready_to_run_task = task2;
    }
    unlock_scheduler();
}

void kernel_idle_task(void) {
    block_task(3);
    for(;;) {
        asm("hlt");
    }
}

const char* get_error_code(int state){
    if(state == 1){
        return "blocked due to insufficent cores or task completed";
    }else if(state == 2){
        return "blocked due to a malicious code";
    }else if(state == 3){
        return "kernel is currently idle.";
    }else if(state == 4){
        return "Shutting down services";
    }else if(state == 5){
        return "Terminated";
    }else if(state == 6){
        return "Paused";
    }else{
        return 0;
    }
}

 
void terminate_task(int reason) {
    lock_scheduler();
    GlobalRenderer->Next();
    current_task_TCB->next = terminated_task_list;
    terminated_task_list = current_task_TCB;
    unlock_scheduler();

    block_task(reason); 
    unblock_task((task*)cleaner_task);
}

void cleaner_task(void) { 
 
    while(terminated_task_list != NULL) {
        task2 = terminated_task_list;
        terminated_task_list = task2->next;
        cleanup_terminated_task(task2);
    }
 
    block_task(6);
}
 
void cleanup_terminated_task(task* task2) {
    task2->kernel_stack_top - KERNEL_STACK_SIZE;
    task2 = (task*)0;
}