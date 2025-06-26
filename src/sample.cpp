#include "sample.h"

void cb_init(CircularBuffer *cb, uint8_t *buffer_array, uint8_t size){
    cb->buffer = buffer_array;
    cb->head = 0;
    cb->tail = 0;
    cb->size = size;
    cb->full = false;
}

bool cb_push(CircularBuffer *cb, uint8_t data){
    if(cb_is_full(cb)) return false;
    cb->buffer[cb->head] = data;
    cb->head = (cb->head + 1) % cb->size;
    cb->full = (cb->head == cb->tail);
    return true;
}

bool cb_pop(CircularBuffer *cb, uint8_t *data){
    if(cb_is_empty(cb)) return false;
    *data = cb->buffer[cb->tail];
    cb->tail = (cb->tail + 1) % cb->size;
    cb->full = false;
    return true;
}

bool cb_is_empty(CircularBuffer *cb){
    return (!cb->full && cb->head == cb->tail);
}

bool cb_is_full(CircularBuffer *cb){
    return cb->full;
}

bool cb_peek(CircularBuffer *cb, uint8_t *data){
    if(cb_is_empty(cb)) return false;
    *data = cb->buffer[cb->tail];
    return true;
}

bool cb_clear(CircularBuffer *cb){

    for(int i = cb->size - 1; i >= 0; i--){
        cb->buffer[i] = 0;
    }
    cb->head = 0;
    cb->tail = 0;
    cb->full = false;

    return true;
}