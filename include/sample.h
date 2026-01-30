#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t * buffer;
    uint8_t head;
    uint8_t tail;
    size_t size;
    bool full;
} CircularBuffer;

void cb_init(CircularBuffer *cb, uint8_t *buffer_array, uint8_t size);

bool cb_pop(CircularBuffer *cb, uint8_t* data);

bool cb_push(CircularBuffer *cb, uint8_t data);

bool cb_is_empty(CircularBuffer *cb);

bool cb_is_full(CircularBuffer *cb);