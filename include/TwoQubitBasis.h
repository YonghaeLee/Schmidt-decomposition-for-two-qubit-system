#ifndef TWOQUBITBASIS_H
#define TWOQUBITBASIS_H

#include "TwoQubitPureState.h"
#include "MyRandom.h"

//===========================================//
//  Class for the bases of two-qubit system  //
//===========================================//

class TwoQubitBasis {
public:
    
    TwoQubitPureState state[4]; // a basis having four two-qubit pure states
    MyRandom            random; // has color text functions

public:

    //--------------
    // constructors
    //--------------
    TwoQubitBasis();
    TwoQubitBasis(const TwoQubitBasis& other);

    //---------------------------------------------
    // update functions for Schmidt decompositions
    //---------------------------------------------
    void updateStatesFromSchDecoms();
    
    //------------------------------------------------------------
    // become functions for two orthogonal Schmidt decompositions
    //------------------------------------------------------------
    void becomePP            (); // Proposition  3(PP).
    void becomePE_Diagonal   (); // Proposition  4(PE: Diagonal).
    void becomePE_NonDiagonal(); // Proposition  5(PE: Non-Diagonal).
    void becomeEP            (); // Proposition  6(EP).
    void becomeEE_Diagonal   (); // Proposition  7(EE: Diagonal).
    void becomeEE_NonDiagonal(); // Proposition  8(EE: Non-Diagonal).
    void becomePM            (); // Proposition 18(PM).
   
    //-----------------------------------------------------------------------
    // become functions for three mutually orthogonal Schmidt decompositions
    //-----------------------------------------------------------------------
    void becomePPP      (); // Proposition  9(PPP).
    void becomePPE_Case1(); // Proposition 10(PPE: Case 1).
    void becomePPE_Case2(); // Proposition 11(PPE: Case 2).
    void becomePPE_Case3(); // Proposition 12(PPE: Case 3).

    //----------------------------------------------------------------------
    // become functions for four mutually orthogonal Schmidt decompositions
    //----------------------------------------------------------------------
    void becomePPPP            (); // Theorem 14(PPPP).
    void becomePPEE_Case1      (); // Theorem 15(PPEE: Case 1).
    void becomePPEE_Case2      (); // Theorem 16(PPEE: Case 2).
    void becomePPEE_Case3      (); // Theorem 17(PPEE: Case 3).
    void becomePMEE            (); // Theorem 19(PMEE).
    void becomeMMEE_Diagonal   (); // Theorem 20(MMEE: Diagonal).
    void becomeMMEE_NonDiagonal(); // Theorem 21(MMEE: Non-Diagonal).

    //----------------
    // bool functions
    //----------------
    bool isFirstNStateUnit       (const int number) const;
    bool isFirstNStateOrthogonal (const int number) const;
    bool isFirstNStateOrthonormal(const int number) const;
    bool isPP              () const; // Proposition  3(PP).
    bool isPE_Diagonal     () const; // Proposition  4(PE: Diagonal).
    bool isPE_NonDiagonal  () const; // Proposition  5(PE: Non-Diagonal).
    bool isEP              () const; // Proposition  6(EP).
    bool isEE_Diagonal     () const; // Proposition  7(EE: Diagonal).
    bool isEE_NonDiagonal  () const; // Proposition  8(EE: Non-Diagonal).
    bool isPM              () const; // Proposition 18(PM).
    bool isPPP             () const; // Proposition  9(PPP).
    bool isPPE             () const; // Proposition 10, 11, 12 (PPE: Case 1, 2, 3).
    bool isPPPP            () const; // Theorem 14(PPPP).
    bool isPPEE            () const; // Theorem 15, 16, 17(PPEE: Case1).
    bool isPMEE            () const; // Theorem 19(PMEE).
    bool isMMEE_Diagonal   () const; // Theorem 20(MMEE: Diagonal).
    bool isMMEE_NonDiagonal() const; // Theorem 21(MMEE: Non-Diagonal).

    //-----------------
    // print functions
    //-----------------
    void printInRow() const;
    void printInColumn() const;
    void printFirstNStates(const int number) const;
    void printFirstNSchDecoms(const int number) const;
};

#endif // TWOQUBITBASIS_H
