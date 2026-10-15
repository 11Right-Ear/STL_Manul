// #include "Phase0/01_template_basics/template_exercises.hpp"
#include "Phase0/02_type_deduction/type_deduction_exercises.hpp"
#include <array>

void x(){
    SHOW("this is a funcation");
}

int main(){
    // int x = 1;
    // wrapper(x);
    // wrapper(42);
    // wrapperevery(1,"what",x);
    // int y = 50;
    // process1(y);
    // double z = 1.31;
    // process1(z);
static_assert(std::is_same<TypeSelector<true, int, double>::type, int>::value, "");
static_assert(std::is_same<TypeSelector<false, int, double>::type, double>::value, "");
    return 0;
}