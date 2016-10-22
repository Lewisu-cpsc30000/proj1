#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tables.h"
#include "translate_utils.h"
#include "translate.h"

/* Writes instructions during the assembler's first pass to OUTPUT. The case
   for general instructions has already been completed, but you need to write
   code to translate the li and blt pseudoinstructions. Your pseudoinstruction 
   expansions should not have any side effects.

   NAME is the name of the instruction, ARGS is an array of the arguments, and
   NUM_ARGS specifies the number of items in ARGS.

   Error checking for regular instructions are done in pass two. However, for
   pseudoinstructions, you must make sure that ARGS contains the correct number
   of arguments. You do NOT need to check whether the registers / label are 
   valid, since that will be checked in part two.


   Use fprintf() to write. If writing multiple instructions, make sure that 
   each instruction is on a different line.

   Returns the number of instructions written (so 0 if there were any errors).
 */
unsigned write_pass_one(FILE* output, const char* name, char** args, int num_args) {
	
		write_inst_string(output, name, args, num_args);
		return 1;
	
}

/* Writes instructions during the assembler's first pass to OUTPUT. The case
   for general instructions has already been completed, but you need to write
   code to translate the li and blt pseudoinstructions. Your pseudoinstruction 
   expansions should not have any side effects.

   NAME is the name of the instruction, ARGS is an array of the arguments, and
   NUM_ARGS specifies the number of items in ARGS.

   
/* Writes the instruction in hexadecimal format to OUTPUT during pass #2.
   
   NAME is the name of the instruction, ARGS is an array of the arguments, and
   NUM_ARGS specifies the number of items in ARGS. 

   The symbol table (SYMTBL) is given for any symbols that need to be resolved
   at this step. If a symbol should be relocated, it should be added to the
   relocation table (RELTBL), and the fields for that symbol should be set to
   all zeros. 

   You must perform error checking on all instructions and make sure that their
   arguments are valid. If an instruction is invalid, you should not write 
   anything to OUTPUT but simply return -1. MARS may be a useful resource for
   this step.

   Note the use of helper functions. Consider writing your own! If the function
   definition comes afterwards, you must declare it first (see translate.h).

   Returns 0 on success and -1 on error. 
 */
int translate_inst(FILE* output, const char* name, char** args, size_t num_args, uint32_t addr,
	SymbolTable* symtbl, SymbolTable* reltbl) {
	if (strcmp(name, "ADDS") == 0)       return write_rtype (0x558, output, args, num_args);
	else if (strcmp(name, "ORR") == 0)    return write_rtype (0x550, output, args, num_args);
	else if (strcmp(name, "SUBS") == 0)  return write_rtype (0x758, output, args, num_args);
	
	else if (strcmp(name, "LSL") == 0)   return write_shift (0x69B, output, args, num_args);
	else if (strcmp(name, "CBZ") == 0)   return write_branch (0xB4, output, args, num_args, addr, symtbl);
	
	/* YOUR CODE HERE  for the remaining instructions*/
	
	
	
	
	else                                 return -1;
}

int write_rtype(uint16_t opcode, FILE* output, char** args, size_t num_args) {
	if (num_args != 3) {
		return -1;
	}
	
	int rd = translate_reg(args[0]);
	int rs = translate_reg(args[1]);
	int rt = translate_reg(args[2]);

	if (rd == -1 || rs == -1 || rt == -1) {
		return -1;
	} 

	
	uint32_t instruction = rd + (rs << 5) + (rt << 16) + (opcode << 21);
	write_inst_hex(output, instruction);
	return 0;
}


int write_shift(uint16_t opcode, FILE* output, char** args, size_t num_args) {
	if (num_args != 3) {
		return -1;
	}

	long int shamt;
	int rd = translate_reg(args[0]);
	int rs = translate_reg(args[1]);
	int err = translate_num(&shamt, args[2], 0, 63);

	if (err == -1 || rd == -1 || rs == -1) {
	  return -1;
	}

	
	
	uint32_t instruction = rd + (rs << 5) + (shamt << 10) + (opcode << 21);
	
	
	write_inst_hex(output, instruction);
	return 0;
}

int write_br(uint16_t opcode, FILE* output, char** args, size_t num_args) {
	if (num_args != 1) {
		return -1;
	}
	int rs = translate_reg(args[0]);
	if (rs == -1) {
	  return -1;
	}

	uint32_t instruction = (opcode << 21) + rs ;
	write_inst_hex(output, instruction);
	return 0;
}






int write_branch(uint8_t opcode, FILE* output, char** args, size_t num_args, 
	uint32_t addr, SymbolTable* symtbl) {
	if (num_args != 2) {
		return -1;
	}

	int rs = translate_reg(args[0]);
	
	char* label = args[1];

	int64_t add = get_addr_for_symbol(symtbl, label);
	uint16_t imm = (add - addr - 4) / 4;
	if (add == -1 || rs == -1 ) {
		return -1;
	}

	uint32_t instruction = (opcode << 24) + rs + (imm << 5);
	write_inst_hex(output, instruction);
	return 0;
}

/* ADD your code here: Functions in translate.h that are not yet implemented */


