
#include "gtest/gtest.h"

#include "../main.cpp"



TEST(ParserTest, StrToInt) {
   EXPECT_EQ(135, str_to_int("135", 0));
   EXPECT_EQ(1350, str_to_int("1350", 0));
   EXPECT_EQ(135, str_to_int("0135", 0));
 }
 
  TEST(ParserTest, CharToInt) {
   EXPECT_EQ(5, char_to_int('5'));
 }
 
 TEST(ParserTest, StrToDouble) {
   EXPECT_EQ(62.6, string_to_double("62.6", 0));
   EXPECT_EQ(62.6, string_to_double("62.60", 0));
   EXPECT_EQ(62.6, string_to_double("062.6", 0));
 }
 
 int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}