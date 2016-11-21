#ifndef __LOADER_H
#define __LOADER_H

#include <stdint.h>
#include <stddef.h>

typedef struct {
    uint16_t *bin;
    size_t bin_length;
    size_t bin_offset;

    uint16_t *program;
    size_t program_length;
} program_loader_t;

typedef struct __attribute__((packed)) {
    uint16_t magic[8];
    uint64_t sym_table_length;
    uint64_t program_length;
} program_header_t;

extern const uint16_t MAGIC[8];
extern const size_t MAGIC_LEN;

program_loader_t new_loader(uint16_t *bytes, size_t len);
int load_program(program_loader_t *loader);

#endif
