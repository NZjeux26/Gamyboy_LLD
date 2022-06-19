#pragma once

#include <common.h>
#include <instructions.h>
typedef struct 
{
    u8 a;
    u8 f;
    u8 b;
    u8 c;
    u8 d;
    u8 e;
    u8 h;
    u8 l;
    u16 pc;
    u16 sp;   
} cpu_registers; //CPU registers

typedef struct //what the CPU is doing
{
    cpu_registers regs;

    u16 fetch_data;
    u16 mem_dest;
    u16 cur_opcode;
    instruction *cur_inst;

    bool halted;
    bool stepping;
} cpu_contex;


void cpu_init();
bool cpu_step();
