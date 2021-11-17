/**
 * @file BeautifulNumbers.h
 * @date 11-15-2021.
 * @brief Provides an interface for counting beautiful numbers and classes for it.
 * @author kolpakov dmitrii.
 */

#pragma once

#include <cstring>

#include "LongNumbers.h"

/**
 * @brief Interface for counting beautiful numbers.
 */
class IBeautifulNumbers {
public:
  /**
   * @brief Counts the number of beautiful numbers based on the number system and
   *        the number of digits in the number.
   * @param base the base of number sustem.
   * @param numberOfDigits the number of digits in one number.
   * @return count of numbers.
   */
  virtual void Calculate(int base, int numberOfDigits) = 0;

  virtual std::string GetResult() = 0;

  virtual ~IBeautifulNumbers() = default;
};

class BeautifulNumbers : public IBeautifulNumbers {
private:
  LongNumber res_;

  /**
   * Calculate number of combinations. See more https://en.wikipedia.org/wiki/Combination
   */
  LongNumber numberOfCombinations(int n, int k);

public:
  /**
   * @brief Counts the number of beautiful numbers based on the number system and
   *        the number of digits in the number.
   * @param base the base of number sustem.
   * @param numberOfDigits the number of digits in one number.
   * @return count of numbers.
   */
  void Calculate(int base, int numberOfDigits) override;

  std::string GetResult() override;

  ~BeautifulNumbers() = default;
};
