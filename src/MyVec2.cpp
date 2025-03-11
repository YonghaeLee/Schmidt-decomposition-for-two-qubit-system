#include "MyVec2.h"

MyVec2::MyVec2() {
    //MyPrint::blue(">  zero vector2 is created.\n");
    becomeZero();
}
MyVec2::MyVec2(const std::complex<double>& a, const std::complex<double>& b) {
    //MyPrint::blue(">  vector2 is created.\n");
    element[0] = a; element[1] = b;
}
MyVec2::MyVec2(double a, double b) {
    //MyPrint::blue(">  vector2 is created.\n");
    element[0] = a; element[1] = b;
}





void MyVec2::setValues(const std::complex<double>& a, const std::complex<double>& b)
{
    element[0] = a; element[1] = b;
}
std::complex<double> MyVec2::getValue(int index) const {
    if (index < 0 || index >= 2) throw std::out_of_range("Index out of range");
    return element[index];
}





MyVec2 MyVec2::operator+(const MyVec2& other) const
{
    return MyVec2(element[0] + other.element[0], element[1] + other.element[1]);
}
MyVec2 MyVec2::operator-(const MyVec2& other) const
{
    return MyVec2(element[0] - other.element[0], element[1] - other.element[1]);
}
MyVec4 MyVec2::operator*(const MyVec2& other) const
{
    return MyVec4(element[0] * other.element[0], element[0] * other.element[1], element[1] * other.element[0], element[1] * other.element[1]);
}
MyVec2 MyVec2::operator*(const std::complex<double>& scalar) const
{
    return MyVec2(element[0] * scalar, element[1] * scalar);
}
MyVec2 MyVec2::operator*(double scalar) const
{
    return *this * std::complex<double>(scalar, 0);
}
MyVec2 MyVec2::operator/(const std::complex<double>& scalar) const {
    if (scalar == std::complex<double>(0, 0)) throw std::runtime_error("Division by zero");
    return MyVec2(element[0] / scalar, element[1] / scalar);
}
MyVec2 MyVec2::operator/(double scalar) const
{
    return *this / std::complex<double>(scalar, 0);
}





MyVec2 MyVec2::getConjugate() const { return MyVec2(std::conj(element[0]), std::conj(element[1])); }
std::complex<double> MyVec2::innerProduct(const MyVec2& other) const { return std::conj(element[0]) * other.element[0] + std::conj(element[1]) * other.element[1]; }
double MyVec2::norm() const { return std::sqrt(std::real(innerProduct(*this))); }
double MyVec2::dist(const MyVec2& other) const { return (*this - other).norm(); }





void MyVec2::becomeConjugate() {
    //printf(">  vector2 becomes its conjugate.\n");
    for (int i = 0; i < 2; ++i) element[i] = std::conj(element[i]);
}
void MyVec2::becomeZero() {
    //printf(">  vector2 becomes zero.\n");
    *this = ZERO_VECTOR2;
}
void MyVec2::becomeUnit() {
    double n = norm();
    if (std::abs(n) < THRESHOLD) {
        printf("Error: Cannot normalize zero vector.\n");
        std::exit(EXIT_FAILURE);
    }
    element[0] /= n;
    element[1] /= n;
    //printf(">  vector2 becomes unit.\n");
}
void MyVec2::becomeRandom() {
    //printf(">  vector2 becomes random.\n");
    element[0] = random.complexNumber(); element[1] = random.complexNumber();
}
void MyVec2::becomeRandomUnit() {
    //printf(">  vector2 becomes random and unit.\n");
    becomeRandom(); becomeUnit();
}





bool MyVec2::isUnit() const { return std::abs(norm() - 1.0) < THRESHOLD; }
bool MyVec2::isEqualTo(const MyVec2& other) const { return              dist(other) < THRESHOLD; }
bool MyVec2::isOrthogonalTo(const MyVec2& other) const { return std::abs(innerProduct(other)) < THRESHOLD; }





void MyVec2::printInRow() const {
    printf("  [  "); printf("%+6.4f %+6.4fi", element[0].real(), element[0].imag());
    printf("  ,  "); printf("%+6.4f %+6.4fi", element[1].real(), element[1].imag());
    printf("  ]"); }
void MyVec2::printInColumn() const {
    printf("  [  "); printf("%+6.4f %+6.4fi", element[0].real(), element[0].imag()); printf("  ]\n");
    printf("  [  "); printf("%+6.4f %+6.4fi", element[1].real(), element[1].imag()); printf("  ]"); }
void MyVec2::printComponent(int index) const { printf("%+6.4f %+6.4fi", element[index].real(), element[index].imag()); }