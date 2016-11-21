#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "loader.h"

const size_t MAGIC_LEN = 8;
const uint16_t MAGIC[MAGIC_LEN] = {
    0x7e,
    0x61,
    0x6d,
    0x65,
    0x6e,
    0x61,
    0x6d,
    0x79
};

program_loader_t new_loader(uint16_t *bytes, size_t len)
{
    program_loader_t loader = { .bin = bytes, .bin_length = len };
    return loader;
}

int parse_header(program_loader_t *loader)
{
    program_header_t *header = (program_header_t *) loader->bin;

    if (memcmp(header->magic, MAGIC, MAGIC_LEN) != 0)
    {
        return EINVAL;
    }

    loader->program_length = header->program_length;
    loader->bin_offset += sizeof(program_header_t) / sizeof(uint16_t);

    return 0;
}

int parse_program(program_loader_t *loader)
{
    if ((loader->program = malloc(sizeof(uint16_t) * loader->program_length)) == NULL)
    {
        return ENOMEM;
    }

    memcpy(loader->program, loader->bin + loader->bin_offset, sizeof(uint16_t) * loader->program_length);
    return 0;
}

int load_program(program_loader_t *loader)
{
    int result = parse_header(loader);
    if (result != 0)
    {
        return result;
    }

    result = parse_program(loader);
    return result;
}
