#include "TwoQubitBasis.h"

TwoQubitBasis::TwoQubitBasis() {}
TwoQubitBasis::TwoQubitBasis(const TwoQubitBasis& other) { for (int i = 0; i < 4; ++i) state[i] = other.state[i]; }





void TwoQubitBasis::updateStatesFromSchDecoms() { for (int i = 0; i < 4; i++) state[i].vec4 = state[i].schmidt.getVector4(); }





// Proposition 3(PP).
void TwoQubitBasis::becomePP() {
    // |Pp> in Eq.(26)
    state[0].schmidt.becomeSchDecomOfProd_CompuCompu(0, 0);
    unsigned int branch = random.Unsignedinteger() % 2;
    if (branch == 0)
        // |pP> in Eq.(27)
        state[1].schmidt.becomeSchDecomOfProd_StateCompu(1);
    else if (branch == 1)
        // |pP> in Eq.(28)
        state[1].schmidt.becomeSchDecomOfProd_CompuState(1);
    updateStatesFromSchDecoms();
}

// Proposition 4(PE: Diagonal).
void TwoQubitBasis::becomePE_Diagonal() {
    // |Pe> in Eq.(29)
    state[0].schmidt.becomeSchDecomOfProd_CompuCompu(0, 0);
    // |pE> in Eq.(30)
    state[1].schmidt.becomeSchDecomOfPsi_CompCoef();
    updateStatesFromSchDecoms();
}

// Proposition 5(PE: Non-Diagonal).
void TwoQubitBasis::becomePE_NonDiagonal() {
    // variables
    std::complex<double> a, b, c;
    double eta[2] = { 0., 0. };
    MyVec2 x[2], y[2];

    // |Pe> in Eq.(29)
    state[0].schmidt.becomeSchDecomOfProd_CompuCompu(0, 0);

    // eta_j in Eq.(33)
    random.unitComplexVector(a, b, c);
    for (int i = 0; i < 2; i++)
        eta[i] = sqrt((1 + (1 - 2 * (i & 1)) * sqrt(1 - 4 * std::abs(a) * std::abs(a) * std::abs(b) * std::abs(b))) / 2.);

    // x_j in Eq.(34)
    for (int i = 0; i < 2; i++) {
        x[i].element[0] = a * ((eta[i] * eta[i]) - (std::abs(b) * std::abs(b)));
        x[i].element[1] = c * eta[i] * eta[i];
        x[i].becomeUnit();
    }

    // y_j in Eq.(34)
    for (int i = 0; i < 2; i++) {
        y[i].element[0] = conj(b) * c;
        y[i].element[1] = (eta[i] * eta[i]) - (std::abs(b) * std::abs(b));
        y[i].becomeUnit();
    }

    // |pE> in Eq.(32)
    for (int i = 0; i < 2; i++) {
        state[1].schmidt.lambda[i] = eta[i];
        state[1].schmidt.alpha[i] = x[i];
        state[1].schmidt.beta[i] = y[i].getConjugate();
    }
    updateStatesFromSchDecoms();
}

// Proposition 6(EP).
void TwoQubitBasis::becomeEP() {
    // variables
    double sqrtGamma, sqrt1mGamma;
    std::complex<double> temp;
    std::complex<double> a, b, i(0., 1.);
    double absA, frac, absB;
    unsigned int branch;

    // |Ep> in Eq.(35)
    state[0].schmidt.becomeSchDecomOfPhi_RealCoef();

    // two complex numbers a and b satisfying condition in Eq.(36)
    sqrtGamma = state[0].schmidt.lambda[0];
    sqrt1mGamma = state[0].schmidt.lambda[1];
    a = random.complexNumber();
    absA = std::abs(a);
    frac = (sqrtGamma / sqrt1mGamma + sqrt1mGamma / sqrtGamma);
    absB = (frac * absA + sqrt((frac * frac - 4.) * absA * absA + 4)) / 2.;
    temp = random.complexNumber();
    temp = temp / std::abs(temp);
    b = temp * absB;

    // |eP> in Eq.(37)
    state[1].schmidt.rank = 1;
    state[1].schmidt.lambda[0] = 1.;
    branch = random.Unsignedinteger() % 2;
    if (branch == 0) {
        state[1].schmidt.alpha[0].vec2 = ZERO_STATE * sqrt(a) - ONE_STATE * i * sqrt(sqrtGamma / sqrt1mGamma) * sqrt(b);
        state[1].schmidt.beta[0].vec2 = ZERO_STATE * i * sqrt(sqrt1mGamma / sqrtGamma) * sqrt(b) + ONE_STATE * sqrt(a);
    }
    else if (branch == 1) {
        state[1].schmidt.alpha[0].vec2 = ZERO_STATE * sqrt(a) + ONE_STATE * i * sqrt(sqrtGamma / sqrt1mGamma) * sqrt(b);
        state[1].schmidt.beta[0].vec2 = ZERO_STATE * -i * sqrt(sqrt1mGamma / sqrtGamma) * sqrt(b) + ONE_STATE * sqrt(a);
    }
    state[1].schmidt.alpha[0].vec2.becomeUnit();
    state[1].schmidt.beta[0].vec2.becomeUnit();
    state[1].schmidt.lambda[1] = 0.;
    state[1].schmidt.alpha[1] = state[1].schmidt.alpha[0].getOrthogonalState();
    state[1].schmidt.beta[1] = state[1].schmidt.beta[0].getOrthogonalState();
    updateStatesFromSchDecoms();
}

// Proposition 7(EE: Diagonal).
void TwoQubitBasis::becomeEE_Diagonal() {
    // |Ee> in Eq.(40)
    state[0].schmidt.becomeSchDecomOfPhi_RealCoef();

    double   sqrtGamma = state[0].schmidt.lambda[0];
    double sqrt1mGamma = state[0].schmidt.lambda[1];
    double zeta[2] = { 0., 0. };

    unsigned int branch = random.Unsignedinteger() % 2;
    if (branch == 0) { // case of a=0
        std::complex<double> b, c;
        // a=0, 
        // b, and c in Eq.(41)
        random.unitComplexVector(b, c);

        // zeta_j in Eq.(45)
        zeta[0] = std::abs(c);
        zeta[1] = std::abs(b);

        // |eE> in Eq.(44)
        state[1].schmidt.rank = 2;
        state[1].schmidt.lambda[0] = zeta[0]; state[1].schmidt.alpha[0] = ONE_STATE * c / zeta[0]; state[1].schmidt.beta[0] = ZERO_STATE;
        state[1].schmidt.lambda[1] = zeta[1]; state[1].schmidt.alpha[1] = ZERO_STATE * b / zeta[1]; state[1].schmidt.beta[1] = ONE_STATE;
    }
    else if (branch == 1) { // case of a!=0
        std::complex<double> A, B;
        std::complex<double> a = 0., b, c;

        while (std::abs(a) == 0. || a * a * sqrtGamma + b * c * sqrt1mGamma == 0.) {
            random.unitComplexVector(A, B);
            // a!=0, 
            // b, and c in Eq.(41)
            a = A * sqrt1mGamma;
            b = B * sqrtGamma;
            c = (sqrt1mGamma / sqrtGamma) * conj(b) * (A / std::abs(A)) * (A / std::abs(A));
        }

        // zeta_j in Eq.(45)
        zeta[0] = sqrt(std::abs(a) * std::abs(a) + std::abs(c) * std::abs(c));
        zeta[1] = sqrt(std::abs(b) * std::abs(b) + ((sqrtGamma * sqrtGamma) / (sqrt1mGamma * sqrt1mGamma)) * std::abs(a) * std::abs(a));

        // |eE> in Eq.(44)
        state[1].schmidt.rank = 2;
        state[1].schmidt.lambda[0] = zeta[0];
        state[1].schmidt.alpha[0] = (ZERO_STATE * a + ONE_STATE * c) / zeta[0];
        state[1].schmidt.beta[0] = ZERO_STATE;
        state[1].schmidt.lambda[1] = zeta[1];
        state[1].schmidt.alpha[1] = (ZERO_STATE * b + ONE_STATE * (-sqrtGamma / sqrt1mGamma) * a) / zeta[1];
        state[1].schmidt.beta[1] = ONE_STATE;
    }
    updateStatesFromSchDecoms();
}

// Proposition 8(EE: Non-Diagonal).
void TwoQubitBasis::becomeEE_NonDiagonal() {
    // variables
    std::complex<double> a, b, c, A, B, C;
    std::complex<double> temp;
    double sqrtGamma, sqrt1mGamma;
    double delta[2] = { 0., 0. };
    MyVec2 y[2];
    MyVec2 x[2];

    // |Ee> in Eq.(40)
    state[0].schmidt.becomeSchDecomOfPhi_RealCoef();

    // a, b, and c in Eq.(41)
    sqrtGamma = state[0].schmidt.lambda[0];
    sqrt1mGamma = state[0].schmidt.lambda[1];
    random.unitComplexVector(A, B, C);
    a = A * sqrt1mGamma;
    b = B;
    c = C;
    while (a * a * sqrtGamma + b * c * sqrtGamma == 0. || a * conj(c) * sqrtGamma - conj(a) * b * sqrt1mGamma == 0.) {
        random.unitComplexVector(A, B, C);
        a = A * sqrt1mGamma;
        b = B;
        c = C;
    }

    // delta_j in Eq.(47)
    temp = a * a * (sqrtGamma / sqrt1mGamma) + b * c;
    for (int i = 0; i < 2; i++)
        delta[i] = sqrt((1. + (1 - 2 * (i & 1)) * sqrt(1. - 4. * std::abs(temp) * std::abs(temp))) / 2.);

    // |y_j> in Eq.(48)
    for (int i = 0; i < 2; i++) {
        y[i] = ZERO_STATE * (conj(a) * b - a * conj(c) * (sqrtGamma / sqrt1mGamma))
            + ONE_STATE * (delta[i] * delta[i] - std::abs(a) * std::abs(a) - std::abs(c) * std::abs(c));
        y[i].becomeUnit();
    }

    // |x_j> in Eq.(49)
    for (int i = 0; i < 2; i++) {
        x[i] = ZERO_STATE * (a * y[i].element[0] + b * y[i].element[1])
            + ONE_STATE * (c * y[i].element[0] - (a * (sqrtGamma / sqrt1mGamma) * y[i].element[1]));
        x[i].becomeUnit();
        y[i].becomeConjugate();  // conjugate of y_i
    }

    // |eE> in Eq.(46)
    state[1].schmidt.rank = 2;
    for (int i = 0; i < 2; i++) {
        state[1].schmidt.lambda[i] = delta[i];
        state[1].schmidt.alpha[i] = x[i];
        state[1].schmidt.beta[i] = y[i];
    }
    updateStatesFromSchDecoms();
}

// Proposition 18(PM).
void TwoQubitBasis::becomePM() {
    // variables
    std::complex<double> eiTheta, eiThetaPrime;

    // |Pm> in Eq.(102)
    state[0].schmidt.becomeSchDecomOfProd_CompuCompu(0, 0);
    // |pM> in Eq.(103)
    eiTheta     =random.unitComplexNumber();
    eiThetaPrime=random.unitComplexNumber();
    state[1].schmidt.becomeSchDecomOfPsi_CompCoef((1. / sqrt(2.)) * eiTheta, (1. / sqrt(2.)) * eiThetaPrime);
    updateStatesFromSchDecoms();
}


// Proposition 9(PPP).
void TwoQubitBasis::becomePPP() {
    // variable
    unsigned int branch;

    // |Ppp> in Eq.(50)
    state[0].schmidt.becomeSchDecomOfProd_CompuCompu(0, 0);

    branch = random.Unsignedinteger() % 2;
    if (branch == 0) {
        // |pPp> in Eq.(51)
        state[1].schmidt.becomeSchDecomOfProd_StateCompu(1);
        // |ppP> in Eq.(52)
        state[2].schmidt.becomeSchDecomOfProd_StateCompu(1);
        state[2].schmidt.alpha[0] = state[1].schmidt.alpha[0].getOrthogonalState();
        state[2].schmidt.alpha[1] = state[1].schmidt.alpha[0];
    }
    else if (branch == 1) {
        // |pPp> in Eq.(53)
        state[1].schmidt.becomeSchDecomOfProd_CompuState(1);
        // |ppP> in Eq.(54)
        state[2].schmidt.becomeSchDecomOfProd_CompuState(1);
        state[2].schmidt.beta[0] = state[1].schmidt.beta[0].getOrthogonalState();
        state[2].schmidt.beta[1] = state[1].schmidt.beta[0];
    }
    updateStatesFromSchDecoms();
}

// Proposition 10(PPE: Case 1).
void TwoQubitBasis::becomePPE_Case1() {
    // |Ppe> in Eq.(59)
    state[0].schmidt.becomeSchDecomOfProd_CompuCompu(0, 0);
    // |pPe> in Eq.(60)
    state[1].schmidt.becomeSchDecomOfProd_CompuCompu(1, 1);
    // |ppE> in Eq.(63)
    state[2].schmidt.becomeSchDecomOfPsi_CompCoef();
    updateStatesFromSchDecoms();
}

// Proposition 11(PPE: Case 2).
// In fact, Proposition 11 is a special case of Theorem 16. Thus, it can be more simplified.
void TwoQubitBasis::becomePPE_Case2() {
    // variables
    double kappa[2] = { 0., 0. };
    MyVec2 x[2], y[2];
    std::complex<double> a, b, c, d;

    // |Ppe> in Eq.(59)
    state[0].schmidt.becomeSchDecomOfProd_CompuCompu(0, 0);
    // |pPe> in Eq.(61)
    state[1].schmidt.becomeSchDecomOfProd_StateCompu(1);

    // kappa_j in Eq.(65)
    a = state[1].schmidt.alpha[0].vec2.element[0];
    b = state[1].schmidt.alpha[0].vec2.element[1];
    random.unitComplexVector(c, d);
    for (int i = 0; i < 2; i++)
        kappa[i] = sqrt((1. + (1 - 2 * (i & 1)) * sqrt(1. - 4. * std::abs(b * c * d) * std::abs(b * c * d))) / 2.);

    // |y_j> in Eq.(66)
    for (int i = 0; i < 2; i++) {
        y[i] = ZERO_STATE * -(conj(a) * c * conj(d))
            + ONE_STATE * (kappa[i] * kappa[i] - std::abs(d) * std::abs(d));
        y[i].becomeUnit();
    }

    // |x_j> in Eq.(66)
    for (int i = 0; i < 2; i++) {
        x[i] = ZERO_STATE * (conj(b) * c * (kappa[i] * kappa[i] - std::abs(d) * std::abs(d)))
            + ONE_STATE * -(conj(a) * c * kappa[i] * kappa[i]);
        x[i].becomeUnit();
        y[i].becomeConjugate();  // conjugate of y_i
    }

    // |ppE> in Eq.(64)
    state[2].schmidt.rank = 2;
    for (int i = 0; i < 2; i++) {
        state[2].schmidt.lambda[i] = kappa[i];
        state[2].schmidt.alpha[i] = x[i];
        state[2].schmidt.beta[i] = y[i];
    }
    updateStatesFromSchDecoms();
}

// Proposition 12(PPE: Case 3).
void TwoQubitBasis::becomePPE_Case3() {
    // variables
    double nu[2] = { 0., 0. };
    MyVec2 x[2], y[2];
    std::complex<double> a, b, c, d;

    // |Ppe> in Eq.(59)
    state[0].schmidt.becomeSchDecomOfProd_CompuCompu(0, 0);
    // |pPe> in Eq.(62)
    state[1].schmidt.becomeSchDecomOfProd_CompuState(1);

    // nu_j in Eq.(69)
    a = state[1].schmidt.beta[0].vec2.element[0];
    b = state[1].schmidt.beta[0].vec2.element[1];
    random.unitComplexVector(c, d);
    for (int i = 0; i < 2; i++)
        nu[i] = sqrt((1. + (1 - 2 * (i & 1)) * sqrt(1. - 4. * std::abs(b * c * d) * std::abs(b * c * d))) / 2.);

    // |y_j> in Eq.(70)
    for (int i = 0; i < 2; i++) {
        y[i] = ZERO_STATE * -(conj(a) * b * std::abs(d) * std::abs(d))
            + ONE_STATE * (nu[i] * nu[i] - std::abs(b * d) * std::abs(b * d));
        y[i].becomeUnit();
    }

    // |x_j> in Eq.(70)
    for (int i = 0; i < 2; i++) {
        x[i] = ZERO_STATE * (c * (nu[i] * nu[i] - std::abs(b * d) * std::abs(b * d)))
            + ONE_STATE * -(conj(a) * d * nu[i] * nu[i]);
        x[i].becomeUnit();
        y[i].becomeConjugate();  // conjugate of y_i
    }

    // |ppE> in Eq.(68)
    state[2].schmidt.rank = 2;
    for (int i = 0; i < 2; i++) {
        state[2].schmidt.lambda[i] = nu[i];
        state[2].schmidt.alpha[i] = x[i];
        state[2].schmidt.beta[i] = y[i];
    }
    updateStatesFromSchDecoms();
}

// Theorem 14(PPPP).
void TwoQubitBasis::becomePPPP() {
    // |Pppp> in Eq.(80)
    state[0].schmidt.becomeSchDecomOfProd_CompuCompu(0, 0);

    unsigned int branch = random.Unsignedinteger() % 2;
    if (branch == 0) {
        // |pPpp> in Eq.(81)
        state[1].schmidt.becomeSchDecomOfProd_StateCompu(1);
        // |ppPp> in Eq.(82)
        state[2].schmidt.becomeSchDecomOfProd_StateCompu(1);
        state[2].schmidt.alpha[0] = state[1].schmidt.alpha[0].getOrthogonalState();
        state[2].schmidt.alpha[1] = state[1].schmidt.alpha[0];
        // |pppP> in Eq.(83)
        state[3].schmidt.becomeSchDecomOfProd_CompuCompu(1, 0);
    }
    else if (branch == 1)
    {
        // |pPpp> in Eq.(84)
        state[1].schmidt.becomeSchDecomOfProd_CompuState(1);
        // |ppPp> in Eq.(85)
        state[2].schmidt.becomeSchDecomOfProd_CompuState(1);
        state[2].schmidt.beta[0] = state[1].schmidt.beta[0].getOrthogonalState();
        state[2].schmidt.beta[1] = state[1].schmidt.beta[0];
        // |pppP> in Eq.(86)
        state[3].schmidt.becomeSchDecomOfProd_CompuCompu(0, 1);
    }
    updateStatesFromSchDecoms();
}

// Theorem 15(PPEE: Case 1).
void TwoQubitBasis::becomePPEE_Case1() {
    // variables
    std::complex<double> a, b;

    // |Ppee> in Eq.(88)
    state[0].schmidt.becomeSchDecomOfProd_CompuCompu(0, 0);
    // |pPee> in Eq.(89)
    state[1].schmidt.becomeSchDecomOfProd_CompuCompu(1, 1);
    // |ppEe> in Eq.(90)
    random.unitComplexVector(a, b);
    state[2].schmidt.becomeSchDecomOfPsi_CompCoef(a, b);
    // |ppeE> in Eq.(91)
    state[3].schmidt.becomeSchDecomOfPsi_CompCoef(conj(b), -conj(a));
    updateStatesFromSchDecoms();
}

// Theorem 16(PPEE: Case 2).
void TwoQubitBasis::becomePPEE_Case2() {
    // variables
    double kappa[2] = { 0., 0. };
    MyVec2 x[2], y[2], z[2];
    std::complex<double> a, b, c, d;

    // |Ppee> in Eq.(88)
    state[0].schmidt.becomeSchDecomOfProd_CompuCompu(0, 0);
    // |pPee> in Eq.(93)
    state[1].schmidt.becomeSchDecomOfProd_StateCompu(1);

    // kappa_j in Eq.(65)
    a = state[1].schmidt.alpha[0].vec2.element[0];
    b = state[1].schmidt.alpha[0].vec2.element[1];
    random.unitComplexVector(c, d);
    for (int i = 0; i < 2; i++)
        kappa[i] = sqrt((1. + (1 - 2 * (i & 1)) * sqrt(1. - 4. * std::abs(b * c * d) * std::abs(b * c * d))) / 2.);

    // |x_j> in Eq.(66)
    for (int i = 0; i < 2; i++) {
        x[i] = ZERO_STATE * (conj(b) * c * (kappa[i] * kappa[i] - std::abs(d) * std::abs(d)))
            + ONE_STATE * -(conj(a) * c * kappa[i] * kappa[i]);
        x[i].becomeUnit();
    }

    // |y_j> in Eq.(66)
    for (int i = 0; i < 2; i++) {
        y[i] = ZERO_STATE * -(conj(a) * c * conj(d))
            + ONE_STATE * (kappa[i] * kappa[i] - std::abs(d) * std::abs(d));
        y[i].becomeUnit();
        y[i].becomeConjugate();  // conjugate of y_i
    }

    // |z_j> in Eq.(96)
    for (int i = 0; i < 2; i++) {
        z[i] = ZERO_STATE * conj(b) * (kappa[i] * kappa[i] - std::abs(c) * std::abs(c))
            + ONE_STATE * -conj(a) * kappa[i] * kappa[i];
        z[i].becomeUnit();
    }

    // |ppEe> in Eq.(94)
    state[2].schmidt.rank = 2;
    for (int i = 0; i < 2; i++) {
        state[2].schmidt.lambda[i] = kappa[i]; state[2].schmidt.alpha[i] = x[i]; state[2].schmidt.beta[i] = y[i];
    }
    // |ppeE> in Eq.(95)
    state[3].schmidt.rank = 2;
    for (int i = 0; i < 2; i++) {
        state[3].schmidt.lambda[i] = kappa[i]; state[3].schmidt.alpha[i] = z[i]; state[3].schmidt.beta[i] = y[(i + 1) % 2];
    }
    updateStatesFromSchDecoms();
}

// Theorem 17(PPEE: Case 3).
void TwoQubitBasis::becomePPEE_Case3() {
    // variables
    double nu[2] = { 0., 0. };
    MyVec2 x[2], y[2], wStar[2];
    std::complex<double> a, b, c, d;

    // |Ppee> in Eq.(88) 
    state[0].schmidt.becomeSchDecomOfProd_CompuCompu(0, 0);
    // |pPee> in Eq.(98)
    state[1].schmidt.becomeSchDecomOfProd_CompuState(1);

    // nu_j in Eq.(69)
    a = state[1].schmidt.beta[0].vec2.element[0];
    b = state[1].schmidt.beta[0].vec2.element[1];
    random.unitComplexVector(c, d);
    for (int i = 0; i < 2; i++)
        nu[i] = sqrt((1. + (1 - 2 * (i & 1)) * sqrt(1. - 4. * std::abs(b * c * d) * std::abs(b * c * d))) / 2.);

    // |x_j> in Eq.(70)
    for (int i = 0; i < 2; i++) {
        x[i] = ZERO_STATE * (c * (nu[i] * nu[i] - std::abs(b * d) * std::abs(b * d)))
            + ONE_STATE * -(conj(a) * d * nu[i] * nu[i]);
        x[i].becomeUnit();
    }

    // |y_j> in Eq.(70)
    for (int i = 0; i < 2; i++) {
        y[i] = ZERO_STATE * -(conj(a) * b * std::abs(d) * std::abs(d))
            + ONE_STATE * (nu[i] * nu[i] - std::abs(b * d) * std::abs(b * d));
        y[i].becomeUnit();
        y[i].becomeConjugate();  // conjugate of y_i
    }

    // |w^*_j> in Eq.(101)
    for (int i = 0; i < 2; i++) {
        wStar[i] = ZERO_STATE * -(a * conj(b) * std::abs(c) * std::abs(c))
            + ONE_STATE * (nu[i] * nu[i] - std::abs(b * c) * std::abs(b * c));
        wStar[i].becomeUnit();
    }

    // |ppEe> in Eq.(99)
    state[2].schmidt.rank = 2;
    for (int i = 0; i < 2; i++) {
        state[2].schmidt.lambda[i] = nu[i]; state[2].schmidt.alpha[i] = x[i]; state[2].schmidt.beta[i] = y[i];
    }

    // |ppeE> in Eq.(100)
    state[3].schmidt.rank = 2;
    for (int i = 0; i < 2; i++) {
        state[3].schmidt.lambda[i] = nu[i]; state[3].schmidt.alpha[i] = x[(i + 1) % 2]; state[3].schmidt.beta[i] = wStar[i];
    }
    updateStatesFromSchDecoms();
}

// Theorem 19(PMEE).
void TwoQubitBasis::becomePMEE() {
    // variables
    std::complex<double> eiTheta, eiThetaPrime, eiThetaPrimePrime;
    eiThetaPrimePrime = random.unitComplexNumber();
    std::complex<double> c;
    double zeta[2] = { 0., 0. }, upsilon[2] = { 0., 0. };
    MyVec2 x[2], yStar[2], z[2], wStar[2];

    // |Pmee> in Eq.(105)
    state[0].schmidt.becomeSchDecomOfProd_CompuCompu(0, 0);
    // |pMee> in Eq.(106)
    eiTheta      = random.unitComplexNumber();
    eiThetaPrime = random.unitComplexNumber();
    state[1].schmidt.becomeSchDecomOfPsi_CompCoef((1. / sqrt(2.)) * eiTheta, (1. / sqrt(2.)) * eiThetaPrime);

    // zeta_j in Eq.(109)
    c = random.complexNumber();
    while (std::abs(c) > (1. / sqrt(2.))) { c = c / 2.; } // 0 < |c| < 1/sqrt(2.)
    for (int i = 0; i < 2; i++)
        zeta[i] = sqrt((1. + (1 - 2 * (i & 1)) * sqrt(1. - 4 * std::abs(c) * std::abs(c) * std::abs(c) * std::abs(c))) / 2.);

    // upsilon_j in Eq.(110)
    for (int i = 0; i < 2; i++)
        upsilon[i] = sqrt((1. + (1 - 2 * (i & 1)) * 2 * std::abs(c) * sqrt(1. - std::abs(c) * std::abs(c))) / 2.);

    // |x_j> in Eq.(111)
    eiThetaPrimePrime = random.unitComplexNumber();
    for (int i = 0; i < 2; i++) {
        x[i] = ZERO_STATE * (1 - 2 * (i & 1)) * c
            + ONE_STATE * eiThetaPrimePrime * zeta[i];
        x[i].becomeUnit();
    }

    // |y^*_j> in Eq.(112)
    for (int i = 0; i < 2; i++) {
        yStar[i] = ZERO_STATE * -conj(eiTheta) * eiThetaPrime * conj(eiThetaPrimePrime) * c
            + ONE_STATE * (1 - 2 * (i & 1)) * zeta[i];
        yStar[i].becomeUnit();
    }

    // |z_j> in Eq.(113)
    for (int i = 0; i < 2; i++) {
        z[i] = ZERO_STATE * (1 - 2 * (i & 1)) * conj(eiThetaPrimePrime) * sqrt(upsilon[0] * upsilon[1]) * std::abs(c)
            + ONE_STATE * -conj(c) * upsilon[i];
        z[i].becomeUnit();
    }

    // |w^*_j> in Eq.(114)
    for (int i = 0; i < 2; i++) {
        wStar[i] = ZERO_STATE * conj(eiTheta) * eiThetaPrime * conj(eiThetaPrimePrime) * sqrt(upsilon[0] * upsilon[1]) * c
            + ONE_STATE * (1 - 2 * (i & 1)) * std::abs(c) * upsilon[i];
        wStar[i].becomeUnit();
    }

    // |pmEe> in Eq.(107)
    state[2].schmidt.rank = 2;
    for (int i = 0; i < 2; i++) {
        state[2].schmidt.lambda[i] = zeta[i]; state[2].schmidt.alpha[i] = x[i]; state[2].schmidt.beta[i] = yStar[i];
    }
    // |pmeE> in Eq.(108)
    state[3].schmidt.rank = 2;
    for (int i = 0; i < 2; i++) {
        state[3].schmidt.lambda[i] = upsilon[i]; state[3].schmidt.alpha[i] = z[i]; state[3].schmidt.beta[i] = wStar[i];
    }
    updateStatesFromSchDecoms();
}

// Theorem 20(MMEE: Diagonal).
void TwoQubitBasis::becomeMMEE_Diagonal() {
    // variables
    unsigned int branch;
    std::complex<double> eiTheta, eiThetaPrime;
    std::complex<double> a, b;

    // |Mmee> in Eq.(115)
    state[0].schmidt.becomeSchDecomOfPhi_RealCoef(1. / 2.);
    // |mMee> in Eq.(116)
    eiTheta      = random.unitComplexNumber();
    eiThetaPrime = random.unitComplexNumber();
    state[1].schmidt.becomeSchDecomOfPsi_CompCoef((1. / sqrt(2.)) * eiTheta, (1. / sqrt(2.)) * eiThetaPrime);

    // a and b satisfying Eq.(117)
    random.unitComplexVector(a, b); // |a|^2 + |b|^2 = 1
    a = a / sqrt(2.);
    b = b / sqrt(2.);

    // a and b satisfying Eq.(117) and Eq.(119)
    b = std::abs(b) * (a / std::abs(a)) * sqrt(eiTheta * conj(eiThetaPrime));
    branch = random.Unsignedinteger() % 2;
    if (branch == 0) b = b * std::complex<double>(0., 1.);
    else if (branch == 1) b = b * std::complex<double>(0., -1.);

    // a and b satisfying Eq.(117), Eq.(118), and Eq.(119)
    while (std::abs(eiThetaPrime * conj(eiTheta) * b * b - a * a) < THRESHOLD) {
        random.unitComplexVector(a, b);
        a = a / sqrt(2.); b = b / sqrt(2.);
        b = std::abs(b) * (a / std::abs(a)) * sqrt(eiTheta * conj(eiThetaPrime));
        branch = random.Unsignedinteger() % 2;
        if (branch == 0) b = b * std::complex<double>(0., 1.);
        else if (branch == 1) b = b * std::complex<double>(0., -1.);
    }

    // |mmEe> in Eq.(120)
    state[2].schmidt.rank = 2;
    state[2].schmidt.lambda[0] = 1. / sqrt(2.);
    state[2].schmidt.alpha[0] = (ZERO_STATE * a + ONE_STATE * -conj(eiTheta) * eiThetaPrime * b) * sqrt(2.);
    state[2].schmidt.beta[0] = ZERO_STATE;
    state[2].schmidt.lambda[1] = 1. / sqrt(2.);
    state[2].schmidt.alpha[1] = (ZERO_STATE * b + ONE_STATE * -a) * sqrt(2.);
    state[2].schmidt.beta[1] = ONE_STATE;
    // |mmeE> in Eq.(121)
    state[3].schmidt.rank = 2;
    state[3].schmidt.lambda[0] = 1. / sqrt(2.);
    state[3].schmidt.alpha[0] = (ZERO_STATE * conj(b) + ONE_STATE * conj(eiTheta) * eiThetaPrime * conj(a)) * sqrt(2.);
    state[3].schmidt.beta[0] = ZERO_STATE;
    state[3].schmidt.lambda[1] = 1. / sqrt(2.);
    state[3].schmidt.alpha[1] = (ZERO_STATE * -conj(a) + ONE_STATE * -conj(b)) * sqrt(2.);
    state[3].schmidt.beta[1] = ONE_STATE;
    updateStatesFromSchDecoms();
}

// Theorem 21(MMEE: Non-Diagonal).
void TwoQubitBasis::becomeMMEE_NonDiagonal() {
    // variables
    std::complex<double> eiTheta;       // e^{i\theta}
    std::complex<double> eiThetaPrime;  // e^{i\theta'}
    std::complex<double> eiTPmT;        // e^{i(\theta'-\theta)}
    std::complex<double> a, b;
    std::complex<double> D = 0.;
    std::complex<double> C[2];
    double tau[2] = { 0., 0. };
    MyVec2 ALPHA[2], BETA[2];

    // |Mmee> in Eq.(115)
    state[0].schmidt.becomeSchDecomOfPhi_RealCoef(1. / 2.);
    // |mMee> in Eq.(116)
    eiTheta      = random.unitComplexNumber();
    eiThetaPrime = random.unitComplexNumber();
    state[1].schmidt.becomeSchDecomOfPsi_CompCoef((1. / sqrt(2.)) * eiTheta, (1. / sqrt(2.)) * eiThetaPrime);

    // e^{i(\theta'-\theta)}
    eiTPmT = eiThetaPrime * conj(eiTheta);
    // a and b satisfying Eq.(117)
    while (std::abs(D) < THRESHOLD || std::abs(eiTPmT * b * b - a * a) < THRESHOLD) {
        random.unitComplexVector(a, b); // |a|^2 + |b|^2 = 1
        a = a / sqrt(2.); b = b / sqrt(2.); // |a|^2 + |b|^2 = 1/2
        D = sqrt(eiTPmT) * conj(a) * b + conj(sqrt(eiTPmT)) * a * conj(b);
    }

    // tau_j in Eq.(126)
    for (int i = 0; i < 2; i++)
        tau[i] = sqrt((1. + (1 - 2 * (i & 1)) * sqrt(1. - 4. * std::abs(a * a - eiTPmT * b * b) * std::abs(a * a - eiTPmT * b * b))) / 2.);

    // C_j in Eq.(129)
    for (int i = 0; i < 2; i++)
        C[i] = sqrt(conj(eiTPmT)) * (D / std::abs(D)) * a + double(1 - 2 * (i & 1)) * b;

    // |alpha_j> in Eq.(127)
    for (int i = 0; i < 2; i++)
        ALPHA[i] = (ZERO_STATE * (-sqrt(conj(eiTPmT)) * (D / std::abs(D)))
            + ONE_STATE * (1 - 2 * (i & 1))) * (C[i] / (std::abs(C[i]) * sqrt(2.)));

    // |beta_j> in Eq.(128)
    for (int i = 0; i < 2; i++)
        BETA[i] = (ZERO_STATE * (sqrt(eiTPmT) * (D / std::abs(D)))
            + ONE_STATE * (1 - 2 * (i & 1))) * (1. / sqrt(2.));

    // |mmEe> in Eq.(124)
    state[2].schmidt.rank = 2;
    for (int i = 0; i < 2; i++) {
        state[2].schmidt.lambda[i] = tau[i];
        state[2].schmidt.alpha[i] = ALPHA[i];
        state[2].schmidt.beta[i] = BETA[i];
    }
    // |mmeE> in Eq.(125)
    state[3].schmidt.rank = 2;
    for (int i = 0; i < 2; i++) {
        state[3].schmidt.lambda[i] = tau[i];
        state[3].schmidt.alpha[i] = (BETA[i].getConjugate()) * (1 - 2 * (i & 1));
        state[3].schmidt.beta[i] = ALPHA[i].getConjugate();
    }
    updateStatesFromSchDecoms();
}





bool TwoQubitBasis::isFirstNStateUnit(const int number) const {
    for (int i = 0; i < number; i++)
        if (!state[i].isUnit()) return false;
    return true;
}
bool TwoQubitBasis::isFirstNStateOrthogonal(const int number) const {
    for (int i = 0; i < number; i++)
        for (int j = i + 1; j < number; j++)
            if (!state[i].isOrthogonalTo(state[j])) return false;
    return true;
}
bool TwoQubitBasis::isFirstNStateOrthonormal(const int number) const {
    return isFirstNStateUnit(number) && isFirstNStateOrthogonal(number);
}
bool TwoQubitBasis::isPP() const {
    return isFirstNStateOrthonormal(2)
        && (state[0].isProduct())
        && (state[1].isProduct()); }
bool TwoQubitBasis::isPE_Diagonal() const {
    return isFirstNStateOrthonormal(2)
        && (state[0].isProduct())
        && (state[1].isEntangled()) && (state[1].isDiagonal()); }
bool TwoQubitBasis::isPE_NonDiagonal() const {
    return isFirstNStateOrthonormal(2)
        && (state[0].isProduct())
        && (state[1].isEntangled()) && (state[1].isNonDiagonal()); }
bool TwoQubitBasis::isEP() const {
    return isFirstNStateOrthonormal(2)
        && (state[0].isEntangled())
        && (state[1].isProduct()); }
bool TwoQubitBasis::isEE_Diagonal() const {
    return isFirstNStateOrthonormal(2)
        && (state[0].isEntangled())
        && (state[1].isEntangled()) && (state[1].isDiagonal()); }
bool TwoQubitBasis::isEE_NonDiagonal() const {
    return isFirstNStateOrthonormal(2)
        && (state[0].isEntangled())
        && (state[1].isEntangled()) && (state[1].isNonDiagonal()); }
bool TwoQubitBasis::isPM() const {
    return isFirstNStateOrthonormal(2)
        && (state[0].isProduct())
        && (state[1].isMaximally()); }
bool TwoQubitBasis::isPPP() const {
    return isFirstNStateOrthonormal(3)
        && (state[0].isProduct())
        && (state[1].isProduct())
        && (state[2].isProduct()); }
bool TwoQubitBasis::isPPE() const {
    return isFirstNStateOrthonormal(3)
        && (state[0].isProduct())
        && (state[1].isProduct())
        && (state[2].isEntangled()); }
bool TwoQubitBasis::isPPPP() const {
    return isFirstNStateOrthonormal(4)
        && (state[0].isProduct())
        && (state[1].isProduct())
        && (state[2].isProduct())
        && (state[3].isProduct());
}
bool TwoQubitBasis::isPPEE() const {
    return isFirstNStateOrthonormal(4)
        && (state[0].isProduct())
        && (state[1].isProduct())
        && (state[2].isEntangled())
        && (state[3].isEntangled());
}
bool TwoQubitBasis::isPMEE() const {
    return isFirstNStateOrthonormal(4)
        && (state[0].isProduct())
        && (state[1].isMaximally())
        && (state[2].isEntangled())
        && (state[3].isEntangled());
}
bool TwoQubitBasis::isMMEE_Diagonal() const {
    return isFirstNStateOrthonormal(4)
        && (state[0].isMaximally())
        && (state[1].isMaximally())
        && (state[2].isEntangled()) && (state[2].isDiagonal())
        && (state[3].isEntangled()) && (state[2].isDiagonal());
}
bool TwoQubitBasis::isMMEE_NonDiagonal() const {
    return isFirstNStateOrthonormal(4)
        && (state[0].isMaximally())
        && (state[1].isMaximally())
        && (state[2].isEntangled()) && (state[2].isNonDiagonal())
        && (state[3].isEntangled()) && (state[2].isNonDiagonal());
}





void TwoQubitBasis::printInRow() const {
     for (int i = 0; i < 4; i++) { state[i].vec4.printInRow(); puts(""); } }
void TwoQubitBasis::printInColumn() const {
    for (int i = 0; i < 4; i++) { state[i].vec4.printInColumn(); puts(""); } }
void TwoQubitBasis::printFirstNStates(const int number) const {
    for (int i = 0; i < number; i++) { state[i].vec4.printInRow(); puts(""); } }
void TwoQubitBasis::printFirstNSchDecoms(const int number) const {
    for (int i = 0; i < number; i++) { state[i].schmidt.print(); puts(""); } }
