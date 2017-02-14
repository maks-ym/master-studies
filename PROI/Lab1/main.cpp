#include <iostream>
#include "Polynomial.h"

using namespace std;

int main()
{
    cout << "Create polynomial 'a' and show" << endl;
    Polynomial a(3,5,2,8);
    cout << a << endl;
    cout << "---------------------------" << endl;

    cout << "Create polynomial 'b' and show" << endl;
    Polynomial b(3,0,2,-8);
    cout << b << endl;
    cout << "---------------------------" << endl;

    cout << "Sum 'a + b'" << endl;
    Polynomial w1 = a + b;
    cout << w1 << endl;
    cout << "---------------------------" << endl;

    cout << "Sum 'a += b'" << endl;
    a += b;
    cout << a << endl;
    cout << "---------------------------" << endl;

    cout << "Subtraction 'a - b'" << endl;
    Polynomial w2 = a - b;
    cout << w2 << endl;
    cout << "---------------------------" << endl;

    cout << "Subtraction 'a -= b'" << endl;
    a -= b;
    cout << a << endl;
    cout << "---------------------------" << endl;

    cout << "Multiplication 'a * b'" << endl;
    Polynomial w3 = a * b;
    cout << w3 << endl;
    cout << "---------------------------" << endl;

    cout << "Multiplication '3*a'" << endl;
    Polynomial w4 = 3*a;
    cout << w4 << endl;
    cout << "---------------------------" << endl;

    cout << "Multiplication 'a*3'" << endl;
    Polynomial w5 = a*3;
    cout << w5 << endl;
    cout << "---------------------------" << endl;

    cout << "Multiplication 'f*=a'" << endl;
    cout << "Created polynomial 'f':" << endl;
    Polynomial f(5,7,1,-6);
    cout << f << endl;
    f*=a;
    cout << f << endl;
    cout << "---------------------------" << endl;

    cout << "Multiplication 'a*=2'" << endl;
    a*=2;
    cout << a << endl;
    cout << "---------------------------" << endl;

    cout << "==========Equality=========" << endl;

    cout << "Created polynomial 'c':" << endl;
    Polynomial c(2,7,-12,10);
    cout << c << endl;
    cout << "Created polynomial 'd':" << endl;
    Polynomial d(2,7,-12,10);
    cout << d << endl;
    cout << "Created polynomial 'e':" << endl;
    Polynomial e(2,-5,9,4);
    cout << e << endl;

    cout << "Equality '(c == d)'" << endl;
    cout << (c == d) << endl;
    cout << "---------------------------" << endl;
    cout << "Equality '(c != d)'" << endl;
    cout << (c != d) << endl;
    cout << "---------------------------" << endl;
    cout << "Equality '(c == e)'" << endl;
    cout << (c == e) << endl;
    cout << "---------------------------" << endl;
    cout << "Equality '(c != e)'" << endl;
    cout << (c != e) << endl;
    cout << "---------------------------" << endl;

    return 0;
}
