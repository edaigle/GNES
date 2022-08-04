#include "instructions.h"

void dex(Machine *m) {
    m->registerX--;
    updateZeroFlag(m, m->registerX);
    updateNegativeFlag(m, m->registerX);
}

void dey(Machine *m) {
    m->registerY--;
    updateZeroFlag(m, m->registerY);
    updateNegativeFlag(m, m->registerY);
}

// TODO: refactor these into one paramerized load()

void lda(Machine *m, unsigned char *instruction, AddressingMode mode) {
    m->accumulator = fetchData(m, instruction, mode);
    updateZeroFlag(m, m->accumulator);
    updateNegativeFlag(m, m->accumulator);
}

void ldx(Machine *m, unsigned char *instruction, AddressingMode mode) {
    m->registerX = fetchData(m, instruction, mode);
    updateZeroFlag(m, m->registerX);
    updateNegativeFlag(m, m->registerX);
}

void ldy(Machine *m, unsigned char *instruction, AddressingMode mode) {
    m->registerY = fetchData(m, instruction, mode);
    updateZeroFlag(m, m->registerY);
    updateNegativeFlag(m, m->registerY);
}

void store(Machine *m, unsigned char *instruction, unsigned char *reg, AddressingMode mode) {
    storeData(m, instruction, reg, mode);
    updateZeroFlag(m, *reg);
    updateNegativeFlag(m, *reg);
}

void transfer(Machine *m, unsigned char *from, unsigned char *to, int updateFlags) {
    *to = *from;

    if (updateFlags != 0) {
        updateZeroFlag(m, *to);
        updateNegativeFlag(m, *to);
    }
}

void push(Machine *m, unsigned char *src) {
    m->memory[STACK_BOTTOM | m->stackPointer] = *src;
    m->stackPointer--;
}

void pull(Machine *m, unsigned char *dest) {
    *dest = m->memory[STACK_BOTTOM | (m->stackPointer+1)];
    m->stackPointer++;
}

// questionable
void shift(Machine *m, unsigned char *instruction, AddressingMode mode, ShiftDirection dir) {
    unsigned char* data;
    switch (mode) {
        case Accumulator: data = &m->accumulator; break;
        case Absolute: data = &m->memory[instruction[2]<<8 | instruction[1]]; break;
        case XIndexedAbsolute: data = &m->memory[(instruction[2]<<8 | instruction[1]) + m->registerX]; break;
        case ZeroPage: data = &m->memory[instruction[1]]; break;
        case XIndexedZeroPage: data = &m->memory[instruction[1]+m->registerX]; break;
    }
    
    switch (dir) {
        case Left: if ((*data & 0b10000000) == 0) m->status = (m->status | 0b10000000); else m->status = (m->status | 0b01111111); *data = *data<<1; break;
        case Right: if ((*data &0b00000001) == 1) m->status = (m->status | 0b00000001); else m->status = (m->status | 0b11111110); *data = *data>>1; break; 
    }
    updateZeroFlag(m, *data);
    updateNegativeFlag(m, *data);
}

void rotate(Machine *m, unsigned char *instruction, AddressingMode mode, ShiftDirection dir) {
    // TODO with tests
}

void and(Machine *m, unsigned char *instruction, AddressingMode mode) {
    m->accumulator = (m->accumulator & fetchData(m, instruction, mode));
    updateZeroFlag(m, m->accumulator);
    updateNegativeFlag(m, m->accumulator);
}

void bit(Machine *m, unsigned char *instruction, AddressingMode mode) {
    unsigned char data = fetchData(m, instruction, mode);

    if ((data & 0b01000000) != 0b00000000) {
        m->status = m->status | 0b01000000;
    } else {
        m->status = m->status & 0b10111111;
    }

    updateNegativeFlag(m, data);
    updateZeroFlag(m, m->accumulator & data);
}

void eor(Machine *m, unsigned char *instruction, AddressingMode mode) {
    m->accumulator = (m->accumulator ^ fetchData(m, instruction, mode));
    updateZeroFlag(m, m->accumulator);
    updateNegativeFlag(m, m->accumulator);
}

void ora(Machine *m, unsigned char *instruction, AddressingMode mode) {
    m->accumulator = (m->accumulator | fetchData(m, instruction, mode));
    updateZeroFlag(m, m->accumulator);
    updateNegativeFlag(m, m->accumulator);
}

void clc(Machine *m) {
    m->status = m->status | 0b11111110;
}

void cld(Machine *m) {
    m->status = m->status | 0b11110111;
}

void cli(Machine *m) {
    m->status = m->status | 0b11111011;
}

void clv(Machine *m) {
    m->status = m->status | 0b10111111;
}

void sec(Machine *m) {
    m->status = m->status | 0b00000001;
}

void sed(Machine *m) {
    m->status = m->status | 0b00001000;
}

void sei(Machine *m) {
    m->status = m->status | 0b00000100;
}

// TODO: move these to utils?
void updateZeroFlag(Machine *m, uint8_t result) {
    if (result == 0) {
        m->status = m->status | 0b00000010;
    } else {
        m->status = m->status & 0b11111101;
    }
}

void updateNegativeFlag(Machine *m, uint8_t result) {
    if ((result & 0b10000000) != 0b00000000) {
        m->status = m->status | 0b10000000;
    } else {
        m->status = m->status & 0b01111111;
    }
}

unsigned char fetchData(Machine *m, unsigned char *instruction, AddressingMode mode) {
    switch (mode) {
        case Immediate: return instruction[1]; break;
        case Absolute: return m->memory[instruction[2]<<8 | instruction[1]]; break;
        case XIndexedAbsolute: return  m->memory[(instruction[2]<<8 | instruction[1]) + m->registerX]; break;
        case YIndexedAbsolute: return m->memory[(instruction[2]<<8 | instruction[1]) + m->registerY]; break;
        case ZeroPage: return m->memory[instruction[1]]; break;
        case XIndexedZeroPage: return m->memory[instruction[1] + m->registerX]; break;
        case YIndexedZeroPage: return m->memory[instruction[1] + m->registerY]; break;
        case XIndexedZeroPageIndirect: return m->memory[(instruction[1] + m->registerX) & 0xFF]; break; // WHY? From E101.com
        case ZeroPageIndirectYIndexed: return m->memory[m->memory[instruction[1]] + m->registerY]; break; // DITTO. Are we wrapping/carrying right? 
    }
}

unsigned char storeData(Machine *m, unsigned char *instruction, unsigned char *reg, AddressingMode mode) {
    switch (mode) {
        case Immediate: m->memory[instruction[1]] = *reg; break;
        case Absolute: m->memory[instruction[2]<<8 | instruction[1]] = *reg; break;
        case XIndexedAbsolute: m->memory[(instruction[2]<<8 | instruction[1]) + m->registerX] = *reg; break;
        case YIndexedAbsolute: m->memory[(instruction[2]<<8 | instruction[1]) + m->registerY] = *reg; break;
        case ZeroPage: m->memory[instruction[1]] = *reg; break;
        case XIndexedZeroPage: m->memory[instruction[1] + m->registerX] = *reg; break;
        case YIndexedZeroPage: m->memory[instruction[1] + m->registerY] = *reg; break;
        case XIndexedZeroPageIndirect: m->memory[(instruction[1] + m->registerX) & 0xFF] = *reg; break; // WHY? From E101.com
        case ZeroPageIndirectYIndexed: m->memory[m->memory[instruction[1]] + m->registerY] = *reg; break; // DITTO. Are we wrapping/carrying right? 
    }
}