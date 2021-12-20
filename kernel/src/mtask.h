#pragma once
#include "paging/PageTableManager.h"

typedef struct task
{
   int id;                // Process ID.
   const char* name;      // Process name.
   int state;             // Current state of the ID.
   uint32_t esp, ebp;     // Stack and base pointers.
   uint32_t eip;          // Instruction pointer.
   struct task *next;     // The next task in a linked list.
   int kernel_stack_top = 2;
} task_t;

class Multiprocessing{
    public:
    int currentProcess;
};

extern uint16_t KERNEL_STACK_SIZE;
extern void kernel_stack();

extern task* task2;
extern Multiprocessing* mp;

extern int ret1;
extern int ret2;

void lock_scheduler(void);
void unlock_scheduler(void);
void schedule(void);
bool block_task(int reason);
void unblock_task(task* task2);
void cleanup_terminated_task(task* task2);
void cleaner_task(void);
void terminate_task();
const char* get_error_code(int state);
void kernel_idle_task(void);
void LastTwoDigit(long long int num);
