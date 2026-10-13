#include "Phase0/01_template_basics/template_exercises.hpp"
#include <iostream>


int main(){
    
    int a, b;
    std::cout << "a is: " << std::endl;
    std::cin >> a;
    std::cout << "b is: " << std::endl;
    std::cin >> b;
    int* a_pr = &a;
    int* b_pr = &b;
    std::cout << "a is: " << &a << std::endl;
    std::cout << "b is: " << &b << std::endl;
    swap(a_pr, b_pr);
    std::cout << "point life has died" << std::endl;
    std::cout << "a_pr is: " << *a_pr << std::endl;
    std::cout << "b_pr is: " << *b_pr << std::endl;
    return 0;
}