#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>

#include <puritan/puritan.h>

#include "loader.h"

int puritan_vm_init(puritan_vm_t *vm)
{
    if (vm == NULL)
    {
        return EINVAL;
    }

    return puritan_exec_ctx_init(&vm->exec_ctx);
}

int puritan_exec_ctx_init(puritan_exec_ctx_t *ctx)
{
    memset(ctx, 0, sizeof(puritan_exec_ctx_t));
    ctx->ready = 0;
    return 0;
}

int puritan_vm_load_program(puritan_vm_t *vm, uint16_t *bytes, size_t len)
{
    puritan_exec_ctx_t *ctx = &vm->exec_ctx;

    program_loader_t loader = new_loader(bytes, len);
    if (load_program(&loader) != 0)
    {
        return EINVAL;
    }

    ctx->program = loader.program;
    ctx->program_length = loader.program_length;
    ctx->ready = 1;

    return 0;
}

int puritan_vm_load_program_file(puritan_vm_t *vm, char *file_name)
{
    struct stat st;

    if (stat(file_name, &st) != 0)
    {
        return EINVAL;
    }

    FILE* f_handle = fopen(file_name, "rb");
    if (f_handle == NULL)
    {
        return EINVAL;
    }

    uint16_t *bin = malloc(sizeof(uint16_t) * st.st_size);
    if (bin == NULL)
    {
        return ENOMEM;
    }

    // TODO: Check read length/retry
    fread(bin, sizeof(uint16_t), st.st_size, f_handle);

    return puritan_vm_load_program(vm, bin, st.st_size);
}

int puritan_exec_ctx_run(puritan_exec_ctx_t *ctx)
{
    if (ctx->ready != 1)
    {
        return EINVAL;
    }

    while (!ctx->exit) {
        if (ctx->pc == ctx->program_length)
        {
            ctx->exit = 1;
            continue;
        }

        printf("%#04x\n", ctx->program[ctx->pc++]);
    }

    return 0;
}

void puritan_exec_ctx_free(puritan_exec_ctx_t *ctx)
{
    free(ctx->program);
    ctx->program = NULL;
}

void puritan_vm_free(puritan_vm_t *vm)
{
    puritan_exec_ctx_free(&vm->exec_ctx);
}

int puritan_vm_run(puritan_vm_t *vm)
{
    puritan_exec_ctx_t *ctx = &vm->exec_ctx;
    return puritan_exec_ctx_run(ctx);
}
