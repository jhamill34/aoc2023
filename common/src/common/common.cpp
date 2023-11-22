#include "common.h"
#include <cstring>

void make_buffer(Buffer &buffer) {
  char *data = (char *)malloc(INITIAL_BUFFER_SIZE);
  memset(data, 0, INITIAL_BUFFER_SIZE);
  buffer = {data, 0, INITIAL_BUFFER_SIZE};
}

void grow(Buffer &buffer) {
  char *new_data = (char *)malloc(buffer.capacity * 2);
  memset(new_data, 0, buffer.capacity * 2);
  memcpy(new_data, buffer.data, buffer.size);
  free(buffer.data);

  buffer.data = new_data;
  buffer.capacity *= 2;
}

void compact(Buffer &buffer) {
  char *new_data = (char *)malloc(buffer.size);
  memcpy(new_data, buffer.data, buffer.size);
  free(buffer.data);

  buffer.data = new_data;
  buffer.capacity = buffer.size;
}

void fill_buffer(Buffer &buffer, FILE *fp) {
	size_t num_bytes = buffer.capacity - buffer.size;
	size_t bytes_read = fread(buffer.data + buffer.size, 1, num_bytes, fp);

	buffer.size += bytes_read; 
}

void read_all(Buffer &buffer, FILE *fp) {
	while (!feof(fp)) {
		fill_buffer(buffer, fp);

		if (buffer.size == buffer.capacity) {
			grow(buffer);
		}
	}
	compact(buffer);
}

char *read_file(const char *filename) {
	FILE *fp;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		perror("Error opening file\n");
		exit(1);
	}
	
	Buffer buffer;
	make_buffer(buffer);
	read_all(buffer, fp);
	fclose(fp);

	return buffer.data;
}

