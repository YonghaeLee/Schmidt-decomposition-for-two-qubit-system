#ifndef MYCOLOR_H
#define MYCOLOR_H

#include <complex>
#include <complex>
#include <iostream>

//===================//
//  print functions  //
//===================//

class MyPrint {
public:

    //----------------------
    // press enter
    //----------------------
    static void pressEnter();

    //----------------------
    // print real and complex
    //----------------------
    static void printReal(const double r);
    static void printComplex(const std::complex<double>& c);

    //----------------------
    // color text functions
    //----------------------
    static void black( const std::string& text);    // print text in black   
    static void red   (const std::string& text);    // print text in red   
    static void green (const std::string& text);    // print text in green 
    static void yellow(const std::string& text);    // print text in yellow
    static void blue  (const std::string& text);    // print text in blue  
    static void purple(const std::string& text);    // print text in purple
    static void cyan  (const std::string& text);    // print text in cyan  
};

#endif // MYCOLOR_H