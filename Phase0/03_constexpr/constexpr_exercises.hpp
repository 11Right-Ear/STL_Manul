/*
 * ============================================================================
 * Phase 0 - constexpr 练习
 * ============================================================================
 * 
 * 本文件包含 constexpr 编程的各种练习。使用 // 你的代码: 注释标注每个需要完成的部分。
 * 不要删除任何注释，只在注释下方编写你的代码。
 * 
 * 学习目标:
 *   1. 掌握 constexpr 变量的声明和使用
 *   2. 掌握 constexpr 函数的概念和实现（C++14/17/20 规则变化）
 *   3. 掌握 constexpr lambda 的用法
 *   4. 理解 constexpr if 的编译期分支控制
 *   5. 理解 constexpr 容器（std::array）的作用
 *   6. 理解编译期计算的优势和应用场景
 * 
 * 建议完成顺序:
 *   1. 先完成 constexpr 变量练习
 *   2. 然后完成 constexpr 函数练习（C++14 规则）
 *   3. 接着完成 constexpr lambda 练习
 *   4. 再完成 constexpr if 练习
 *   5. 最后完成 constexpr 容器和编译期计算练习
 * 
 * C++ 标准版本说明:
 *   - C++11: constexpr 函数只能包含一条返回语句
 *   - C++14: 放宽限制，constexpr 函数可以包含更多语句
 *   - C++17: 允许 constexpr 静态成员变量
 *   - C++20: 允许 constexpr virtual 函数、try-catch、动态内存分配等
 * 
 * ============================================================================
 */

#ifndef CONSTEXPR_EXERCISES_HPP
#define CONSTEXPR_EXERCISES_HPP

#include <iostream>
#include <array>
#include <string>
#include <type_traits>
#include <vector>

#define ENTER '\n';
#define SHOW(x) std::cout << x 
#define SHOWE(x) std::cout << x << '\n'
#define PUTIN(x) std::cin >> x 
#define SPACE "    "

// ============================================================================
// 第一部分: constexpr 变量 (constexpr Variable)
// ============================================================================
// 
// constexpr 用于声明编译期常量，其值必须在编译期确定。
// 语法: constexpr type name = value;
// 
// constexpr vs const:
//   - const: 运行时常量或编译期常量均可
//   - constexpr: 必须是编译期常量
// 
// 练习 1.1: 声明各种 constexpr 变量
// 
// 提示: 
//   - 基本类型可以直接使用 constexpr
//   - 使用 constexpr 确保计算在编译期完成
//   - 浮点类型也可以是 constexpr
// 
// 你的代码:
constexpr int a = 10;
constexpr double b = 3.14;
constexpr float c = 7.12121;
// 涉及动态内存分配 只被c++20支持
// constexpr std::string s1 = "Hello";
const int a1 = 0;
const double b1 = 0;
const std::string s2 = "Hello";



// 练习 1.2: 使用 constexpr 定义编译期常量数组的大小
// 
// 提示:
//   - 数组大小必须是编译期常量
//   - constexpr 变量可以用作数组维度
// 
// 你的代码:
constexpr int a3 = 90;
int arr[a3] = {0};
std::array<int ,a3> arr1 = {0};


// ============================================================================
// 第二部分: constexpr 函数 (constexpr Function)
// ============================================================================
//
// constexpr 函数可以在编译期求值，也可以在运行时调用。
// C++14 之后，constexpr 函数的限制大大放宽。
//
// 练习 2.1: 实现一个 constexpr 函数，计算平方
// 
// 提示:
//   - C++14 起，constexpr 函数可以包含多条语句
//   - 函数体应该简洁，逻辑清晰
// 
// 你的代码:
constexpr double squr(const double& x){
    double results = 0;
    results = x * x;

    return results;
}


// 练习 2.2: 实现一个 constexpr 函数，计算阶乘
// 
// 提示:
//   - 可以使用递归或迭代实现
//   - C++14 支持循环语句
//   - 考虑使用递归实现更简洁
// 
// 你的代码:
//递归
constexpr int stepmuti(const int& x){
   if(x == 1){
    return 1;
   } 
   else if(x == 2){
    return 2 * 1;
   }
   return x * stepmuti(x - 1);
}
//迭代
constexpr int Nstepmumi(const int& x){
    int result = 1;
    for(int i = 2; i <= x; i++){
        // result = i * (i -  1);
        result *= i;
        SHOW("当前循环次是： ") << i << ENTER
        SHOW("当前值是： ") << result << ENTER
    }
    return result;
}


// 练习 2.3: 实现一个 constexpr 函数，判断是否为质数
// 
// 提示:
//   - 质数定义：大于1的自然数，除了1和它自身外不能被其他自然数整除
//   - 可以使用简单的试除法
//   - constexpr 函数可以在编译期用于数组大小等场景
// 
// 你的代码:
constexpr bool is_prime_number(const int& x){
    if(x == 1){
        return false;
    } 
    //除完发现只用1,x 则 ture 否则 false
    int z = 0;
    for(int i = x; i > 0; i--){
        SHOW("打印次数为： ") << i << ENTER
        if(!(x % i)){
            int arr[3] = {0};
            if(z < 3){
            arr[z] = 1;
            }
            SHOW("第") << i; 
            SHOW("次能被整除") << ENTER
            z++;
            SHOW("z是: ") << z << ENTER
            if(i == 1 && z == 2){ return true;}
        }
    }
    return false;
}


// 练习 2.4: 实现一个 constexpr 函数，计算斐波那契数列第 N 项
// 
// 提示:
//   - 斐波那契数列: F(0)=0, F(1)=1, F(n)=F(n-1)+F(n-2)
//   - 可以使用递归或迭代
//   - 递归版本更简洁
// 
// 你的代码:
// constexpr int Fabolaqi(const int& x){
constexpr int Fabolaqi(const int& x){
    // SHOW("数数我") << ENTER;
    // if(x == 0){SHOW("this is 0") << ENTER; return 0; }
    // if(x == 1){SHOW("this is 1") << ENTER; return 1; }
    if(x == 0){return 0; }
    if(x == 1){return 1; }
    int result = 0;
    //1. 3这个值就等于 Fabolaqi(3 - 1 = 2) + Fabolaqi(3 - 2 = 1)
    //2. 2这个值就等于 Fabolaqi(2 - 1 = 1) + Fabolaqi(2 - 2 = 0);
    //3. 因为1 = 1， 0 = 0所以至此可以得到结果
    //4. 它是递归到了2 从2 开始返回值
    result = Fabolaqi(x - 1) + Fabolaqi(x - 2);

    return result;
}


// ============================================================================
// 第三部分: constexpr Lambda (constexpr Lambda)
// ============================================================================
//
// C++17 引入了 constexpr lambda，可以在编译期计算 lambda 表达式的值。
// 语法: auto lambda = [](auto x) constexpr { return x * x; };
//
// 练习 3.1: 创建一个 constexpr lambda，计算两数之和
// 
// 提示:
//   - C++17 起，lambda 默认是 constexpr（如果满足条件）
//   - lambda 的捕获不能用于 constexpr，除非使用泛 lambda
//   - 使用 auto 声明参数类型
// 
// 你的代码:
auto lambda = [](auto& x, auto& y) constexpr {return x + y;};



// 练习 3.2: 创建一个 constexpr lambda，用于判断是否为偶数
// 
// 提示:
//   - 使用取模运算符 %
//   - 偶数判断: n % 2 == 0
// 
// 你的代码:
auto is_evennumber = [](int& x) constexpr { return (x % 2 == 0);};



// 练习 3.3: 使用 constexpr lambda 和 std::invoke (C++17)
// 
// 提示:
//   - std::invoke 可以调用可调用对象
//   - constexpr lambda 可以在编译期通过 std::invoke 调用
// 
// 你的代码:




// ============================================================================
// 第四部分: constexpr if (constexpr if)
// ============================================================================
//
// constexpr if 是 C++17 引入的编译期条件语句。
// 语法: if constexpr (condition) { ... } else { ... }
// 
// 特点:
//   - condition 必须是编译期可确定的常量表达式
//   - 不满足条件的分支不会被编译（也被称为 "庙式 if"）
//   - 可以用于模板代码的类型分支
//
// 练习 4.1: 使用 constexpr if 实现类型选择器
// 
// 提示:
//   - 根据条件在编译期选择不同的返回类型
//   - T 可以是不同类型
// 你的代码:
// int double string  通过constexpr 去选择不同的类型在编译器就直接执行
template <typename T>
auto type_selector(const T& x){
    //根据T 不同做处理 第一个是 int ,double ,string;
    if constexpr (std::is_same<T, int>::value){
        SHOW("i am int value") << ENTER;
    }
    if constexpr (std::is_same<T, double>::value){
        SHOW("i am double value") << ENTER;
    }
    if constexpr (std::is_same<T, std::string>::value){
        SHOW("i am string value") << ENTER;
    }
    return "unknow type";

} 



// 练习 4.2: 使用 constexpr if 实现编译期类型检测
// 
// 提示:
//   - 检测类型是否为整数类型
//   - 使用 std::is_integral
//   - 在编译期分支中选择不同的处理方式
// 
// 你的代码:
template <typename T>
void is_integral1(T value){
    if constexpr 
    (std::is_integral<T>::value){
        SHOWE("porecess intergral");
    }else{
        SHOWE("process non-intergral");
    }
    //居然需要末尾换行 --> 宏没有换行或刷新
}

// 练习 4.3: 使用 constexpr if 实现递归终止
// 
// 提示:
//   - 在模板递归中，constexpr if 可以替代 SFINAE
//   - 更清晰的代码结构
// 
// 你的代码:
template <typename T, std::size_t N, std::size_t... Is>
T recursion_s_impl(const T (&arr)[N], std::index_sequence<Is...>) {
    if constexpr (N == 0) return T{};
    T result = T{};
    ((result += arr[Is]), ...);
    return result;
}

template <typename T, std::size_t N>
T recursion_s(const T (&arr)[N]) {
    return recursion_s_impl(arr, std::make_index_sequence<N>{});
}



// ============================================================================
// 第五部分: constexpr 容器 (constexpr Container)
// ============================================================================
//
// C++20 引入了 constexpr std::vector 等容器。
// C++11/14/17 中，可以使用 std::array 作为 constexpr 容器。
//
// 练习 5.1: 创建并使用 constexpr std::array
// 
// 提示:
//   - std::array 是固定大小的数组容器
//   - 可以使用 std::array<int, N> 声明编译期数组
//   - 可以用聚合初始化或 std::array 的 make_array 创建
// 
// 你的代码:
void creatarr(){
    constexpr std::array<int, 2> arr = {1, 2};
}


// 练习 5.2: 实现一个 constexpr 函数，对数组进行排序
// 
// 提示:
//   - C++20 支持 constexpr 排序（C++14/17 不支持）
//   - C++14/17 可以实现简单的排序算法（如冒泡排序）
//   - 注意数组大小必须是编译期常量
// 
// 你的代码:
// 冒泡排序： 从左往右一次找最大
template <typename T, std::size_t N>
constexpr std::size_t array_size(T (&)[N]){return N;}

template <typename T, std::size_t N>
void sort_1(T (&x)[N]) {
    int z = array_size(x) - 1;
    for(int i = 0; i < z; i++){
        SHOW("第： "); SHOWE(i);
        for(int j = i + 1; j <= z; ++j){
            // i 不动了 j 动
            SHOW("x[i]"); SHOWE(x[i]);
            SHOW("x[j]"); SHOWE(x[j]);
            if(x[i] > x[j]){
                SHOW("将： "); SHOW(x[i]); SHOW("与： "); SHOW(x[j]); SHOWE("交换");
                
                std::swap(x[i],x[j]);
            }
        }
    }

}

// ============================================================================
// 第六部分: 编译期计算 (Compile-time Computation)
// ============================================================================
//
// constexpr 的主要优势是可以在编译期完成计算，减少运行时开销。
// 典型应用：查表表生成、配置验证、类型计算等。
//
// 练习 6.1: 使用编译期计算生成素数表
// 
// 提示:
//   - 利用前面的 is_prime 函数
//   - 将素数存储在 constexpr std::array 中
//   - 编译期计算可以用于静态断言验证
// 
// 你的代码:
constexpr auto prime_table = []{
    std::array<int, 25> arr{};
    int idx = 0;
    for(int i = 2; i <= 100 && idx < 25; ++i){
        if(is_evennumber( i)) arr[idx++] = i;
    }
    return arr;
}();


// 练习 6.2: 使用编译期计算验证数据约束
// 
// 提示:
//   - 假设有某些编译期已知的常量
//   - 使用 static_assert 验证这些常量满足某些条件
//   - 例如：数组大小必须是正数，某个配置值必须在有效范围内
// 
// 你的代码:



// 练习 6.3: 实现一个编译期字符串哈希函数
// j
// 提示:
//   - 简单的哈希算法：如 ELF hash 或 DJB2
//   - 使用 constexpr 函数计算字符串的哈希值
//   - 可以用于编译期字符串字面量的比较
// 
// 你的代码:



// ============================================================================
// 第七部分: C++20 constexpr 扩展 (C++20 Extensions)
// ============================================================================
//
// C++20 大幅扩展了 constexpr 的能力：
//   - 允许 dynamic_cast、typeid
//   - 允许 try-catch
//   - 允许 virtual 函数
//   - 允许 new/delete
//   - 允许 std::vector 等容器
//
// 练习 7.1: 使用 constexpr new/delete (C++20)
// 
// 提示:
//   - C++20 允许在 constexpr 上下文中使用动态内存分配
//   - 注意资源管理，考虑使用 RAII 或手动释放
// 
// 你的代码:



// 练习 7.2: 使用 constexpr std::array 和 std::span (C++20)
// 
// 提示:
//   - std::span 提供数组的视图
//   - 可以用于编写泛型代码
//   - 注意：std::span 本身 C++20 才支持 constexpr
// 
// 你的代码:



// ============================================================================
// 验证清单
// ============================================================================
//
// 完成以上所有练习后，确保你能够:
// 
// [ ] 理解 constexpr 变量的声明和使用场景
// [ ] 理解 constexpr 函数与普通函数的区别
// [ ] 理解 C++14 与 C++11 constexpr 规则的差异
// [ ] 理解 C++17 constexpr lambda 的用法
// [ ] 理解 constexpr if 的编译期分支特性
// [ ] 理解 constexpr 容器（std::array）的限制和优势
// [ ] 理解编译期计算的意义和典型应用
// [ ] 了解 C++20 对 constexpr 的重大扩展
// 
// 编译验证命令（C++17）:
//   g++ -std=c++17 -Wall -Wextra -c constexpr_exercises.hpp
// 
// 编译验证命令（C++20）:
//   g++ -std=c++20 -Wall -Wextra -c constexpr_exercises.hpp
// 
// 运行验证（创建测试文件后）:
//   g++ -std=c++20 -Wall -Wextra test_constexpr.cpp -o test && ./test
//
// ============================================================================

#endif
