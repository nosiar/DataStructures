#pragma once;

#include <string>

class BigInteger
{
public:
    BigInteger() : reverse_number("0"), plus(true) {}

    BigInteger(const std::string &number);
    BigInteger(std::string &&number);

    BigInteger(const BigInteger &other)
        : reverse_number(other.reverse_number), plus(other.plus) {}
    BigInteger(BigInteger &&other)
        : reverse_number(std::move(other.reverse_number)), plus(other.plus) {}

    const BigInteger operator+(const BigInteger &other) const;
    const BigInteger operator-(const BigInteger &other) const;
    const BigInteger operator*(const BigInteger &other) const;
    //const BigInteger operator/(const BigInteger &other) const;

    const BigInteger operator+() const;
    const BigInteger operator-() const;

    int size() const { return reverse_number.size(); }

    virtual ~BigInteger() {};

    friend std::ostream& operator<<(std::ostream &os, const BigInteger &bi);
    friend void test();

private:
    const std::string add(const std::string &lhs, const std::string &rhs) const;
    const std::string sub(const std::string &lhs, const std::string &rhs) const;
    const std::string mul(const std::string &lhs, const std::string &rhs) const;
    int compare(const std::string &lhs, const std::string &rhs) const;

private:
    bool plus;
    std::string reverse_number;
};

