#ifndef TWOQUBITSCHDECOM_H
#define TWOQUBITSCHDECOM_H

#include "QubitPureState.h"
#include "MyVec4.h"
#include "MyRandom.h"

//=============================================//
//  This class is necessary                    //
//  for representing and manipulating          //
//  each element of the Schmidt decomposition  //
//=============================================//

class TwoQubitSchDecom {
public:

    char   rank;                      // Schmidt rank
    double lambda[2];                 // Schmidt coefficients
    QubitPureState alpha[2], beta[2]; // Schmidt basis
    MyRandom random;                  // has random number functions

public:

    //--------------
    // constructors
    //--------------
    TwoQubitSchDecom(                             );
    TwoQubitSchDecom(const TwoQubitSchDecom& other);

    //--------------
    // get function
    //--------------
    MyVec4 getVector4() const;

    //---------------------------------------------------------
    // functions that modify the member variables of an object
    //---------------------------------------------------------
    //--------------------------------
    // |0>|0>, |0>|1>, |1>|0>, |1>|1>
    //--------------------------------
    void becomeSchDecomOfProd_CompuCompu(unsigned char i, unsigned char j);
    //--------------------------------------------------------
    // |alpha>|0>, |alpha>|1>,  where |alpha> is random state 
    //--------------------------------------------------------
    void becomeSchDecomOfProd_StateCompu(unsigned char i);
    //----------------------------------------------------------------------------
    // |alpha>|0>, |alpha>|1>,  where |alpha> is given by complex numbers a and b
    //----------------------------------------------------------------------------
    void becomeSchDecomOfProd_StateCompu(const std::complex<double>& a,
                                         const std::complex<double>& b,
                                                       unsigned char i);
    //------------------------------------------------------
    // |0>|beta>,  |1>|beta>,  where |beta> is random state
    //------------------------------------------------------
    void becomeSchDecomOfProd_CompuState(unsigned char i);
    //--------------------------------------------------------------------------
    // |0>|beta>,  |1>|beta>,  where |beta> is given by complex numbers c and d
    //--------------------------------------------------------------------------
    void becomeSchDecomOfProd_CompuState(              unsigned char i,
                                         const std::complex<double>& c,
                                         const std::complex<double>& d);
    //--------------------------------------------------------------------
    // |alpha>|beta>,  where |alpha> is given by complex numbers a and b, 
    //                   and  |beta> is given by complex numbers c and d
    //--------------------------------------------------------------------
    void becomeSchDecomOfProd_SetupSetup(const std::complex<double>& a,
                                         const std::complex<double>& b,
                                         const std::complex<double>& c,
                                         const std::complex<double>& d);
    //-----------------------------------------------------------------------
    // sqrt(lambda)|0>|0> + sqrt(1-lambda)|1>|1>,  lambda is random in (0,1)
    //-----------------------------------------------------------------------
    void becomeSchDecomOfPhi_RealCoef();
    //------------------------------------------------------------------------
    // sqrt(lambda)|0>|0> + sqrt(1-lambda)|1>|1>,  lambda is given l in (0,1)
    //------------------------------------------------------------------------
    void becomeSchDecomOfPhi_RealCoef(double l);
    //------------------------------------------------
    // a|0>|0> + b|1>|1>,  a and b are random complex
    //------------------------------------------------
    void becomeSchDecomOfPhi_CompCoef();
    //---------------------------------------
    // a|0>|0> + b|1>|1>,  a and b are given
    //---------------------------------------
    void becomeSchDecomOfPhi_CompCoef(const std::complex<double>& a,
                                      const std::complex<double>& b);
    //-----------------------------------------------------------------------
    // sqrt(lambda)|0>|1> + sqrt(1-lambda)|1>|0>,  lambda is random in (0,1)
    //-----------------------------------------------------------------------
    void becomeSchDecomOfPsi_RealCoef();
    //------------------------------------------------------------------------
    // sqrt(lambda)|0>|1> + sqrt(1-lambda)|1>|0>,  lambda is given l in (0,1)
    //------------------------------------------------------------------------
    void becomeSchDecomOfPsi_RealCoef(double l);
    //------------------------------------------------
    // a|0>|1> + b|1>|0>,  a and b are random complex
    //------------------------------------------------
    void becomeSchDecomOfPsi_CompCoef();
    //---------------------------------------
    // a|0>|1> + b|1>|0>,  a and b are given
    //---------------------------------------
    void becomeSchDecomOfPsi_CompCoef(const std::complex<double>& a,
                                      const std::complex<double>& b);

    //----------------
    // bool functions
    //----------------
    bool isSchRank      () const;
    bool isSchDecom     () const;
    bool isSchCoef      () const;
    bool isSchBasisAlpha() const;
    bool isSchBasisBeta () const;
    bool isUnit         () const;

    //-----------------
    // print functions
    //-----------------
    void print() const;
};

#endif // TWOQUBITSCHDECOM_H
