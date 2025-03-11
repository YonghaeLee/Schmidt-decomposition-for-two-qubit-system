#ifndef MYRANDOM_H
#define MYRANDOM_H

#include <complex>
#include <random>
#include <cmath>

//=======================================//
//  This class generates random numbers  //
//=======================================//

class MyRandom {
public:

    static std::mt19937 gen;
    static bool isSeedSet;

public:

    //-----------------
    // integers
    //-----------------
    int                  integer() const;
    int              Unitinteger() const;
    unsigned int Unsignedinteger() const;

    //---------------------
    // real numbers
    //---------------------
    double realNumber () const;
    double realNumber0To1() const; // between 0 and 1
    
    //-------------------------------------------------
    // unit real vector
    //-------------------------------------------------
    void unitRealVector(double& r0, double& r1) const;
    void unitRealVector(double& r0, double& r1, double& r2) const;
    void unitRealVector(double& r0, double& r1, double& r2, double& r3) const;

    //------------------------
    // complex number
    //------------------------
    std::complex<double> complexNumber() const;
    std::complex<double> unitComplexNumber() const;
    
    //-----------------------------
    // unit complex vector
    //-----------------------------
    void unitComplexVector(std::complex<double>& c0, std::complex<double>& c1) const;
    void unitComplexVector(std::complex<double>& c0, std::complex<double>& c1, std::complex<double>& c2) const;
    void unitComplexVector(std::complex<double>& c0, std::complex<double>& c1, std::complex<double>& c2, std::complex<double>& c3) const;

private:
    void initializeSeed() const;
};

#endif // MYRANDOM_H
