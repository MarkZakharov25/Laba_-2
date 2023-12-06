int main(){

    Long_Num num1("847598275097805378310597908095017557105791751857180571057105781305413904781097415670137590174501741780471056701561890571890");
    Long_Num num2("10");
    Long_Num num3 = num1 - num2;

    cout << num3 << endl << endl;

    Long_Num n1("123456789");
    Long_Num n2("9876");
    Long_Num quotient = n1 / n2;
    Long_Num mult_res = n1 * n2;
    
    cout << "Multiplication result: " << mult_res << endl;
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