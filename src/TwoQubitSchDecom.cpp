#include "TwoQubitSchDecom.h"

TwoQubitSchDecom::TwoQubitSchDecom() : rank(0) { lambda[0] = lambda[1] = 0.0; }
TwoQubitSchDecom::TwoQubitSchDecom(const TwoQubitSchDecom& other) {
    rank = other.rank;
    for (int i = 0; i < 2; i++) {
        lambda[i] = other.lambda[i];
        alpha[i] = other.alpha[i];
        beta[i] = other.beta[i];
    }
}





MyVec4 TwoQubitSchDecom::getVector4() const
{
    MyVec4  firstTensorProd = alpha[0].vec2 * beta[0].vec2;
    MyVec4 secondTensorProd = alpha[1].vec2 * beta[1].vec2;
    return MyVec4(firstTensorProd * lambda[0] + secondTensorProd * lambda[1]);
}





void TwoQubitSchDecom::becomeSchDecomOfProd_CompuCompu(unsigned char i, unsigned char j) {
    rank = 1;
    lambda[0] = 1.;
    if (i == 0) alpha[0] = ZERO_STATE; else if (i == 1) alpha[0] = ONE_STATE;
    if (j == 0)  beta[0] = ZERO_STATE; else if (j == 1)  beta[0] = ONE_STATE;
    lambda[1] = 0.;
    if (i == 0) alpha[1] = ONE_STATE; else if (i == 1) alpha[1] = ZERO_STATE;
    if (j == 0)  beta[1] = ONE_STATE; else if (j == 1)  beta[1] = ZERO_STATE;
}
void TwoQubitSchDecom::becomeSchDecomOfProd_StateCompu(unsigned char i) {
    std::complex<double> a, b;
    random.unitComplexVector(a, b);
    becomeSchDecomOfProd_StateCompu(a, b, i);
}
void TwoQubitSchDecom::becomeSchDecomOfProd_StateCompu(const std::complex<double>& a, const std::complex<double>& b, unsigned char i) {
    rank = 1;
    lambda[0] = 1.;
    alpha[0].vec2.element[0] = a; alpha[0].vec2.element[1] = b;
    if (i == 0) beta[0] = ZERO_STATE; else if (i == 1) beta[0] = ONE_STATE;
    lambda[1] = 0.;
    alpha[1] = alpha[0].getOrthogonalState();
    if (i == 0) beta[1] = ONE_STATE; else if (i == 1) beta[1] = ZERO_STATE;
}
void TwoQubitSchDecom::becomeSchDecomOfProd_CompuState(unsigned char i) {
    std::complex<double> c, d;
    random.unitComplexVector(c, d);
    becomeSchDecomOfProd_CompuState(i, c, d);
}
void TwoQubitSchDecom::becomeSchDecomOfProd_CompuState(unsigned char i, const std::complex<double>& c, const std::complex<double>& d)
{
    rank = 1;
    lambda[0] = 1.;
    if (i == 0) alpha[0] = ZERO_STATE; else if (i == 1)alpha[0] = ONE_STATE;
    beta[0].vec2.element[0] = c; beta[0].vec2.element[1] = d;
    lambda[1] = 0.;
    if (i == 0) alpha[1] = ONE_STATE; else if (i == 1)alpha[1] = ZERO_STATE;
    beta[1] = beta[0].getOrthogonalState();
}
void TwoQubitSchDecom::becomeSchDecomOfProd_SetupSetup(const std::complex<double>& a, const std::complex<double>& b, const std::complex<double>& c, const std::complex<double>& d) {
    rank = 1;
    lambda[0] = 1.;
    alpha[0].vec2.element[0] = a; alpha[0].vec2.element[1] = b;
    beta[0].vec2.element[0] = c; beta[0].vec2.element[1] = d;
    lambda[1] = 0.;
    alpha[1] = alpha[0].getOrthogonalState();
    beta[1] = beta[0].getOrthogonalState();
}
void TwoQubitSchDecom::becomeSchDecomOfPhi_RealCoef() { becomeSchDecomOfPhi_RealCoef(random.realNumber0To1()); }
void TwoQubitSchDecom::becomeSchDecomOfPhi_RealCoef(double r) {
    rank = 2;
    lambda[0] = sqrt(    r); alpha[0] = ZERO_STATE; beta[0] = ZERO_STATE;
    lambda[1] = sqrt(1 - r); alpha[1] = ONE_STATE; beta[1] = ONE_STATE;
}
void TwoQubitSchDecom::becomeSchDecomOfPhi_CompCoef() {
    std::complex<double> c, d;
    random.unitComplexVector(c, d);
    becomeSchDecomOfPhi_CompCoef(c, d);
}
void TwoQubitSchDecom::becomeSchDecomOfPhi_CompCoef(const std::complex<double>& a, const std::complex<double>& b) {
    rank = 2;
    lambda[0] = std::abs(a); alpha[0] = ZERO_STATE; beta[0] = ZERO_STATE;
    lambda[1] = std::abs(b); alpha[1] = ONE_STATE; beta[1] = ONE_STATE;
    unsigned int i = random.Unsignedinteger() % 2;
    unsigned int j = random.Unsignedinteger() % 2;
    if (i == 0) alpha[0] = alpha[0].vec2 * (a / std::abs(a)); else if (i == 1) beta[0] = beta[0].vec2 * (a / std::abs(a));
    if (j == 0) alpha[1] = alpha[1].vec2 * (b / std::abs(b)); else if (j == 1) beta[1] = beta[1].vec2 * (b / std::abs(b));
}
void TwoQubitSchDecom::becomeSchDecomOfPsi_RealCoef() { becomeSchDecomOfPsi_RealCoef(random.realNumber0To1()); }
void TwoQubitSchDecom::becomeSchDecomOfPsi_RealCoef(double r) {
    rank = 2;
    lambda[0] = sqrt(    r); alpha[0] = ZERO_STATE; beta[0] = ONE_STATE;
    lambda[1] = sqrt(1 - r); alpha[1] = ONE_STATE; beta[1] = ZERO_STATE;
}
void TwoQubitSchDecom::becomeSchDecomOfPsi_CompCoef() {
    std::complex<double> a, b;
    random.unitComplexVector(a, b);
    becomeSchDecomOfPsi_CompCoef(a, b);
}
void TwoQubitSchDecom::becomeSchDecomOfPsi_CompCoef(const std::complex<double>& a, const std::complex<double>& b) {
    rank = 2;
    lambda[0] = std::abs(a); alpha[0] = ZERO_STATE; beta[0] = ONE_STATE;
    lambda[1] = std::abs(b); alpha[1] = ONE_STATE; beta[1] = ZERO_STATE;
    unsigned int i = random.Unsignedinteger() % 2;
    unsigned int j = random.Unsignedinteger() % 2;
    if (i == 0) alpha[0] = alpha[0].vec2 * (a / std::abs(a)); else if (i == 1) beta[0] = beta[0].vec2 * (a / std::abs(a));
    if (j == 0) alpha[1] = alpha[1].vec2 * (b / std::abs(b)); else if (j == 1) beta[1] = beta[1].vec2 * (b / std::abs(b));
}





bool TwoQubitSchDecom::isSchRank() const {
    int count = 0;
    if (lambda[0] > 0.) count++;
    if (lambda[1] > 0.) count++;
    if (rank == count) return true;
    else               return false;
}
bool TwoQubitSchDecom::isSchDecom() const { return isSchCoef() && isSchBasisAlpha() && isSchBasisBeta() && isUnit(); }
bool TwoQubitSchDecom::isSchCoef() const { return lambda[0] >= 0. && lambda[1] >= 0. && std::abs(lambda[0] * lambda[0] + lambda[1] * lambda[1] - 1.0) < THRESHOLD; }
bool TwoQubitSchDecom::isSchBasisAlpha() const { return alpha[0].vec2.isOrthogonalTo(alpha[1].vec2) && alpha[0].vec2.isUnit() && alpha[1].vec2.isUnit(); }
bool TwoQubitSchDecom::isSchBasisBeta() const { return  beta[0].vec2.isOrthogonalTo(beta[1].vec2) && beta[0].vec2.isUnit() && beta[1].vec2.isUnit(); }
bool TwoQubitSchDecom::isUnit() const { return getVector4().isUnit(); }





void TwoQubitSchDecom::print() const {
    //printf("\033[0;33m");
    //printf(" %+6.4f *", lambda[0]);
    //printf(" [ "); alpha[0].vec2.printComponent(0); printf(" ] * [ "); beta[0].vec2.printComponent(0); printf(" ]");
    //printf(" %+6.4f *", lambda[1]);
    //printf(" [ "); alpha[1].vec2.printComponent(0); printf(" ] * [ "); beta[1].vec2.printComponent(0); printf(" ]\n");
    //printf("\033[0;30m"); printf(" %+6.4f *", lambda[0]); printf("\033[0;33m");
    //printf(" [ "); alpha[0].vec2.printComponent(1); printf(" ]   [ "); beta[0].vec2.printComponent(1); printf(" ]");
    //printf("\033[0;30m"); printf(" %+6.4f *", lambda[1]); printf("\033[0;33m");
    //printf(" [ "); alpha[1].vec2.printComponent(1); printf(" ]   [ "); beta[1].vec2.printComponent(1); printf(" ]");
    //printf("\033[0m");

    printf("\033[0;33m");
    printf(" "); MyPrint::printReal(lambda[0]); printf("\033[0;33m"); printf(" *");
    printf(" [ "); MyPrint::printComplex(alpha[0].vec2.element[0]); printf("\033[0;33m"); printf(" ] * [ "); MyPrint::printComplex(beta[0].vec2.element[0]); printf("\033[0;33m"); printf(" ]");
    printf(" "); MyPrint::printReal(lambda[1]); printf("\033[0;33m"); printf(" *");
    printf(" [ "); MyPrint::printComplex(alpha[1].vec2.element[0]); printf("\033[0;33m"); printf(" ] * [ "); MyPrint::printComplex(beta[1].vec2.element[0]); printf("\033[0;33m"); printf(" ]\n");
    printf("\033[0;30m"); printf(" %+6.4f *", lambda[0]); printf("\033[0;33m");
    printf(" [ "); MyPrint::printComplex(alpha[0].vec2.element[1]); printf("\033[0;33m"); printf(" ]   [ "); MyPrint::printComplex(beta[0].vec2.element[1]); printf("\033[0;33m"); printf(" ]");
    printf("\033[0;30m"); printf(" %+6.4f *", lambda[1]); printf("\033[0;33m");
    printf(" [ "); MyPrint::printComplex(alpha[1].vec2.element[1]); printf("\033[0;33m"); printf(" ]   [ "); MyPrint::printComplex(beta[1].vec2.element[1]); printf("\033[0;33m"); printf(" ]");
    printf("\033[0m");
}
