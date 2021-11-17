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
  virtual void Calculate() = 0;

  virtual std::string GetResult() = 0;

  virtual ~IBeautifulNumbers() = default;
};

class BeautifulNumbers : public IBeautifulNumbers {
private:
  LongNumber res_;
  int base_;
  int numberOfDigits_;

  /**
   * Calculate number of combinations. See more https://en.wikipedia.org/wiki/Combination
   */
  LongNumber numberOfCombinations(int n, int k);

public:
  explicit BeautifulNumbers(int base, int numberOfDigits);

  ~BeautifulNumbers() = default;

  /**
   * @brief Counts the number of beautiful numbers based on the number system and
   *        the number of digits in the number.
   */
  void Calculate() override;

  /**
   * Get the result of calculations.
   * @return the result.
   */
  std::string GetResult() override;
};
