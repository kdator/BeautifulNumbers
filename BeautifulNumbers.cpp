#include <cstring>

#include "BeautifulNumbers.h"
#include "LongNumbers.h"

using std::string;

LongNumber BeautifulNumbers::numberOfCombinations(int n, int k) {
  return LongNumber::Factorial(n) / (LongNumber::Factorial(n - k) * LongNumber::Factorial(k));
}

void BeautifulNumbers::Calculate(int base, int numberOfDigits) {
  LongNumber res;
  LongNumber minusOne(-1);
  int half = numberOfDigits / 2;
  bool isOdd = numberOfDigits % 2;
  if (base < 1 || numberOfDigits <= 1) {
    res = LongNumber(0);
    return;
  }
  for (int i = 0; i <= (base - 1) * half / base; i++)
    res += minusOne.Pow(i) * numberOfCombinations(2 * half, i) 
           * numberOfCombinations((base - 1) * half + 2 * half - 1 - base * i, 2 * half - 1);
  if (isOdd)
    res *= base;
  res_ = res.GetValue();
}

string BeautifulNumbers::GetResult() { return res_.GetValue(); }