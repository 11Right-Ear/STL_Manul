#include "Phase0/01_template_basics/template_exercises.hpp"
#include <iostream>
#include <string>


int main(){
    // auto p1 = make_unique_ptr<int>(32);
    // SHOW(*p1) << ENTER;
    // auto p2 = make_unique_ptr<std::string>("intellengence");
    // SHOW(*p2);
    Pair<double, double> p1(1.31, 3.13);
    SHOW(p1);
    Pair<int, int> p2(p1);
    SHOW(p2);


    return 0;
}