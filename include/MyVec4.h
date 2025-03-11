#ifndef COLUMNVECTOR4_H
#define COLUMNVECTOR4_H

#include <complex>
#include "MyRandom.h"
#include "MyPrint.h"

#define THRESHOLD 1e-10
#define ZERO_VEC4 MyVec4(0., 0., 0., 0.)

//================================================================//
//  This class implements a SYSTEM OF COMPLEX VECTORS OF SIZE 4.  //
//================================================================//

class MyVec4 {
public:

    std::complex<double> element[4]; // complex vecor of size 4
    MyRandom                 random; // has random number functions
    MyPrint                   color; // has color text functions

public:
    
    //--------------
    // constructors
    //--------------
    MyVec4();
    MyVec4(const std::complex<double>& element1,
           const std::complex<double>& element2,
           const std::complex<double>& element3,
           const std::complex<double>& element4);
    MyVec4(double element1,
           double element2,
           double element3,
           double element4);

    //-----------------------
    // set and get functions
    //-----------------------
    void setValues(const std::complex<double>& element1,
                   const std::complex<double>& element2,
                   const std::complex<double>& element3,
                   const std::complex<double>& element4);
    std::complex<double> getValue(int index) const;

    //-----------------------
    // +, -, *, / operations
    //-----------------------
    MyVec4 operator+(const MyVec4& other) const;
    MyVec4 operator-(const MyVec4& other) const;
    MyVec4 operator*(const std::complex<double>& scalar) const;
    MyVec4 operator*(double                      scalar) const;
    MyVec4 operator/(const std::complex<double>& scalar) const;
    MyVec4 operator/(double                      scalar) const;

    //------------------------------------------
    // conjugate, inner product, norm, distance
    //------------------------------------------
    MyVec4 getConjugateVector() const;
    std::complex<double> innerProduct(const MyVec4& other) const;
    std::complex<double> diagonalCondition() const;
    double norm() const;
    double dist(const MyVec4& other) const;
    double concurrence() const;

    //---------------------------------------------------------
    // functions that modify the member variables of an object
    //---------------------------------------------------------
    void becomeConjugate (         );
    void becomeZero      (         );
    void becomeZero      (int index);
    void becomeUnit      (         );
    void becomeRandom    (         );
    void becomeRandom    (int index);
    void becomeRandomUnit(         );

    //----------------
    // bool functions
    //----------------
    bool isUnit        (                   ) const;
    bool isDiagonal    (                   ) const;
    bool isNonDiagonal (                   ) const;
    bool isProduct     (                   ) const;
    bool isEntangled   (                   ) const;
    bool isMaximally   (                   ) const;
    bool isOrthogonalTo(const MyVec4& other) const;
    bool isEqualTo     (const MyVec4& other) const;

    //-----------------
    // print functions
    //-----------------
    void printInRow() const;
    void printInColumn() const;
    void printComponent(int index) const;
};

#endif // COLUMNVECTOR4_H
