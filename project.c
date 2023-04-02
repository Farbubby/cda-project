#include "spimcore.h"

// I have not used C language code obtained from other students, the 
// Internet, and any other unauthorized sources, either modified or 
// unmodified. If any code in my program was obtained from an authorized 
// source, such as textbook or course notes, that has been clearly noted 
// as a citation in the comments of the program.
// Farhan Mahbub
// farhanmahbub88@Knights.ucf.edu

/* ALU */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{
    if (strcmp(ALUControl, "000") == 0)
    {
        *ALUresult = A + B;
    }

    if (strcmp(ALUControl, "001") == 0)
    {
        *ALUresult = A - B;
    }

    if (strcmp(ALUControl, "010") == 0)
    {
        *ALUresult = ((int)A < (int)B) ? 1 : 0;
    }

    if (strcmp(ALUControl, "011") == 0)
    {
        *ALUresult = (A < B) ? 1 : 0;
    }

    if (strcmp(ALUControl, "100") == 0)
    {
        *ALUresult = A & B;
    }

    if (strcmp(ALUControl, "101") == 0)
    {
        *ALUresult = A | B;
    }

    if (strcmp(ALUControl, "110") == 0)
    {
        *ALUresult = B << 16;
    }

    if (strcmp(ALUControl, "111") == 0)
    {
        *ALUresult = ~A;
    }

    *Zero = ((A - B) == 0) ? "1" : "0";
}

/* Instruction Fetch */
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{
    if (PC % 4 == 0)
    {
        *instruction = Mem[PC];
    }
    else
    {
        return 1;
    }
}

/* Instruction Partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{

}

/* Instruction Decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{

}

/* Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{

}

/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{

}

/* ALU Operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{

}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{

}

/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{

}

/* PC Update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{

}
