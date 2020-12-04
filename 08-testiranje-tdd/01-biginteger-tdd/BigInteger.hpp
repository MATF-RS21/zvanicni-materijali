#include <vector>
#include <string>
#include <numeric>
#include <iterator>
#include <algorithm>

class BigInteger
{
public:
    enum Sign
    {
        Zero,
        Positive,
        Negative
    };

public:
    BigInteger()
        : _digits({0}), _sign(Zero)
    {
    }

    BigInteger(std::string number)
    {
        extractSign(number);
        extractDigits(number);
    }

    int toInt() const
    {
        using std::begin, std::end;
        return SignToInt(sign()) * std::accumulate(begin(_digits), end(_digits), int{}, [](const auto acc, const auto next) {
            return 10 * acc + next;
        });
    }

    size_t numberOfDigits() const
    {
        return _digits.size();
    }

    Sign sign() const
    {
        return _sign;
    }

    bool operator==(const BigInteger &other) const 
    {
        if (!SignsAreEqual(sign(), other.sign()))
        {
            return false;
        }
        if (!BothNumberOfDigitsAreEqual(numberOfDigits(), other.numberOfDigits()))
        {
            return false;
        }

        using std::begin, std::end;
        return std::equal(begin(_digits), end(_digits), begin(other._digits));
    }

private:
    static int SignToInt(const Sign sign)
    {
        if (sign == Zero) return 0;
        if (sign == Positive) return 1;
        return -1;
    }

    static bool SignsAreEqual(const Sign sign1, const Sign sign2)
    {
        return sign1 == sign2;
    }

    static bool BothNumberOfDigitsAreEqual(const size_t numOfDigits1, const size_t numOfDigits2)
    {
        return numOfDigits1 == numOfDigits2;
    }

private:
    void extractSign(std::string &number)
    {
        if (number.front() == '-')
        {
            _sign = Negative;
            number = number.substr(1);
        }
        else if (number.front() == '0')
        {
            _sign = Zero;
        }
        else 
        {
            _sign = Positive;
        }
    }

    void extractDigits(const std::string &number)
    {
        extractFirstDigit(number);
        extractTail(number);
    }

    void extractFirstDigit(const std::string &number)
    {
        _digits.push_back(digitFromChar(number.front()));
    }

    void extractTail(const std::string &number)
    {
        auto tail{number.substr(1)};
        if (tail.empty())
        {
            return;
        }
        extractDigits(tail);
    }

    unsigned digitFromChar(const char digit) const
    {
        return static_cast<unsigned>(digit - '0');
    }

private:
    std::vector<unsigned> _digits;
    Sign _sign;
};