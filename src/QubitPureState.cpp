#include "QubitPureState.h"

QubitPureState::QubitPureState() : vec2() {}
QubitPureState::QubitPureState(const QubitPureState& other) : vec2(other.vec2) {}
QubitPureState::QubitPureState(const MyVec2& other) : vec2(other) {}
QubitPureState::QubitPureState(const std::complex<double>& a, const std::complex<double>& b) : vec2(a, b) {}





QubitPureState QubitPureState::getOrthogonalState() const {
    unsigned int branch = vec2.random.Unsignedinteger() % 2;
    if (branch == 0) return QubitPureState(-conj(vec2.element[1]), conj(vec2.element[0]));
    else return QubitPureState(conj(vec2.element[1]), -conj(vec2.element[0]));
}





void QubitPureState::becomeZero() { vec2.becomeZero(); }
void QubitPureState::becomeUnit() { vec2.becomeUnit(); }
void QubitPureState::becomeRandom() { vec2.becomeRandom(); }
void QubitPureState::becomeRandomUnit() { vec2.becomeRandomUnit(); }





bool QubitPureState::isUnit() const { return vec2.isUnit(); }
bool QubitPureState::isOrthogonalTo(const QubitPureState& other) const { return vec2.isOrthogonalTo(other.vec2); }
bool QubitPureState::isEqualTo(const QubitPureState& other) const { return vec2.isEqualTo(other.vec2); }





void QubitPureState::printInRow() const { vec2.printInRow(); }
void QubitPureState::printInColumn() const {  vec2.printInColumn(); }
