#include "poly.h"

using namespace std;

// --------------------------------------------------------------------------
/*  operator>>
    Overloading in order to take input from user
*/
istream& operator>>(istream& inputStream, Poly& ogCoeff) {
	int co, pow; // coefficient and power variables
	bool isDone = false; 

	while (isDone == false) { // while isDone is false, keep taking input
		inputStream >> co >> pow;
		if (co == -1 && pow == -1) { // will become true when user enters -1 for both coeff and pow
			isDone = true;
			break;
		}
		ogCoeff.setCoeff(co, pow); // using setter to set coeff and pow
	}

	return inputStream;
}

// --------------------------------------------------------------------------
/*  operator<<
    Overloading in order to output the formatted input, in descending order
*/
ostream& operator<<(ostream& outputStream, Poly& og) {
	bool isZero = true; // making sure to not print out any zeros
	for (int i = og.size - 1; i >= 0; --i) { // going in descending order to print larger powers first
		if (og.coeffPtr[i] != 0) { // if it's not 0
			isZero = false;
			outputStream << " ";
			if (og.coeffPtr[i] > 0) outputStream << "+"; // if the coefficiet is greater than 0, then add +
			outputStream << og.coeffPtr[i]; // output.
			if (i != 0 && i != 1) outputStream << "x^" << i; // not printing out x^1 or x^0
			if (i == 1) outputStream << "x";
		}
	}
	if (isZero == false) return outputStream;
	else return outputStream << "0";
}

// --------------------------------------------------------------------------
/*  Constructor
	Default constructor taking no arguments for class Poly
*/
Poly::Poly() {
	this->size = 1;
	coeffPtr = new int[this->size];
	coeffPtr[0] = 0;
}

/*  Constructor
	Constructor taking in 1 parameter (coefficient) for class Poly
*/
Poly::Poly(int coeff) {
	this->size = 1;
	coeffPtr = new int[this->size];
	coeffPtr[0] = coeff;
}
// --------------------------------------------------------------------------
/*	Constructor
	Constructor taking in 2 parameters (coefficient and power) for class Poly
*/
Poly::Poly(int coeff, int pow) {
	this->size = pow + 1; // increasing size by 1
	coeffPtr = new int[this->size];
	for (int i = 0; i < this->size; ++i) coeffPtr[i] = 0; // setting all values to 0
	coeffPtr[pow] = coeff; // set coeffiicient at power
}

// --------------------------------------------------------------------------
/*	Constructor
	Copy constructor taking in 1 parameter (Poly object) for class Poly
*/
Poly::Poly(const Poly& source) {
	this->size = source.size;
	coeffPtr = new int[size];
	for (int i = 0; i < this->size; ++i) coeffPtr[i] = source.coeffPtr[i];
}
// --------------------------------------------------------------------------
/*
	Destructor
	Destructor for class Poly
*/
Poly::~Poly() {
	delete[] coeffPtr;
	coeffPtr = nullptr;
}

// --------------------------------------------------------------------------
/*
	getCoeff
	Getter function taking in a power, returning coefficient at that slot
*/
int Poly::getCoeff(int pow) const {
	if (pow >= 0 && pow < this->size) return coeffPtr[pow]; 
	else return 0;
}

// --------------------------------------------------------------------------
/*
	setCoeff
	Setter function taking in 2 parameters (coefficient and power) to set polynomials.
*/
void Poly::setCoeff(int coeff, int pow) {
	if (pow >= 0) { // as long as power is greater than or = to 0
		if (pow < size) coeffPtr[pow] = coeff; // if power is less than size of array, it's valid
		else { // if not, we create a temp array to resize the array
			int* temp = new int[pow + 1];
			for (int i = 0; i < this->size; ++i) temp[i] = coeffPtr[i]; // copy over all the data
			for (int i = this->size; i < pow + 1; ++i) temp[i] = 0; // set remaining data to 0
																	// (errors out if we don't)

			temp[pow] = coeff;
			this->~Poly(); //intialize destructor so we can point to temp array
			coeffPtr = temp; // not deleting temp otherwise no more linking new data
			this->size = pow + 1;
		}
	}
}

// --------------------------------------------------------------------------
/*
	operator+
	Overloading + operator taking in const Poly object for class Poly
*/
Poly Poly::operator+(const Poly& rs) const {
	if (this->size > rs.size) { // if size of array is greater than size of what's being added
		Poly sum(0, this->size); // temp array to store sum
		// for loop to copy values into larger array
		for (int i = 0; i < this->size; ++i) sum.coeffPtr[i] = coeffPtr[i]; 
		// new array will store the sum of two polynomials
		for (int i = 0; i < rs.size; ++i) sum.coeffPtr[i] += rs.coeffPtr[i];
		return sum; // return sum
	}
	else {
		Poly sum(0, rs.size); // same thing if the rs array size was bigger.
		for (int i = 0; i < rs.size; ++i) sum.coeffPtr[i] = rs.coeffPtr[i];
		for (int i = 0; i < this->size; ++i) sum.coeffPtr[i] += coeffPtr[i]; 
		return sum;
	}
}

// --------------------------------------------------------------------------
/*
	operator-
	Overloading - operator taking in const Poly object for class Poly
*/
Poly Poly::operator-(const Poly& rs) const {
	if (this->size > rs.size) { // if poly size bigger than right side's size
		Poly diff(0, this->size); // create temp array that'll store difference
							// with its size being the largest
		// set all values of coeffPtr into temp array
		for (int i = 0; i < this->size; ++i) diff.coeffPtr[i] = coeffPtr[i];
		// use temp array to -= values inside of right side's array
		for (int i = 0; i < rs.size; ++i) diff.coeffPtr[i] -= rs.coeffPtr[i];
		return diff;
	}
	else {
		Poly diff(0, rs.size); // same thing but with size being right side's size
		for (int i = 0; i < this->size; ++i) diff.coeffPtr[i] = coeffPtr[i];
		for (int i = 0; i < rs.size; ++i) diff.coeffPtr[i] -= rs.coeffPtr[i];
		return diff;
	}
}

// --------------------------------------------------------------------------
/*
	operator*
	Overloading the * operator taking in const Poly object for class Poly
*/
Poly Poly::operator*(const Poly& rs) const {
	int newSize = this->size + rs.size; // multiplying powers adds them together, hence newSize = sum.
	Poly product(0, newSize); // new Poly object to store product
	for (int i = 0; i < this->size; ++i) {
		if (coeffPtr[i] != 0) { // can't mutliply by 0 
			for (int j = 0; j < rs.size; ++j) { // basically does PEMDAS
				product.coeffPtr[i + j] += (this->coeffPtr[i] * rs.coeffPtr[j]); 
			}
		}
	}
	return product;
}

// --------------------------------------------------------------------------
/*
	operator+=
	Overloading += operator taking in const Poly object for class Poly
*/
Poly& Poly::operator+=(const Poly& other) {
	*this = *this + other; // uses overloaded + operator, making it simpler
	return *this;
}						// same goes for -= and *=

// --------------------------------------------------------------------------
/*
	operator-=
	Overloading -= operator taking in const Poly object for class Poly
*/
Poly& Poly::operator-=(const Poly& other) {
	*this = *this - other;
	return *this;
}

// --------------------------------------------------------------------------
/*
	operator*=
	Overloading *= operator taking in const Poly object for class Poly
*/
Poly& Poly::operator*=(const Poly& other) {
	*this = *this * other;
	return *this;
}

// --------------------------------------------------------------------------
/*
	operator==
	Overloading == operator taking in const Poly object for class Poly
*/
bool Poly::operator==(const Poly& other) const {
	if (this->size == other.size) { // if sizes are equal, then check to see if each value inside equal
						// each other
		for (int i = 0; i < this->size || i < other.size; ++i) {
			if (coeffPtr[i] != other.coeffPtr[i]) return false;
		}
		return true;
	}
	else { // if sizes are different, we'll make a small and large int variables to hold sizes
		int small, large;
		if (this->size < other.size) {
			small = this->size;
			large = other.size;

			for (int i = 0; i < small; ++i) { // first will check if they're all equal to each other or not
				if (coeffPtr[i] != other.coeffPtr[i]) return false;
			}
			for (int i = small; i < large; ++i) { // and if they are, then we see the remaining values if 
								// they are the same
				if (coeffPtr[i] != other.coeffPtr[i]) return false;
			}
			return true;
		}
		else {
			small = other.size;
			large = this->size;
			for (int i = 0; i < small; ++i) {
				if (coeffPtr[i] != other.coeffPtr[i]) return false;
			}
			for (int i = small; i < large; ++i) {
				if (coeffPtr[i] != other.coeffPtr[i]) return false;
			}
			return true;
		}
	}
}

// --------------------------------------------------------------------------
/*
	operator!=
	Overloading != operator taking in const Poly object for class Poly
*/
bool Poly::operator!=(const Poly& other) const {
	return !(*this == other); // using overloaded == function to create != operator
}

// --------------------------------------------------------------------------
/*
	operator=
	Overloading = operator taking in const Poly object for class Poly
*/
Poly& Poly::operator=(const Poly& rs) {
	if (this->coeffPtr == rs.coeffPtr) return *this; // if they're the same return left side 

	if (this->size < rs.size) { // if left side is < right side
		this->~Poly(); // initialize destructor and set the size to be the same as right side
		this->size = rs.size;
		coeffPtr = new int[this->size]; // set new size of coeffPtr as the larger size

		for (int i = 0; i < this->size; ++i) coeffPtr[i] = rs.coeffPtr[i];
		// iterate through loop to set all values of right side into left side
	}
	if (this->size > rs.size) { 
		// if the left side is greater, than initialize all the values to 0 first, and then copy over
		// right side values
		for (int i = 0; i < this->size; ++i) coeffPtr[i] = 0;
		for (int i = 0; i < rs.size; ++i) coeffPtr[i] = rs.coeffPtr[i];
	}
	if (this->size == rs.size) { // if they're the same size, just copy values over
		for (int i = 0; i < this->size; ++i) coeffPtr[i] = rs.coeffPtr[i];
	}
	return *this;
}