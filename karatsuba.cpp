#include "karatsuba.h"
#include "Long_num.h"
#include "Long_num.cpp"


Long_Num Karatsuba::findSum(const Long_Num &num1, const Long_Num &num2) {
    // Поелементне додавання чисел
    Long_Num result;
    int carry = 0;
    int n = std::max(num1.getBlocks().size(), num2.getBlocks().size());

    for (int i = 0; i < n; ++i) {
        int digitSum = carry + ((i < num2.getBlocks().size()) ? num1.getBlocks()[i] : 0) + ((i < num2.getBlocks().size()) ? num2.getBlocks()[i] : 0);
        result.getBlocks().push_back(digitSum % Long_Num::BASE_10);
        carry = digitSum / Long_Num::BASE_10;
    }

    if (carry > 0) {
        result.getBlocks().push_back(carry);
    }

    return result;
}

Long_Num Karatsuba::findDiff(const Long_Num &num1, const Long_Num &num2) {
    // Поелементне віднімання чисел
    Long_Num result;
    int borrow = 0;
    int n = std::max(num1.getBlocks().size(), num2.getBlocks().size());

    for (int i = 0; i < n; ++i) {
        int digitDiff = ((i < num1.getBlocks().size()) ? num1.getBlocks()[i] : 0) - borrow - ((i < num2.getBlocks().size()) ? num2.getBlocks()[i] : 0);
        if (digitDiff < 0) {
            digitDiff += Long_Num::BASE;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.getBlocks().push_back(digitDiff);
    }

    // Видаляємо ведучі нулі
    result.trimLeadingZeros();

    return result;
}

Long_Num Karatsuba::multiply(const Long_Num &num1, const Long_Num &num2) {
    // Якщо довжина num1 більша, ніж num2, поміняємо їх місцями
    Long_Num A = (num1.getBlocks().size() >= num2.getBlocks().size()) ? num1 : num2;
    Long_Num B = (num1.getBlocks().size() >= num2.getBlocks().size()) ? num2 : num1;

    // Зробимо обидва числа однаковими за кількістю розрядів
    while (B.getBlocks().size() < A.getBlocks().size()) {
    
    B.getBlocks().push_back(0);
    }

    // Base case
    if (A.getBlocks().size() == 1) {
        Long_Num result = A * B;
        return result;
    }

    // Додаємо нулі на початку блоків, якщо довжина блоків непарна
    if (A.getBlocks().size() % 2 == 1) {
        A.getBlocks().insert(A.getBlocks().begin(), 0);
        B.getBlocks().insert(B.getBlocks().begin(), 0);
    }

    // Розділяємо числа на 4 частини: Al, Ar, Bl, Br.
    int m = A.getBlocks().size() / 2;
    Long_Num Al(A.getBlocks().begin(), A.getBlocks().begin() + m);
    Long_Num Ar(A.getBlocks().begin() + m, A.getBlocks().end());
    Long_Num Bl(B.getBlocks().begin(), B.getBlocks().begin() + m);
    Long_Num Br(B.getBlocks().begin() + m, B.getBlocks().end());

    // Рекурсивно обчислюємо добутки P1, P2, P3.
    Long_Num P1 = multiply(Al, Bl);
    Long_Num P2 = multiply(Ar, Br);
    Long_Num P3 = multiply(findSum(Al, Ar), findSum(Bl, Br));

    // Знаходимо добуток P1 * 10^(2 * (n - n/2)), P2, і різницю P3 - (P1 + P2).
    Long_Num temp = P3 - findSum(P1, P2);
    Long_Num result = findSum(findSum(P1 * Long_Num("1" + std::string(m * 2, '0')), P2), temp * Long_Num(std::string(m, '0')));

    // Видалимо ведучі нулі з результату
    result.trimLeadingZeros();

    // Повертаємо результат
    return result;
}