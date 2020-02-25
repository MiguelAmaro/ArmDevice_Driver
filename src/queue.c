#include "queue.h"

void Init_Queue(queue_t* queue) {
  unsigned int index;
  for (index = 0; index <MAX_QUEUE_SIZE; index++)  
    queue->Data[index] = '_';  // to simplify our lives when debugging
  queue->Head = 0;
  queue->Tail = 0;
  queue->Size = 0;
}

int isQueueEmpty(queue_t * queue) {
  return queue->Size == 0;
}

int isQueueFull(queue_t * queue) {
  return queue->Size == MAX_QUEUE_SIZE;
}

int queueSize(queue_t * queue) {
	return queue->Size;
}

int enqueueChar(queue_t * queue, uint8_t data) {
	uint32_t masking_state;
  // If queue is full, don't overwrite data, but do return an error code
  if (!isQueueFull(queue)) {
    queue->Data[queue->Tail++] = data;
    queue->Tail %= MAX_QUEUE_SIZE;
		
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

uint8_t dequeueChar(queue_t * queue) {
	uint32_t masking_state;
  uint8_t lastChar = 0;
  // Check to see if queue is empty before dequeueing
  if (!isQueueEmpty(queue)) {
    lastChar = queue->Data[queue->Head];
    queue->Data[queue->Head++] = '_'; // empty unused entries for debugging
		queue->Head %= MAX_QUEUE_SIZE;

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
  return lastChar;
}


// *******************************ARM University Program Copyright © ARM Ltd 2013*************************************   
