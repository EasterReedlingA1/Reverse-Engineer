#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct Instructions {
    string inst;
    int code;
    int functionCode;
    bool immediate;
};
struct RegTable {
    string reg;
    int address;
};
int main() {
    Instructions instr[5];
    RegTable registers[5];
    ifstream machine("machine.txt");
    // getting addresses of instructions
    for (int i = 0; i < 5; i++) machine >> registers[i].address;
    // saving opcode
    for (int i = 0; i < 5; i++) {
        instr[i].code = (registers[i].address & 0x20000000) >> 26;
        instr[i].immediate = instr[i].code == 0 ? false : true;
    }
    // saving function code
    for (int i = 0; i < 5; i++) {
        if (instr[i].immediate) {
            instr[i].functionCode = registers[i].address & 0x0000FFFF;
        } else {
            instr[i].functionCode = registers[i].address & 0x0000002F;
        }
    }
    // assigning instruction names
    for (int i = 0; i < 5; i++) {
        if (instr[i].immediate) {
            instr[i].inst = "addi";
        } else {
            if (instr[i].functionCode == 0x32) {
                instr[i].inst = "add";
            } else if (instr[i].functionCode == 0x22) {
                instr[i].inst = "sub";
            }
        }
    }
    // assigning register names
    for (int i = 0; i < 5; i++) {
        if (registers[i].address == 0x00000008) {
            registers[i].reg = "t0";
        } else if (registers[i].address == 0x00000009) {
            registers[i].reg = "t1";
        } else if (registers[i].address == 0x0000000A) {
            registers[i].reg = "t2";
        } else if (registers[i].address == 0x00000000) {
            registers[i].reg = "zero";
        }
    }
    // print instructions
    for (int i = 0; i < 5; i++) {
        cout << instr[i].inst << " ";
        if (instr[i].immediate) {
            cout << "$" << registers[i].reg << ", " << registers[i].reg << ", " << instr[i].functionCode << endl;
        } else {
            cout << "$" << registers[i].reg << ", " << "$" << registers[i].reg << ", " << "$" << registers[i].reg << endl;
        }
    }
    return 0;
}