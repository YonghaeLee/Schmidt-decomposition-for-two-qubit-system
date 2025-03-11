#include "MyPrint.h"

void MyPrint::pressEnter() {
	yellow("\n---------------------------------------------------- Press Enter! ----------------------------------------------------");
	std::cin.get();
}

void MyPrint::printReal(const double r) {
	printf("\033[0;33m");
	if (r == 0.) {
		printf("\033[0m"); 
		printf("%-+7d", 0);
	}
	else if (r ==  1.) printf("%-+7d", 1);
	else if (r == -1.) printf("%-7d", -1);
	else               printf("%+6.4f", r);
	printf("\033[0m");
}

void MyPrint::printComplex(const std::complex<double>& c) {
	printf("\033[0;33m");
	if (c.real() == 0. && c.imag() == 0.) {
		printf("\033[0m");
		printf("%-+7d ", 0); printf("\033[0;30m"); printf("%-+7di", 0); printf("\033[0;33m");
	}
	else if (c.real() == 0. && c.imag() != 0.) {
		printf("\033[0;30m"); printf("%-+7d ", 0); printf("\033[0;33m"); printReal(c.imag()); printf("\033[0;33m");  printf("i");
	}
	else if (c.real() != 0. && c.imag() == 0.) {
		printReal(c.real()); printf(" "); printf("\033[0;30m"); printf("%-+7di", 0); printf("\033[0;33m");
	}
	else
		printf("%+6.4f %+6.4fi", c.real(), c.imag());
	printf("\033[0m");
}
// "%+6.4f %+6.4fi"



void MyPrint::black(const std::string& text) { printf("\033[0;30m"); std::cout << text; printf("\033[0m"); }
void MyPrint::red(const std::string& text) { printf("\033[0;31m"); std::cout << text; printf("\033[0m"); }
void MyPrint::green(const std::string& text) { printf("\033[0;32m"); std::cout << text; printf("\033[0m"); }
void MyPrint::yellow(const std::string& text) { printf("\033[0;33m"); std::cout << text; printf("\033[0m"); }
void MyPrint::blue(const std::string& text) { printf("\033[0;34m"); std::cout << text; printf("\033[0m"); }
void MyPrint::purple(const std::string& text) { printf("\033[0;35m"); std::cout << text; printf("\033[0m"); }
void MyPrint::cyan(const std::string& text) { printf("\033[0;36m"); std::cout << text; printf("\033[0m"); }

