#ifndef TWOQUBITPURESTATE_H
#define TWOQUBITPURESTATE_H

#include "MyVec4.h"
#include "TwoQubitSchDecom.h"

#define ZERO_ZERO_STATE MyVec4(1., 0., 0., 0.)
#define ZERO_ONE_STATE  MyVec4(0., 1., 0., 0.)
#define ONE_ONE_STATE   MyVec4(0., 0., 0., 1.)
#define ONE_ZERO_STATE  MyVec4(0., 0., 1., 0.)
#define PHI_PLUS  MyVec4(1. / sqrt(2.), 0., 0.,  1. / sqrt(2.));
#define PHI_MINUS MyVec4(1. / sqrt(2.), 0., 0., -1. / sqrt(2.));
#define PSI_PLUS  MyVec4(0., 1. / sqrt(2.),  1. / sqrt(2.), 0.);
#define PSI_MINUS MyVec4(0., 1. / sqrt(2.), -1. / sqrt(2.), 0.);

//===========================================================//
//  This class implements a SYSTEM OF TWO-QUBIT PURE STATES  //
//===========================================================//

class TwoQubitPureState {
public:

    MyVec4              vec4; // two-qubit pure state
    TwoQubitSchDecom schmidt; // its Schmidt decomposition
    MyRandom          random; // has color text functions

public:

    //--------------
    // constructors
    //--------------
    TwoQubitPureState();
    TwoQubitPureState(const TwoQubitPureState& other);

    //-----------------------------------------------------
    // Proposition 1(Schmidt Decomposition: Diagonal).
    // proposition 2(Schmidt Decomposition: Non-Diagonal).
    //-----------------------------------------------------
    void findSchDecom();

    //------------------------------------------
    // distance
    //------------------------------------------
    double dist(const TwoQubitPureState& other) const;

    //---------------------------------------------------------
    // functions that modify the member variables of an object
    //---------------------------------------------------------
    void becomeZero      ();
    void becomeUnit      ();
    void becomeRandom    ();
    void becomeRandomUnit();
    void becomeRandomProduct        ();
    void becomeRandomDiagonal       ();
    void becomeRandomProductDiagonal();

    //----------------
    // bool functions
    //----------------
    bool isUnit        (                              ) const;
    bool isDiagonal    (                              ) const;
    bool isNonDiagonal (                              ) const;
    bool isProduct     (                              ) const;
    bool isEntangled   (                              ) const;
    bool isMaximally   (                              ) const;
    bool isOrthogonalTo(const TwoQubitPureState& other) const;
    bool isEqualTo     (const TwoQubitPureState& other) const;
    
    //-----------------
    // print functions
    //-----------------
    void printInColumn() const;
    void printInRow() const;
    void printSchDecom() const;
};

#endif // TWOQUBITPURESTATE_H
