#ifndef QUEUE_H
#define QUEUE_H

#include <stdint.h>
#include <MKL25Z4.h>

#define MAX_QUEUE_SIZE (256)

typedef struct {
  unsigned int Head; // Index of oldest data element 
  unsigned int Tail; // Index of next free space
  unsigned int Size; // Number of elements in use
  uint8_t Data[MAX_QUEUE_SIZE];
} volatile queue_t;

extern void Init_Queue  (queue_t*);
extern int  isQueueEmpty(queue_t*);
extern int  isQueueFull (queue_t*);
extern int  queueSize   (queue_t*);
extern int     enqueueChar(queue_t*, uint8_t);
extern uint8_t dequeueChar(queue_t*         );


#endif // QUEUE_H

