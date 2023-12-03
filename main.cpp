#include <iostream>
#include <vector>

using namespace std;


int mm_divison(int num, int divisor) {
    if ((num < 0) && (num % divisor))
        return num / divisor - 1;
    else
        return num / divisor;
}

int _mod(int num, int divisor) {
    if ((num < 0) && (num % divisor))
        return num % divisor + divisor;
    else
        return num % divisor;
}


class LongNum {
private:
    vector<int> blocks;  
    int sign;
    static const int BASE = 2;
    static const int BASE_10 = 100;
    void normalize_sign();
    void normalize_blocks(); 

public:

    friend ostream &operator<<(ostream &output, LongNum &num);
    
    LongNum(string num_start) {
        int i;
        if (BASE != 1) {
            for (i = num_start.size() - BASE; i >= BASE - 1; i -= BASE) {
                blocks.push_back(stoi(num_start.substr(i, BASE)));
            }
        } else {
            for (i = num_start.size() - BASE; i >= BASE; i -= BASE) {
                blocks.push_back(stoi(num_start.substr(i, BASE)));
            }
        }
        if (num_start[0] == '-') {
            sign = -1;
            if (i + BASE - 1 != 0) {
                blocks.push_back(stoi(num_start.substr(1, i + BASE - 1)));
            }
        } else {
            sign = 1;
            blocks.push_back(stoi(num_start.substr(0, i + BASE)));
        }
    }
    LongNum() {
        sign = 1;
    }
    
};

void LongNum::normalize_blocks() {
    int garbage = 0;
    for (int i = 0; i < blocks.size() - 1; i++) {
        blocks[i] += garbage; 
        garbage = mm_divison(blocks[i], BASE_10); 
        blocks[i] = _mod(blocks[i], BASE_10);
    }
    blocks[blocks.size() - 1] += garbage;
    if (blocks[blocks.size() - 1] / BASE_10) {
        garbage = mm_divison(blocks[blocks.size() - 1], BASE_10);
        blocks[blocks.size() - 1] = _mod(blocks[blocks.size() - 1], BASE_10);
        blocks.push_back(garbage); 
    }
    return;
}

void LongNum::normalize_sign() {
    if (blocks[blocks.size() - 1] < 0) {
        sign = -sign;
        blocks[0] = BASE_10 - blocks[0];
        for (int i = 1; i < blocks.size(); i++) {
            blocks[i] = (BASE_10 - blocks[i] - 1) % BASE_10;
        }
    }
    int i = blocks.size() - 1;
    while (blocks[i] == 0) {
        if (i == 0) {
            sign = 1;
            return;
        }
        blocks.pop_back();
        i--;
    }
    return;
}

ostream &operator<<(ostream &output, LongNum &num) {
    num.normalize_sign();
    if (num.sign == -1) {
        output << '-';
    }
    output << num.blocks[num.blocks.size() - 1];
    for (int i = num.blocks.size() - 2; i >= 0; i--) {
        output << num.blocks[i];
    }
    return output;
}



int main() {
    LongNum n1("1389081290485792752893749714910740148917918570949129047105705705958094809841");
    LongNum n2("814010480015679146186491471984701749169461964174491");

    cout << n1 << endl;
    cout << n2 << endl;
    
    return 0;
}