#include <cstring>

#include "BeautifulNumbers.h"
#include "LongNumbers.h"

using std::string;

LongNumber BeautifulNumbers::numberOfCombinations(int n, int k) {
  return LongNumber::Factorial(n) / (LongNumber::Factorial(n - k) * LongNumber::Factorial(k));
}

string BeautifulNumbers::Calculate(int base, int half) {
  LongNumber res;
  LongNumber minusOne(-1);
  for (int i = 0; i <= (base - 1) * half / base; i++)
    res += minusOne.Pow(i) * numberOfCombinations(2 * half, i) 
           * numberOfCombinations((base - 1) * half + 2 * half - 1 - base * i, 2 * half - 1);
  return res.GetValue();
}
