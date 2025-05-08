//#include "polynomials.h"
//#include <gtest.h>
//
//TEST(PolinomXYZTest, ConstructsCorrectly) {
//    std::vector<double> coefs = { 3.5, -2, 1 };
//    std::vector<int> degrees = { 210, 132, 000 };
//
//    PolinomXYZ<9> poly(coefs, degrees);
//
//    EXPECT_NO_THROW(PolinomXYZ<9>(coefs, degrees));
//}
//
//TEST(PolinomXYZTest, ThrowsOnMismatchedInputSizes) {
//    std::vector<double> coefs = { 3.5, -2 };
//    std::vector<int> degrees = { 210 };
//
//    EXPECT_THROW(PolinomXYZ<9>(coefs, degrees), const char*);
//}
//
//TEST(PolinomXYZTest, AdditionWorks) {
//    PolinomXYZ<9> poly1({ 3, 4 }, { 210, 132 });
//    PolinomXYZ<9> poly2({ 2, -4 }, { 210, 132 });
//
//    PolinomXYZ<9> result = poly1 + poly2;
//
//    EXPECT_EQ(result.GetCoefficients(), std::vector<double>({ 5 }));
//    EXPECT_EQ(result.GetDegrees(), std::vector<int>({ 210 }));
//}
//
//TEST(PolinomXYZTest, SubtractionWorks) {
//    PolinomXYZ<9> poly1({ 3, 4 }, { 210, 132 });
//    PolinomXYZ<9> poly2({ 2, 1 }, { 210, 132 });
//
//    PolinomXYZ<9> result = poly1 - poly2;
//
//    EXPECT_EQ(result.GetCoefficients(), std::vector<double>({ 3, 1 }));
//    EXPECT_EQ(result.GetDegrees(), std::vector<int>({ 132, 210 }));
//}
//
//TEST(PolinomXYZTest, ScalarMultiplicationWorks) {
//    PolinomXYZ<9> poly({ 3, -4 }, { 210, 132 });
//    PolinomXYZ<9> result = poly * 2;
//
//    EXPECT_EQ(result.GetCoefficients(), std::vector<double>({ -8, 6 }));
//    EXPECT_EQ(result.GetDegrees(), std::vector<int>({ 132, 210 }));
//}
//
//TEST(PolinomXYZTest, ScalarDivisionWorks) {
//    PolinomXYZ<9> poly({ 6, -8 }, { 210, 132 });
//    PolinomXYZ<9> result = poly / 2;
//
//    EXPECT_EQ(result.GetCoefficients(), std::vector<double>({ -4, 3 }));
//    EXPECT_EQ(result.GetDegrees(), std::vector<int>({ 132, 210 }));
//}
//
//TEST(PolinomXYZTest, ThrowsOnDivisionByZero) {
//    PolinomXYZ<9> poly({ 6, -8 }, { 210, 132 });
//    EXPECT_ANY_THROW(poly / 0);
//}
//
//TEST(PolinomXYZTest, PolynomialMultiplicationWorks) {
//    PolinomXYZ<9> poly1({ 2 }, { 210 });
//    PolinomXYZ<9> poly2({ 3 }, { 132 });
//
//    PolinomXYZ<9> result = poly1 * poly2;
//
//    EXPECT_EQ(result.GetCoefficients(), std::vector<double>({ 6 }));
//    EXPECT_EQ(result.GetDegrees(), std::vector<int>({ 342 }));
//}
