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


#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <iostream>
/**
 *   Class representing polynomials
 *   e.g. 3*x^3 + 5*x^2 - 9*x + 25 = 0
 *   Polynomials up to the 3rd power are available
 */
class Polynomial
{
    private:
        int coefs[7];               // Coefficients for 0, 1st, 2nd and 3rd powered x
                                    // Plus Coefficients for saving coefficients after multiplication
    public:
        Polynomial(int, int, int, int);         //Coefficients must be inputed from 0 to 3rd power
        ~Polynomial();
        void showCoefs() const; //remove
        Polynomial operator + (const Polynomial & polynomial_b) const;
        Polynomial operator - (const Polynomial & polynomial_b) const;
        Polynomial operator * (const Polynomial & polynomial_b) const;
        Polynomial operator * (int b) const;
        void operator += (const Polynomial & polynomial_b);
        void operator -= (const Polynomial & polynomial_b);
        void operator *= (const Polynomial & polynomial_b);
        void operator *= (int b);
        bool operator == (const Polynomial & polynomial_b) const;
        bool operator != (const Polynomial & polynomial_b) const;
        friend Polynomial operator * (int, const Polynomial &);
        friend std::ostream& operator<< ( std::ostream & os, Polynomial & ob);
};

#endif // POLYNOMIAL_H
