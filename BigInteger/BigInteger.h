#pragma once;

#include <string>

class BigInteger final
{
public:
    // default constructor
    BigInteger() : reverse_number("0"), positive(true) {}

    // constructors
    BigInteger(const std::string &number);
    BigInteger(std::string &&number);

    // copy & move constructor
    BigInteger(const BigInteger &other)
        : reverse_number(other.reverse_number), positive(other.positive) {}
    BigInteger(BigInteger &&other)
        : reverse_number(std::move(other.reverse_number)), positive(other.positive) {}

    // destructor
    ~BigInteger() {};

    // assignment operators
    BigInteger& operator=(const BigInteger& other);
    BigInteger& operator=(BigInteger&& other);


    const BigInteger operator+(const BigInteger &other) const;
    const BigInteger operator-(const BigInteger &other) const;
    const BigInteger operator*(const BigInteger &other) const;
    //const BigInteger operator/(const BigInteger &other) const;

    const BigInteger operator+() const;
    const BigInteger operator-() const;

    int size() const { return reverse_number.size(); }


    friend std::ostream& operator<<(std::ostream &os, const BigInteger &bi);
    friend void test();

private:
    const std::string add(const std::string &lhs, const std::string &rhs) const;
    const std::string sub(const std::string &lhs, const std::string &rhs) const;
    const std::string mul(const std::string &lhs, const std::string &rhs) const;
    int compare(const std::string &lhs, const std::string &rhs) const;

private:
    bool positive;
    std::string reverse_number; // store numbers in reverse order for the convenience of calculations.
};

