#include <stdio.h>
#include <stdlib.h>

int Disassemble6502Op(unsigned char *codebuffer, int pc)
{
    unsigned char *opcode = &codebuffer[pc];
    int oplength = 1;

    printf("%04x: ", opcode);
    switch (*opcode) {
        case 0x00: printf("BRK"); break;
        case 0x01: printf("(ORA $%02x, X)", opcode[1]); oplength = 2; break;
        case 0x05: printf("ORA $%02x", opcode[1]); oplength = 2; break;
        case 0x06: printf("ASL $%02x", opcode[1]); oplength = 2; break;
        case 0x08: printf("PHP"); break;
        case 0x09: printf("ORA #$%02x", opcode[1]); oplength = 2; break;
        case 0x0A: printf("ASL A"); break;
        case 0x0D: printf("ORA $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;
        case 0x0E: printf("ASL $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;
        case 0x10: printf("BPL $%02x", opcode[1]); oplength = 2; break;
        case 0x11: printf("ORA $%02x, X", opcode[1]); oplength = 2; break;
        case 0x15: printf("ORA $%02x, X", opcode[1]); oplength = 2; break;
        case 0x16: printf("ASL $%02x, X", opcode[1]); oplength = 2; break;
        case 0x18: printf("CLC"); break;
        case 0x19: printf("ORA $%02x%02x, Y", opcode[2], opcode[1]); oplength = 3; break;
        case 0x1D: printf("ORA $%02x%02x, X", opcode[2], opcode[1]); oplength = 3; break;
        case 0x1E: printf("ASL $%02x%02x, X", opcode[2], opcode[1]); oplength = 3; break;
        case 0x20: printf("JSR $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;
        case 0x21: printf("(AND $%02x, X)", opcode[1]); oplength = 2; break;
        case 0x24: printf("BIT $%02x", opcode[1]); oplength = 2; break;
        case 0x25: printf("AND $%02x", opcode[1]); oplength = 2; break;
        case 0x26: printf("ROL $%02x", opcode[1]); oplength = 2; break;
        case 0x28: printf("PLP"); break;
        case 0x29: printf("AND #$%02x", opcode[1]); oplength = 2; break;
        case 0x2A: printf("ROL A"); break;
        case 0x2C: printf("BIT $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;
        case 0x2D: printf("AND $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;
        case 0x2E: printf("ROL $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;
        case 0x30: printf("BMI $%02x", opcode[1]); oplength = 2; break;
        case 0x31: printf("AND ($%02x), Y", opcode[1]); oplength = 2; break;
        case 0x35: printf("AND $%02x, X", opcode[1]); oplength = 2; break;
        case 0x36: printf("ROL $%02x, X", opcode[1]); oplength = 2; break;
        case 0x38: printf("SEC"); break;
        case 0x39: printf("AND $%02x%02x, Y", opcode[2], opcode[1]); oplength = 3; break;
        case 0x3D: printf("AND $%02x%02x, X", opcode[2], opcode[1]); oplength = 3; break;
        case 0x3E: printf("ROL $%02x%02x, X", opcode[2], opcode[1]); oplength = 3; break;
        case 0x40: printf("RTI"); break;
        case 0x41: printf("EOR ($%02x, X)", opcode[1]); oplength = 2; break;
        case 0x45: printf("EOR $%02x", opcode[1]); oplength = 2; break;
        case 0x46: printf("LSR $%02x", opcode[1]); oplength = 2; break;
        case 0x48: printf("PHA"); break;
        case 0x49: printf("EOR #$%02x", opcode[1]); oplength = 2; break;
        case 0x4A: printf("LSR A"); break;
        case 0x4C: printf("JMP $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;
        case 0x4D: printf("EOR $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;
        case 0x4E: printf("LSR $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;
        case 0x50: printf("BVC $%02x", opcode[1]); oplength = 2; break;
        case 0x51: printf("EOR ($%02x), Y", opcode[1]); oplength = 2; break;
        case 0x55: printf("EOR $%02x, X", opcode[1]); oplength = 2; break;
        case 0x56: printf("LSR $%02x, X", opcode[1]); oplength = 2; break;
        case 0x58: printf("CLI"); break;
        case 0x59: printf("EOR $%02x%02x, Y", opcode[2], opcode[1]); oplength = 3; break;
        case 0x5D: printf("EOR $%02x%02x, X", opcode[2], opcode[1]); oplength = 3; break;
        case 0x5E: printf("LSR $%02x%02x, X", opcode[2], opcode[1]); oplength = 3; break;
        case 0x60: printf("RTS"); break;
        case 0x61: printf("ADC ($%02x, X)", opcode[1]); oplength = 2; break;
        case 0x65: printf("ADD $%02x", opcode[1]); oplength = 2; break;
        case 0x66: printf("ROR $%02x", opcode[1]); oplength = 2; break;
        case 0x68: printf("PLA"); break;
        case 0x69: printf("ADC #$%02x", opcode[1]); oplength = 2; break;
        case 0x6A: printf("ROR A"); break;
        case 0x6C: printf("JMP ($%02x%02x)", opcode[2], opcode[1]); oplength = 3; break;
        case 0x6D: printf("ADC $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;
        case 0x6E: printf("ROR $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;
        case 0x70: printf("BVS $%02x", opcode[1]); oplength = 2; break;
        case 0x71: printf("ADC ($%02x), Y", opcode[1]); oplength = 2; break;
        case 0x75: printf("ADC $%02x, X", opcode[1]); oplength = 2; break;
        case 0x76: printf("ROR $%02x, X", opcode[1]); oplength = 2; break;
        case 0x78: printf("SEI"); break;
        case 0x79: printf("ADC $%02x%02x, Y", opcode[2], opcode[1]); oplength = 3; break;
        case 0x7D: printf("ADC $%02x%02x, X", opcode[2], opcode[1]); oplength = 3; break;
        case 0x7E: printf("ROR $%02x%02x, X", opcode[2], opcode[1]); oplength = 3; break;
        case 0x81: printf("STA ($%02x), X", opcode[1]); oplength = 2; break;
        case 0x84: printf("STY $%02x", opcode[1]); oplength = 2; break;
        case 0x85: printf("STA $%02x", opcode[1]); oplength = 2; break;
        case 0x86: printf("STX $%02x", opcode[1]); oplength = 2; break;
        case 0x88: printf("DEY"); break;
        case 0x8A: printf("TXA"); break;
        case 0x8C: printf("STY $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;
        case 0x8D: printf("STA $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;
        case 0x8E: printf("STX $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;
        case 0x90: printf("BCC $%02x", opcode[1]); oplength = 2; break;
        case 0x91: printf("STA ($%02x), Y", opcode[1]); oplength = 2; break;
        case 0x94: printf("STY $%02x, X", opcode[1]); oplength = 2; break;
        case 0x95: printf("STA $%02x, X", opcode[1]); oplength = 2; break;
        case 0x96: printf("STX $%02x, Y", opcode[1]); oplength = 2; break;
        case 0x98: printf("TYA"); break;
        case 0x99: printf("STA $%02x%02x, Y", opcode[2], opcode[1]); oplength = 3; break;
        case 0x9A: printf("TXS"); break;
        case 0x9D: printf("STA $%02x%02x, X", opcode[2], opcode[1]); oplength = 3; break;
        case 0xA0: printf("LDY #$%02x", opcode[1]); oplength = 2; break;
        case 0xA1: printf("LDA ($%02x, X)", opcode[1]); oplength = 2; break;
        case 0xA2: printf("LDX #$%02x", opcode[1]); oplength = 2; break;
        case 0xA4: printf("LDY $%02x", opcode[1]); oplength = 2; break;
        case 0xA5: printf("LDA $%02x", opcode[1]); oplength = 2; break;
        case 0xA6: printf("LDX $%02x", opcode[1]); oplength = 2; break;
        case 0xA8: printf("TAY"); break;
        case 0xA9: printf("LDA #$%02x", opcode[1]); oplength = 2; break;
        case 0xAA: printf("TAX"); break;
        case 0xAC: printf("LTY $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;
        case 0xAD: printf("LTA $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;
        case 0xAE: printf("LTX $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;
        case 0xB0: printf("BCS $%02x", opcode[1]); oplength = 2; break;
        case 0xB1: printf("LDA ($%02x), Y", opcode[1]); oplength = 2; break;
        case 0xB4: printf("LDY $%02x, X", opcode[1]); oplength = 2; break;
        case 0xB5: printf("LDA $%02x, X", opcode[1]); oplength = 2; break;
        case 0xB6: printf("LDX $%02x, Y", opcode[1]); oplength = 2; break;
        case 0xB8: printf("CLV"); break;
        case 0xB9: printf("LDA $%02x%02x, Y", opcode[2], opcode[1]); oplength = 3; break;
        case 0xBA: printf("TSX"); break;
        case 0xBC: printf("LTY $%02x%02x, X", opcode[2], opcode[1]); oplength = 3; break;
        case 0xBD: printf("LTA $%02x%02x, X", opcode[2], opcode[1]); oplength = 3; break;
        case 0xBE: printf("LTX $%02x%02x, Y", opcode[2], opcode[1]); oplength = 3; break;
        case 0xC0: printf("CPY #$%02x", opcode[1]); oplength = 2; break;
        case 0xC1: printf("CMP ($%02x, X)", opcode[1]); oplength = 2; break;
        case 0xC4: printf("CPY $%02x", opcode[1]); oplength = 2; break;
        case 0xC5: printf("CMP $%02x", opcode[1]); oplength = 2; break;
        case 0xC6: printf("DEC $%02x", opcode[1]); oplength = 2; break;
        case 0xC8: printf("INY"); break;
        case 0xC9: printf("CMP #$%02x", opcode[1]); oplength = 2; break;
        case 0xCA: printf("INY"); break;
        case 0xCC: printf("CPY $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;
        case 0xCD: printf("CMP $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;
        case 0xCE: printf("DEC $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;
        case 0xD0: printf("BNE $%02x", opcode[1]); oplength = 2; break;
        case 0xD1: printf("LDX ($%02x), Y", opcode[1]); oplength = 2; break;
        case 0xD5: printf("CMP $%02x, X", opcode[1]); oplength = 2; break;
        case 0xD6: printf("DEC $%02x, X", opcode[1]); oplength = 2; break;
        case 0xD8: printf("CLD"); break;
        case 0xD9: printf("CMP $%02x%02x, Y", opcode[2], opcode[1]); oplength = 3; break;
        case 0xDD: printf("CMP $%02x%02x, X", opcode[2], opcode[1]); oplength = 3; break;
        case 0xDE: printf("DEC $%02x%02x, X", opcode[2], opcode[1]); oplength = 3; break;
        case 0xE0: printf("CPX #$%02x", opcode[1]); oplength = 2; break;
        case 0xE1: printf("SBC ($%02x, X)", opcode[1]); oplength = 2; break;
        case 0xE4: printf("CPX $%02x", opcode[1]); oplength = 2; break;
        case 0xE5: printf("SBC $%02x", opcode[1]); oplength = 2; break;
        case 0xE6: printf("INC $%02x", opcode[1]); oplength = 2; break;
        case 0xE8: printf("INX"); break;
        case 0xE9: printf("SBC #$%02x", opcode[1]); oplength = 2; break;
        case 0xEA: printf("NOP"); break;
        case 0xEC: printf("CPX $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;
        case 0xED: printf("SBC $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;
        case 0xEE: printf("INC $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;
        case 0xF0: printf("BEQ $%02x", opcode[1]); oplength = 2; break;// case ...: TODO
        case 0xF1: printf("SBC ($%02x), Y", opcode[1]); oplength = 2; break;
        case 0xF5: printf("SBC $%02x, X", opcode[1]); oplength = 2; break;
        case 0xF6: printf("INC $%02x, X", opcode[1]); oplength = 2; break;
        case 0xF8: printf("SED"); break;
        case 0xF9: printf("SBC $%02x%02x, Y", opcode[2], opcode[1]); oplength = 3; break;
        case 0xFD: printf("SBC $%02x%02x, X", opcode[2], opcode[1]); oplength = 3; break;
        case 0xFE: printf("INC $%02x%02x, X", opcode[2], opcode[1]); oplength = 3; break;
    }

    printf("\n");
    return oplength;
}

int main(int argc, char** argv) 
{
    if (argc < 2) {
        printf("Usage: disassembler <rom.nes>");
        return -1;
    }

    FILE *f = fopen(argv[1], "rb");
    if (!f) {
        printf("Error opening ROM\n");
        return -1;
    }

    fseek(f, 0L, SEEK_END);
    int fsize = ftell(f);    
    fseek(f, 0L, SEEK_SET);

    unsigned char *rom_buffer = malloc(fsize);
    fread(rom_buffer, fsize, 1, f);
    fclose(f);

    int pc = 0;    
    while (pc < fsize) {    
        pc += Disassemble6502Op(rom_buffer, pc);    
    }

    return 0;     
}