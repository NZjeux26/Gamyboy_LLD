#include <cpu.h>
#include <emu.h>
#include <bus.h>


cpu_contex ctx = {0};

void cpu_init() {

}

static void fetch_instruction(){
    ctx.cur_opcode = bus_read(ctx.regs.pc++);//read next opcode, inc PC by 1
    ctx.cur_inst = instruction_by_opcode(ctx.cur_opcode);//get the instruction

    if (ctx.cur_inst == NULL){//if the current instruction is blank, throw
        printf("Unknown Instruction! %02X\n", ctx.cur_opcode);
        exit(-7);
    }
}

static void fetch_data(){
    ctx.mem_dest = 0;
    ctx.dest_is_mem = false;

    switch(ctx.cur_inst->mode){
        case AM_IMP: return; //nothing needs to be read so return
        case AM_R://fetch data from register
            ctx.fetch_data = cpu_read_reg(ctx.cur_inst->reg_1);
            return;
        case AM_R_D8://take 8bu value and transfer to register
            ctx.fetch_data = bus_read(ctx.regs.pc);
            emu_cycles(1);//fetch data from PC, inc by one CPU cycle
            ctx.regs.pc++;//inc the PC
            return;
        case AM_D16: {//read 16bit value
            u16 lo = bus_read(ctx.regs.pc);//read program counter
            emu_cycles(1);//cycle

            u16 hi = bus_read(ctx.regs.pc + 1);//read high value
            emu_cycles(1);

            ctx.fetch_data = lo | (hi << 8);// the fetched data is the lo data OR'd with the hi value shifted.

            ctx.regs.pc += 2;
            return;
        }
        default:
            printf("UNknown addressing mode! %d\n", ctx.cur_inst->mode);
            exit(-7);
            return;
    }
}

static void execute(){
    printf("Not doing this quite yet! \n");
}

bool cpu_step() {
   
   if(!ctx.halted){//if the CPU is not halted
    fetch_instruction();//fetch the instruction
    fetch_data();//get the instruction data
    execute();//execute it
   }
   
    return false;
}
