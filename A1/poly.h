// file poly.h
// Simple class Poly

#ifndef POLY_POLY_H
#define POLY_POLY_H
#include <iostream>
using namespace std;


class Poly {

    friend istream& operator>>(istream& inputStream, Poly& ogCoeff);
    friend ostream& operator<<(ostream& outputStream, Poly& og);

private:
    int* coeffPtr; // pointer to array
    int size; // size of array

public:
    Poly();                                 // default constructor
    Poly(int coeff);                        // constructor taking in 1 parameter (int)
    Poly(int coeff, int pow);               // constructor taking in 2 parameters (int, int)
    Poly(const Poly& source);               // copy constructor taking 1 parameter (Poly)
    ~Poly();                                // destructor

    int getCoeff(int power) const;          // returns coefficient at given power if it exists
    void setCoeff(int coeff, int pow);      // sets coefficient at power

    Poly operator+(const Poly& rs) const;   // overloaded operator+
    Poly operator-(const Poly& rs) const;   // overloaded operator-
    Poly operator*(const Poly& rs) const;   // overloaded operator*

    Poly& operator+=(const Poly& rs);       // overloaded operator+=
    Poly& operator-=(const Poly& rs);       // overloaded operator-=
    Poly& operator*=(const Poly& rs);       // overloaded operator*=

    bool operator==(const Poly& other) const; // overloaded operator==
    bool operator!=(const Poly& other) const; // overloaded operator!=

    Poly& operator=(const Poly& rs); // overloaded operator=

};
#endif