#include "instructions.h"

void dex(CPU_6502 *cpu) {
    cpu->registerX--;

    if (cpu->registerX == 0) {
        cpu->status = cpu->status | 0b00000010;
    } else {
        cpu->status = cpu->status & 0b11111101;
    }

    if ((cpu->registerX & 0b10000000) != 0b00000000) {
        cpu->status = cpu->status | 0b10000000;
    } else {
        cpu->status = cpu->status & 0b01111111;
    }
}

void dey(CPU_6502 *cpu) {
    cpu->registerY--;

    if (cpu->registerY == 0) {
        cpu->status = cpu->status | 0b00000010;
    } else {
        cpu->status = cpu->status & 0b11111101;
    }

    if ((cpu->registerY & 0b10000000) != 0b00000000) {
        cpu->status = cpu->status | 0b10000000;
    } else {
        cpu->status = cpu->status & 0b01111111;
    }
}

void lda(CPU_6502 *cpu, unsigned char *instruction, AddressingMode mode) {
    switch (mode) {
        case Immediate: cpu->accumulator = instruction[1]; break;
        case Absolute: cpu->accumulator = memory[instruction[2]<<4 | instruction[1]];
        case XIndexedAbsolute: break;
        case YIndexedAbsolute: break;
        case ZeroPage: break;
        case XIndexedZeroPage: break;
        case XIndexedZeroPageIndirect: break;
        case ZeroPageIndirectYIndexed: break;
    }

    if (cpu->accumulator == 0) {
        cpu->status = cpu->status | 0b00000010;
    } else {
        cpu->status = cpu->status & 0b11111101;
    }

    if ((cpu->accumulator & 0b10000000) != 0b00000000) {
        cpu->status = cpu->status | 0b10000000;
    } else {
        cpu->status = cpu->status & 0b01111111;
    }
}