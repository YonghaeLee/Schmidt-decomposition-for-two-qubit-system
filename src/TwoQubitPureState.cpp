#include "TwoQubitPureState.h"

TwoQubitPureState::TwoQubitPureState() : vec4(), schmidt() {}
TwoQubitPureState::TwoQubitPureState(const TwoQubitPureState& other) : vec4(other.vec4), schmidt(other.schmidt) {}





//-----------------------------------------------------
// Proposition 1(Schmidt Decomposition: Diagonal).
// proposition 2(Schmidt Decomposition: Non-Diagonal).
//-----------------------------------------------------
void TwoQubitPureState::findSchDecom() {
    // Eq.(3)
    std::complex<double> c00 = vec4.element[0];
    std::complex<double> c01 = vec4.element[1];
    std::complex<double> c10 = vec4.element[2];
    std::complex<double> c11 = vec4.element[3];

    // Eq.(14)
    std::complex<double> DC = conj(c00) * c01 + conj(c10) * c11;
    
    if (std::abs(DC) < THRESHOLD)
    {
        // Proposition 1(Schmidt Decomposition: Diagonal).
        // Eq.(17)
        if ((std::abs(c00) < THRESHOLD) && (std::abs(c10) < THRESHOLD)) // diagonal & product
            schmidt.becomeSchDecomOfProd_StateCompu(c01, c11, 1);
        else if ((std::abs(c01) < THRESHOLD) && (std::abs(c11) < THRESHOLD)) // diagonal & product
            schmidt.becomeSchDecomOfProd_StateCompu(c00, c10, 0);
        else // diagonal & entangled
        {
            schmidt.rank = 2;
            schmidt.lambda[0] = sqrt(std::abs(c00) * std::abs(c00) + std::abs(c10) * std::abs(c10));
            schmidt.alpha[0].vec2.element[0] = c00 / schmidt.lambda[0]; schmidt.beta[0].vec2.element[0] = 1.0;
            schmidt.alpha[0].vec2.element[1] = c10 / schmidt.lambda[0]; schmidt.beta[0].vec2.element[1] = 0.0;
            schmidt.lambda[1] = sqrt(std::abs(c01) * std::abs(c01) + std::abs(c11) * std::abs(c11));
            schmidt.alpha[1].vec2.element[0] = c01 / schmidt.lambda[1]; schmidt.beta[1].vec2.element[0] = 0.0;
            schmidt.alpha[1].vec2.element[1] = c11 / schmidt.lambda[1]; schmidt.beta[1].vec2.element[1] = 1.0;
        }
    }
    else {
        // proposition 2(Schmidt Decomposition: Non-Diagonal).
        if (vec4.concurrence() < THRESHOLD) {   // non-diagoal & product
            schmidt.rank = 1;
            // Eq.(23)
            schmidt.lambda[0] = 1.;
            schmidt.lambda[1] = 0.;

            // Eq.(24)
            schmidt.beta[0].vec2.element[0] = DC;
            schmidt.beta[0].vec2.element[1] = 1. - (std::abs(c00) * std::abs(c00)) - (std::abs(c10) * std::abs(c10));
            schmidt.beta[1].vec2.element[0] = DC;
            schmidt.beta[1].vec2.element[1] = -(std::abs(c00) * std::abs(c00)) - (std::abs(c10) * std::abs(c10));
            for (int i = 0; i < 2; i++) {
                // Eq.(25)
                schmidt.alpha[i].vec2.element[0] = c00 * schmidt.beta[i].vec2.element[0] + c01 * schmidt.beta[i].vec2.element[1];
                schmidt.alpha[i].vec2.element[1] = c10 * schmidt.beta[i].vec2.element[0] + c11 * schmidt.beta[i].vec2.element[1];

                // Using Eq.(25) makes alpha[1] zero vector. It makes error in "alpha[1].vec2.becomeUnit();"
                if (i == 1) schmidt.alpha[1] = schmidt.alpha[0].getOrthogonalState();
                schmidt.alpha[i].vec2.becomeUnit();
                schmidt.beta[i].vec2.becomeConjugate();
                schmidt.beta[i].vec2.becomeUnit();
            }
        }
        else {  // non-diagoal & entangled
            schmidt.rank = 2;
            for (int i = 0; i < 2; i++) {
                // Eq.(23)
                schmidt.lambda[i] = sqrt((1 + (1 - 2 * (i & 1)) * sqrt(1 - (vec4.concurrence() * vec4.concurrence()))) / 2.);
                // Eq.(24)
                schmidt.beta[i].vec2.element[0] = DC;
                schmidt.beta[i].vec2.element[1] = schmidt.lambda[i] * schmidt.lambda[i] - (std::abs(c00) * std::abs(c00)) - (std::abs(c10) * std::abs(c10));
                // Eq.(25)
                schmidt.alpha[i].vec2.element[0] = c00 * schmidt.beta[i].vec2.element[0] + c01 * schmidt.beta[i].vec2.element[1];
                schmidt.alpha[i].vec2.element[1] = c10 * schmidt.beta[i].vec2.element[0] + c11 * schmidt.beta[i].vec2.element[1];

                schmidt.alpha[i].vec2.becomeUnit();
                schmidt.beta[i].vec2.becomeConjugate();
                schmidt.beta[i].vec2.becomeUnit();
            }
        }
    }
}






double TwoQubitPureState::dist(const TwoQubitPureState& other) const { return vec4.dist(other.vec4); }





void TwoQubitPureState::becomeZero() { vec4.becomeZero(); }
void TwoQubitPureState::becomeUnit() { vec4.becomeUnit(); }
void TwoQubitPureState::becomeRandom() { vec4.becomeRandom(); }
void TwoQubitPureState::becomeRandomUnit() { vec4.becomeRandom(); vec4.becomeUnit(); }
void TwoQubitPureState::becomeRandomProduct() {
    vec4.becomeRandom();
    if (std::abs(vec4.element[0]) == 0.) {
        unsigned int branch = random.Unsignedinteger() % 3;
        if (branch == 0)   vec4.becomeZero(1);
        else if (branch == 1)   vec4.becomeZero(2);
        else if (branch == 2) { vec4.becomeZero(1); vec4.becomeZero(2); }
    }
    else { vec4.element[3] = (vec4.element[1] * vec4.element[2]) / vec4.element[0]; }
    becomeUnit();
}
void TwoQubitPureState::becomeRandomDiagonal() {
    vec4.becomeRandom();
    if (std::abs(vec4.element[2]) == 0.) {
        unsigned int branch = random.Unsignedinteger() % 3;
        if (branch == 0)   vec4.becomeZero(0);
        else if (branch == 1)   vec4.becomeZero(1);
        else if (branch == 2) { vec4.becomeZero(0); vec4.becomeZero(1); }
    }
    else { vec4.element[3] = ((conj(vec4.element[0]) * vec4.element[1]) * -1.) / conj(vec4.element[2]); }
    becomeUnit();
}
void TwoQubitPureState::becomeRandomProductDiagonal() {
    unsigned int branch = random.Unsignedinteger() % 2;
    vec4.becomeRandom();
    if (branch == 0) { vec4.becomeZero(0); vec4.becomeZero(2); }
    else if (branch == 1) { vec4.becomeZero(1); vec4.becomeZero(3); }
    becomeUnit();
}





bool TwoQubitPureState::isUnit() const { return vec4.isUnit(); }
bool TwoQubitPureState::isDiagonal() const { return vec4.isDiagonal(); }
bool TwoQubitPureState::isNonDiagonal() const { return vec4.isNonDiagonal(); }
bool TwoQubitPureState::isProduct() const { return vec4.isProduct(); }
bool TwoQubitPureState::isEntangled() const { return vec4.isEntangled(); }
bool TwoQubitPureState::isMaximally() const { return vec4.isMaximally(); }
bool TwoQubitPureState::isOrthogonalTo(const TwoQubitPureState& other) const { return vec4.isOrthogonalTo(other.vec4); }
bool TwoQubitPureState::isEqualTo(const TwoQubitPureState& other) const { return vec4.isEqualTo(other.vec4); }





void TwoQubitPureState::printInColumn() const { vec4.printInColumn(); }
void TwoQubitPureState::printInRow() const { vec4.printInRow(); }
void TwoQubitPureState::printSchDecom() const { schmidt.print(); }
