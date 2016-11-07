#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <puritan/puritan.h>

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

    if ((ctx->program = malloc(sizeof(uint16_t) * len)) == NULL)
    {
        return ENOMEM;
    }

    memcpy(ctx->program, bytes, sizeof(uint16_t) * len);

    ctx->program_length = len;
    ctx->ready = 1;

    return 0;
}
