#include <stdint.h>
#include <stdlib.h>
#include "miros.h"

struct struct_threads {
    OSThread TCB_thread;
    uint32_t stack_thread[40];
};

const uint8_t produceBuffer_start_value = 25;
const uint8_t consumeBuffer_start_value = 0;
const uint8_t delay_to_produce = 50;
const uint8_t delay_to_consume = 80;
const uint8_t productor_delay = 100;        // delay in ticks
const uint8_t consumer_delay = 100;         // delay in ticks
const uint8_t number_of_productors = 2;
const uint8_t number_of_consumers = 2;
uint8_t buffer;     // Number of items in buffer/storage

semaphore_t produceBuffer;      // Number of items that can be produced
semaphore_t consumeBuffer;      // Number of items that can be consumed
semaphore_t mutexBuffer;        // Control the access to the critical region: 'buffer'

void productor() {
    while (1) {
        sem_down(&produceBuffer);
        OS_delay(delay_to_produce);     // Time to produce

        sem_down(&mutexBuffer);
        buffer++;
        sem_up(&mutexBuffer);

        sem_up(&consumeBuffer);
        OS_delay(productor_delay);       // Interval between produces
    }
}

void consumer() {
    while (1) {
        sem_down(&consumeBuffer);
        OS_delay(delay_to_consume);     // Time to consume

        sem_down(&mutexBuffer);
        buffer--;
        sem_up(&mutexBuffer);

        sem_up(&produceBuffer);
        OS_delay(consumer_delay);       // Interval between consumers
    }
}

int main() {
	uint32_t stack_idleThread[40];

    // start the OS
    OS_init(stack_idleThread, sizeof(stack_idleThread));

    // start the semaphores
    semaphore_init(&produceBuffer, produceBuffer_start_value);
    semaphore_init(&consumeBuffer, consumeBuffer_start_value);
    semaphore_init(&mutexBuffer, 1);

    // start the structs of producers and consumers
    struct struct_threads productors_struct[number_of_productors];
    struct struct_threads consumers_struct[number_of_consumers];

    // start producers threads
    for (uint8_t i = 0; i < number_of_productors; i++){
        OSThread_start(&(productors_struct[i].TCB_thread),
                   (2*i+1), /* priority */
                   &productor,
                   productors_struct[i].stack_thread, sizeof(productors_struct[i].stack_thread));
    }

    // start consumers threads
    for (uint8_t i = 0; i < number_of_consumers; i++){
        OSThread_start(&(consumers_struct[i].TCB_thread),
                   (2*i+2), /* priority */
                   &consumer,
                   consumers_struct[i].stack_thread, sizeof(consumers_struct[i].stack_thread));
    }

    /* transfer control to the RTOS to run the threads */
    OS_run();
}
