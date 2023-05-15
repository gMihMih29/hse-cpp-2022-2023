#include "rational.h"

#include <cmath>

Rational::Rational() : numer_(0), denom_(1) {
}

Rational::Rational(int value) : numer_(value), denom_(1) {  // NOLINT
}

Rational::Rational(int numer, int denom) {
    denom_ = 1;
    this->SetNumerator(numer);
    this->SetDenominator(denom);
}

int Rational::GetNumerator() const {
    return numer_;
}

int Rational::GetDenominator() const {
    return denom_;
}

void Rational::SetNumerator(int value) {
    int gcd = std::gcd(value, denom_);
    numer_ = value / gcd;
    denom_ /= gcd;
}

void Rational::SetDenominator(int value) {
    if (value == 0) {
        throw RationalDivisionByZero();
    }
    int gcd = std::gcd(numer_, value);
    numer_ /= (value > 0 ? gcd : -gcd);
    denom_ = std::abs(value) / gcd;
}

Rational& operator+=(Rational& lhs, const Rational& rhs) {
    return lhs = lhs + rhs;
}

Rational& operator*=(Rational& lhs, const Rational& rhs) {
    return lhs = lhs * rhs;
}

Rational& operator++(Rational& ratio) {
    return ratio = Rational(ratio.numer_ + ratio.denom_, ratio.denom_);
}

Rational& operator--(Rational& ratio) {
    return ratio = Rational(ratio.numer_ - ratio.denom_, ratio.denom_);
}

std::istream& operator>>(std::istream& is, Rational& ratio) {
    const int base = 10;
    std::string input;
    is >> input;
    int top = 0;
    int bottom = 0;
    bool is_top = true;
    bool is_negative = false;
    for (const char& i : input) {
        if (i == '/') {
            is_top = false;
            continue;
        }
        if (i == '+') {
            continue;
        }
        if (i == '-') {
            is_negative = !is_negative;
            continue;
        }
        if (is_top) {
            top = top * base + (i - '0');
        } else {
            bottom = bottom * base + (i - '0');
        }
    }
    if (is_top) {
        bottom = 1;
    }
    ratio = Rational(top * (is_negative ? -1 : 1), bottom);
    return is;
}

Rational operator+(const Rational& ratio) {
    return Rational(ratio.GetNumerator(), ratio.GetDenominator());
}

Rational operator-(const Rational& ratio) {
    return Rational(-ratio.GetNumerator(), ratio.GetDenominator());
}

Rational& operator-=(Rational& lhs, const Rational& rhs) {
    return lhs += -rhs;
}

Rational& operator/=(Rational& lhs, const Rational& rhs) {
    return lhs *= Rational(rhs.GetDenominator(), rhs.GetNumerator());
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    int top = static_cast<int>(lhs.GetNumerator() * rhs.GetDenominator() + rhs.GetNumerator() * lhs.GetDenominator());
    int bottom = static_cast<int>(lhs.GetDenominator() * rhs.GetDenominator());
    return Rational(top, bottom);
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
    int top = static_cast<int>(lhs.GetNumerator() * rhs.GetDenominator() - rhs.GetNumerator() * lhs.GetDenominator());
    int bottom = static_cast<int>(lhs.GetDenominator() * rhs.GetDenominator());
    return Rational(top, bottom);
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
    int top = static_cast<int>(lhs.GetNumerator() * rhs.GetNumerator());
    int bottom = static_cast<int>(lhs.GetDenominator() * rhs.GetDenominator());
    return Rational(top, bottom);
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
    int top = static_cast<int>(lhs.GetNumerator() * rhs.GetDenominator());
    int bottom = static_cast<int>(lhs.GetDenominator() * rhs.GetNumerator());
    return Rational(top, bottom);
}

Rational operator++(Rational& ratio, int) {
    Rational ans = ratio;
    ++ratio;
    return ans;
}

Rational operator--(Rational& ratio, int) {
    Rational ans = ratio;
    --ratio;
    return ans;
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    if (rhs == 0) {
        return lhs.GetNumerator() < 0;
    }
    return (lhs - rhs) < 0;
}

bool operator>(const Rational& lhs, const Rational& rhs) {
    return rhs < lhs;
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
    return lhs < rhs || lhs == rhs;
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
    return lhs > rhs || lhs == rhs;
}

bool operator==(const Rational& lhs, const Rational& rhs) {
    return lhs.GetNumerator() == rhs.GetNumerator() && lhs.GetDenominator() == rhs.GetDenominator();
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const Rational& ratio) {
    if (ratio.GetDenominator() == 1) {
        return os << ratio.GetNumerator();
    }
    return os << ratio.GetNumerator() << "/" << ratio.GetDenominator();
}