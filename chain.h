/**
 * Define a chain of instruction
 */

#ifndef __CHAIN_H_
#define __CHAIN_H_

#include "utils.h"
#include "chunk.h"
#include "map.h"
#include "linked_list.h"
#include "xed-interface.h"

/*
 * Using -isystem qemu te handle warnings
 */
#include <include/exec/user/abitypes.h>

void gen_intermediate_code(CPUArchState *env, struct TranslationBlock *tb);

typedef struct chain_t chain_t;

struct chain_t
{
    uint64_t (*get_addr)(chain_t *);
    char *(*get_str)(chain_t *);
    chunk_t (*get_chunk)(chain_t *);
    linked_list_t *(*get_instructions)(chain_t *);
    map_t *(*get_map)(chain_t*);
    map_t *(*get_map_prefix)(chain_t*, chunk_t);

    void (*set_addr)(chain_t *, uint64_t);
    void (*set_str)(chain_t *, char *);
    void (*set_chunk)(chain_t *, chunk_t);
    void (*set_instructions)(chain_t *, linked_list_t *);
    void (*set_Z3_context)(chain_t *, Z3_context ctx);

    void (*destroy)(chain_t *);
};

chain_t *chain_create_from_string(uint64_t addr, chunk_t chain_str);
chain_t *chain_create_from_insn(uint64_t addr, linked_list_t *instructions);
chain_t *chain_create(uint64_t addr, char *str, chunk_t chunk, linked_list_t *instructions);

#endif
