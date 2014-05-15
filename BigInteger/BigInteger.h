#ifndef DATASTRUCTURE_BIGINTEGER_H
#define DATASTRUCTURE_BIGINTEGER_H


class BigInteger
{
public:
	BigInteger();

	BigInteger(const BigInteger &other);

	BigInteger(const BigInteger &&other);	

	BigInteger& operator=(const BigInteger &rhs);

	const BigInteger operator+(const BigInteger &other) const ;
	const BigInteger operator-(const BigInteger &other) const ;
	const BigInteger operator*(const BigInteger &other) const ;

	virtual ~BigInteger();

private:
	char *number;
};



#endif /* DATASTRUCTURE_BIGINTEGER_H */