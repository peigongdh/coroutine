#include "coroutine.h"
#include <stdio.h>

int i = 0;

static void
producer(struct schedule *S) {
    while (1) {
        if (i >= 5) {
            break;
        }
        i++;
        printf("produce: %d\n", i);
        coroutine_yield(S);
    }
}

static void
consumer(struct schedule *S, int producerID) {
    while (1) {
        if (i >= 5) {
            break;
        }
        printf("producer_status: %d\n", coroutine_status(S, producerID));
        coroutine_resume(S, producerID);
        printf("consume: %d\n", i);
    }
}

int
main() {
    int producerID;
    struct schedule *S = coroutine_open();

    producerID = coroutine_new(S, producer, NULL);
    consumer(S, producerID);

    coroutine_close(S);
    return 0;
}