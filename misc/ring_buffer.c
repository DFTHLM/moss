#include "ring_buffer.h"

void rb_init(ring_buffer_t *rb) {
    rb->head = 0;
    rb->tail = 0;
}

int rb_is_empty(ring_buffer_t *rb) {
    return rb->head == rb->tail;
}

int rb_is_full(ring_buffer_t *rb) {
    return ((rb->head + 1) % BUFFER_SIZE) == rb->tail;
}

int rb_put(ring_buffer_t *rb, char c) {
    if (rb_is_full(rb)) return -1; // buffer full
    rb->data[rb->head] = c;
    rb->head = (rb->head + 1) % BUFFER_SIZE;
    return 0;
}

int rb_get(ring_buffer_t *rb, char *c) {
    if (rb_is_empty(rb)) return -1; // buffer empty
    *c = rb->data[rb->tail];
    rb->tail = (rb->tail + 1) % BUFFER_SIZE;
    return 0;
}

