#define _CRT_SECURE_NO_WARNINGS //disabling warnings caused by using "unsafe" functions

#include "myFileSys.h"
#include <iostream>


int main()
{
    myFileSys* ff = new myFileSys;
    ff->update(); //Obtaining the data from the existing txt files
    ff->main_menu();
    std::cout << "Thank you for using our program. Bye-bye!" << std::endl;
    delete ff;
    return 0;
}
