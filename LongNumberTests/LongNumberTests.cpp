#include "pch.h"

#include <cstring>
#include <vector>
#include <map>
#include <utility>

#include "..\LongNumbers.h"

using std::string;
using std::vector;
using std::map;

using std::make_pair;

TEST(LongNumbers, Factorials) {
  vector<LongNumber> factorials;
  factorials.push_back(LongNumber::Factorial(1));
  for (int i = 10; i <= 100; i += 10)
    factorials.push_back(LongNumber::Factorial(i));

  // number to its factorial.
  // vector element (index + 1) * 10 = map key. 
  map<int, string> numToStr = { 
    make_pair(1, "1"), make_pair(10, "3628800"), make_pair(20, "2432902008176640000"),
    make_pair(30, "265252859812191058636308480000000"), make_pair(40, "815915283247897734345611269596115894272000000000"),
    make_pair(50, "30414093201713378043612608166064768844377641568960512000000000000"),
    make_pair(60, "8320987112741390144276341183223364380754172606361245952449277696409600000000000000"),
    make_pair(70, "119785716699698917960727837216890987364589381425464258575553628646280095827898453196800000000"
                  "00000000"),
    make_pair(80, "715694570462638022948115337231865321655846573423657525771094450582270392554801488426689448672"
                  "80814080000000000000000000"),
    make_pair(90, "148571596448176149730952273362082573788556996128468876694221686370498539309406587654599213137"
                  "0884059645617234469978112000000000000000000000"),
    make_pair(100, "93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976"
                   "156518286253697920827223758251185210916864000000000000000000000000"),
  };

  ASSERT_EQ(factorials[0], numToStr[1]);
  ASSERT_EQ(factorials[1], numToStr[10]);
  ASSERT_EQ(factorials[2], numToStr[20]);
  ASSERT_EQ(factorials[3], numToStr[30]);
  ASSERT_EQ(factorials[4], numToStr[40]);
  ASSERT_EQ(factorials[5], numToStr[50]);
  ASSERT_EQ(factorials[6], numToStr[60]);
  ASSERT_EQ(factorials[7], numToStr[70]);
  ASSERT_EQ(factorials[8], numToStr[80]);
  ASSERT_EQ(factorials[9], numToStr[90]);
  ASSERT_EQ(factorials[10], numToStr[100]);
}

TEST(LongNumbers, DefaultConstructor) {
  LongNumber num;
  EXPECT_EQ(num.GetValue(), "0");
}

TEST(LongNumbers, ConstructWithInt) {
  LongNumber val1(-1);
  LongNumber val2(0);
  LongNumber val3(1);
  LongNumber val4(-0xFF);
  LongNumber val5(1000);

  ASSERT_EQ(val1.GetValue(), "1");
  ASSERT_TRUE(val1.IsNegative());

  ASSERT_EQ(val2.GetValue(), "0");
  ASSERT_FALSE(val2.IsNegative());

  ASSERT_EQ(val3.GetValue(), "1");
  ASSERT_FALSE(val3.IsNegative());

  ASSERT_EQ(val4.GetValue(), "255");
  ASSERT_TRUE(val4.IsNegative());

  ASSERT_EQ(val5.GetValue(), "1000");
  ASSERT_FALSE(val5.IsNegative());
}

TEST(LongNumbers, ConstructWithString) {
  LongNumber val1("-1");
  LongNumber val2("0");
  LongNumber val3("1");
  LongNumber val4("-255");
  LongNumber val5("1000");

  ASSERT_EQ(val1.GetValue(), "1");
  ASSERT_TRUE(val1.IsNegative());

  ASSERT_EQ(val2.GetValue(), "0");
  ASSERT_FALSE(val2.IsNegative());

  ASSERT_EQ(val3.GetValue(), "1");
  ASSERT_FALSE(val3.IsNegative());

  ASSERT_EQ(val4.GetValue(), "255");
  ASSERT_TRUE(val4.IsNegative());

  ASSERT_EQ(val5.GetValue(), "1000");
  ASSERT_FALSE(val5.IsNegative());
}

TEST(LongNumbers, ConstructWithCopy) {
  LongNumber val1(LongNumber(-1));
  LongNumber val2(LongNumber(0));
  LongNumber val3(LongNumber(1));
  LongNumber val4(LongNumber(-0xFF));
  LongNumber val5(LongNumber(1000));

  ASSERT_EQ(val1.GetValue(), "1");
  ASSERT_TRUE(val1.IsNegative());

  ASSERT_EQ(val2.GetValue(), "0");
  ASSERT_FALSE(val2.IsNegative());

  ASSERT_EQ(val3.GetValue(), "1");
  ASSERT_FALSE(val3.IsNegative());

  ASSERT_EQ(val4.GetValue(), "255");
  ASSERT_TRUE(val4.IsNegative());

  ASSERT_EQ(val5.GetValue(), "1000");
  ASSERT_FALSE(val5.IsNegative());
}

TEST(LongNumbers, CheckIsEven) {
  LongNumber val1(1);
  LongNumber val2(2);
  LongNumber val3(100);
  LongNumber val4(-1);
  LongNumber val5(-2);
  LongNumber val6(0);

  ASSERT_FALSE(val1.IsEven());
  ASSERT_TRUE(val2.IsEven());
  ASSERT_TRUE(val3.IsEven());
  ASSERT_FALSE(val4.IsEven());
  ASSERT_TRUE(val5.IsEven());
  ASSERT_TRUE(val6.IsEven());
}

TEST(LongNumbers, InvalidValueMinus) {
  try {
    LongNumber num("-");
    ASSERT_FALSE(true);
  }
  catch (const string& ex) {
    ASSERT_EQ(ex, "number must contain digits");
  }
}

TEST(LongNumbers, InvalidValueContainsLetters) {
  try {
    LongNumber num("13219fjl12");
    ASSERT_FALSE(true);
  }
  catch(const string & ex) {
    ASSERT_EQ(ex, "invalid value");
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}