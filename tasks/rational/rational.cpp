#include <rational.h>

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
    int gcd = std::gcd(std::abs(value), std::abs(denom_));
    numer_ = value / gcd;
    denom_ = denom_ / gcd;
}

void Rational::SetDenominator(int value) {
    if (value == 0) {
        throw RationalDivisionByZero();
    }
    int gcd = std::gcd(std::abs(numer_), std::abs(value));
    numer_ = numer_ / gcd * (value > 0 ? 1 : -1);
    denom_ = std::abs(value) / gcd;
}

Rational& operator+=(Rational& lhs, const Rational& rhs) {
    int top = lhs.numer_ * rhs.denom_ + rhs.numer_ * lhs.denom_;
    int bottom = lhs.denom_ * rhs.denom_;
    int gcd = std::gcd(std::abs(top), std::abs(bottom));
    lhs = Rational(top / gcd, bottom / gcd);
    return lhs;
}

Rational& operator*=(Rational& lhs, const Rational& rhs) {
    int top = lhs.numer_ * rhs.numer_;
    int bottom = lhs.denom_ * rhs.denom_;
    int gcd = std::gcd(std::abs(top), std::abs(bottom));
    lhs = Rational(top / gcd, bottom / gcd);
    return lhs;
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
            top += top * base + (i - '0');
        } else {
            bottom += bottom * base + (i - '0');
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
    if (rhs == 0) {
        throw RationalDivisionByZero();
    }
    return lhs *= Rational(rhs.GetDenominator(), rhs.GetNumerator());
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    int top = lhs.GetNumerator() * rhs.GetDenominator() + rhs.GetNumerator() * lhs.GetDenominator();
    int bottom = lhs.GetDenominator() * rhs.GetDenominator();
    int gcd = std::gcd(std::abs(top), std::abs(bottom));
    return Rational(top / gcd, bottom / gcd);
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
    int top = lhs.GetNumerator() * rhs.GetDenominator() - rhs.GetNumerator() * lhs.GetDenominator();
    int bottom = lhs.GetDenominator() * rhs.GetDenominator();
    int gcd = std::gcd(std::abs(top), std::abs(bottom));
    return Rational(top / gcd, bottom / gcd);
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
    int top = lhs.GetNumerator() * rhs.GetNumerator();
    int bottom = lhs.GetDenominator() * rhs.GetDenominator();
    int gcd = std::gcd(std::abs(top), std::abs(bottom));
    return Rational(top / gcd, bottom / gcd);
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
    if (rhs == 0) {
        throw RationalDivisionByZero();
    }
    int top = lhs.GetNumerator() * rhs.GetDenominator();
    int bottom = lhs.GetDenominator() * rhs.GetNumerator();
    int gcd = std::gcd(std::abs(top), std::abs(bottom));
    return Rational(top / gcd, bottom / gcd);
}

Rational operator++(Rational& ratio, int) {
    Rational ans(ratio.GetNumerator(), ratio.GetDenominator());
    ++ratio;
    return ans;
}

Rational operator--(Rational& ratio, int) {
    Rational ans(ratio.GetNumerator(), ratio.GetDenominator());
    --ratio;
    return ans;
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    return lhs.GetNumerator() * rhs.GetDenominator() - rhs.GetNumerator() * lhs.GetDenominator() < 0;
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
        os << ratio.GetNumerator();
    } else {
        os << ratio.GetNumerator() << "/" << ratio.GetDenominator();
    }
    return os;
}