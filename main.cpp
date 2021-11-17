#include <iostream>
#include <memory>
#include <cstring>
#include <limits>

#include "BeautifulNumbers.h"

using std::unique_ptr;
using std::string;
using std::numeric_limits;
using std::streamsize;

using std::cout;
using std::cin;
using std::endl;
using std::make_unique;

int main() {
  const int base = 13;
  const int numberOfDigits = 13;

  unique_ptr<IBeautifulNumbers> pt = make_unique<BeautifulNumbers>(base, numberOfDigits);
  string res;
  if (pt) {
    pt.get()->Calculate();
    res = pt.get()->GetResult();
  }

  cout << "Count of beautiful numbers: " << res << endl;
  cin.get();
  return 0; 
}
