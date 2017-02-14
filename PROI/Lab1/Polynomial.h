#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <iostream>
/*
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
