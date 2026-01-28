#include <gtest/gtest.h>

#include <cstdint>

#include "data_lab.hpp"

// Add function tests (12 tests)
TEST(AddTest, PositiveNumbers) { EXPECT_EQ(data_lab::add(5, 3), 8); }

TEST(AddTest, NegativeNumbers) { EXPECT_EQ(data_lab::add(-5, -3), -8); }

TEST(AddTest, MixedSigns) { EXPECT_EQ(data_lab::add(10, -3), 7); }

TEST(AddTest, WithZero) { EXPECT_EQ(data_lab::add(0, 5), 5); }

TEST(AddTest, BothZero) { EXPECT_EQ(data_lab::add(0, 0), 0); }

TEST(AddTest, LargePositive) {
  EXPECT_EQ(data_lab::add(1000000, 2000000), 3000000);
}

TEST(AddTest, PowersOfTwo) {
  EXPECT_EQ(data_lab::add(1 << 20, 1 << 20), 1 << 21);
}

TEST(AddTest, NearIntMax) {
  EXPECT_EQ(data_lab::add(INT32_MAX - 1, 1), INT32_MAX);
}

TEST(AddTest, NearIntMin) {
  EXPECT_EQ(data_lab::add(INT32_MIN + 1, -1), INT32_MIN);
}

TEST(AddTest, OverflowWrap) {
  EXPECT_EQ(data_lab::add(INT32_MAX, 1), INT32_MIN);
}

TEST(AddTest, RandomNumber1) {
  EXPECT_EQ(data_lab::add(-894229282, -1769294128), 1631443886);
}

TEST(AddTest, RandomNumber2) {
  EXPECT_EQ(data_lab::add(438424601, 513276783), 951701384);
}

// Subtract function tests (12 tests)
TEST(SubtractTest, PositiveNumbers) { EXPECT_EQ(data_lab::subtract(10, 3), 7); }

TEST(SubtractTest, NegativeNumbers) {
  EXPECT_EQ(data_lab::subtract(-10, -3), -7);
}

TEST(SubtractTest, MixedSigns) { EXPECT_EQ(data_lab::subtract(10, -3), 13); }

TEST(SubtractTest, WithZero) { EXPECT_EQ(data_lab::subtract(5, 0), 5); }

TEST(SubtractTest, FromZero) { EXPECT_EQ(data_lab::subtract(0, 5), -5); }

TEST(SubtractTest, BothZero) { EXPECT_EQ(data_lab::subtract(0, 0), 0); }

TEST(SubtractTest, PowersOfTwo) {
  EXPECT_EQ(data_lab::subtract(1 << 22, 1 << 21), 1 << 21);
}

TEST(SubtractTest, NearIntMax) {
  EXPECT_EQ(data_lab::subtract(INT32_MAX, 1), INT32_MAX - 1);
}

TEST(SubtractTest, NearIntMin) {
  EXPECT_EQ(data_lab::subtract(INT32_MIN, -1), INT32_MIN + 1);
}

TEST(SubtractTest, UnderflowWrap) {
  EXPECT_EQ(data_lab::subtract(INT32_MIN, 1), INT32_MAX);
}

TEST(SubtractTest, SameNumbers) { EXPECT_EQ(data_lab::subtract(42, 42), 0); }

TEST(SubtractTest, RandomNumber) {
  EXPECT_EQ(data_lab::subtract(-31188285, -1132498087), 1101309802);
}

// Multiply function tests (12 tests)
TEST(MultiplyTest, PositiveNumbers) { EXPECT_EQ(data_lab::multiply(5, 3), 15); }

TEST(MultiplyTest, NegativeNumbers) {
  EXPECT_EQ(data_lab::multiply(-5, -3), 15);
}

TEST(MultiplyTest, MixedSigns) { EXPECT_EQ(data_lab::multiply(5, -3), -15); }

TEST(MultiplyTest, WithZero) { EXPECT_EQ(data_lab::multiply(5, 0), 0); }

TEST(MultiplyTest, ZeroWithNegative) {
  EXPECT_EQ(data_lab::multiply(0, -5), 0);
}

TEST(MultiplyTest, WithOne) { EXPECT_EQ(data_lab::multiply(7, 1), 7); }

TEST(MultiplyTest, WithNegativeOne) {
  EXPECT_EQ(data_lab::multiply(7, -1), -7);
}

TEST(MultiplyTest, PowersOfTwo) {
  EXPECT_EQ(data_lab::multiply(1 << 10, 1 << 5), 1 << 15);
}

TEST(MultiplyTest, LargeNumbers) {
  EXPECT_EQ(data_lab::multiply(1000, 1000), 1000000);
}

TEST(MultiplyTest, NearIntMax) {
  EXPECT_EQ(data_lab::multiply(INT32_MAX / 2, 2), INT32_MAX - 1);
}

TEST(MultiplyTest, RandomNumber1) {
  EXPECT_EQ(data_lab::multiply(-1351161440, -839349802), -1016206400);
}

TEST(MultiplyTest, RandomNumber2) {
  EXPECT_EQ(data_lab::multiply(1827679637, -1888372867), 1000391873);
}

// Divide function tests (12 tests)
TEST(DivideTest, PositiveNumbers) { EXPECT_EQ(data_lab::divide(15, 3), 5); }

TEST(DivideTest, NegativeNumbers) { EXPECT_EQ(data_lab::divide(-15, -3), 5); }

TEST(DivideTest, NegativeByPositive) {
  EXPECT_EQ(data_lab::divide(-15, 3), -5);
}

TEST(DivideTest, PositiveByNegative) {
  EXPECT_EQ(data_lab::divide(15, -3), -5);
}

TEST(DivideTest, ZeroDividend) { EXPECT_EQ(data_lab::divide(0, 5), 0); }

TEST(DivideTest, DivideByOne) { EXPECT_EQ(data_lab::divide(42, 1), 42); }

TEST(DivideTest, DivideByNegativeOne) {
  EXPECT_EQ(data_lab::divide(42, -1), -42);
}

TEST(DivideTest, SameNumbers) { EXPECT_EQ(data_lab::divide(42, 42), 1); }

TEST(DivideTest, LargeNumbers) {
  EXPECT_EQ(data_lab::divide(1000000, 1000), 1000);
}

TEST(DivideTest, PowersOfTwo) {
  EXPECT_EQ(data_lab::divide(1 << 20, 1 << 10), 1 << 10);
}

TEST(DivideTest, RandomNumber1) {
  EXPECT_EQ(data_lab::divide(-1223815843, -195563321), 6);
}

TEST(DivideTest, RandomNumber2) {
  EXPECT_EQ(data_lab::divide(1927263441, -754677301), -2);
}

// Modulo function tests (12 tests)
TEST(ModuloTest, PositiveNumbers) { EXPECT_EQ(data_lab::modulo(17, 5), 2); }

TEST(ModuloTest, NegativeByPositive) {
  EXPECT_EQ(data_lab::modulo(-17, 5), -2);
}

TEST(ModuloTest, PositiveByNegative) { EXPECT_EQ(data_lab::modulo(17, -5), 2); }

TEST(ModuloTest, NegativeNumbers) { EXPECT_EQ(data_lab::modulo(-17, -5), -2); }

TEST(ModuloTest, ZeroDividend) { EXPECT_EQ(data_lab::modulo(0, 5), 0); }

TEST(ModuloTest, NoRemainder) { EXPECT_EQ(data_lab::modulo(15, 5), 0); }

TEST(ModuloTest, DividendSmallerThanDivisor) {
  EXPECT_EQ(data_lab::modulo(3, 5), 3);
}

TEST(ModuloTest, SameNumbers) { EXPECT_EQ(data_lab::modulo(42, 42), 0); }

TEST(ModuloTest, ModuloByOne) { EXPECT_EQ(data_lab::modulo(42, 1), 0); }

TEST(ModuloTest, LargeNumbers) {
  EXPECT_EQ(data_lab::modulo(1000007, 1000), 7);
}

TEST(ModuloTest, RandomNumber1) {
  EXPECT_EQ(data_lab::modulo(1866041187, -1992637480), 1866041187);
}

TEST(ModuloTest, RandomNumber2) {
  EXPECT_EQ(data_lab::modulo(-1205291292, -644190970), -561100322);
}
