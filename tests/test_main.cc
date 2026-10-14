#include "Phase0/01_template_basics/template_exercises.hpp"
#include <iostream>
#include <string>


int main(){
    Myptr<int> m1 = new int(42);
    SHOW(m1.GetType());
    SHOW(*m1);
    return 0;
}