#ifndef COLUMNVECTOR2_H
#define COLUMNVECTOR2_H

#include "MyRandom.h"
#include "MyPrint.h"
#include "MyVec4.h"

#define ZERO_VECTOR2 MyVec2(0., 0.)

//================================================================//
//  This class implements a SYSTEM OF COMPLEX VECTORS OF SIZE 2.  //
//================================================================//

class MyVec2 {
public:

    std::complex<double> element[2]; // complex vecor of size 2
    MyRandom                 random; // has random number functions
    MyPrint                   color; // has color text functions

public:

    //--------------
    // constructors
    //--------------
    MyVec2();
    MyVec2(const std::complex<double>& element1,
           const std::complex<double>& element2);
    MyVec2(double element1,
           double element2);

    //-----------------------
    // set and get functions
    //-----------------------
    void setValues(const std::complex<double>& element1,
                   const std::complex<double>& element2);
    std::complex<double> getValue(int index) const;
    
    //-----------------------
    // +, -, *, / operations
    //-----------------------
    MyVec2 operator+(const MyVec2& other) const;
    MyVec2 operator-(const MyVec2& other) const;
    MyVec4 operator*(const MyVec2& other) const;
    MyVec2 operator*(const std::complex<double>& scalar) const;
    MyVec2 operator*(double                      scalar) const;
    MyVec2 operator/(const std::complex<double>& scalar) const;
    MyVec2 operator/(double                      scalar) const;

    //------------------------------------------
    // conjugate, inner product, norm, distance
    //------------------------------------------
    MyVec2 getConjugate() const;
    std::complex<double> innerProduct(const MyVec2& other) const;
    double norm() const;
    double dist(const MyVec2& other) const;

    //---------------------------------------------------------
    // functions that modify the member variables of an object
    //---------------------------------------------------------
    void becomeConjugate ();
    void becomeZero      ();
    void becomeUnit      ();
    void becomeRandom    ();
    void becomeRandomUnit();

    //----------------
    // bool functions
    //----------------
    bool isUnit        (                   ) const;
    bool isOrthogonalTo(const MyVec2& other) const;
    bool isEqualTo     (const MyVec2& other) const;

    //-----------------
    // print functions
    //-----------------
    void printInRow() const;
    void printInColumn() const;
    void printComponent(int index) const;
};

#endif // COLUMNVECTOR2_H
