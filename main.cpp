#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int neg_division(int num, int divisor)  {
    if ((num < 0) && (num % divisor))
        return num / divisor - 1;
    else
        return num / divisor;
}

int neg_mod(int num, int divisor)  {
    if ((num < 0) && (num % divisor))
            return num % divisor + divisor;
    else
        return num % divisor;
}
class Long_Num {
private:
    vector<int> blocks;
    int sign;
    static const int BASE = 2;
    static const int BASE_10 = 100;
    Long_Num _plus(Long_Num &a);
    Long_Num _minus(Long_Num &a);
    void normalize_sign();
    void normalize_blocks();
    void _resize(int newsize);
public:
    Long_Num operator + (Long_Num &num);
    Long_Num operator - (Long_Num &num);

    Long_Num operator * (Long_Num &num);
    Long_Num operator / (Long_Num &num);

    bool operator == (const Long_Num &num) const;
    bool operator != (const Long_Num &num) const;
    bool operator < (const Long_Num &num) const;
    bool operator <= (const Long_Num &num) const;
    bool operator > (const Long_Num &num) const;
    bool operator >= (const Long_Num &num) const;

    

    friend ostream & operator << (ostream &output, Long_Num &num);
    
    int getBASE() {
        return this->BASE;
    }

    Long_Num(string num_start) {
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

    Long_Num() {
        sign = 1;
    }
};

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

Long_Num Long_Num::_plus(Long_Num &num) {
    Long_Num res;
    res.sign = this->sign;
    for (int i = 0; i < this->blocks.size(); i++) {
        res.blocks.push_back(this->blocks[i] + num.blocks[i]);
    }
    return res;
}

Long_Num Long_Num::_minus(Long_Num &num) {
    Long_Num res;
    res.sign = this->sign;
    for (int i = 0; i < this->blocks.size(); i++) {
        res.blocks.push_back(this->blocks[i] - num.blocks[i]);
    }
    return res;
}

Long_Num Long_Num::operator + (Long_Num &num) {
    
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

Long_Num Long_Num::operator - (Long_Num &num) {
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

bool Long_Num::operator == (const Long_Num &num) const {
    return (sign == num.sign) && (blocks == num.blocks);
}

bool Long_Num::operator != (const Long_Num &num) const {
    return !(*this == num);
}

bool Long_Num::operator < (const Long_Num &num) const {
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

bool Long_Num::operator <= (const Long_Num &num) const {
    return (*this < num) || (*this == num);
}

bool Long_Num::operator > (const Long_Num &num) const {
    return !(*this <= num);
}

bool Long_Num::operator >= (const Long_Num &num) const {
    return !(*this < num);
}

Long_Num Long_Num::operator * (Long_Num &num) {
    Long_Num result;
    
    // Set the sign of the result
    result.sign = this->sign * num.sign;

    // Resize the result to accommodate the multiplication
    result._resize(this->blocks.size() + num.blocks.size());

    // Perform multiplication algorithm
    for (int i = 0; i < this->blocks.size(); i++) {
        for (int j = 0; j < num.blocks.size(); j++) {
            result.blocks[i + j] += this->blocks[i] * num.blocks[j];
        }
    }

    // Normalize the result
    result.normalize_blocks();
    result.normalize_sign();

    return result;
}

Long_Num Long_Num::operator / (Long_Num &num) {

    if (num == Long_Num("0")) {
        cerr << "Error: Division by zero." << endl;
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

ostream & operator << (ostream &output, Long_Num &num) {
    num.normalize_sign();
    if (num.sign == -1) {
        output << '-';
    }
    output << num.blocks[num.blocks.size() - 1];
    for (int i = num.blocks.size() - 2; i >= 0; i--) {
        output << setw(num.getBASE()) << setfill('0') << num.blocks[i];
    }
    return output;
}

int main() {
    Long_Num num1("847598275097805378310597908095017557105791751857180571057105781305413904781097415670137590174501741780471056701561890571890");
    Long_Num num2("10");
    Long_Num num3 = num1 - num2;

    cout << num3 << endl << endl;

    Long_Num n1("123456789");
    Long_Num n2("9876");
    Long_Num quotient = n1 / n2;
    cout << "Quotient: " << quotient << endl;

    cout << "Comparison results:" << endl;
    cout << "num1 == num2: " << (num1 == num2) << endl;
    cout << "num1 != num2: " << (num1 != num2) << endl;
    cout << "num1 < num2: " << (num1 < num2) << endl;
    cout << "num1 <= num2: " << (num1 <= num2) << endl;
    cout << "num1 > num2: " << (num1 > num2) << endl;
    cout << "num1 >= num2: " << (num1 >= num2) << endl;

    return 0;
}