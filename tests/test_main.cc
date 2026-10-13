#include "Phase0/01_template_basics/template_exercises.hpp"
#include <iostream>


int main(){
    // std::cout << "show someting" << std::endl;
    // std::cout << "PI: " << pi<double> << std::endl;
    // std::cout << "please putin numbers: "<< std::endl;
    // std::cin >> a >> b;
    // std::cout << "max is: " << std::max(a, b) << std::endl;
    // double  c = 0, d = 0;
    // std::cin >> c >> d;
    // std::cout << "max is: " << std::max(c, d) << std::endl;
    // float e = 0, f = 0;
    // std::cin >> e >> f;
    // std::cout << "max is: " << std::max(e, f) << std::endl;
    // 用一个 for 循环将其括起来 输入值判断，然后输出max 
    
    for(int i = 0; i < 3; i++){
        // std::cout << "please input numbers" << std::endl;
        // 问题是这个 a, b 怎么实现声明存储类型？
        // 读取的时候用模板！！！
        // 这里必须传入实参
        readtype<int>();
    }
    return 0;
}