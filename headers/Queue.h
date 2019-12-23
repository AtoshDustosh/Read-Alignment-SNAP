#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include <inttypes.h>

#define True 1
#define False 0

/**
 * Queue data structure.
 */
typedef struct _define_QueueCell {
    uint64_t data;
    struct _define_QueueCell* next;
} QueueCell;

typedef struct _define_Queue {
    uint64_t length;    // size of queue
    QueueCell* head;  // head pointer
    QueueCell* tail;    // tail pointer
} Queue;


/**
 * A collection of test in this header file.
 */
void _QueueTestSet();


/*
 * Working functions.
 */



/**
 * Get a new queue cell with specific data.
 *
 * @param data data to be stored in the queue cell
 * @return new queue cell with data
 */
QueueCell* newQueueCell(uint64_t data);


/**
 * Initialize a queue.
 *
 * @param queueInstance an instance of Queue - cannot be NULL pointer
 */
void initQueue(Queue* queueInstance);


/**
 * Set a queue with specific head, tail and length.
 *
 * @param queueInstance an instance of Queue - cannot be NULL pointer
 * @param head head of queue
 * @param tail tail of queue
 * @param length length of queue
 */
void setQueue(Queue* queueInstance, QueueCell* head, QueueCell* tail, uint64_t length);


/**
 * Clear a queue.
 *
 * @param queueInstance an instance of Queue - cannot be NULL pointer
 */
void clearQueue(Queue* queueInstance);


/**
 * Judge whether a queue is empty.
 *
 * @param queueInstance an instance of Queue - cannot be NULL pointer
 * @return 1 if queue is empty; 0 otherwise
 */
uint64_t isQueueEmpty(Queue* queueInstance);


/**
 * Get the length of a queue.
 *
 * @param queueInstance an instance of Queue - cannot be NULL pointer
 * @return length of the queue
 */
uint64_t queueLength(Queue* queueInstance);


/**
 * Get the head of a queue.
 *
 * @param queueInstance an instance of Queue - cannot be NULL pointer
 * @return head of the queue
 */
QueueCell* getQueueHead(Queue* queueInstance);


/**
 * Get the tail of a queue.
 *
 * @param queueInstance an instance of Queue - cannot be NULL pointer
 * @return tail of the queue
 */
QueueCell* getQueueTail(Queue* queueInstance);


/**
 * Dequeue a queue and get the element dequeued.
 *
 * @param queueInstance an instance of Queue - cannot be NULL pointer
 * @param queueCell return element dequeued
 */
void deQueue(Queue* queueInstance, QueueCell* queueCell);


/**
 * Enqueue an element into a queue.
 *
 * @param queueInstance an instance of Queue - cannot be NULL pointer
 * @param queueCell element to be enqueued
 */
void enQueue(Queue* queueInstance, QueueCell* queueCell);


/**
 * Print a queue.
 *
 * @param queueInstance an instance of Queue - cannot be NULL pointer
 */
void printQueue(Queue* queueInstance);



#endif // QUEUE_H_INCLUDED