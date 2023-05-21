#include <iostream>
#include <string>

class Turing {
public:
    std::string tape;
    int position = 0;
    bool state;

    Turing() {
        tape = "llllll";
    }

    Turing(const std::string& value) {
        this->tape = "lll";
        this->tape += value;
        this->tape += "lll";
    }
    char get_current_symbol() {
        return this->tape[position];
    }

    void shr() {
        position++;
        if (position > tape.size() - 3) {
            tape += "l";
        }
    }
    void shl() {
        position--;
        if (position < 2) {
            position++;
            std::string tmp = this->tape;
            tape = "l" + tmp;
        }
    }
    void wrz() {
        this->tape[position] = '*';
        print();
    }
    void wra() {
        this->tape[position] = 'a';
        print();
    }
    void wrb() {
        this->tape[position] = 'b';
        print();
    }
    void wr1() {
        this->tape[position] = '1';
        print();
    }
    void wr0() {
        this->tape[position] = '0';
        print();
    }
    void stop() {
        this->print();
    }
    void print() {
        for (char i : this->tape) {
            std::cout << i;
        }
        std::cout << "\n";
    }
    void jmp(const std::string& command0, const std::string& command1) {
        int flag0, flag1;
        if (command0 == "wra") {
            flag0 = 1;
        } else if (command0 == "wrb") {
            flag0 = 0;
        }
        if (command1 == "wra") {
            flag1 = 1;
        } else if (command1 == "wrb") {
            flag1 = 0;
        }
        if (this->tape[position] == '0') {
            this->state = false;
            switch (flag0) {
                case 0:
                    this->wra();
                    break;
                case 1:
                    this->wrb();
                    break;
            }
        } else {
            this->state = true;
            switch (flag1) {
                case 0:
                    this->wra();
                    break;
                case 1:
                    this->wrb();
                    break;
            }
        }
    }

    void jmp_end(const std::string& command0, const std::string& command1) {
        if (this->tape[position] == 'a') {
            this->wr0();
        } else if (this->tape[position] == 'b') {
            this->wr1();
        }
    }
};

int main() {
    std::string base = "011010";
    int length = base.size();
    Turing base_turing(base);
    base_turing.position = 3;

    while (base_turing.get_current_symbol() != 'l') {
        base_turing.shr();
    }
    base_turing.wrz();
    while (base_turing.get_current_symbol() != 'l') {
        base_turing.shl();
    }
    base_turing.shr();
    base_turing.jmp("wrb", "wra");
    for (int i = 0; i < length - 1; i++) {
        while (base_turing.get_current_symbol() != 'l') {
            base_turing.shr();
        }
        if (base_turing.state) {
            base_turing.wr1();
        } else {
            base_turing.wr0();
        }
        while (base_turing.get_current_symbol() == '0' || base_turing.get_current_symbol() == '1' || base_turing.get_current_symbol() == '*') {
            base_turing.shl();
        }
        base_turing.shr();
        base_turing.jmp("wrb", "wra");
    }
    while (base_turing.get_current_symbol() != 'l') {
        base_turing.shr();
    }
    if (base_turing.state) {
        base_turing.wr1();
    } else {
        base_turing.wr0();
    }
    base_turing.tape += 'l';
    while (base_turing.get_current_symbol() != 'l') {
        base_turing.shl();
    }
    base_turing.shr();
    for (int i = 0; i < length; i++) {
        base_turing.jmp_end("wr0", "wr1");
        base_turing.shr();
    }
    return 0;
}
