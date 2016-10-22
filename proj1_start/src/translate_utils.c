#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "translate_utils.h"

void write_inst_string(FILE* output, const char* name, char** args, int num_args) {
    fprintf(output, "%s", name);
    for (int i = 0; i < num_args; i++) {
        fprintf(output, " %s", args[i]);
    }
    fprintf(output, "\n");
}

void write_inst_hex(FILE *output, uint32_t instruction) {
    fprintf(output, "%08x\n", instruction);
}

int is_valid_label(const char* str) {
    if (!str) {
        return 0;
    }

    int first = 1;
    while (*str) {
        if (first) {
            if (!isalpha((int) *str) && *str != '_') {
                return 0;   // does not start with letter or underscore
            } else {
                first = 0;
            }
        } else if (!isalnum((int) *str) && *str != '_') {
            return 0;       // subsequent characters not alphanumeric
        }
        str++;
    }
    return first ? 0 : 1;   // empty string is invalid
}

/* Translate the input string into a signed number. The number is then 
   checked to be within the correct range (note bounds are INCLUSIVE)
   ie. NUM is valid if LOWER_BOUND <= NUM <= UPPER_BOUND. 

   The input may be in either positive or negative, and be in either
   decimal or hexadecimal format. It is also possible that the input is not
   a valid number. Fortunately, the library function strtol() can take 
   care of all that (with a little bit of work from your side of course).
   
 */
int translate_num(long int* output, const char* str, long int lower_bound, 
    long int upper_bound) {
    if (!str || !output) {
        return -1;
    }
   
    char* end;
    if (strtol(str, NULL, 0) == 0 && strcmp(str, "0") != 0 && strcmp(str, "0x0") != 0) return -1;
    *output = strtol(str, &end, 0);
    if (lower_bound <= *output && *output <= upper_bound && *end == 0) return 0;
    else return -1;
}

/* Translates the register name to the corresponding register number. Please
   see the MIPS Green Sheet for information about register numbers.

   Returns the register number of STR or -1 if the register name is invalid.
 */
int translate_reg(const char* str) {
    if (strcmp(str, "XZR") == 0)      return 31;
	else if (strcmp(str, "X31") == 0)    return 31;
	else if (strcmp(str, "X30") == 0)    return 30;
	else if (strcmp(str, "LR") == 0)    return 30;
	
	else if (strcmp(str, "X29") == 0)    return 29;
	else if (strcmp(str, "FP") == 0)    return 29;
	
    else if (strcmp(str, "X28") == 0)   return 28;
	else if (strcmp(str, "SP") == 0)   return 28;
    else if (strcmp(str, "X27") == 0)   return 27;
    else if (strcmp(str, "X26") == 0)   return 26;
	else if (strcmp(str, "X25") == 0)   return 25;
    else if (strcmp(str, "X24") == 0)   return 24;
    
    /* YOUR CODE HERE */
	
	

    else                                return -1;
}
