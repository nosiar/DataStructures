#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <boost/tokenizer.hpp>
#include "BigInteger.h"

void test()
{
    std::cout << BigInteger{ "23367" } +BigInteger{ "11748" } << '\n';
    std::cout << BigInteger{ "23367" } +BigInteger{ "+11748" } << '\n';
    std::cout << BigInteger{ "23367" } +BigInteger{ "-11748" } << '\n';

    std::cout << BigInteger{ "+23367" } +BigInteger{ "11748" } << '\n';
    std::cout << BigInteger{ "+23367" } +BigInteger{ "+11748" } << '\n';
    std::cout << BigInteger{ "+23367" } +BigInteger{ "-11748" } << '\n';

    std::cout << BigInteger{ "-23367" } +BigInteger{ "11748" } << '\n';
    std::cout << BigInteger{ "-23367" } +BigInteger{ "+11748" } << '\n';
    std::cout << BigInteger{ "-23367" } +BigInteger{ "-11748" } << "\n\n";

    std::cout << BigInteger{ "23367" } -BigInteger{ "11748" } << '\n';
    std::cout << BigInteger{ "23367" } -BigInteger{ "+11748" } << '\n';
    std::cout << BigInteger{ "23367" } -BigInteger{ "-11748" } << '\n';

    std::cout << BigInteger{ "+23367" } -BigInteger{ "11748" } << '\n';
    std::cout << BigInteger{ "+23367" } -BigInteger{ "+11748" } << '\n';
    std::cout << BigInteger{ "+23367" } -BigInteger{ "-11748" } << '\n';

    std::cout << BigInteger{ "-23367" } -BigInteger{ "11748" } << '\n';
    std::cout << BigInteger{ "-23367" } -BigInteger{ "+11748" } << '\n';
    std::cout << BigInteger{ "-23367" } -BigInteger{ "-11748" } << "\n\n";

    std::cout << BigInteger{ "-123456" } -BigInteger{ "-123456" } << '\n';
    std::cout << BigInteger{ "999999" } -BigInteger{ "-1" } << '\n';
    std::cout << BigInteger{ "0" } -BigInteger{ "0" } << "\n\n";

    std::cout << +BigInteger{ "123" } << '\n';
    std::cout << -BigInteger{ "123" } << '\n';
    std::cout << BigInteger{ "1" } +BigInteger{ "2" } +BigInteger{ "3" } << "\n\n";

    std::cout << BigInteger{ "12345" } *BigInteger{ "12" } << '\n';
    std::cout << BigInteger{ "12" } *BigInteger{ "12345" } << '\n';
    std::cout << BigInteger{ "9" } *BigInteger{ "12345" } << '\n';
    std::cout << BigInteger{ "12345" } *BigInteger{ "9" } << '\n';
    std::cout << BigInteger{ "-99999999999999" } *BigInteger{ "99999999999999" } << '\n';
    std::cout << BigInteger{ "-99999999999999" } *BigInteger{ "0" } << '\n';
    std::cout << BigInteger{ "0" } *BigInteger{ "99999999999999" } << '\n';
    std::cout << BigInteger{ "0" } *BigInteger{ "0" } << '\n';
}

enum class State { INIT, LHS, OP, RHS };

bool is_operator(std::string token)
{
    return token.find_first_of("+-*/") != std::string::npos;
}

void process(std::string& line)
{
    using tokenizer = boost::tokenizer < boost::char_separator<char> > ;

    boost::char_separator<char> sep("\t ", "+-*/");

    tokenizer tokens(line, sep);

    State s = State::INIT;

    BigInteger lhs, rhs;
    std::string unary_op = "+";
    std::string binary_op;

    for (auto& x : tokens)
    {
        if (is_operator(x))
        {
            /* operators following another operator are unary.
               the operator with which the expression starts are unary. */
            if (s == State::INIT || s == State::OP)
            {
                /* ex: ++++ -> +
                       -+-- -> -
                       --++ -> + */
                if (x == "-")
                {
                    if (unary_op == "+")
                        unary_op = "-";
                    else
                        unary_op = "+";
                }
                else if (x != "+")
                    throw std::invalid_argument("only '+' and '-' can be unary.");
            }
            // the operator comes right after the first number is binary.
            else if (s == State::LHS)
            {
                binary_op = x;

                s = State::OP;
            }
            else
            {
                throw std::invalid_argument("invalid input.");
            }
        }
        else // x is a number
        {
            if (s == State::INIT)
            {
                if (unary_op == "+")
                    lhs = BigInteger(x);
                else
                    lhs = -BigInteger(x);

                unary_op = "+";

                s = State::LHS;
            }
            else if (s == State::LHS)
            {
                throw std::invalid_argument("a number can't come after a number.");
            }
            else if (s == State::OP)
            {
                if (unary_op == "+")
                    rhs = BigInteger(x);
                else
                    rhs = -BigInteger(x);

                s = State::RHS;
            }
            else
            {
                throw std::invalid_argument("invalid input.");
            }
        }
    }

    if (s != State::RHS)
        throw std::invalid_argument("invalid input.");

    if (binary_op == "+")
        std::cout << lhs + rhs << '\n';
    else if (binary_op == "-")
        std::cout << lhs - rhs << '\n';
    else if (binary_op == "*")
        std::cout << lhs * rhs << '\n';
}

int main()
{
    for (std::string line; std::getline(std::cin, line);)
    {
        if (line == "quit")
            break;

        try
        {
            process(line);
        }
        catch (std::invalid_argument& e)
        {
            std::cout << e.what() << std::endl;
        }
    }
}