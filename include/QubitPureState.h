#ifndef QUBITPURESTATE_H
#define QUBITPURESTATE_H

#include "MyVec2.h"

#define ZERO_STATE MyVec2(1., 0.)
#define  ONE_STATE MyVec2(0., 1.)

//=======================================================//
//  This class implements a SYSTEM OF QUBIT PURE STATES  //
//=======================================================//

class QubitPureState {
public:

    MyVec2 vec2; // qubit pure state

public:

    //--------------
    // constructors
    //--------------
    QubitPureState(                           );
    QubitPureState(const QubitPureState& other);
    QubitPureState(const         MyVec2& other);
    QubitPureState(const std::complex<double>& element1,
                   const std::complex<double>& element2);

    //-----------
    // conjugate
    //-----------
    QubitPureState getOrthogonalState() const;

    //---------------------------------------------------------
    // functions that modify the member variables of an object
    //---------------------------------------------------------
    void becomeZero      ();
    void becomeUnit      ();
    void becomeRandom    ();
    void becomeRandomUnit();

    //----------------
    // bool functions
    //----------------
    bool isUnit        (                           ) const;
    bool isOrthogonalTo(const QubitPureState& other) const;
    bool isEqualTo     (const QubitPureState& other) const;

    //-----------------
    // print functions
    //-----------------
    void printInRow() const;
    void printInColumn() const;
};

#endif // QUBITPURESTATE_H
