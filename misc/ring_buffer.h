#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdint.h>

#define BUFFER_SIZE 512

typedef struct {
    char data[BUFFER_SIZE];
    uint32_t head;
    uint32_t tail;
} ring_buffer_t;

void rb_init(ring_buffer_t *rb);
int rb_put(ring_buffer_t *rb, char c);
int rb_get(ring_buffer_t *rb, char *c);
int rb_is_empty(ring_buffer_t *rb);
int rb_is_full(ring_buffer_t *rb);

#endif
