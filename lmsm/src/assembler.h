//
// Created by carson on 11/15/21.
//

#ifndef LMSM_ASSEMBLER_H
#define LMSM_ASSEMBLER_H

//===================================================================
//  Error messages
//===================================================================
extern char *ASM_ERROR_UNKNOWN_INSTRUCTION;
extern char *ASM_ERROR_ARG_REQUIRED;
extern char *ASM_ERROR_BAD_LABEL;
extern char *ASM_ERROR_OUT_OF_RANGE;

//===================================================================
//  Represents an asm_instruction for the LMSM architecture
//===================================================================
typedef struct asm_instruction {
    char* instruction;         // the type of the asm_instruction
    char* label;               // the label of the asm_instruction if any
    char* label_reference;     // the label this asm_instruction refers to, if any
    int value;                 // the value of the asm_instruction, if any
    int slots;                // the offset of the asm_instruction, if any
    int offset;                // the offset of the asm_instruction, if any
    struct asm_instruction * next; // the next asm_instruction
} asm_instruction;

//===================================================================
//  The result of an assembly compilation
//===================================================================
typedef struct asm_compilation_result {
    char* error;         // any error that occurred (e.g. a missing label)
    asm_instruction *root;   // the root asm_instruction of the compilation
    int code[100];       // the machine code generated by the assembler
} asm_compilation_result;

//===================================================================
//  API
//===================================================================

asm_instruction * asm_make_instruction(char* type, char *label, char *label_reference, int value, asm_instruction * predecessor);
void asm_delete_instruction(asm_instruction *instruction);

asm_compilation_result *asm_make_compilation_result();
void asm_delete_compilation_result(asm_compilation_result *result);

void asm_parse_src(asm_compilation_result *result, char *original_src);

void asm_gen_code_for_instruction(asm_compilation_result  * result, asm_instruction *instruction);

asm_compilation_result * asm_assemble(char * src);

int asm_is_instruction(char * token);
int asm_is_num(char * token);

void asm_delete_compilation_result(asm_compilation_result *result);

#endif //LMSM_ASSEMBLER_H