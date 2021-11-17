#include <cstring>

#include "BeautifulNumbers.h"
#include "LongNumbers.h"

using std::string;

BeautifulNumbers::BeautifulNumbers(int base, int numberOfDigits) 
  : base_(base), numberOfDigits_(numberOfDigits) {}

void BeautifulNumbers::Calculate() {
  LongNumber res;
  LongNumber minusOne(-1);
  int half = numberOfDigits_ / 2;
  bool isOdd = numberOfDigits_ % 2;
  if (base_ < 1 || numberOfDigits_ <= 1) {
    res = LongNumber(0);
    return;
  }
  for (int i = 0; i <= (base_ - 1) * half / base_; i++)
    res += minusOne.Pow(i) * numberOfCombinations(2 * half, i) 
           * numberOfCombinations((base_ - 1) * half + 2 * half - 1 - base_ * i, 2 * half - 1);
  if (isOdd)
    res *= base_;
  res_ = res.GetValue();
}

string BeautifulNumbers::GetResult() { return res_.GetValue(); }

LongNumber BeautifulNumbers::numberOfCombinations(int n, int k) {
  return LongNumber::Factorial(n) / (LongNumber::Factorial(n - k) * LongNumber::Factorial(k));
}
