#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
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
        fprintf(stderr, "Initialising Puritan failed: errno %i\n", result);
        return result;
    }

    result = puritan_vm_load_program_file(&vm, "example.bin");
    if (result != 0)
    {
        fprintf(stderr, "Loading program failed: errno %i\n", result);
        return result;
    }

    result = puritan_vm_run(&vm);

    puritan_vm_free(&vm);
    return result;
}
