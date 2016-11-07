#include <stdio.h>
#include <puritan/puritan.h>

const uint16_t EXAMPLE_PROGRAM[] = {
    0x0,
    0x1
};
const int EXAMPLE_PROGRAM_LENGTH = 2;

int main(int argc, char **argv)
{
    puritan_vm_t vm;

    int result = puritan_vm_init(&vm);
    if (result != 0)
    {
        fprintf(stderr, "Initialising Puritan failed: errno %i", result);
        return result;
    }

    result = puritan_vm_load_program(&vm, (uint16_t *) &EXAMPLE_PROGRAM, EXAMPLE_PROGRAM_LENGTH);

    for (int i = 0; i < vm.exec_ctx.program_length; i++)
    {
        printf("%#04x ", vm.exec_ctx.program[i]);
    }
    printf("\n");

}
