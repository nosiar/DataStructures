#pragma once;

class BigInteger
{
public:
	BigInteger(char *number);

	BigInteger(const BigInteger &other);

	BigInteger(const BigInteger &&other);	

	BigInteger& operator=(const BigInteger &rhs);

	const BigInteger operator+(const BigInteger &other) const ;
	const BigInteger operator-(const BigInteger &other) const ;
	const BigInteger operator*(const BigInteger &other) const ;

	virtual ~BigInteger() { delete [] number; };

private:
	bool plus;
	char *number;
};

