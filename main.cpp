#include "MyVec2.h"
#include "MyVec4.h"
#include "TwoQubitPureState.h"
#include "TwoQubitBasis.h"
#include "MyRandom.h"
#include "MyPrint.h"
#include "TestPaper.h"

//-------------------------------------------------------------------------------------
// Paper title:
//   Formulas for Mutually Orthogonal Quantum States in Two-Qubit Systems:
//   Orthogonal Schmidt Decompositions
//
// Explanation:
//   - The TestPaper.h file contains functions
//     for testing the propositions and theorems included in the above paper.
//   - Using find and replace, you can comment out only the functions you want to test.
//-------------------------------------------------------------------------------------

int main() {

    TestPaper test;
    MyPrint prnt;

    //-------------------------------------------------------------------------------------
    //  inputs: coefficients of the initial state
    // outputs: formulas for its Schmidt decomposition
    //-------------------------------------------------------------------------------------
    test.Proposition1 (); // diagonal two-qubit pure states
    prnt.pressEnter   (); 
    test.Proposition2 (); // non-diagonal two-qubit pure states
    prnt.pressEnter   ();
    
    //-------------------------------------------------------------------------------------
    //  inputs: variables characterizing orthogonal Schmidt decompositions
    // outputs: formulas for mutually orthogonal Schmidt decompositions
    //-------------------------------------------------------------------------------------
    
    // two states    
    
    test.Proposition3 (); // PP
    prnt.pressEnter   (); 
    test.Proposition4 (); // PE: Diagonal
    prnt.pressEnter   (); 
    test.Proposition5 (); // PE: Non-Diagonal
    prnt.pressEnter   (); 
    test.Proposition6 (); // EP
    prnt.pressEnter   (); 
    test.Proposition7 (); // EE: Diagonal
    prnt.pressEnter   (); 
    test.Proposition8 (); // EE: Non-Diagonal
    prnt.pressEnter   (); 
    //test.Proposition18(); // PM
    //prnt.pressEnter   ();

    // three states

    test.Proposition9 (); // PPP
    prnt.pressEnter   (); 
    test.Proposition10(); // PPE: Case 1
    prnt.pressEnter   (); 
    test.Proposition11(); // PPE: Case 2
    prnt.pressEnter   (); 
    test.Proposition12(); // PPE: Case 3
    prnt.pressEnter   ();

    // four states

    test.Theorem14 ();    // PPPP
    prnt.pressEnter();    
    test.Theorem15 ();    // PPEE: Case 1
    prnt.pressEnter();    
    test.Theorem16 ();    // PPEE: Case 2
    prnt.pressEnter();    
    test.Theorem17 ();    // PPEE: Case 3
    prnt.pressEnter();    
    test.Theorem19 ();    // PPMM
    prnt.pressEnter();    
    test.Theorem20 ();    // MMEE: Diagonal
    prnt.pressEnter();    
    test.Theorem21 ();    // MMEE: Non-Diagonal

    //test.test.state[0].testSchDecom();

    return 0;
}
