#ifndef TRANSLATE_H
#define TRANSLATE_H

#include <stdint.h>

/*-----------------------------------------------------*/

/* IMPLEMENT ME - see documentation in translate.c */
int translate_inst(FILE* output, const char* name, char** args, size_t num_args, 
    uint32_t addr, SymbolTable* symtbl, SymbolTable* reltbl);

/* Declaring helper functions: */

int write_rtype(uint16_t opcode, FILE* output, char** args, size_t num_args); /* for adds, subs, and orr instructions */


int write_shift(uint16_t opcode, FILE* output, char** args, size_t num_args); /* For lsl instruction */ 

/* SOLUTION CODE BELOW */

int write_br(uint16_t opcode, FILE* output, char** args, size_t num_args);    /* For br (branch to register) instruction */

int write_imm(uint16_t opcode, FILE* output, char** args, size_t num_args); /* for addi and orri instructions */



int write_mem(uint16_t opcode, FILE* output, char** args, size_t num_args); /* for ldurw, ldurb, sturw, and sturb instructions */
                      

int write_branch(uint8_t opcode, FILE* output, char** args, size_t num_args, 
    uint32_t addr, SymbolTable* symtbl);									/* for cbz and cbnz instructions */

int write_jump(uint8_t opcode, FILE* output, char** args, size_t num_args, 
    uint32_t addr, SymbolTable* reltbl);                                   /* for b and bl instructions */

#endif
