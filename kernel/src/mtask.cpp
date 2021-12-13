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

int ret1;
int ret2;

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
    LastTwoDigit(task2->id);
    //GlobalRenderer->Print(to_string((long int)ret2));
    //GlobalRenderer->Print(to_string((long int)ret1));
    //GlobalRenderer->Print(":");
    //GlobalRenderer->Print("Started!");
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
    while(1){}
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
        return "Terminated. PID:", to_string((long int)task2->id);;
    }else if(state == 6){
        return "Paused";
    }else if(state == 7){
        return "Terminated Due to System error.";
    }else{
        return 0;
    }
}

 
void terminate_task() {
    lock_scheduler();
    GlobalRenderer->Next();
    current_task_TCB->next = terminated_task_list;
    terminated_task_list = current_task_TCB;
    unlock_scheduler();

    block_task(5); 
    unblock_task((task*)cleaner_task);
    cleaner_task();
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

void LastTwoDigit(long long int num)
{
    // Get the last digit from the number
    int one = num % 10;
 
    // Remove last digit from number
    num /= 10;
 
    // Get the last digit from
    // the number(last second of num)
    int tens = num % 10;
 
    // Take last digit to ten's position
    // i.e. last second digit
    tens *= 10;
 
    // Add the value of ones and tens to
    // make it complete 2 digit number
    ret2 = tens;
    ret1 = one;
}