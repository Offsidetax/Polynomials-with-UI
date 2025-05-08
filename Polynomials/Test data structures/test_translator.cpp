//#pragma once
//#include "translator.h"
//#include <gtest.h>
//
//TEST(ArithmeticExpressionTest, ParsesCorrectExpression_Coefficients) {
//    Arithmetic_Expression expr("3.5*X^2*Y^1*Z^0+2*X^1*Y^3*Z^2");
//
//    std::vector<double> expected_coefs = { 3.5, 2 };
//    std::vector<int> expected_degs = { 210, 132 };  // X^2Y^1Z^0 ? 210, X^1Y^3Z^2 ? 132
//
//    EXPECT_EQ(expr.GetCoefficients(), expected_coefs);
//}
//
//TEST(ArithmeticExpressionTest, ParsesCorrectExpression_Degrees) {
//    Arithmetic_Expression expr("3.5*X^2*Y^1*Z^0+2*X^1*Y^3*Z^2");
//
//    std::vector<double> expected_coefs = { 3.5, 2 };
//    std::vector<int> expected_degs = { 210, 132 };  // X^2Y^1Z^0 ? 210, X^1Y^3Z^2 ? 132
//
//    EXPECT_EQ(expr.GetDegree(), expected_degs);
//}
//
//TEST(ArithmeticExpressionTest, ParsesNegativeCoefficients) {
//    Arithmetic_Expression expr("-4*X^3*Y^2*Z^1+7.1*X^0*Y^1*Z^2");
//
//    std::vector<double> expected_coefs = { -4, 7.1 };
//    std::vector<int> expected_degs = { 321, 12 };  // X^3Y^2Z^1 ? 321, X^0Y^1Z^2 ? 12
//
//    EXPECT_EQ(expr.GetCoefficients(), expected_coefs);
//    EXPECT_EQ(expr.GetDegree(), expected_degs);
//}
//
//TEST(ArithmeticExpressionTest, ThrowsOnMissingMultiplicationSign) {
//    EXPECT_ANY_THROW(Arithmetic_Expression expr("3X^2Y^1Z^0"));
//}
//
//TEST(ArithmeticExpressionTest, ThrowsOnInvalidCharacter) {
//    EXPECT_ANY_THROW(Arithmetic_Expression expr("5*X^2*Y^1*Z^0+A"));
//}
//
//TEST(ArithmeticExpressionTest, ThrowsOnMultipleDotsInNumber) {
//    EXPECT_ANY_THROW(Arithmetic_Expression expr("3..5*X^2*Y^1*Z^0"));
//}
//
//TEST(ArithmeticExpressionTest, ThrowsOnMissingExponent) {
//    EXPECT_ANY_THROW(Arithmetic_Expression expr("3*X*Y^1*Z^0"));
//}
//
//TEST(ArithmeticExpressionTest, ThrowsOnEmptyInput) {
//    EXPECT_ANY_THROW(Arithmetic_Expression expr(""));
//}
//
//TEST(ArithmeticExpressionTest, ParsesMinimalExpression) {
//    Arithmetic_Expression expr("1*X^0*Y^0*Z^0");
//
//    std::vector<double> expected_coefs = { 1 };
//    std::vector<int> expected_degs = { 0 };
//
//    EXPECT_EQ(expr.GetCoefficients(), expected_coefs);
//    EXPECT_EQ(expr.GetDegree(), expected_degs);
//}
//
