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
  int base, numberOfDigits;

  cout << "Enter the base of number system: ";
  cin >> base;
  if (cin.fail()) {
    cout << "\nBad parameter.";
    cin.ignore();
    cin.fail();
    return 0;
  }
  cout << "\nEnter the number of digits in the number: ";
  cin >> numberOfDigits;
  if (cin.fail()) {
    cout << "\nBad parameter.";
    cin.ignore();
    cin.fail();
    return 0;
  }

  unique_ptr<IBeautifulNumbers> pt = make_unique<BeautifulNumbers>();
  string res;
  if (pt) {
    pt.get()->Calculate(base, numberOfDigits);
    res = pt.get()->GetResult();
  }

  cout << "\nCount of beautiful numbers: " << res << endl;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cin.clear();
  cin.get();
  return 0; 
}
