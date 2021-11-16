/**
 * @file LongNumbers.h
 * @date 11-14-2021.
 * @brief A class that provides operations with long arithmetic.
 * @author kolpakov dmitrii.
 */

#pragma once

#include <iostream>
#include <string>

class LongNumber {
private:
  std::string value_; /**< value of a number. */
  bool isNegative_; /**< flag that this number is negative. */

  /**
   * @brief Multiplication by Karatsuba's method.
   */
  static LongNumber karatsubaMultiptication(const LongNumber& first, const LongNumber& second);

  /**
   * @brief Get an absolute value.
   * @return absolute value.
   */
  LongNumber abs() const;

public:
  LongNumber(); // inizialize the value with zero.
  LongNumber(const int value); // inizialize the value with a digit.
  LongNumber(const std::string& value); // inizialize the value with a string.
  LongNumber(const LongNumber& other); // copy-constructor.
  //LongNumber(LongNumber&& rhs); // move-constructor.

  /**
   * @brief Get the value equal to 1.
   * @return value equal 1.
   */
  static LongNumber One();

  /**
   * @brief Get the value equal to 0.
   * @return value equal 0.
   */
  static LongNumber Zero();

  /**
   * @brief Calculate factorial for the number n.
   * @param n number to factorial.
   * @return factorial of the number n if n >= 0,
   *         0 otherwise.
   */
  static LongNumber Factorial(int n);

  /**
   * @brief Get current value of the number.
   * @return current value.
   */
  const std::string GetValue() const;

  /**
   * @brief Get the flag of negativity of this number.
   * @return flag of negativity.
   */
  const bool IsNegative() const;

  /**
   * @brief Check if this number is an even.
   * @return is even?
   */
  const bool IsEven() const;
  
  /**
   * @brief Raise the value to a power n.
   * @param n power.
   * @return powered value.
   */
  LongNumber Pow(int n) const;

  /**
   * @brief Extract the root of the n-th degree. n = 2 by default.
   * @param n degree.
   * @return extracted value.
   */
  LongNumber Sqrt(int n = 2) const;

  /**
   * Block of comparision operators.
   */
  const bool operator==(const LongNumber& other) const;
  const bool operator!=(const LongNumber& other) const;
  const bool operator<(const LongNumber& other) const;
  const bool operator>(const LongNumber& other) const;
  const bool operator<=(const LongNumber& other) const;
  const bool operator>=(const LongNumber& other) const;

  /**
   * copy-assignment operator.
   */
  LongNumber& operator=(const LongNumber& other);

  /**
   * Block of unary operators.
   */
  LongNumber operator+() const&&;
  LongNumber operator-() const&&;

  /**
   * Block of binary operators.
   */
  LongNumber operator+(const LongNumber& other) const;
  LongNumber operator-(const LongNumber& other) const;
  LongNumber operator*(const LongNumber& other) const;
  LongNumber operator/(const LongNumber& other) const;
  LongNumber operator%(const LongNumber& other) const;
  LongNumber operator<<(size_t n) const;
  LongNumber operator>>(size_t n) const;

  /**
   * Short form of binary operators.
   */
  LongNumber& operator+=(const LongNumber& other);
  LongNumber& operator-=(const LongNumber& other);
  LongNumber& operator*=(const LongNumber& other);
  LongNumber& operator/=(const LongNumber& other);
  LongNumber& operator%=(const LongNumber& other);
  LongNumber& operator<<=(size_t n);
  LongNumber& operator>>=(size_t n);

  /**
   * Block of postfix and prefix operators.
   */
  LongNumber& operator++();
  LongNumber& operator--();
  LongNumber operator++(int);
  LongNumber operator--(int);

  /**
   * Block of stream operators.
   */
  friend std::ostream& operator<<(std::ostream& stream, const LongNumber& value);
  friend std::istream& operator>>(std::istream& stream, LongNumber& value);
};