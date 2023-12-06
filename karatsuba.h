#pragma once

#include <iostream>
#include <cmath>
#include <algorithm>
#include <regex>
#include "Long_num.h"

class Karatsuba {
public:
    Long_Num multiply(const Long_Num &num1, const Long_Num &num2);
    Long_Num findSum(const Long_Num &num1, const Long_Num &num2);
    Long_Num findDiff(const Long_Num &num1, const Long_Num &num2);
};