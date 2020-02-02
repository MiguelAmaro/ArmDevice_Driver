#include "queue.h"

void Q_Init(Q_T * queue) {
  unsigned int i;
  for (i=0; i<Q_MAX_SIZE; i++)  
    queue->Data[i] = '_';  // to simplify our lives when debugging
  queue->Head = 0;
  queue->Tail = 0;
  queue->Size = 0;
}

int Q_Empty(Q_T * queue) {
  return queue->Size == 0;
}

int Q_Full(Q_T * queue) {
  return queue->Size == Q_MAX_SIZE;
}

int Q_Size(Q_T * queue) {
	return queue->Size;
}

int Q_Enqueue(Q_T * queue, uint8_t d) {
	uint32_t masking_state;
  // If queue is full, don't overwrite data, but do return an error code
  if (!Q_Full(queue)) {
    queue->Data[queue->Tail++] = d;
    queue->Tail %= Q_MAX_SIZE;
		
		// protect q->Size++ operation from preemption
		// save current masking state
		masking_state = __get_PRIMASK();
		// disable interrupts
		__disable_irq();
		// update variable
    queue->Size++;
		// restore  interrupt masking state
		__set_PRIMASK(masking_state);
		
    return 1; // success
  } else 
    return 0; // failure
}

uint8_t Q_Dequeue(Q_T * queue) {
	uint32_t masking_state;
  uint8_t t=0;
  // Check to see if queue is empty before dequeueing
  if (!Q_Empty(queue)) {
    t = queue->Data[queue->Head];
    queue->Data[queue->Head++] = '_'; // empty unused entries for debugging
		queue->Head %= Q_MAX_SIZE;

		// protect q->Size-- operation from preemption
		// save current masking state
		masking_state = __get_PRIMASK();
		// disable interrupts
		__disable_irq();
		// update variable
    queue->Size--;
		// restore  interrupt masking state
		__set_PRIMASK(masking_state);
  }
  return t;
}


// *******************************ARM University Program Copyright © ARM Ltd 2013*************************************   
