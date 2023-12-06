#include <iostream>
#include "Long_num.h"

int neg_division(int num, int divisor) {
    if ((num < 0) && (num % divisor))
        return num / divisor - 1;
    else
        return num / divisor;
}

int neg_mod(int num, int divisor) {
    if ((num < 0) && (num % divisor))
        return num % divisor + divisor;
    else
        return num % divisor;
}

const std::vector<int>& Long_Num::getBlocks() const {
    return blocks;
}

std::vector<int>& Long_Num::getBlocks() {
    return blocks;
}


Long_Num::Long_Num() {
        sign = 1;
    }

void Long_Num::trimLeadingZeros() {
    
    while (blocks.size() > 1 && blocks.back() == 0) {
        blocks.pop_back();
    }
}

Long_Num::Long_Num(string num_start) {
        int i;
        if (BASE != 1) {
            for (i = num_start.size() - BASE; i >= BASE - 1; i -= BASE) {
                blocks.push_back(stoi(num_start.substr(i, BASE)));
            }
        }
        else {
            for (i = num_start.size() - BASE; i >= BASE; i -= BASE) {
                blocks.push_back(stoi(num_start.substr(i, BASE)));
            }
        }

        if (num_start[0] == '-') {
            sign = -1;
            if (i + BASE - 1 != 0) {
                blocks.push_back(stoi(num_start.substr(1, i + BASE - 1)));
            }
        }
        else {
            sign = 1;
            blocks.push_back(stoi(num_start.substr(0, i+BASE)));
        }
    }

void Long_Num::_resize(int newSize) {
    blocks.resize(newSize);
}

void Long_Num::normalize_blocks() {
    int over = 0;
    for (int i = 0; i < blocks.size() - 1; i++) {
        blocks[i] += over;
        over = neg_division(blocks[i], BASE_10);
        blocks[i] = neg_mod(blocks[i], BASE_10);
    }
    blocks[blocks.size() - 1] += over;
    if (blocks[blocks.size() - 1] / BASE_10) {
        over = neg_division(blocks[blocks.size() - 1], BASE_10);
        blocks[blocks.size() - 1] = neg_mod(blocks[blocks.size() - 1], BASE_10);
        blocks.push_back(over);
    }
    return;
}

void Long_Num::normalize_sign() {
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

Long_Num Long_Num::_plus(Long_Num& num) {
    Long_Num res;
    res.sign = this->sign;
    for (int i = 0; i < this->blocks.size(); i++) {
        res.blocks.push_back(this->blocks[i] + num.blocks[i]);
    }
    return res;
}

Long_Num Long_Num::_minus(Long_Num& num) {
    Long_Num res;
    res.sign = this->sign;
    for (int i = 0; i < this->blocks.size(); i++) {
        res.blocks.push_back(this->blocks[i] - num.blocks[i]);
    }
    return res;
}

Long_Num Long_Num::operator + (Long_Num& num) {

    Long_Num res;
    if (this->blocks.size() > num.blocks.size()) {
        num._resize(blocks.size());
    }
    else {
        (*this)._resize(num.blocks.size());
    }

    if (sign == num.sign) {
        res = (*this)._plus(num);
    }
    else {
        res = (*this)._minus(num);
    }

    res.normalize_blocks();
    return res;
}

Long_Num Long_Num::operator - (Long_Num& num) {
    Long_Num res;
    if (this->blocks.size() > num.blocks.size()) {
        num._resize(blocks.size());
    }
    else {
        (*this)._resize(num.blocks.size());
    }

    if (sign != num.sign) {
        res = (*this)._plus(num);
    }
    else {
        res = (*this)._minus(num);
    }

    res.normalize_blocks();
    return res;
}

bool Long_Num::operator == (const Long_Num& num) const {
    return (sign == num.sign) && (blocks == num.blocks);
}

bool Long_Num::operator != (const Long_Num& num) const {
    return !(*this == num);
}

bool Long_Num::operator < (const Long_Num& num) const {
    if (sign < num.sign) {
        return true;
    } else if (sign > num.sign) {
        return false;
    }

    if (sign == 1) {
        if (blocks.size() < num.blocks.size()) {
            return true;
        } else if (blocks.size() > num.blocks.size()) {
            return false;
        }

        for (int i = blocks.size() - 1; i >= 0; i--) {
            if (blocks[i] < num.blocks[i]) {
                return true;
            } else if (blocks[i] > num.blocks[i]) {
                return false;
            }
        }
    } else {
        if (blocks.size() > num.blocks.size()) {
            return true;
        } else if (blocks.size() < num.blocks.size()) {
            return false;
        }

        for (int i = blocks.size() - 1; i >= 0; i--) {
            if (blocks[i] > num.blocks[i]) {
                return true;
            } else if (blocks[i] < num.blocks[i]) {
                return false;
            }
        }
    }
    return false;
}

bool Long_Num::operator <= (const Long_Num& num) const {
    return (*this < num) || (*this == num);
}

bool Long_Num::operator > (const Long_Num& num) const {
    return !(*this <= num);
}

bool Long_Num::operator >= (const Long_Num& num) const {
    return !(*this < num);
}

Long_Num Long_Num::operator * (Long_Num& num) {
    Long_Num result;

    result.sign = this->sign * num.sign;

    result._resize(this->blocks.size() + num.blocks.size());

    // Perform multiplication algorithm
    for (int i = 0; i < this->blocks.size(); i++) {
        for (int j = 0; j < num.blocks.size(); j++) {
            result.blocks[i + j] += this->blocks[i] * num.blocks[j];
        }
    }

    result.normalize_blocks();
    result.normalize_sign();

    return result;
}

Long_Num Long_Num::operator / (Long_Num& num) {

    if (num == Long_Num("0")) {
        std::cerr << "Error: Division by zero." << std::endl;
        exit(1);
    }

    Long_Num quotient, remainder, temp;

    quotient.sign = this->sign * num.sign;
    remainder.sign = this->sign;

    temp = *this;
    temp.sign = 1;

    for (int i = temp.blocks.size() - 1; i >= 0; i--) {
        remainder.blocks.insert(remainder.blocks.begin(), temp.blocks[i]);

        int guess = 0;
        while (!(remainder < num)) {
            remainder = remainder - num;
            guess++;
        }

        quotient.blocks.insert(quotient.blocks.begin(), guess);
    }

    quotient.normalize_sign();
    remainder.normalize_sign();

    return quotient;
}

std::ostream& operator << (std::ostream& output, Long_Num& num) {
    num.normalize_sign();
    if (num.sign == -1) {
        output << '-';
    }
    output << num.blocks[num.blocks.size() - 1];
    for (int i = num.blocks.size() - 2; i >= 0; i--) {
        output << std::setw(num.getBASE()) << std::setfill('0') << num.blocks[i];
    }
    return output;
}
