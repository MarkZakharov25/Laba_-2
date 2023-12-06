#pragma once

#include <vector>
#include <iomanip>

using namespace std;

class Long_Num {
private:
    vector<int> blocks;
    int sign;
    Long_Num _plus(Long_Num& a);
    Long_Num _minus(Long_Num& a);
    void normalize_sign();
    void normalize_blocks();
    void _resize(int newsize);

public:

    static const int BASE = 2;
    static const int BASE_10 = 100;
    static const int BASE_BASE = 10;

    const vector<int>& getBlocks() const;
    vector<int>& getBlocks();

    Long_Num operator + (Long_Num& num);
    
    Long_Num operator - (Long_Num& num);
    Long_Num operator - (const Long_Num& num) const;
    

    Long_Num operator * (Long_Num& num);
    Long_Num operator * (const Long_Num& num) const;

    Long_Num operator / (Long_Num& num);

    bool operator == (const Long_Num& num) const;
    bool operator != (const Long_Num& num) const;
    bool operator < (const Long_Num& num) const;
    bool operator <= (const Long_Num& num) const;
    bool operator > (const Long_Num& num) const;
    bool operator >= (const Long_Num& num) const;

    void trimLeadingZeros();
    Long_Num resizeTo(int newSize) const;

    friend ostream& operator << (ostream& output, Long_Num& num);


    int getBASE() {
        return this->BASE;
    }

    Long_Num(string num_start);
    Long_Num();
    Long_Num(std::vector<int>::const_iterator begin, std::vector<int>::const_iterator end) : blocks(begin, end) {}
};


