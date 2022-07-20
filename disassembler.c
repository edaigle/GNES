int Disassemble6502Op(unsigned char *codebuffer, int pc)
{
    unsigned char *opcode = &codebuffer[pc];
    int oplength = 1;

    printf("%04x: ", opcode)
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
        case 0x6D: printf("ROR $%02x%02x", opcode[2], opcode[1]); oplength = 3; break;

        // case ...: TODO
    }
}
