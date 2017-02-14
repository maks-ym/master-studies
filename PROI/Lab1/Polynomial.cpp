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

Polynomial::Polynomial(int coef0 = 0, int coef1 = 0, int coef2 = 0, int coef3 = 0)
{
    coefs[0] = coef0;
    coefs[1] = coef1;
    coefs[2] = coef2;
    coefs[3] = coef3;
    coefs[4] = 0;
    coefs[5] = 0;
    coefs[6] = 0;
}

Polynomial::~Polynomial()
{
}

Polynomial Polynomial::operator+ (const Polynomial & polynomial_b) const
{
    Polynomial c;
    for (int i = 0; i < 4; ++i)
    {
        c.coefs[i] = coefs[i] + polynomial_b.coefs[i];
    }
    return c;
}

Polynomial Polynomial::operator- (const Polynomial & polynomial_b) const
{
    Polynomial c;
    for (int i = 0; i < 4; ++i)
    {
        c.coefs[i] = coefs[i] - polynomial_b.coefs[i];
    }
    return c;
}

Polynomial Polynomial::operator* (const Polynomial & polynomial_b) const
{
    Polynomial c;
    for(int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            c.coefs[i+j] += coefs[i] * polynomial_b.coefs[j];
        }
    }
    return c;
}

Polynomial Polynomial::operator* (int b) const
{
    Polynomial c;
    for (int i = 0; i < 4; ++i)
    {
        c.coefs[i] += coefs[i] * b;
    }
    return c;
}

void Polynomial::operator+= (const Polynomial & polynomial_b)
{
    for (int i = 0; i < 4; ++i)
    {
        coefs[i] = coefs[i] + polynomial_b.coefs[i];
    }
}

void Polynomial::operator-= (const Polynomial & polynomial_b)
{
    for (int i = 0; i < 4; ++i)
    {
        coefs[i] = coefs[i] - polynomial_b.coefs[i];
    }
}

void Polynomial::operator *= (const Polynomial & polynomial_b)
{
    int temp_coefs[7];
    for(int i = 0; i < 7; ++i) temp_coefs[i] = 0;
    for(int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            temp_coefs[i+j] += coefs[i] * polynomial_b.coefs[j];
        }
    }
    for (int i = 0; i < 7; ++i)
    {
        coefs[i] = temp_coefs[i];
    }
}

void Polynomial::operator *= (int b)
{
    for (int i = 0; i < 7; ++i)
    {
        coefs[i] = coefs[i] * b;
    }
}

bool Polynomial::operator == (const Polynomial & polynomial_b) const
{
    for (int i = 0; i < 7; ++i)
    {
        if(coefs[i] != polynomial_b.coefs[i]) return false;
    }
    return true;
}

bool Polynomial::operator != (const Polynomial & polynomial_b) const
{
    return !((*this) == polynomial_b);
}

void Polynomial::showCoefs() const
{
    for (int i = 0; i < 4; ++i)
    {
        std::cout << coefs[i] << " ";
    }
    std::cout << std::endl;
}

Polynomial operator * (int a, const Polynomial & polynomial_b)
{
    Polynomial c;
    for (int i = 0; i < 4; ++i)
    {
        c.coefs[i] += polynomial_b.coefs[i] * a;
    }
    return c;
}

std::ostream & operator<< (std::ostream & os , Polynomial & ob)
{
    int firstNonZero = 6;
    // Search for first non-zero element
    for(int i = firstNonZero; i >= 0; --i)
    {
        if(ob.coefs[i] != 0)
        {
            firstNonZero = i;
            break;
        }
    }
    // Write to stream all non-zero members except free term
    for (int i = firstNonZero; i > 0; --i)
    {
        if(ob.coefs[i] != 0)
        {
            if((i != firstNonZero) && (ob.coefs[i] >=0))
            {
                os << " + " << ob.coefs[i] << "*x^" << i;
            }
            else if((ob.coefs[i] <0))
            {
                os << " - " << -ob.coefs[i] << "*x^" << i;
            }
            else
            {
                os << ob.coefs[i] << "*x^" << i;
            }
        }
    }
    // Write free term
    if(ob.coefs[0] > 0) os <<  " + " << ob.coefs[0];
    if(ob.coefs[0] < 0) os <<  " - " << -ob.coefs[0];
    // Finish polynomial
    os << " = 0\n";
    return os;
}
