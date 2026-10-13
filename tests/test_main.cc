#include "Phase0/01_template_basics/template_exercises.hpp"
#include <iostream>
#include <string>


int main(){
    
    Pair P1{"vegetable", 19};
    std::cout << "name is: "<< P1.getFist() << std::endl;
    std::cout << "value is: "<< P1.getSecond() << std::endl;

    return 0;
}