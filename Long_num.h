#pragma once

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class Long_Num {
private:
    vector<int> blocks;
    int sign;
    static const int BASE = 2;
    static const int BASE_10 = 100;

    Long_Num _plus(Long_Num& a);
    Long_Num _minus(Long_Num& a);
    void normalize_sign();
    void normalize_blocks();
    void _resize(int newsize);

public:
    Long_Num operator + (Long_Num& num);
    Long_Num operator - (Long_Num& num);
    Long_Num operator * (Long_Num& num);
    Long_Num operator / (Long_Num& num);

    bool operator == (const Long_Num& num) const;
    bool operator != (const Long_Num& num) const;
    bool operator < (const Long_Num& num) const;
    bool operator <= (const Long_Num& num) const;
    bool operator > (const Long_Num& num) const;
    bool operator >= (const Long_Num& num) const;

    friend ostream& operator << (ostream& output, Long_Num& num);

    int getBASE() {
        return this->BASE;
    }

    Long_Num(string num_start);
    Long_Num();
};