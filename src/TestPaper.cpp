#include "TestPaper.h"

void TestPaper::Proposition1() {
	MyPrint::green("\n******************************** Test Proposition 1 (Schmidt Decomposition: Diagonal) ********************************\n\n");

	printf(">  We test Prop. 1 in the paper.\n");
	printf(">  Prop. 1 provides an explicit formula for computing the Schmidt decomposition of an arbitrary two-qubit\n");
	printf("   pure state that "); MyPrint::red("satisfies the diagonal condition "); printf("in Eq. (14).\n");
	printf(">  The `void findSchDecom()` function computes the decomposition according to Prop. 1.\n\n");
	
	MyPrint::cyan(">  To test Prop. 1, we generate a random initial state, which satisfies the diagonal condition.\n");
	test.state[0].becomeRandomDiagonal();
	test.state[0].printInColumn(); puts("\n");

	printf(">  The `bool isDiagonal()` function checks whether the state satisfies the diagonal condition.\n");
	printf(">  By using this function, we can conclude that\n\n");

	MyPrint::cyan(">  This random initial state is ");
	if (test.state[0].isDiagonal()) MyPrint::yellow("diagonal"); else MyPrint::yellow("non-diagonal"); puts(".\n");
	
	MyPrint::cyan(">  Next, the Schmidt decomposition of this random state is obtained using Eq. (17).\n");
	test.state[0].findSchDecom();
	test.state[0].printSchDecom(); puts("\n");
	
	printf(">  To determine whether this decomposition is valid, the following two questions need to be answered:\n");
	printf("     1) Does this decomposition satisfy the conditions of the Schmidt decomposition?\n");
	printf("     2) Does this decomposition accurately reconstruct the initial state?\n\n");

	printf(">  For the first question, the test checks whether the two Schmidt coefficients are positive real numbers\n");
	printf("   whose squares sum to 1 and whether the Schmidt basis vectors for each qubit system form an orthonormal basis.\n");
	printf(">  The `bool isSchCoef()`, `bool isSchBasisAlpha()`, and `bool isSchBasisBeta()` functions\n");
	printf(">  check whether the given decomposition satisfies the Schmidt decomposition condition.\n\n");
	
	MyPrint::cyan(">  Schmidt coefficients ");
	if (test.state[0].schmidt.isSchCoef()) MyPrint::yellow("are "); else MyPrint::yellow("are not ");
	MyPrint::cyan("positive real numbers whose squares sum to 1.\n");
	MyPrint::cyan(">  Schmidt basis A ");
	if (test.state[0].schmidt.isSchBasisAlpha()) MyPrint::yellow("is "); else MyPrint::yellow("is not ");
	MyPrint::cyan("orthonormal.\n");
	MyPrint::cyan(">  Schmidt basis B ");
	if (test.state[0].schmidt.isSchBasisBeta()) MyPrint::yellow("is "); else MyPrint::yellow("is not ");
	MyPrint::cyan("orthonormal.\n"); puts("");

	printf(">  Finally, to confirm that the Schmidt decomposition exactly reconstructs the initial state,\n");
	printf("   the decomposition is converted into a complex vector of size 4.\n");
	printf(">  This is done using the `MyVec4 getVector4()` function .\n\n");

	MyPrint::cyan(">  The reconstructed state is \n");
	MyVec4 temp = test.state[0].schmidt.getVector4();
	temp.printInRow(); puts("");
	MyPrint::cyan(">  The initial state is \n");
	test.state[0].printInRow(); puts("\n");

	printf(">  Using the `bool isEqualTo(const MyVec4& other)` function,\n");
	printf("   it is determined whether the two vectors are identical based on their distance.\n\n");
	
	MyPrint::cyan(">  The initial state and the reconstructed state ");
	if (test.state[0].vec4.isEqualTo(temp)) MyPrint::yellow("are "); else MyPrint::red("are not ");
	MyPrint::cyan("equal.\n");
}

void TestPaper::Proposition2() {
	MyPrint::green("\n****************************** Test Proposition 2 (Schmidt Decomposition: Non-Diagonal) ******************************\n\n");

	printf(">  We test Prop. 2 in the paper.\n");
	printf(">  Prop. 2 provides an explicit formula for computing the Schmidt decomposition of an arbitrary two-qubit\n");
	printf("   pure state that "); MyPrint::red("does not satisfy the diagonal condition "); printf("in Eq. (14).\n");
	printf(">  The `void findSchDecom()` function computes the decomposition according to Prop. 2.\n\n");

	MyPrint::cyan(">  To test Prop. 2, we generate a random initial state not satisfying the diagonal condition.\n");
	test.state[0].becomeRandomUnit(); // set of diagonal states is measure zero.
	test.state[0].printInColumn(); puts("");
	MyPrint::cyan(">  This random initial state is ");
	if (test.state[0].isDiagonal()) MyPrint::yellow("diagonal"); else MyPrint::yellow("non-diagonal"); puts(".\n");
	
	MyPrint::cyan(">  Next, the Schmidt decomposition of the initial state is obtained using Eqs. (23), (24), and (25).\n");
	test.state[0].findSchDecom();
	test.state[0].printSchDecom(); puts("");
	MyPrint::cyan(">  Schmidt coefficients ");
	if (test.state[0].schmidt.isSchCoef()) MyPrint::yellow("are "); else MyPrint::yellow("are not ");
	MyPrint::cyan("positive real numbers whose squares sum to 1.\n");
	MyPrint::cyan(">  Schmidt basis A ");
	if (test.state[0].schmidt.isSchBasisAlpha()) MyPrint::yellow("is "); else MyPrint::yellow("is not ");
	MyPrint::cyan("orthonormal.\n");
	MyPrint::cyan(">  Schmidt basis B ");
	if (test.state[0].schmidt.isSchBasisBeta()) MyPrint::yellow("is "); else MyPrint::yellow("is not ");
	MyPrint::cyan("orthonormal.\n"); puts("");

	MyPrint::cyan(">  Finally, the reconstructed state is \n");
	MyVec4 temp = test.state[0].schmidt.getVector4();
	temp.printInRow(); puts("");
	MyPrint::cyan(">  The initial state is \n");
	test.state[0].printInRow(); puts("\n");
	
	MyPrint::cyan(">  The initial state and the reconstructed state ");
	if (test.state[0].vec4.isEqualTo(temp)) MyPrint::yellow("are "); else MyPrint::red("are not ");
	MyPrint::cyan("equal.\n");
}

void TestPaper::Proposition3() {
	MyPrint::green("\n********************************************** Test Proposition 3 (PP) ***********************************************\n\n");
	
	printf(">  We test Prop. 3 in the paper.  \n");
	printf(">  The `void becomePP()` function generates two orthogonal Schmidt decompositions based on Prop. 3.\n\n");

	MyPrint::cyan(">  Assume that a product state |Pp> has the Schmidt decomposition in Eq. (26).\n");
	test.becomePP();
	test.state[0].schmidt.print(); puts("\n");

	printf(">  Prop. 3 provides an explicit formula for the Schmidt decomposition of another product state |pP>.\n");
	printf(">  The Schmidt decomposition of |pP> is characterized by a single qubit pure state.\n\n");
	
	MyPrint::cyan(">  The Schmidt decomposition of |pP> is determined by Eq. (27) or Eq. (28).\n");
	test.state[1].schmidt.print(); puts("\n");
	test.updateStatesFromSchDecoms();
	
	printf(">  To test whether Prop. 3 holds, the two decompositions are reconstructed as complex vectors of size 4.\n");
	printf(">  If the two vectors form an orthonormal set and each represents a product state,\n");
	printf("   then the formulas given in Prop. 3 are correct.\n");
	printf(">  To verify this, the `bool isPP()` function is used.\n\n");

	MyPrint::cyan(">  The two states reconstructed from the decompositions ");
	if (test.isPP()) MyPrint::yellow("form "); else MyPrint::red("do not form ");
	MyPrint::cyan("the PP-type orthonormal set.\n\n");

	printf(">  For reference,\n");
	printf("|Pp> : "); test.state[0].printInRow(); puts("");
	printf("|pP> : "); test.state[1].printInRow(); puts("");
}

void TestPaper::Proposition4() {
	MyPrint::green("\n***************************************** Test Proposition 4 (PE: Diagonal) ******************************************\n\n");

	printf(">  We test Prop. 4 in the paper.  \n");
	printf(">  The `void becomePE_Diagonal()` function generates two orthogonal Schmidt decompositions based on Prop. 4.\n\n");

	MyPrint::cyan(">  Assume that a product state |Pe> has the Schmidt decomposition given in Eq. (29).\n");
	test.becomePE_Diagonal();
	test.state[0].schmidt.print(); puts("\n");


	printf(">  Prop. 4 provides an explicit formula for the Schmidt decomposition of an entangled and ");
	MyPrint::red("diagonal"); printf(" state |pE>\n");
	printf("   that is orthogonal to the first one.\n");
	printf(">  The Schmidt decomposition of |pE> is characterized by two nonzero complex numbers ");
	MyPrint::purple("a"); printf(" and "); MyPrint::purple("b.\n\n");

	MyPrint::cyan(">  The Schmidt decomposition of |pE> is determined by Eq. (30).\n");
	test.state[1].schmidt.print(); puts("\n");
	test.updateStatesFromSchDecoms();

	printf(">  To verify the formula given in Prop. 4 is correct,\n");
	printf("   the `bool isPE_Diagonal()` function is used.\n\n");

	MyPrint::cyan(">  The two states reconstructed from the decompositions ");
	if (test.isPE_Diagonal()) MyPrint::yellow("form "); else MyPrint::red("do not form ");
	MyPrint::cyan("the PE-type orthonormal set, where |pE> is ");
	MyPrint::red("diagonal"); MyPrint::cyan(".\n\n");


	printf(">  For reference,\n");
	printf("|Pe> : "); test.state[0].printInRow(); puts("");
	printf("|pE> : "); test.state[1].printInRow(); puts("");
}

void TestPaper::Proposition5() {
	MyPrint::green("\n**************************************** Test Proposition 5 (PE: Non-Diagonal)****************************************\n\n");

	printf(">  We test Prop. 5 in the paper.  \n");
	printf(">  The `void becomePE_NonDiagonal()` function generates two orthogonal Schmidt decompositions based on Prop. 5.\n\n");

	MyPrint::cyan(">  Assume that a product state |Pe> has the Schmidt decomposition given in Eq. (29).\n");
	test.becomePE_NonDiagonal();
	test.state[0].schmidt.print(); puts("\n");

	printf(">  Prop. 5 provides an explicit formula for the Schmidt decomposition of an entangled and ");
	MyPrint::red("non-diagonal"); printf(" state |pE>\n");
	printf("   that is orthogonal to the first one.\n");
	printf(">  The Schmidt decomposition of this entangled state |pE> is characterized\n");
	printf("   by three nonzero complex numbers "); MyPrint::purple("a"); printf(", "); MyPrint::purple("b"); printf(", and "); MyPrint::purple("c.\n\n");


	MyPrint::cyan(">  The Schmidt decomposition of |pE> is determined by Eqs. (33) and (34).\n");
	test.state[1].schmidt.print(); puts("\n");
	test.updateStatesFromSchDecoms();

	printf(">  To verify the formula given in Prop. 5 is correct, the `bool isPE_NonDiagonal()` function is used.\n\n");
	
	MyPrint::cyan(">  The two states reconstructed from the decompositions ");
	if (test.isPE_NonDiagonal()) MyPrint::yellow("form "); else MyPrint::red("do not form ");
	MyPrint::cyan("the PE-type orthonormal set, where |pE> is ");
	MyPrint::red("non-diagonal"); MyPrint::cyan(".\n\n");

	printf(">  For reference,\n");
	printf("|Pe> : "); test.state[0].printInRow(); puts("");
	printf("|pE> : "); test.state[1].printInRow(); puts("");
}

void TestPaper::Proposition6() {
	MyPrint::green("\n********************************************** Test Proposition 6 (EP) ***********************************************\n\n");
	
	printf(">  We test Prop. 6 in the paper.  \n");
	printf(">  The `void becomeEP()` function generates two orthogonal Schmidt decompositions based on Prop. 6.\n\n");

	MyPrint::cyan(">  Assume that an entangled state |Ep> has the Schmidt decomposition given in Eq. (35).\n");
	test.becomeEP();
	test.state[0].schmidt.print(); puts("\n");

	printf(">  The proposition provides an explicit formula for the Schmidt decomposition of a product state |eP>\n");
	printf("   that is orthogonal to the first one.\n");
	printf(">  The Schmidt decomposition of |eP> is characterized by two complex numbers ");
	MyPrint::purple("a"); printf(" and "); MyPrint::purple("b"); printf(" satisfying Eq. (36).\n\n");

	MyPrint::cyan(">  The Schmidt decomposition of |eP> is determined by Eq. (37).\n");
	test.state[1].schmidt.print(); puts("\n");
	test.updateStatesFromSchDecoms();

	printf(">  To verify the formula given in Prop. 6 is correct, the `bool isEP()` function is used.\n\n");

	MyPrint::cyan(">  The two states reconstructed from the decompositions ");
	if (test.isEP()) MyPrint::yellow("form "); else MyPrint::red("do not form ");
	MyPrint::cyan("the EP-type orthonormal set.\n\n");

	printf(">  For reference,\n");
	printf("|Ep> : "); test.state[0].printInRow(); puts("");
	printf("|eP> : "); test.state[1].printInRow(); puts("");
}

void TestPaper::Proposition7() {
	MyPrint::green("\n***************************************** Test Proposition 7 (EE: Diagonal) ******************************************\n\n");

	printf(">  We test Prop. 7 in the paper.  \n");
	printf(">  The `void becomeEE_Diagonal()` function generates two orthogonal Schmidt decompositions based on Prop. 7.\n\n");

	MyPrint::cyan(">  Assume that the 1st entangled state |Ee> has the Schmidt decomposition given in Eq. (40).\n");
	test.becomeEE_Diagonal();
	test.state[0].schmidt.print(); puts("\n");

	printf(">  The Prop. 7 provides an explicit formula for the Schmidt decomposition of an entangled and ");
	MyPrint::red("diagonal"); printf(" state |eE>\n");
	printf("   that is orthogonal to the first one.\n");
	printf(">  The Schmidt decomposition of |eE> is characterized by three complex numbers\n");
	printf("   "); MyPrint::purple("a"); printf(", "); MyPrint::purple("b"); printf(", and "); MyPrint::purple("c");
	printf(" satisfying the conditions in Eqs. (41), (42), and (43).\n\n");

	MyPrint::cyan(">  The Schmidt decomposition of |eE> is determined by Eq. (44) and Eq. (45).\n");
	test.state[1].schmidt.print(); puts("\n");
	test.updateStatesFromSchDecoms();

	printf(">  To verify the formula given in Prop. 7 is correct, the `bool isEE_Diagonal()` function is used.\n\n");

	MyPrint::cyan(">  The two states reconstructed from the decompositions ");
	if (test.isEE_Diagonal()) MyPrint::yellow("form "); else MyPrint::red("do not form ");
	MyPrint::cyan("the EE-type orthonormal set, where |eE> is ");
	MyPrint::red("diagonal"); MyPrint::cyan(".\n\n");

	printf(">  For reference,\n");
	printf("|Ee> : "); test.state[0].printInRow(); puts("");
	printf("|eE> : "); test.state[1].printInRow(); puts("");
}

void TestPaper::Proposition8() {
	MyPrint::green("\n*************************************** Test Proposition 8 (EE: Non-Diagonal) ****************************************\n\n");
	
	printf(">  We test Prop. 8 in the paper.  \n");
	printf(">  The `void becomeEE_NonDiagonal()` function generates two orthogonal Schmidt decompositions based on Prop. 8.\n\n");

	MyPrint::cyan(">  Assume that the 1st entangled state |Ee> has the Schmidt decomposition given in Eq. (40).\n");
	test.becomeEE_NonDiagonal();
	test.state[0].schmidt.print(); puts("\n");

	printf(">  The Prop. 8 provides an explicit formula for the Schmidt decomposition of\n");
	printf("   an entangled and "); MyPrint::red("non-diagonal"); printf(" state |eE>\n"); printf("   that is orthogonal to the first one.\n");
	printf(">  The Schmidt decomposition of |eE> is characterized by three complex numbers\n");
	printf("   "); MyPrint::purple("a"); printf(", "); MyPrint::purple("b"); printf(", and "); MyPrint::purple("c");
	printf(" satisfying the conditions in Eqs. (41), (42), and not satisfying (43).\n\n");

	MyPrint::cyan(">  The Schmidt decomposition of |eE> is determined by Eqs. (47), (48), and (49).\n");
	test.state[1].schmidt.print(); puts("\n");
	test.updateStatesFromSchDecoms();

	printf(">  To verify the formula given in Prop. 8 is correct, the `bool isEE_NonDiagonal()` function is used.\n\n");

	MyPrint::cyan(">  The two states reconstructed from the decompositions ");
	if (test.isEE_NonDiagonal()) MyPrint::yellow("form "); else MyPrint::red("do not form ");
	MyPrint::cyan("the EE-type orthonormal set, where |eE> is ");
	MyPrint::red("non-diagonal"); MyPrint::cyan(".\n\n");

	printf(">  For reference,\n");
	printf("|Ee> : "); test.state[0].printInRow(); puts("");
	printf("|eE> : "); test.state[1].printInRow(); puts("");
}

void TestPaper::Proposition18() {
	MyPrint::green("\n********************************************** Test Proposition 18 (PM) **********************************************\n\n");

	printf(">  We test Prop. 18 in the paper.  \n");
	printf(">  The `void becomePM()` function generates two orthogonal Schmidt decompositions based on Prop. 18.\n\n");

	MyPrint::cyan(">  Assume that a product state |Pm> has the Schmidt decomposition given in Eq. (102).\n");
	test.becomePM();
	test.state[0].schmidt.print(); puts("\n");

	printf(">  The proposition provides an explicit formula for the Schmidt decomposition of a maximally entangled state\n");
	printf("   |pM> that is orthogonal to the first one.\n");
	printf(">  The Schmidt decomposition of |pM> is characterized by two real numbers ");
	MyPrint::purple("theta"); printf(" and "); MyPrint::purple("theta'"); printf(".\n\n");

	MyPrint::cyan(">  The Schmidt decomposition of |pM> is determined by Eq. (103).\n");
	test.state[1].schmidt.print(); puts("\n");
	test.updateStatesFromSchDecoms();

	printf(">  To verify the formula given in Prop. 18 is correct, the `bool isPM()` function is used.\n\n");

	MyPrint::cyan(">  The two states reconstructed from the decompositions ");
	if (test.isPM()) MyPrint::yellow("form "); else MyPrint::red("do not form ");
	MyPrint::cyan("the PM-type orthonormal set.\n\n");

	printf(">  For reference,\n");
	printf("|Pm> : "); test.state[0].printInRow(); puts("");
	printf("|pM> : "); test.state[1].printInRow(); puts("");
}

void TestPaper::Proposition9() {
	MyPrint::green("\n********************************************** Test Proposition 9 (PPP) **********************************************\n\n");

	printf(">  We test Prop. 9 in the paper.  \n");
	printf(">  The `void becomePPP()` function generates three mutually orthogonal Schmidt decompositions based on Prop. 9.\n\n");
	
	MyPrint::cyan(">  Assume that the 1st product state |Ppp> has the Schmidt decomposition given in Eq. (50).\n");
	test.becomePPP();
	test.state[0].schmidt.print(); puts("\n");

	printf(">  The proposition provides explicit formulas for the Schmidt decompositions of two product states\n");
	printf("   that are orthogonal to the first.\n");
	printf(">  The Schmidt decompositions of these product states |pPp> and |ppP> are characterized\n");
	printf("   by an orthonormal basis of the qubit subsystem.\n\n");

	MyPrint::cyan(">  The Schmidt decomposition of |pPp> is determined by either Eq. (51) or Eq. (53).\n");
	test.state[1].schmidt.print(); puts("");
	MyPrint::cyan(">  Then the Schmidt decomposition of |ppP> is determined as\n");
	test.state[2].schmidt.print(); puts("\n");
	test.updateStatesFromSchDecoms();

	printf(">  To verify the formulas given in Prop. 9 is correct, the `bool isPPP()` function is used.\n\n");

	MyPrint::cyan(">  The three states reconstructed from the decompositions ");
	if (test.isPPP()) MyPrint::yellow("form "); else MyPrint::red("do not form ");
	MyPrint::cyan("the PPP-type orthonormal set.\n\n");

	printf(">  For reference,\n");
	printf("|Ppp> : "); test.state[0].printInRow(); puts("");
	printf("|pPp> : "); test.state[1].printInRow(); puts("");
	printf("|ppP> : "); test.state[2].printInRow(); puts("");
}

void TestPaper::Proposition10() {
	MyPrint::green("\n***************************************** Test Proposition 10 (PPE: Case 1) ******************************************\n\n");

	printf(">  We test Prop. 10 in the paper.  \n");
	printf(">  The `void becomePPE_Case1()` function generates three mutually orthogonal Schmidt decompositions based on Prop. 10.\n\n");

	MyPrint::cyan(">  Assume that the 1st product state |Ppe> has the Schmidt decomposition given in Eq. (59).\n");
	test.becomePPE_Case1();
	test.state[0].schmidt.print(); puts("");
	MyPrint::cyan(">  Assume that the 2nd product state |pPe> has the Schmidt decomposition given in Eq. (60).\n");
	test.state[1].schmidt.print(); puts("\n");

	printf(">  The proposition provides an explicit formula for the Schmidt decomposition of an entangled state |ppE>\n");
	printf("   that are orthogonal to the first two product states.\n");
	printf(">  The Schmidt decomposition of |ppE> is characterized by two nonzero complex numbers ");
	MyPrint::purple("c"); printf(" and "); MyPrint::purple("d"); printf(".\n\n");

	MyPrint::cyan(">  The Schmidt decomposition of |ppE> is determined by Eq. (63).\n");
	test.state[2].schmidt.print(); puts("\n");
	test.updateStatesFromSchDecoms();

	printf(">  To verify the formula given in Prop. 10 is correct, the `bool isPPE()` function is used.\n\n");

	MyPrint::cyan(">  The three states reconstructed from the decompositions ");
	if (test.isPPE()) MyPrint::yellow("form "); else MyPrint::red("do not form ");
	MyPrint::cyan("the PPE-type orthonormal set.\n\n");

	printf(">  For reference,\n");
	printf("|Ppe> : "); test.state[0].printInRow(); puts("");
	printf("|pPe> : "); test.state[1].printInRow(); puts("");
	printf("|ppE> : "); test.state[2].printInRow(); puts("");
}

void TestPaper::Proposition11() {
	MyPrint::green("\n***************************************** Test Proposition 11 (PPE: Case 2) ******************************************\n\n");

	printf(">  We test Prop. 11 in the paper.  \n");
	printf(">  The `void becomePPE_Case2()` function generates three mutually orthogonal Schmidt decompositions based on Prop. 11.\n\n");

	MyPrint::cyan(">  Assume that the 1st state |Ppe> has the Schmidt decomposition given in Eq. (59).\n");
	test.becomePPE_Case2();
	test.state[0].schmidt.print(); puts("");
	MyPrint::cyan(">  Assume that the 2nd state |pPe> has the Schmidt decomposition given in Eq. (61).\n");
	test.state[1].schmidt.print(); puts("\n");

	printf(">  The proposition provides an explicit formula for the Schmidt decomposition of an entangled state |ppE>\n");
	printf("   that are orthogonal to the first two product states.\n");
	printf(">  The Schmidt decomposition of |ppE> is characterized by two nonzero complex numbers ");
	MyPrint::purple("c"); printf(" and "); MyPrint::purple("d"); printf(".\n\n");

	MyPrint::cyan(">  The Schmidt decomposition of |ppE> is determined by Eqs. (65) and (66).\n");
	test.state[2].schmidt.print(); puts("\n");
	test.updateStatesFromSchDecoms();

	printf(">  To verify the formula given in Prop. 11 is correct, the `bool isPPE()` function is used.\n\n");

	MyPrint::cyan(">  The three states reconstructed from the decompositions ");
	if (test.isPPE()) MyPrint::yellow("form "); else MyPrint::red("do not form ");
	MyPrint::cyan("the PPE-type orthonormal set.\n\n");

	printf(">  For reference,\n");
	printf("|Ppe> : "); test.state[0].printInRow(); puts("");
	printf("|pPe> : "); test.state[1].printInRow(); puts("");
	printf("|ppE> : "); test.state[2].printInRow(); puts("");
}

void TestPaper::Proposition12() {
	MyPrint::green("\n***************************************** Test Proposition 12 (PPE: Case 3) ******************************************\n\n");

	printf(">  We test Prop. 12 in the paper.  \n");
	printf(">  The `void becomePPE_Case3()` function generates three mutually orthogonal Schmidt decompositions based on Prop. 12.\n\n");

	MyPrint::cyan(">  Assume that the 1st state |Ppe> has the Schmidt decomposition given in Eq. (59).\n");
	test.becomePPE_Case3();
	test.state[0].schmidt.print(); puts("");
	MyPrint::cyan(">  Assume that the 2nd state |pPe> has the Schmidt decomposition given in Eq. (62).\n");
	test.state[1].schmidt.print(); puts("\n");

	printf(">  The proposition provides an explicit formula for the Schmidt decomposition of an entangled state |ppE>\n");
	printf("   that are orthogonal to the first two product states.\n");
	printf(">  The Schmidt decomposition of |ppE> is characterized by two nonzero complex numbers ");
	MyPrint::purple("c"); printf(" and "); MyPrint::purple("d"); printf(".\n\n");

	MyPrint::cyan(">  The Schmidt decomposition of |ppE> is determined by Eqs. (69) and (70).\n");
	test.state[2].schmidt.print(); puts("\n");
	test.updateStatesFromSchDecoms();

	printf(">  To verify the formula given in Prop. 12 is correct, the `bool isPPE()` function is used.\n\n");

	MyPrint::cyan(">  The three states reconstructed from the decompositions ");
	if (test.isPPE()) MyPrint::yellow("form "); else MyPrint::red("do not form ");
	MyPrint::cyan("the PPE-type orthonormal set.\n\n");

	printf(">  For reference,\n");
	printf("|Ppe> : "); test.state[0].printInRow(); puts("");
	printf("|pPe> : "); test.state[1].printInRow(); puts("");
	printf("|ppE> : "); test.state[2].printInRow(); puts("");
}

void TestPaper::Theorem14() {
	MyPrint::green("\n*********************************************** Test Theorem 14 (PPPP) ***********************************************\n\n");

	printf(">  We test Thm. 14 in the paper.  \n");
	printf(">  The `void becomePPPP()` function generates four mutually orthogonal Schmidt decompositions based on Thm. 14.\n\n");

	MyPrint::cyan(">  Assume that the 1st state |Pppp> has the Schmidt decomposition given in Eq. (80).\n");
	test.becomePPPP();
	test.state[0].schmidt.print(); puts("\n");
	
	printf(">  The proposition provides explicit Schmidt decomposition formulas for the rest states.\n");
	printf(">  The Schmidt decompositions of them are characterized by an orthonormal basis for the qubit system.\n\n");

	MyPrint::cyan(">  The Schmidt decomposition of |pPpp> is determined by either Eq. (81) or Eq. (84).\n");
	test.state[1].schmidt.print(); puts("");
	MyPrint::cyan(">  Then the Schmidt decomposition of |ppPp> is determined as\n");
	test.state[2].schmidt.print(); puts("");
	MyPrint::cyan(">  The Schmidt decomposition of |pppP> is determined as\n");
	test.state[3].schmidt.print(); puts("\n");
	test.updateStatesFromSchDecoms();

	printf(">  To verify the formula given in Thm. 14 is correct, the `bool isPPPP()` function is used.\n\n");

	MyPrint::cyan(">  The four states reconstructed from the decompositions ");
	if (test.isPPPP()) MyPrint::yellow("form "); else MyPrint::red("do not form ");
	MyPrint::cyan("the PPPP-type orthonormal basis.\n\n");

	printf(">  For reference,\n");
	printf("|Pppp> : "); test.state[0].printInRow(); puts("");
	printf("|pPpp> : "); test.state[1].printInRow(); puts("");
	printf("|ppPp> : "); test.state[2].printInRow(); puts("");
	printf("|pppP> : "); test.state[3].printInRow(); puts("");
}

void TestPaper::Theorem15() {
	MyPrint::green("\n******************************************* Test Theorem 15 (PPEE: Case 1) *******************************************\n\n");

	printf(">  We test Thm. 15 in the paper.  \n");
	printf(">  The `void becomePPEE_Case1()` function generates four mutually orthogonal Schmidt decompositions based on Thm. 15.\n\n");

	MyPrint::cyan(">  Assume that the 1st product state |Ppee> has the Schmidt decomposition given in Eq. (88).\n");
	test.becomePPEE_Case1();
	test.state[0].schmidt.print(); puts("");
	MyPrint::cyan(">  Assume that the 2nd product state |pPee> has the Schmidt decomposition given in Eq. (89).\n");
	test.state[1].schmidt.print(); puts("\n");

	printf(">  The proposition provides explicit formulas for the Schmidt decompositions of two entangled states |ppEe> and |ppeE>.\n");
	printf(">  The Schmidt decompositions of |ppEe> and |ppeE> are characterized by two nonzero complex numbers ");
	MyPrint::purple("a"); printf(" and "); MyPrint::purple("b.\n\n");

	
	MyPrint::cyan(">  The Schmidt decomposition of |ppEe> is determined by Eq. (90).\n");
	test.state[2].schmidt.print(); puts("");
	MyPrint::cyan(">  The Schmidt decomposition of |ppeE> is determined by Eq. (91).\n");
	test.state[3].schmidt.print(); puts("\n");
	test.updateStatesFromSchDecoms();

	printf(">  To verify the formulas given in Thm. 15 is correct, the `bool isPPEE()` function is used.\n\n");

	MyPrint::cyan(">  The four states reconstructed from the decompositions ");
	if (test.isPPEE()) MyPrint::yellow("form "); else MyPrint::red("do not form ");
	MyPrint::cyan("the PPEE-type orthonormal basis.\n\n");

	printf(">  For reference,\n");
	printf("|Ppee> : "); test.state[0].printInRow(); puts("");
	printf("|pPee> : "); test.state[1].printInRow(); puts("");
	printf("|ppEe> : "); test.state[2].printInRow(); puts("");
	printf("|ppeE> : "); test.state[3].printInRow(); puts("");
}

void TestPaper::Theorem16() {
	MyPrint::green("\n******************************************* Test Theorem 16 (PPEE: Case 2) *******************************************\n\n");

	printf(">  We test Thm. 16 in the paper.  \n");
	printf(">  The `void becomePPEE_Case2()` function generates four mutually orthogonal Schmidt decompositions based on Thm. 16.\n\n");

	MyPrint::cyan(">  Assume that the 1st product state |Ppee> has the Schmidt decomposition given in Eq. (88).\n");
	test.becomePPEE_Case2();
	test.state[0].schmidt.print(); puts("\n");
	
	printf(">  The proposition provides explicit formulas for the Schmidt decompositions of the rest three states\n");
	printf("   |pPee>, |ppEe>, and |ppeE>.\n");
	printf(">  The Schmidt decompositions of them are characterized by two nonzero complex numbers ");
	MyPrint::purple("a"); printf(" and "); MyPrint::purple("b.\n\n");

	MyPrint::cyan(">  The Schmidt decomposition of |pPee> is determined by Eq. (93).\n");
	test.state[1].schmidt.print(); puts("");
	MyPrint::cyan(">  The Schmidt decomposition of |ppEe> is determined by Eq. (94).\n");
	test.state[2].schmidt.print(); puts("");
	MyPrint::cyan(">  The Schmidt decomposition of |ppeE> is determined by Eq. (95).\n");
	test.state[3].schmidt.print(); puts("\n");
	test.updateStatesFromSchDecoms();

	printf(">  To verify the formulas given in Thm. 16 is correct, the `bool isPPEE()` function is used.\n\n");

	MyPrint::cyan(">  The four states reconstructed from the decompositions ");
	if (test.isPPEE()) MyPrint::yellow("form "); else MyPrint::red("do not form ");
	MyPrint::cyan("the PPEE-type orthonormal basis.\n\n");

	printf(">  For reference,\n");
	printf("|Ppee> : "); test.state[0].printInRow(); puts("");
	printf("|pPee> : "); test.state[1].printInRow(); puts("");
	printf("|ppEe> : "); test.state[2].printInRow(); puts("");
	printf("|ppeE> : "); test.state[3].printInRow(); puts("");
}

void TestPaper::Theorem17() {
	MyPrint::green("\n******************************************* Test Theorem 17 (PPEE: Case 3) *******************************************\n\n");

	printf(">  We test Thm. 17 in the paper.  \n");
	printf(">  The `void becomePPEE_Case3()` function generates four mutually orthogonal Schmidt decompositions based on Thm. 17.\n\n");

	MyPrint::cyan(">  Assume that the 1st product state |Ppee> is given in Eq. (88).\n");
	test.becomePPEE_Case3();
	test.state[0].schmidt.print(); puts("\n");

	printf(">  The proposition provides explicit formulas for the Schmidt decompositions of the rest three states\n");
	printf("   |pPee>, |ppEe> and |ppeE>.\n");
	printf(">  The Schmidt decompositions of them are characterized by two nonzero complex numbers ");
	MyPrint::purple("a"); printf(" and "); MyPrint::purple("b.\n\n");

	MyPrint::cyan(">  The Schmidt decomposition of |pPee> is determined by Eq. (98).\n");
	test.state[1].schmidt.print(); puts("");
	MyPrint::cyan(">  The Schmidt decomposition of |ppEe> is determined by Eq. (99).\n");
	test.state[2].schmidt.print(); puts("");
	MyPrint::cyan(">  The Schmidt decomposition of |ppeE> is determined by Eq. (100).\n");
	test.state[3].schmidt.print(); puts("\n");
	test.updateStatesFromSchDecoms();

	printf(">  To verify the formulas given in Thm. 17 is correct, the `bool isPPEE()` function is used.\n\n");

	MyPrint::cyan(">  The four states reconstructed from the decompositions ");
	if (test.isPPEE()) MyPrint::yellow("form "); else MyPrint::red("do not form ");
	MyPrint::cyan("the PPEE-type orthonormal basis.\n\n");

	printf(">  For reference,\n");
	printf("|Ppee> : "); test.state[0].printInRow(); puts("");
	printf("|pPee> : "); test.state[1].printInRow(); puts("");
	printf("|ppEe> : "); test.state[2].printInRow(); puts("");
	printf("|ppeE> : "); test.state[3].printInRow(); puts("");
}

void TestPaper::Theorem19() {
	MyPrint::green("\n*********************************************** Test Theorem 19 (PMEE) ***********************************************\n\n");

	printf(">  We test Thm. 19 in the paper.  \n");
	printf(">  The `void becomePMEE()` function generates four mutually orthogonal Schmidt decompositions based on Thm. 19.\n\n");

	MyPrint::cyan(">  Assume that a product state |Pmee> is given in Eq. (105).\n");
	test.becomePMEE();
	test.state[0].schmidt.print(); puts("");
	MyPrint::cyan(">  Assume that the maximally entangled state |pMee> is given in Eq. (106).\n");
	test.state[1].schmidt.print(); puts("\n");

	printf(">  The proposition provides explicit formulas for the Schmidt decompositions of the rest entangled states\n");
	printf("   |pmEe> and |pmeE>.\n");
	printf(">  The Schmidt decompositions of them are characterized by one real number "); MyPrint::purple("theta''"); printf(" and ");
	printf("one complex number "); MyPrint::purple("c.\n\n");
	MyPrint::cyan(">  The Schmidt decomposition of |pmEe> is determined by Eq. (107).\n");
	test.state[2].schmidt.print(); puts("");
	MyPrint::cyan(">  The Schmidt decomposition of |pmeE> is determined by Eq. (108).\n");
	test.state[3].schmidt.print(); puts("\n");
	test.updateStatesFromSchDecoms();

	printf(">  To verify the formulas given in Thm. 19 is correct, the `bool isPMEE()` function is used.\n\n");

	MyPrint::cyan(">  The four states reconstructed from the decompositions ");
	if (test.isPMEE()) MyPrint::yellow("form "); else MyPrint::red("do not form ");
	MyPrint::cyan("the PMEE-type orthonormal basis.\n\n");

	printf(">  For reference,\n");
	printf("|Pmee> : "); test.state[0].printInRow(); puts("");
	printf("|pMee> : "); test.state[1].printInRow(); puts("");
	printf("|pmEe> : "); test.state[2].printInRow(); puts("");
	printf("|pmeE> : "); test.state[3].printInRow(); puts("");
}

void TestPaper::Theorem20() {
	MyPrint::green("\n****************************************** Test Theorem 20 (MMEE: Diagonal) ******************************************\n\n");

	printf(">  We test Thm. 20 in the paper.  \n");
	printf(">  The `void becomeMMEE_Diagonal()` function generates four mutually orthogonal Schmidt decompositions based on Thm. 20.\n\n");

	MyPrint::cyan(">  Assume that the 1st maximally entangled state |Mmee> is given in Eq. (115).\n");
	test.becomeMMEE_Diagonal();
	test.state[0].schmidt.print(); puts("");
	MyPrint::cyan(">  Assume that the 2nd maximally entangled state |mMee> is given in Eq. (116).\n");
	test.state[1].schmidt.print(); puts("\n");

	printf(">  The Thm. 20 provides explicit formulas for the Schmidt decompositions of\n");
	printf("   the rest entangled and "); MyPrint::red("diagonal"); printf(" states |mmEe> and |mmeE>.\n");
	printf(">  The Schmidt decompositions of them are characterized\n");
	printf("   by two complex numbers "); MyPrint::purple("a"); printf(" and "); MyPrint::purple("b"); printf(" satisfying Eqs. (117), (118), and (119).\n\n");

	MyPrint::cyan(">  The Schmidt decomposition of |mmEe> is determined by Eq. (120).\n");
	test.state[2].schmidt.print(); puts("");
	MyPrint::cyan(">  The Schmidt decomposition of |mmeE> is determined by Eq. (121).\n");
	test.state[3].schmidt.print(); puts("\n");
	test.updateStatesFromSchDecoms();

	printf(">  To verify the formulas given in Thm. 20 is correct, the `bool isMMEE_Diagonal()` function is used.\n\n");

	MyPrint::cyan(">  The four states reconstructed from the decompositions ");
	if (test.isMMEE_Diagonal()) MyPrint::yellow("form "); else MyPrint::red("do not form ");
	MyPrint::cyan("the MMEE-type orthonormal basis whose the last two states are ");
	MyPrint::red("diagonal"); MyPrint::cyan(".\n\n");

	printf(">  For reference,\n");
	printf("|mmee> : "); test.state[0].printInRow(); puts("");
	printf("|mMee> : "); test.state[1].printInRow(); puts("");
	printf("|mmEe> : "); test.state[2].printInRow(); puts("");
	printf("|mmeE> : "); test.state[3].printInRow(); puts("");
}

void TestPaper::Theorem21() {
	MyPrint::green("\n**************************************** Test Theorem 21 (MMEE: Non-Diagonal) ****************************************\n\n");

	printf(">  We test Thm. 21 in the paper.  \n");
	printf(">  The `void becomeMMEE_NonDiagonal()` function generates four mutually orthogonal Schmidt decompositions based on Thm. 21.\n\n");

	MyPrint::cyan(">  Assume that the 1st maximally entangled state |Mmee> is given in Eq. (115).\n");
	test.becomeMMEE_NonDiagonal();
	test.state[0].schmidt.print(); puts("");
	MyPrint::cyan(">  Assume that the 2nd maximally entangled state |mMee> is given in Eq. (116).\n");
	test.state[1].schmidt.print(); puts("\n");

	printf(">  The Thm. 20 provides explicit formulas for the Schmidt decompositions of\n");
	printf("   the rest entangled and "); MyPrint::red("non-diagonal"); printf(" states |mmEe> and |mmeE>.\n");
	printf(">  The Schmidt decompositions of them are characterized\n");
	printf("   by two complex numbers "); MyPrint::purple("a"); printf(" and "); MyPrint::purple("b"); printf(" satisfying Eqs. (117) and (118), not satisfying Eq. (119).\n\n");

	MyPrint::cyan(">  The Schmidt decomposition of |mmEe> is determined by Eq. (124).\n");
	test.state[2].schmidt.print(); puts("");
	MyPrint::cyan(">  The Schmidt decomposition of |mmeE> is determined by Eq. (125).\n");
	test.state[3].schmidt.print(); puts("\n");
	test.updateStatesFromSchDecoms();

	printf(">  To verify the formulas given in Thm. 21 is correct, the `bool isMMEE_NonDiagonal()` function is used.\n\n");

	MyPrint::cyan(">  The four states reconstructed from the decompositions ");
	if (test.isMMEE_NonDiagonal()) MyPrint::yellow("form "); else MyPrint::red("do not form ");
	MyPrint::cyan("the MMEE-type orthonormal basis whose the last two states are ");
	MyPrint::red("non-diagonal"); MyPrint::cyan(".\n\n");

	printf(">  For reference,\n");
	printf("|mmee> : "); test.state[0].printInRow(); puts("");
	printf("|mMee> : "); test.state[1].printInRow(); puts("");
	printf("|mmEe> : "); test.state[2].printInRow(); puts("");
	printf("|mmeE> : "); test.state[3].printInRow(); puts("");
}
