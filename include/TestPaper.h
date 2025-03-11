#ifndef TESTPAPER_H
#define TESTPAPER_H

#include "TwoQubitBasis.h"

//============================================================//
//  This class tests the paper                                //
//  "Formulas for mutaully orthogonal quantum state           //
//   in two-qubit systems: Orthogonal Schmidt decompositions" //
//============================================================//

class TestPaper {
public:

    TwoQubitBasis test;

public:

    //  inputs: coefficients of the initial state
    // outputs: formulas for its Schmidt decomposition
    void Proposition1(); // diagonal two-qubit pure states
    void Proposition2(); // non-diagonal two-qubit pure states

    //  inputs: variables characterizing orthogonal Schmidt decompositions
    // outputs: formulas for mutually orthogonal Schmidt decompositions
    void Proposition3 (); // PP
    void Proposition4 (); // PE: Diagonal
    void Proposition5 (); // PE: Non-Diagonal
    void Proposition6 (); // EP
    void Proposition7 (); // EE: Diagonal
    void Proposition8 (); // EE: Non-Diagonal
    void Proposition18(); // PM

    void Proposition9 (); // PPP
    void Proposition10(); // PPE: Case 1
    void Proposition11(); // PPE: Case 2
    void Proposition12(); // PPE: Case 3

    void Theorem14(); // PPPP
    void Theorem15(); // PPEE: Case 1
    void Theorem16(); // PPEE: Case 2
    void Theorem17(); // PPEE: Case 3
    void Theorem19(); // PPMM
    void Theorem20(); // MMEE: Diagonal
    void Theorem21(); // MMEE: Non-Diagonal

};

#endif // TESTPAPER_H

// diagonal two-qubit pure states

// non-diagonal two-qubit pure states

// PP

// PE: Diagonal

// PE: Non-Diagonal

// EP

// EE: Diagonal

// EE: Non-Diagonal

// PM

// PPP

// PPE: Case 1

// PPE: Case 2

// PPE: Case 3

// PPPP

// PPEE: Case 1

// PPEE: Case 2

// PPEE: Case 3

// PPMM

// MMEE: Diagonal

// MMEE: Non-Diagonal