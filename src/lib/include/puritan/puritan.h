#ifndef __PURITAN_H
#define __PURITAN_H

#include <stdint.h>

typedef struct {
    int ready;
    int exit;
    int pc;
    uint16_t *program;
    int program_length;
} puritan_exec_ctx_t;

typedef struct {
    puritan_exec_ctx_t exec_ctx;
} puritan_vm_t;

const uint16_t MAGIC[] = {
    0x7e,
    0x61,
    0x6d,
    0x65,
    0x6e,
    0x61,
    0x6d,
    0x79
};

int puritan_vm_init(puritan_vm_t *vm);
int puritan_vm_load_program(puritan_vm_t *vm, uint16_t *bytes, size_t len);
int puritan_vm_run(puritan_vm_t *vm);

int puritan_exec_ctx_init(puritan_exec_ctx_t *ctx);

#endif
