#include "MyVec4.h"
#include <cstdio>

MyVec4::MyVec4() {
    for (int i = 0; i < 4; ++i) element[i] = std::complex<double>(0, 0); }
MyVec4::MyVec4(const std::complex<double>& a, const std::complex<double>& b, const std::complex<double>& c, const std::complex<double>& d) {
    element[0] = a; element[1] = b; element[2] = c; element[3] = d; }
MyVec4::MyVec4(double a, double b, double c, double d) {
    element[0] = a; element[1] = b; element[2] = c; element[3] = d; }





void MyVec4::setValues(const std::complex<double>& a, const std::complex<double>& b, const std::complex<double>& c, const std::complex<double>& d) {
    element[0] = a; element[1] = b; element[2] = c; element[3] = d; }
std::complex<double> MyVec4::getValue(int index) const {
    if (index < 0 || index >= 4) throw std::out_of_range("Index out of range");
    return element[index];
}





MyVec4 MyVec4::operator+(const MyVec4& other) const {
    return MyVec4(element[0] + other.element[0], element[1] + other.element[1], element[2] + other.element[2], element[3] + other.element[3]); }
MyVec4 MyVec4::operator-(const MyVec4& other) const {
    return MyVec4(element[0] - other.element[0], element[1] - other.element[1], element[2] - other.element[2], element[3] - other.element[3]); }
MyVec4 MyVec4::operator*(const std::complex<double>& scalar) const {
    return MyVec4(element[0] * scalar, element[1] * scalar, element[2] * scalar, element[3] * scalar); }
MyVec4 MyVec4::operator*(double scalar) const {
    return *this * std::complex<double>(scalar, 0); }
MyVec4 MyVec4::operator/(const std::complex<double>& scalar) const {
    if (scalar == std::complex<double>(0, 0)) throw std::runtime_error("Division by zero");
    return MyVec4(element[0] / scalar, element[1] / scalar, element[2] / scalar, element[3] / scalar);
}
MyVec4 MyVec4::operator/(double scalar) const { return *this / std::complex<double>(scalar, 0); }





MyVec4 MyVec4::getConjugateVector() const { return MyVec4(std::conj(element[0]), std::conj(element[1]), std::conj(element[2]), std::conj(element[3])); }
std::complex<double> MyVec4::innerProduct(const MyVec4& other) const {
    std::complex<double> result = 0;
    for (int i = 0; i < 4; ++i)  result += std::conj(element[i]) * other.element[i];
    return result;
}
std::complex<double> MyVec4::diagonalCondition() const { return conj(element[0]) * element[1] + std::conj(element[2]) * element[3]; }
double MyVec4::norm() const { return std::sqrt(std::real(innerProduct(*this))); }
double MyVec4::dist(const MyVec4& other) const { return (*this - other).norm(); }
double MyVec4::concurrence() const { return 2. * std::abs(element[0] * element[3] - element[1] * element[2]); }





void MyVec4::becomeConjugate() { for (int i = 0; i < 4; ++i) element[i] = std::conj(element[i]); }
void MyVec4::becomeZero() { for (int i = 0; i < 4; ++i) element[i] = { 0.0, 0.0 }; }
void MyVec4::becomeZero(int index) { element[index] = { 0.0, 0.0 }; }
void MyVec4::becomeUnit() {
    double n = norm();
    if (std::abs(n) < THRESHOLD) {
        printf("Error: Cannot normalize zero vector.\n");
        std::exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 4; ++i)  element[i] /= n;
}
void MyVec4::becomeRandom() {
    for (int i = 0; i < 4; ++i) element[i] = random.complexNumber(); }
void MyVec4::becomeRandom(int index) { element[index] = random.complexNumber(); }
void MyVec4::becomeRandomUnit() { becomeRandom(); becomeUnit(); }





bool MyVec4::isEqualTo(const MyVec4& other) const { return dist(other) < THRESHOLD; }
bool MyVec4::isUnit() const { return std::abs(norm() - 1.0) < THRESHOLD; }
bool MyVec4::isDiagonal() const { return std::abs(diagonalCondition()) < THRESHOLD; }
bool MyVec4::isNonDiagonal() const { return std::abs(diagonalCondition()) > THRESHOLD; }
bool MyVec4::isProduct() const { return std::abs(concurrence()) < THRESHOLD; }
bool MyVec4::isEntangled() const { return std::abs(concurrence()) > THRESHOLD; }
bool MyVec4::isMaximally() const { return std::abs(std::abs(concurrence()) - 1.) < THRESHOLD; }
bool MyVec4::isOrthogonalTo(const MyVec4& other) const { return std::abs(innerProduct(other)) < THRESHOLD; }





void MyVec4::printInRow() const {
    printf("\033[0;33m"); 
    printf(" [ "); MyPrint::printComplex(element[0]); printf("\033[0;33m");
    printf(" , "); MyPrint::printComplex(element[1]); printf("\033[0;33m");
    printf(" , "); MyPrint::printComplex(element[2]); printf("\033[0;33m");
    printf(" , "); MyPrint::printComplex(element[3]); printf("\033[0;33m");
    printf(" ]");
    printf("\033[0m"); }
void MyVec4::printInColumn() const {
    printf("\033[0;33m"); 
    printf(" [ "); MyPrint::printComplex(element[0]); printf("\033[0;33m"); printf(" ]\n");
    printf(" [ "); MyPrint::printComplex(element[1]); printf("\033[0;33m"); printf(" ]\n");
    printf(" [ "); MyPrint::printComplex(element[2]); printf("\033[0;33m"); printf(" ]\n");
    printf(" [ "); MyPrint::printComplex(element[3]); printf("\033[0;33m"); printf(" ]");
    printf("\033[0m"); }
void MyVec4::printComponent(int index) const { printf("%+6.4f %+6.4fi", element[index].real(), element[index].imag()); }
