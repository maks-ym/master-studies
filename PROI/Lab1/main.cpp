/**
 * Copyright (C) 2017-02-14 Maks-ym (hereafter "Author")
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE X CONSORTIUM BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of the Author shall not be used in advertising or
 * otherwise to promote the sale, use or other dealings in this Software without prior written
 * authorization from the Author.
 */

/**
 *   Class representing polynomials
 *   e.g. 3*x^3 + 5*x^2 - 9*x + 25 = 0
 *   Polynomials up to the 3rd power are available
 */

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
