// #include "Phase0/01_template_basics/template_exercises.hpp"
// #include "Phase0/02_type_deduction/type_deduction_exercises.hpp"
#include "Phase0/03_constexpr/constexpr_exercises.hpp"
#include <array>


int main(){

    // int arr[5] = {9,5,2,6,7};
    int arr[4] = {5,1,4,2};
    sort_1(arr);
    for(int i = 0; i < 4; i++){
        SHOWE(arr[i]);
    }
    return 0;
}