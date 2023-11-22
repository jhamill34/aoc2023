#pragma once

#include <cstdlib>
#include <cstdio>

#define INITIAL_BUFFER_SIZE 1024

typedef struct Buffer {
  char *data;
  size_t size;
  size_t capacity;
} Buffer;

void make_buffer(Buffer &buffer);
void grow(Buffer &buffer);
void compact(Buffer &buffer);
void fill_buffer(Buffer &buffer, FILE *fp);
void read_all(Buffer &buffer, FILE *fp);

char *read_file(const char *filename);

