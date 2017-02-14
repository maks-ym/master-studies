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
