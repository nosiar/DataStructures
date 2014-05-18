#include "BigInteger.h"

#include <iostream>
#include <algorithm>

BigInteger::BigInteger(const std::string &number) : reverse_number(number)
{
    std::reverse(reverse_number.begin(), reverse_number.end());

    if(reverse_number.back() == '+')
    {
        plus = true;
        reverse_number.pop_back();
    }
    else if(reverse_number.back() == '-')
    {
        if(reverse_number == "0")
            plus = true;
        else
            plus = false;
        reverse_number.pop_back();
    }
    else
    {
        plus = true;
    }
}

BigInteger::BigInteger(std::string &&number) : reverse_number(std::move(number))
{
    std::reverse(reverse_number.begin(), reverse_number.end());

    if(reverse_number.back() == '+')
    {
        plus = true;
        reverse_number.pop_back();
    }
    else if(reverse_number.back() == '-')
    {
        plus = false;
        reverse_number.pop_back();
    }
    else
    {
        plus = true;
    }
}

const BigInteger BigInteger::operator+(const BigInteger &other) const
{
    BigInteger result;

    // this and other have difference signs.
    if(this->plus ^ other.plus)
    {		
        result.reverse_number = sub(this->reverse_number, other.reverse_number);

        int r = compare(this->reverse_number, other.reverse_number);
        
        if(result.reverse_number == "0")
            result.plus = true;
        else if(r > 0)
            result.plus = this->plus;
        else if( r < 0)
            result.plus = other.plus;
        else
            result.plus = true;
    }
    // this and other have same signs.
    else
    {
        result.reverse_number = add(this->reverse_number, other.reverse_number);
        result.plus = this->plus;
    }

    return result;
}

const BigInteger BigInteger::operator-(const BigInteger &other) const
{
    BigInteger result;

    // this and other have difference signs.
    if(this->plus ^ other.plus)
    {
        result.reverse_number = add(this->reverse_number, other.reverse_number);
        result.plus = this->plus;
    }
    // this and other have same signs.
    else
    {
        result.reverse_number = sub(this->reverse_number, other.reverse_number);

        int r = compare(this->reverse_number, other.reverse_number);

        if(result.reverse_number == "0")
            result.plus = true;
        else if(r > 0)
            result.plus = this->plus;
        else if( r < 0)
            result.plus = !other.plus;
        else
            result.plus = true;
    }

    return result;
}

const BigInteger BigInteger::operator*(const BigInteger &other) const
{
    BigInteger result;
    
    result.reverse_number = mul(this->reverse_number, other.reverse_number);
    
    if(result.reverse_number == "0")
        result.plus = true;
    else
        result.plus = !(this->plus ^ other.plus);

    return result;
}

const BigInteger BigInteger::operator+() const
{
    return BigInteger(*this);
}

const BigInteger BigInteger::operator-() const
{
    BigInteger result(*this);

    result.plus = !result.plus;

    return result;
}

const std::string BigInteger::add(const std::string &lhs, const std::string &rhs) const
{
    std::string result;

    result.reserve(std::max(lhs.size(), rhs.size()) + 1);

    const std::string &small = lhs.size() < rhs.size() ? lhs : rhs;
    const std::string &large = lhs.size() >= rhs.size() ? lhs : rhs;

    auto small_it = small.begin();
    auto large_it = large.begin();
    auto result_it = std::back_inserter(result);

    int carry = 0;
    while(small_it != small.end())
    {
        int sum = *small_it++ + *large_it++ + carry - 96;

        *result_it++ = sum % 10 + 48;

        carry = sum / 10;
    }

    while(large_it != large.end())
    {
        int sum = *large_it++ + carry - 48;

        *result_it++ = sum % 10 + 48;

        carry = sum / 10;
    }

    if(carry > 0)
        *result_it = carry + 48;

    return result;
}

const std::string BigInteger::sub(const std::string &lhs, const std::string &rhs) const
{
    std::string result;

    result.reserve(std::max(lhs.size(), rhs.size()));

    const std::string &small = compare(lhs, rhs) < 0 ? lhs : rhs;
    const std::string &large = compare(lhs, rhs) >= 0 ? lhs : rhs;

    auto small_it = small.begin();
    auto large_it = large.begin();
    auto result_it = std::back_inserter(result);

    int carry = 0;
    while(small_it != small.end())
    {
        int sum = *large_it++ - *small_it++ + carry;

        if(sum < 0)
        {
            *result_it++ = sum + 10 + 48;
            carry = -1;
        }
        else
        {
            *result_it++ = sum + 48;
            carry = 0;
        }
    }

    while(large_it != large.end())
    {
        int sum = *large_it++ + carry - 48;

        if(sum < 0)
        {
            *result_it++ = sum + 10 + 48;
            carry = -1;
        }
        else
        {
            *result_it++ = sum + 48;
            carry = 0;
        }
    }

    // remove 0s
    result.resize(result.find_last_not_of('0')+1);
    if(result.empty())
        result.append("0");

    return result;
}

const std::string BigInteger::mul(const std::string &lhs, const std::string &rhs) const
{
    std::string result;

    result.reserve(lhs.size() + rhs.size());
    
    auto lhs_begin = lhs.begin();
    auto rhs_begin = rhs.rbegin();
    auto result_it = std::back_inserter(result);

    int max_digit = lhs.size() - 1 + rhs.size() - 1;

    int carry = 0;

    for(int digit = 0; digit <= max_digit; ++digit )
    {
        int lhs_start = std::max(0, digit - (int)(rhs.size() - 1));
        int rhs_start = std::max(0, (int)(rhs.size() - 1) - digit);

        auto lhs_it = lhs_begin + lhs_start;
        auto rhs_it = rhs_begin + rhs_start;
        
        int sum = 0;
        while(lhs_it != lhs.end() && rhs_it != rhs.rend())
        {
            sum += (*lhs_it++ - 48) * (*rhs_it++ - 48);
        }
        sum += carry;

        *result_it++ = sum % 10 + 48;

        carry = sum / 10;
    }
    
    while(carry > 0)
    {
        *result_it++ = carry % 10 + 48;

        carry /= 10;
    }
    
    // remove 0s
    result.resize(result.find_last_not_of('0')+1);
    if(result.empty())
        result.append("0");

    return result;
}

int BigInteger::compare(const std::string &lhs, const std::string &rhs) const
{
    if(lhs.size() < rhs.size())
        return -1;
    else if(lhs.size() > rhs.size())
        return 1;
    else if(lhs.size() == rhs.size())
    {
        for(auto lhs_it = lhs.rbegin(), rhs_it = rhs.rbegin(); lhs_it != lhs.rend(); ++lhs_it, ++rhs_it)
        {
            if(*lhs_it < *rhs_it)
                return -1;
            else if(*lhs_it > *rhs_it)
                return 1;	
        }
    }

    return 0;
}

std::ostream& operator<<(std::ostream &os, const BigInteger &bi)
{
    std::string obverse;
    obverse.reserve(bi.reverse_number.size());

    std::reverse_copy(bi.reverse_number.begin(), bi.reverse_number.end(), std::back_inserter(obverse));

    if(!bi.plus)
        os << '-';

    os << obverse;

    return os;
}
