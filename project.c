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
    // Adds the 2 unsigned ints
    if (ALUControl == '0')
    {
        *ALUresult = A + B;
    }

    // Subtracts the 2 unsigned ints
    else if (ALUControl == '1')
    {
        *ALUresult = A - B;
    }

    // Result is 1 if A is less than B, otherwise 0 (A and B are signed ints)
    else if (ALUControl == '2')
    {
        *ALUresult = (int)A < (int)B;
    }

    // Result is 1 if A is less than B, otherwise 0 (A and B are unsigned ints)
    else if (ALUControl == '3')
    {
        *ALUresult = A < B;
    }

    // Uses AND bitwise operator on A and B 
    else if (ALUControl == '4')
    {
        *ALUresult = A & B;
    }

    // Uses OR bitwise operator on A and B 
    else if (ALUControl == '5')
    {
        *ALUresult = A | B;
    }

    // Bit shifts B to the left by 16 bits
    else if (ALUControl == '6')
    {
        B = B << 16;
    }

    // Uses NOT bitwise operator on A
    else if (ALUControl == '7')
    {
        *ALUresult = ~A;
    }

    // Result is 1 if A = B, otherwise 0
    *Zero = ((A - B) == 0) ? '1' : '0';
}

/* Instruction Fetch */
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{
    if (PC % 4 == 0 && PC < 65535)
    {
        // Fetches instruction in memory from PC
        // Divides PC by 4 (>> 2) to get Mem[1], Mem[2], Mem[3], etc
        *instruction = Mem[PC >> 2];
    }

    // If PC isn't word aligned (not a multiple of 4)
    else
    {
        return 1;
    }
}

/* Instruction Partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{
    // Uses bitmasking to extract parts of a 32 bit unsigned int
    *op = (instruction & (63 << 26)) >> 26;
    *r1 = (instruction & (31 << 21)) >> 21;
    *r2 = (instruction & (31 << 16)) >> 16;
    *r3 = (instruction & (31 << 11)) >> 11;
    *funct = (instruction & 63);
    *offset = (instruction & 65535);
    *jsec = (instruction & ~(63 << 26));
}

/* Instruction Decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{   
    // add, slt, sltu
    if (op == 0)
    {
        controls->RegDst = '1';
        controls->Jump = '0';
        controls->Branch = '0';
        controls->MemRead = '0';
        controls->MemtoReg = '0';
        controls->ALUOp = '7';
        controls->MemWrite = '0';
        controls->ALUSrc = '0';
        controls->RegWrite = '1';
    }

    // j
    else if (op == 2)
    {
        controls->RegDst = '2';
        controls->Jump = '1';
        controls->Branch = '0';
        controls->MemRead = '0';
        controls->MemtoReg = '2';
        controls->ALUOp = '0';
        controls->MemWrite = '0';
        controls->ALUSrc = '2';
        controls->RegWrite = '0';
    }

    // beq
    else if (op == 4)
    {
        controls->RegDst = '2';
        controls->Jump = '0';
        controls->Branch = '1';
        controls->MemRead = '0';
        controls->MemtoReg = '2';
        controls->ALUOp = '1';
        controls->MemWrite = '0';
        controls->ALUSrc = '0';
        controls->RegWrite = '0';
    }

    // addi
    else if (op == 8)
    {
        controls->RegDst = '0';
        controls->Jump = '0';
        controls->Branch = '0';
        controls->MemRead = '0';
        controls->MemtoReg = '0';
        controls->ALUOp = '0';
        controls->MemWrite = '0';
        controls->ALUSrc = '1';
        controls->RegWrite = '1';
    }

    // slti
    else if (op == 10)
    {
        controls->RegDst = '0';
        controls->Jump = '0';
        controls->Branch = '0';
        controls->MemRead = '0';
        controls->MemtoReg = '0';
        controls->ALUOp = '2';
        controls->MemWrite = '0';
        controls->ALUSrc = '1';
        controls->RegWrite = '1';
    }

    // sltiu
    else if (op == 11)
    {
        controls->RegDst = '0';
        controls->Jump = '0';
        controls->Branch = '0';
        controls->MemRead = '0';
        controls->MemtoReg = '0';
        controls->ALUOp = '3';
        controls->MemWrite = '0';
        controls->ALUSrc = '1';
        controls->RegWrite = '1';
    }

    // lui
    else if (op == 15)
    {
        controls->RegDst = '0';
        controls->Jump = '0';
        controls->Branch = '0';
        controls->MemRead = '0';
        controls->MemtoReg = '0';
        controls->ALUOp = '6';
        controls->MemWrite = '0';
        controls->ALUSrc = '1';
        controls->RegWrite = '1';
    }

    // lw
    else if (op == 34)
    {
        controls->RegDst = '0';
        controls->Jump = '0';
        controls->Branch = '0';
        controls->MemRead = '1';
        controls->MemtoReg = '1';
        controls->ALUOp = '0';
        controls->MemWrite = '0';
        controls->ALUSrc = '1';
        controls->RegWrite = '1';
    }

    // sw
    else if (op == 43)
    {
        controls->RegDst = '2';
        controls->Jump = '0';
        controls->Branch = '0';
        controls->MemRead = '0';
        controls->MemtoReg = '2';
        controls->ALUOp = '0';
        controls->MemWrite = '1';
        controls->ALUSrc = '1';
        controls->RegWrite = '0';
    }
    
    // If the instruction is invalid
    else
    {
        return 1;
    }

    return 0;
}

/* Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{
    *data1 = Reg[r1];
    *data2 = Reg[r2];
}

/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{
    // If the offset value is negative
    if ((offset >> 15) == 1)
    {
        *extended_value = offset | ~65535;
    }

    // If the offset value is positive
    else
    {
        *extended_value = offset & 65535;
    }
}

/* ALU Operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{
    char ALUControl = ALUOp;

    // R-type instruction only
    if (ALUOp == '7')
    {   
        // add
        if (funct == 32)
        {
            ALUControl = '0';
        }

        // sub
        if (funct == 34)
        {
            ALUControl = '1';
        }

        // and
        if (funct == 36)
        {
            ALUControl = '4';
        }

        // or
        if (funct == 37)
        {
            ALUControl = '5';
        }

        // slt
        else if (funct == 42)
        {
            ALUControl = '2';
        }

        // sltu
        else if (funct == 43)
        {
            ALUControl = '3';
        }

        else
        {
            return 1;
        }
    }

    // Sign extended value for immediates or data2 for other register
    unsigned value = (ALUSrc == 1) ? extended_value : data2;

    ALU(data1, value, ALUControl, ALUresult, Zero);

    return 0;
}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{
    if (MemRead == '1')
    {   
        // Memory is word-aligned and to ensure ALUresult isn't out of bounds (65535 = FFFF)
        if (ALUresult % 4 == 0 && ALUresult < 65535)
        {
            // Gets value from data memory
            *memdata = Mem[ALUresult >> 2];
        }

        else 
        {
            return 1;
        }
    }

    if (MemWrite == '1')
    {
        if (ALUresult % 4 == 0 && ALUresult < 65535)
        {
            // Adds value to data memory
            Mem[ALUresult >> 2] = data2;
        }

        else 
        {
            return 1;
        }
    }

    return 0;
}

/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{
    // Write to the register
    if (RegWrite == '1')
    {   
        // Value comes from data memory
        if (MemtoReg == '1')
        {
            Reg[r2] = memdata;
        }

        // Value comes from ALU
        else if (MemtoReg == '0')
        {
            // Reserved for another register
            if (RegDst == '1')
            {
                Reg[r3] = ALUresult;
            }

            else if (RegDst == '0')
            {
                Reg[r2] = ALUresult;
            }
        }
    }
}

/* PC Update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{
    *PC += 4;

    // Branching leads to these calculations
    if (Zero == '1' && Branch == '1')
    {
        *PC += (extended_value << 2);
    }

    // Jumping leads to these calculations
    if (Jump == '1')
    {
        *PC = (*PC & 4026531840) | (jsec << 2);
    }

}
