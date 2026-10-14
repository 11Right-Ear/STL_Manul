#include "Phase0/01_template_basics/template_exercises.hpp"
#include <iostream>
#include <string>


int main(){
    
    Pair P1{"vegetable", 19};
    int i = 1;
    SHOW(i);
    // std::cout << "name is: "<< P1.getFist() << std::endl;
    // std::cout << "value is: "<< P1.getSecond() << std::endl;
    SHOW(P1);
    // Pair P2 = P1;
    // P2.setFirst("apple");
    // P2.setSecond(100);
    // std::cout << "P2name is: "<< P2.getFist() << std::endl;
    // std::cout << "P2value is: "<< P2.getSecond() << std::endl;
    // swap(P1,P2);
    // // if(P1 > P2){
    // //     std::cout << "大于" << std::endl;
    // //     return 0;
    // // }
    // std::cout << "P1:name is: "<< P1.getFist() << std::endl;
    // std::cout << "P1value is: "<< P1.getSecond() << std::endl;
    // std::cout << "P2name is: "<< P2.getFist() << std::endl;
    // std::cout << "P2value is: "<< P2.getSecond() << std::endl;
    return 0;
}