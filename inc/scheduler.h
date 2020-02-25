#ifndef SCHEDULER_H
#define SCHEDULER_H

void Init_SysTick(void);
void scheduler(void);

// Idea...
// Declare a data strucuture containing function pointers
// and command characters to each module's task which can be passed to a 
// function of "serialcomm" 

#endif
