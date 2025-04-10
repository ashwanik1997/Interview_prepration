#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 5 // Define the size of the circular buffer

typedef struct {
    int buffer[BUFFER_SIZE]; // Array to store the buffer
    int head;               // Points to the front of the buffer
    int tail;               // Points to the end of the buffer
    int size;               // Tracks the current number of elements
} CircularBuffer;

// Initialize the circular buffer
void initBuffer(CircularBuffer* cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->size = 0;
}

// Check if the buffer is full
int isFull(CircularBuffer* cb) {
    return cb->size == BUFFER_SIZE;
}

// Check if the buffer is empty
int isEmpty(CircularBuffer* cb) {
    return cb->size == 0;
}

// Add an element to the circular buffer
void enqueue(CircularBuffer* cb, int item) {
    if (isFull(cb)) {
        printf("Buffer is full! Cannot enqueue %d\n", item);
        return;
    }

    cb->buffer[cb->tail] = item;
    cb->tail = (cb->tail + 1) % BUFFER_SIZE; // Wrap around the buffer
    cb->size++;
}

// Remove an element from the circular buffer
int dequeue(CircularBuffer* cb) {
    if (isEmpty(cb)) {
        printf("Buffer is empty! Cannot dequeue\n");
        return -1; // Return a special value to indicate failure
    }

    int item = cb->buffer[cb->head];
    cb->head = (cb->head + 1) % BUFFER_SIZE; // Wrap around the buffer
    cb->size--;
    return item;
}

// Display the buffer's current elements
void displayBuffer(CircularBuffer* cb) {
    printf("Circular Buffer: ");
    if (isEmpty(cb)) {
        printf("Empty\n");
        return;
    }

    for (int i = 0, index = cb->head; i < cb->size; i++) {
        printf("%d ", cb->buffer[index]);
        index = (index + 1) % BUFFER_SIZE; // Wrap around the buffer
    }
    printf("\n");
}

int main() {
    CircularBuffer cb;
    initBuffer(&cb);

    enqueue(&cb, 10);
    enqueue(&cb, 20);
    enqueue(&cb, 30);
    enqueue(&cb, 40);
    enqueue(&cb, 50); // Buffer becomes full
    displayBuffer(&cb);

    enqueue(&cb, 60); // Attempt to enqueue when buffer is full

    printf("Dequeued: %d\n", dequeue(&cb));
    printf("Dequeued: %d\n", dequeue(&cb));
    displayBuffer(&cb);

    enqueue(&cb, 60); // Enqueue after dequeuing elements
    displayBuffer(&cb);

    return 0;
}
