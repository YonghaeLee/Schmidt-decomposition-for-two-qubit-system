#include "MyRandom.h"

std::mt19937 MyRandom::gen;
bool MyRandom::isSeedSet = false;





int MyRandom::integer() const {
    initializeSeed();
    std::uniform_int_distribution<int> dist(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
    return dist(gen);
}
int MyRandom::Unitinteger() const {
    initializeSeed();
    std::uniform_int_distribution<int> dist(0, 1);
    return dist(gen) == 0 ? -1 : 1;
}
unsigned int MyRandom::Unsignedinteger() const {
    initializeSeed();
    return static_cast<unsigned int>(gen());
}





double MyRandom::realNumber() const {
    initializeSeed();
    std::uniform_real_distribution<double> dist(-100.0, 100.0);
    return dist(gen);
}
double MyRandom::realNumber0To1() const {
    initializeSeed();
    std::uniform_real_distribution<double> dist(0.0, 1.0);  // [0, 1] 범위의 실수 생성
    return dist(gen);
}





void MyRandom::unitRealVector(double& r0, double& r1) const {
    r0 = realNumber(); r1 = realNumber();
    double denom = sqrt(r0 * r0 + r1 * r1);
    r0 = r0 / denom;
    r1 = r1 / denom;
}
void MyRandom::unitRealVector(double& r0, double& r1, double& r2) const {
    r0 = realNumber(); r1 = realNumber(); r2 = realNumber();
    double denom = sqrt(r0 * r0 + r1 * r1 + r2 * r2);
    r0 = r0 / denom;
    r1 = r1 / denom;
    r2 = r2 / denom;
}
void MyRandom::unitRealVector(double& r0, double& r1, double& r2, double& r3) const {
    r0 = realNumber(); r1 = realNumber(); r2 = realNumber(); r3 = realNumber();
    double denom = sqrt(r0 * r0 + r1 * r1 + r2 * r2 + r3 * r3);
    r0 = r0 / denom;
    r1 = r1 / denom;
    r2 = r2 / denom;
    r3 = r3 / denom;
}





std::complex<double> MyRandom::complexNumber() const {
    initializeSeed();
    std::uniform_real_distribution<double> dist(-100.0, 100.0);
    return std::complex<double>(dist(gen), dist(gen));
}
std::complex<double> MyRandom::unitComplexNumber() const {
    std::complex<double> c = complexNumber();
    return c / std::abs(c);
}





void MyRandom::unitComplexVector(std::complex<double>& c0, std::complex<double>& c1) const {
    c0 = complexNumber(); c1 = complexNumber();
    double denom = sqrt(std::abs(c0) * std::abs(c0) + std::abs(c1) * std::abs(c1));
    c0 = c0 / denom;
    c1 = c1 / denom;
}
void MyRandom::unitComplexVector(std::complex<double>& c0, std::complex<double>& c1, std::complex<double>& c2) const {
    c0 = unitComplexNumber(); c1 = unitComplexNumber(); c2 = unitComplexNumber();
    double denom = sqrt(std::abs(c0) * std::abs(c0) + std::abs(c1) * std::abs(c1) + std::abs(c2) * std::abs(c2));
    c0 = c0 / denom;
    c1 = c1 / denom;
    c2 = c2 / denom;
}
void MyRandom::unitComplexVector(std::complex<double>& c0, std::complex<double>& c1, std::complex<double>& c2, std::complex<double>& c3) const {
    c0 = unitComplexNumber(); c1 = unitComplexNumber(); c2 = unitComplexNumber(); c3 = unitComplexNumber();
    double denom = sqrt(std::abs(c0) * std::abs(c0) + std::abs(c1) * std::abs(c1) + std::abs(c2) * std::abs(c2) + std::abs(c3) * std::abs(c3));
    c0 = c0 / denom;
    c1 = c1 / denom;
    c2 = c2 / denom;
    c3 = c3 / denom;
}





void MyRandom::initializeSeed() const {
    if (!isSeedSet) {
        std::random_device rd;
        gen.seed(rd());
        isSeedSet = true;
    }
}