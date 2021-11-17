#include <algorithm>
#include <cstring>
#include <string>

#include "LongNumbers.h"

using std::string;

using std::max;
using std::find_if;
using std::to_string;
using std::stol;

LongNumber::LongNumber() : value_("0"), isNegative_(false) {}

LongNumber::LongNumber(const int value) {
  isNegative_ = value < 0;
  value_ = to_string(isNegative_ ? -1 * value : value);
}

LongNumber::LongNumber(const string& value) {
  if (!value.length()) {
    this->value_ = "0";
    isNegative_ = false;
    return;
  }

  isNegative_ = value[0] == '-';
  if (isNegative_ && value.length() == 1)
    throw string("number must contain digits");
  this->value_ = value.substr(isNegative_);

  uint32_t count = 0;
  while (this->value_[count] == '0' && this->value_.length() - count > 1)
    count++;
  this->value_ = this->value_.substr(count);

  auto it = find_if(value_.cbegin(), value_.cend(), [](const char& c) { return !isdigit(c); });
  if (it != value_.cend())
    throw string("invalid value");
}

LongNumber::LongNumber(const LongNumber& other) {
  value_ = other.GetValue();
  isNegative_ = other.IsNegative();
}

LongNumber LongNumber::One() { return LongNumber(1); }

LongNumber LongNumber::Zero() { return LongNumber(); }

LongNumber LongNumber::Factorial(int n) {
  if (n < 0)
    return 0;
  LongNumber res(1);
  for (LongNumber i = 2; i <= n; i++)
    res *= i;
  return res;
}

const string LongNumber::GetValue() const { return value_; }

const bool LongNumber::IsNegative() const { return isNegative_; }

const bool LongNumber::IsEven() const {
  return static_cast<int>(value_[value_.length() - 1] - '0') & (0x1 << 0) ? false : true;
}

LongNumber LongNumber::abs() const { return LongNumber(value_); }

LongNumber LongNumber::Pow(int n) const {
  // TODO: implement fast algorithm of powering. see https://cp-algorithms.com/algebra/binary-exp.html
  if (!n)
    return 1;
  if (n & 1)
    return Pow(n - 1) * (*this);
  else {
    LongNumber tmp = Pow(n / 2);
    return tmp * tmp;
  }
}

LongNumber LongNumber::Sqrt(int n) const {
  if (n < 2)
    throw string("power() - a power must be more or equal than 2");
  if (isNegative_ && ((n & 1) == 0))
    throw string("sqrt() -  value_ must be positive");

  size_t length = (value_.length() + 1) / 2;
  size_t index = 0;

  string res(length, '0');
  while (index < length) {
    res[index] = '9';

    while (LongNumber(res).Pow(n) > this->abs() && res[index] > '0')
      res[index]--;

    index++;
  }

  return isNegative_ ? string("-") + res : res;
}

const bool LongNumber::operator==(const LongNumber& other) const {
  return (value_ == other.GetValue()) && (isNegative_ == other.IsNegative());
}

const bool LongNumber::operator!=(const LongNumber& other) const {
  return !(*this == other);
}

const bool LongNumber::operator<(const LongNumber& other) const {
  string otherValue = other.GetValue();
  size_t valLen = value_.length();
  size_t otherValLen = otherValue.length();
  if (isNegative_ == other.IsNegative()) {
    if (otherValLen != valLen)
      return (valLen < otherValLen) ^ isNegative_;
    
    size_t i = 0;
    while (i < valLen && value_[i] == otherValue[i])
      i++;

    // если разряд найден, то меньше число с меньшей цифрой для положительных и с 
    // большей цифрой для отрицательных, иначе числа равны.
    return (i < valLen) && ((value_[i] < otherValue[i]) ^ isNegative_);
  }

  return isNegative_;
}

const bool LongNumber::operator>(const LongNumber& other) const {
  return !(*this < other || *this == other);
}

const bool LongNumber::operator<=(const LongNumber& other) const {
  return *this < other || *this == other;
}

const bool LongNumber::operator>=(const LongNumber& other) const {
  return *this > other || *this == other;
}

LongNumber& LongNumber::operator=(const LongNumber& other) {
  value_ = other.GetValue();
  isNegative_ = other.IsNegative();

  return *this;
}

LongNumber LongNumber::operator-() const&& {
  return LongNumber(isNegative_ ? value_ : string("-") + value_);
}

LongNumber LongNumber::operator+() const&& {
  return LongNumber(*this);
}

LongNumber LongNumber::karatsubaMultiptication(const LongNumber& first, const LongNumber& second) {
  // SEE MORE https://en.wikipedia.org/wiki/Karatsuba_algorithm
  string v1 = first.GetValue();
  string v2 = second.GetValue();
  size_t len1 = v1.length();
  size_t len2 = v2.length();
  size_t len = max(len1, len2);

  if (len1 + len2 < 9)
    return stol(first.GetValue()) * stol(second.GetValue());

  len += len % 2;
  size_t n = len / 2;

  LongNumber Xl(first >> n);
  LongNumber Xr(len1 > n ? v1.substr(len1 - n, n) : v1);
  LongNumber Yl(second >> n);
  LongNumber Yr(len2 > n ? v2.substr(len2 - n, n) : v2);

  LongNumber P1 = karatsubaMultiptication(Xl, Yl);
  LongNumber P2 = karatsubaMultiptication(Xr, Yr);
  LongNumber P3 = karatsubaMultiptication(Xl + Xr, Yl + Yr);

  return (P1 << len) + ((P3 - P2 - P1) << n) + P2;
}

LongNumber LongNumber::operator+(const LongNumber& other) const {
  bool isAddOpp = !(other.IsNegative() ^ isNegative_); // if sign equals, add numbers;

  if (isAddOpp) {
    string num2 = other.GetValue(); // copy value_ of other object.

    size_t len1 = value_.length(); // remember the length of this value_.
    size_t len2 = num2.length(); // remember the length of other value_.
    size_t length = 1 + max(len1, len2); // length of addition with extra one pos for possible shift.

    char* res = new char[length + 1];
    res[length - 1] = res[length] = '\0';

    for (size_t i = 0; i < length - 1; i++) {
      int j = length - 1 - i;
      res[j] += ((i < len2) ? (num2[len2 - 1 - i] - '0') : 0) 
                 + ((i < len1) ? (value_[len1 - 1 - i] - '0') : 0);
      res[j - 1] = res[j] / 10;
      res[j] = res[j] % 10 + '0';
    }
    res[0] += '0';

    LongNumber out(isNegative_ ? string("-") + string(res) : string(res));
    delete[] res;
    return out;
  }
  else
    return isNegative_ ? (other - (-LongNumber(*this))) : (*this - (-LongNumber(other)));
}

LongNumber LongNumber::operator-(const LongNumber& other) const {
  if (*this == other)
    return 0; // if values are equal, return 0.

  // if both are negative - do subtract.
  if (!isNegative_ && !other.IsNegative()) {
    string value2 = other.GetValue();

    size_t len1 = value_.length();
    size_t len2 = value2.length();
    size_t length = max(len1, len2); // result length cannot be more that max between the values.

    bool isNegRes = other > *this; // check the result sign.

    int* a = new int[length];
    int* b = new int[length];
    a[0] = b[0] = 0;

    char* res = new char[length + 1];
    res[length - 1] = res[length] = '\0'; // make buf to C-string.

    int sign = (2 * isNegRes - 1); // result sign from bool -> int.

    for (size_t i = 0; i < length - 1; i++) {
      a[i] += (i < len1) ? (value_[len1 - 1 - i] - '0') : 0;
      b[i] += (i < len2) ? (value2[len2 - 1 - i] - '0') : 0;
      
      // depending on the sign, we take or do not take 10 from the next digit.
      b[i + 1] = -isNegRes;
      a[i + 1] = isNegRes - 1;

      res[length - 1 - i] += 10 + sign * (b[i] - a[i]);
      res[length - 1 - i - 1] = res[length - 1 - i] / 10;
      res[length - 1 - i] = res[length - 1 - i] % 10 + '0';
    }

    a[length - 1] += (length - 1 < len1) * (value_[0] - '0');
    b[length - 1] += (length - 1 < len2) * (value2[0] - '0');

    res[0] += sign * (b[length - 1] - a[length - 1]) + '0';

    delete[] a;
    delete[] b;
    LongNumber out(isNegRes ? string("-") + string(res) : string(res));
    delete[] res;
    return out;
  }
  else // if both are negative, then we swap, change the signs and repeat the subtraction, and if the signs are different, then we do the sum.
    return isNegative_ && other.IsNegative() ? (-LongNumber(other) - (-LongNumber(*this))) : (*this + -LongNumber(other));
}

LongNumber LongNumber::operator*(const LongNumber& other) const {
  if (value_ == "0" || other.GetValue() == "0")
    return 0;

  string value2 = other.GetValue();

  size_t len2 = value2.length();
  size_t len1 = value_.length();
  size_t length = len1 + len2 + 1;
  bool isNegRes = isNegative_ ^ other.IsNegative();

  if (length < 10) { // do multiplication like with int.
    long res = stol(value_) * stol(value2);
    return LongNumber(isNegRes ? -res : res);
  }
  else if (length < 2000) { // column multiplication
    int* a = new int[length];
    int* b = new int[length];

    char* res = new char[length + 1];
    res[length] = '\0';

    for (size_t i = 0; i < length; i++) {
      a[i] = (i < len1) ? (value_[len1 - 1 - i] - '0') : 0;
      b[i] = (i < len2) ? (value2[len2 - 1 - i] - '0') : 0;
      res[i] = 0;
    }

    for (size_t i = 0; i < len1; i++) {
      for (size_t j = 0; j < len2; j++) {
        res[length - 1 - (i + j)] += a[i] * b[j];
        res[length - 1 - (i + j + 1)] += res[length - 1 - (i + j)] / 10;
        res[length - 1 - (i + j)] %= 10;
      }
    }

    for (size_t i = 0; i < length; i++)
      res[length - 1 - i] += '0';

    delete[] a;
    delete[] b;
    LongNumber out(isNegRes ? string("-") + string(res) : string(res));
    delete[] res;
    return out;
  }
  else { // Karatsuba's multiplication.
    LongNumber res = karatsubaMultiptication(*this, other);
    return isNegRes ? -LongNumber(res) : res;
  }
}

LongNumber LongNumber::operator/(const LongNumber& other) const {
  string value1 = value_;
  string value2 = other.GetValue();

  if (value2[0] == '0')
    throw string("Division by zero!"); // like really? division by zero? :/

  if (value_[0] == '0')
    return 0;

  if (value2 == "1")
    return LongNumber(other.IsNegative() ? -LongNumber(*this) : *this);

  size_t zeroes = 0;
  while (value2[value2.length() - 1 - zeroes] == '0')
    zeroes++;

  if (zeroes >= value_.length())
    return 0;

  if (zeroes) {
    value1 = value1.substr(0, value1.length() - zeroes);
    value2 = value2.substr(0, value2.length() - zeroes);
  }

  bool isNegRes = isNegative_ ^ other.IsNegative();
  LongNumber tmp(value2);

  size_t divider_length = value2.length();
  long divider_v = divider_length > 8 ? 0 : atol(value2.c_str()); // if the length is greater than 8, then we reset the long divisor, 
                                                                  // otherwise we convert the string to long.

  size_t length = value1.length();
  size_t index = 0;

  string div;
  string v; // a row for a number (which is divided by a divisor in a column).

  // forming the initial number for division.
  while (LongNumber(v) < tmp && index < length)
    v += value1[index++];

  do {
    int count = 0; // the result of dividing by a number by a divisor.

    // if we can divide, then do it.
    if (LongNumber(v) >= tmp) {
      if (divider_length > 8) { // if not fitted in long, then divide by subtraction.
        LongNumber mod = v;

        while (mod >= tmp) {
          mod -= tmp;
          count++;
        }

        v = mod.GetValue();
      }
      else {
        long mod = stol(v);
        count = mod / divider_v;
        v = to_string(mod % divider_v);
      }
    }

    div += count + '0'; // if they did not divide, then they added zero 
                        // to the result, otherwise they added the result of division.

    if (index <= length)
      v += value1[index++]; // forming a new value for a sub-number.
  } while (index <= length);

  return LongNumber(isNegRes && div != "0" ? string("-") + div : div);
}

LongNumber LongNumber::operator%(const LongNumber& other) const {
  string value2 = other.GetValue();

  if (value2[0] == '0')
    throw string("Division by zero!");

  if (value_[0] == '0' || value2 == "1")
    return 0;

  if (value_.length() < 9 && value2.length() < 9) {
    long res = stol(value_) % stol(value2);
    return isNegative_ ? -res : res;
  }

  LongNumber tmp(value2);

  size_t divider_length = value2.length();
  long divider_v = divider_length >= 9 ? 0 : atol(value2.c_str()); // if the length is greater than 8, then we reset the long divisor, 
                                                                   // otherwise we convert the string to long.

  size_t length = value_.length();
  size_t index = 0;
  LongNumber mod2 = value_;
  string v;

  while (LongNumber(v) < tmp && index < length)
    v += value_[index++];

  do {
    if (LongNumber(v) >= tmp) {
      if (divider_v)
        v = to_string(stol(v) % divider_v);
      else {
        LongNumber mod = v;

        while (mod >= tmp)
          mod -= tmp;

        v = mod.GetValue();
      }
    }

    if (index <= length) {
      mod2 = v;
      v += value_[index++];
    }
  } while (index <= length);

  if (mod2.GetValue() == "0")
    return 0;

  return isNegative_ ? -LongNumber(mod2) : mod2;
}

LongNumber LongNumber::operator<<(size_t n) const {
  return LongNumber(string(isNegative_ ? "-" : "") + value_ + string(n, '0'));
}

LongNumber LongNumber::operator>>(size_t n) const {
  if (n >= value_.length())
    return 0;
  return LongNumber(string(isNegative_ ? "-" : "") + value_.substr(0, value_.length() - n));
}

LongNumber& LongNumber::operator+=(const LongNumber& other) {
  return *this = *this + other;
}

LongNumber& LongNumber::operator-=(const LongNumber& other) {
  return *this = *this - other;
}

LongNumber& LongNumber::operator*=(const LongNumber& other) {
  return *this = *this * other;
}

LongNumber& LongNumber::operator/=(const LongNumber& other) {
  return *this = *this / other;
}

LongNumber& LongNumber::operator%=(const LongNumber& other) {
  return *this = *this % other;
}

LongNumber& LongNumber::operator<<=(size_t n) {
  return *this = *this << n;
}

LongNumber& LongNumber::operator>>=(size_t n) {
  return *this = *this >> n;
}

LongNumber& LongNumber::operator++() {
  return *this = *this + 1;
}

LongNumber& LongNumber::operator--() {
  return *this = *this - 1;
}

LongNumber LongNumber::operator++(int) {
  LongNumber copy = *this;
  *this = *this + LongNumber(1);
  return copy;
}

LongNumber LongNumber::operator--(int) {
  LongNumber copy = *this;
  *this = *this - LongNumber(1);
  return copy;
}

std::ostream& operator<<(std::ostream& stream, const LongNumber& value) {
  if (value.IsNegative())
    stream << '-';
  return stream << value.GetValue();
}

std::istream& operator>>(std::istream& stream, LongNumber& value) {
  string v;
  stream >> v;
  value = LongNumber(v);
  return stream;
}
