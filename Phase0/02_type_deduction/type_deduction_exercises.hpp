/*
 * ============================================================================
 * Phase 0 - 类型推导练习
 * ============================================================================
 * 
 * 本文件包含 C++ 类型推导的各种练习。使用 // 注释标注每个需要完成的部分。
 * 不要删除任何注释，只在注释下方编写你的代码。
 * 
 * 学习目标:
 *   1. 掌握 auto 的类型推导规则
 *   2. 掌握 decltype 的用法和推导规则
 *   3. 理解函数模板的参数推导机制
 *   4. 理解引用折叠和完美转发
 *   5. 理解 std::decay、std::enable_if 等类型特性
 * 
 * 建议完成顺序:
 *   1. 先完成 auto 推导练习
 *   2. 然后完成 decltype 练习
 *   3. 接着完成模板参数推导练习
 *   4. 最后完成类型特性相关练习
 * 
 * ============================================================================
 */

#ifndef TYPE_DEDUCTION_EXERCISES_HPP
#define TYPE_DEDUCTION_EXERCISES_HPP

#include <iostream>
#include <type_traits>
#include <vector>
#include <memory>

#define ENTER '\n'
#define SHOW(x) std::cout << x << ENTER
#define PUTIN(x) std::cin >> x  
#define SPACE "    "

// ============================================================================
// 第一部分: auto 类型推导 (auto Type Deduction)
// ============================================================================
// 
// auto 的类型推导规则与模板推导类似，但有一些重要区别：
//   - auto 总是将引用类型的初始值推导为值类型（除非使用 auto& 或 auto&&）
//   - auto 会忽略顶层 const 和 volatile，保留底层 const
//   - 使用 auto&& 可以保持原始引用语义
//
// 练习 1.1: 理解 auto 推导基本规则
// 
// 提示: 
//   - 查看 typeid(x).name() 可以看到推导后的类型
//   - 使用 std::is_same<T, U> 判断类型是否相同
//   - 使用 std::remove_reference 等类型特性查看实际类型
// 
// 你的代码:
void DistinguishAutoType(){
    int x = 42;
    const int cx = 42;
    int& ref = x;
    const int& cref = x;
    auto a = x;    // int
    auto b = cx;   // int(const 被丢弃)
    auto c = ref;  // int(引用被丢弃)
    auto d = cref; // int(const 和引用都被丢弃)
    //显示了数据类型名？
    SHOW(typeid(a).name());
    SHOW(typeid(b).name());
    SHOW(typeid(c).name());
    SHOW(typeid(d).name());
    //编译时断言，如果条件为true 静默通过，为false报错
    static_assert(std::is_same<decltype(a), int>::value, "?");
    static_assert(std::is_same<decltype(b), int>::value, "?");
    static_assert(std::is_same<decltype(c), int>::value, "?");
    static_assert(std::is_same<decltype(d), int>::value, "?");
    //看底层类型 std::remove_fererence std::remove_cv
    SHOW(typeid(std::remove_reference_t<decltype(ref)>).name());
    SHOW(typeid(std::remove_cv_t<const int>).name()); 
    SHOW("我走到了这一步");
}



// 练习 1.2: auto 与引用
// 
// 提示:
//   - auto& 保留引用语义
//   - auto&& 可以绑定左值或右值（转发引用）
//   - auto 本身会丢弃引用
// 
// 你的代码:
void DistinguishAutoType2(){
    int x = 42;
    const int cx = 42;
    auto a1 = x;
    auto& a2 = x;
    auto&& a3 = x;
    auto b1 = cx;
    auto& b2 = cx;
    auto&& b3 = cx;
    //显示了数据类型名？
    SHOW(typeid(a1).name());
    SHOW(typeid(a2).name());
    SHOW(typeid(a3).name());
    SHOW(typeid(b1).name());
    SHOW(typeid(b2).name());
    SHOW(typeid(b3).name());
    //编译时断言，如果条件为true 静默通过，为false报错
    static_assert(std::is_same<decltype(a1), int>::value, "?");
    static_assert(std::is_same<decltype(a2), int&>::value, "?");
    static_assert(std::is_same<decltype(a3), int&>::value, "?");
    static_assert(std::is_same<decltype(b1), int>::value, "?");
    static_assert(std::is_same<decltype(b2), const int&>::value, "?");
    static_assert(std::is_same<decltype(b3), const int&>::value, "?");
    //测试右值绑定
    auto&& c1 = 42;
    SHOW(typeid(c1).name());
    static_assert(std::is_same<decltype(c1), int&&>::value, "?");
    SHOW("我走到了这一步");
}




// ============================================================================
// 第二部分: decltype 类型推导 (decltype Type Deduction)
// ============================================================================
// 
// decltype 可以查询表达式或名字的类型：
//   - decltype(name) 返回命名实体类型
//   - decltype(expr) 返回表达式类型（保留左值性）
//   - decltype(auto) (C++14) 推导规则同 auto 但保留引用
//
// 练习 2.1: 使用 decltype 获取变量类型
// 
// 提示:
//   - decltype 可以用于任何有名字的实体
//   - 可以用于模板参数推导
// 
// 你的代码:
void Decltype(){
    int x = 42;
    const int cx = 32;
    int& ref = x;
    const int& cref = cx;
    
    auto a1 = x;
    auto a2= ref;

    decltype(x) d1 = x;
    decltype(ref) d2 = ref;

}



// 练习 2.2: decltype(auto) 的特殊行为
// 
// 提示:
//   - decltype(auto) 会保留表达式的值类别
//   - 用于函数返回类型时特别有用
//   - 注意 decltype(auto) 和 auto 的区别
// 
// 你的代码:
void DecltypeAutoDemo() {
    int x = 42;
    int& ref = x;

    // 对比 auto vs decltype(auto)
    auto a1 = ref;              // int（丢弃引用）
    decltype(auto) d1 = ref;   // int&（保留引用！）

    SHOW(typeid(a1).name()); // i (int)
    SHOW(typeid(d1).name()); // i (int&)—— 但 static_assert 会区分

    static_assert(std::is_same<decltype(a1), int>::value, "auto 丢弃引用");
    static_assert(std::is_same<decltype(d1), int&>::value, "decltype(auto) 保留引用");

    // 函数返回类型的应用
    static auto lambda = [](int& r) -> decltype(auto) {
        return r;  // 返回 int&，不是 int
    };

    auto result = lambda(x);
    static_assert(std::is_same<decltype(result), int>::value, "lambda 返回引用");

    SHOW("DecltypeAutoDemo 完成");
}





// ============================================================================
// 第三部分: 函数模板参数推导 (Function Template Parameter Deduction)
// ============================================================================
//
// 模板参数推导是函数模板的核心机制：
//   - 按值传递时：const/volatile 被忽略
//   - 按引用传递时：保留顶层 const
//   - 数组和函数会退化为指针
//
// 练习 3.1: 实现一个函数模板，获取传入参数的类型信息
// 
// 提示:
//   - 使用 std::decay 去除引用和 const/volatile
//   - 使用 std::is_array 检查是否是数组
//   - 使用 std::is_function 检查是否是函数
// 
// 你的代码:
template <typename T>
void PrintType(T x){
    //打印什么类型
    SHOW(typeid(T).name());
    //decay摘掉所拥有的特质
    using Decayed = std::decay_t<T>;
    SHOW(typeid(Decayed).name());
    //if 数组 if 函数
    if constexpr (std::is_array_v<T>){
        SHOW("原始数据类型是数组");
    }
    if constexpr (std::is_function_v<T>){
        SHOW("原始数据类型是函数");
    }
}




// 练习 3.2: 实现一个函数模板，返回传入值的类型（不丢失引用和 cv 限定符）
// 
// 提示:
//   - 使用 decltype(auto) 作为返回类型
//   - 可以配合转发引用完美转发参数
// 
// 你的代码:
// 关键：使用 decltype(auto) 作为返回类型
template<typename T>
decltype(auto) ReturnType(T&& arg) {
    return arg;  // 原样返回，不丢失引用
}

void TestReturnType() {
    int x = 42;
    int& ref = x;
    const int cx = 42;

    // 测试 ReturnType
    auto a1 = ReturnType(x);   // int
    auto a2 = ReturnType(ref); // int&（保留了引用！）
    auto a3 = ReturnType(cx);  // const int（保留了 const！）

    // 验证类型
    SHOW("=== ReturnType 测试 ===");
    SHOW(typeid(a1).name());  // i (int)
    SHOW(typeid(a2).name());  // i (int&)—— 显示相同
    SHOW(typeid(a3).name());  // i (const int&)—— 显示可能相同

    static_assert(std::is_same<decltype(a1), int>::value, "");
    static_assert(std::is_same<decltype(a2), int>::value, "ref 保留了引用！");
    static_assert(std::is_same<decltype(a3), int>::value, "cx 保留了 const！");

    SHOW("ReturnType 测试完成");
}





// ============================================================================
// 第四部分: 引用折叠与完美转发 (Reference Collapsing & Perfect Forwarding)
// ============================================================================
//
// 引用折叠规则：
//   - T& & → T&
//   - T& && → T&
//   - T&& & → T&
//   - T&& && → T&&
//
// 完美转发：使用 std::forward<T> 保持参数的原始值类别
//
// 练习 4.1: 实现一个包装函数，完美转发参数
// 
// 提示:
//   - 使用模板参数推导和 std::forward
//   - 理解左值和右值的转发语义
// 
// 你的代码:
void process(int&) {SHOW("left value");}
void process(int&&) {SHOW("right value");}
void process(const char*) {SHOW("string value");}
template <typename T>
void wrapper(T&& x){
    process(std::forward<T>(x));
}




// 练习 4.2: 实现一个可变参数的完美转发函数
// 
// 提示:
//   - 使用可变参数模板
//   - 使用 std::forward 转发每个参数
//   - 递归展开参数包
// 
// 你的代码:
template <typename... T>
void wrapperevery(T&&... x){
    (process(std::forward<T>(x)), ...);
}




// ============================================================================
// 第五部分: 类型特性 (Type Traits)
// ============================================================================
//
// std::type_traits 提供了一系列类型查询和转换工具：
//   - is_xxx: 查询类型属性
//   - enable_if: 条件启用函数
//   - decay/remove_xxx: 类型转换
//
// 练习 5.1: 使用 std::enable_if 实现条件函数重载
// 
// 提示:
//   - 使用 enable_if<condition, T>::type 
//   - 常用场景：只接受整数类型或只接受浮点类型
// 
// 你的代码:
template <typename T>
std::enable_if_t<std::is_integral<T>::value,void>
process1(T){
    SHOW("this is intergral");
}
template <typename T>
std::enable_if_t<std::is_floating_point<T>::value,void>
process1(T){
    SHOW("this is floating");
}




// 练习 5.2: 实现一个类型选择器
// 
// 提示:
//   - 根据条件选择不同的类型
//   - 类似 std::conditional
// 
// 你的代码:
template <bool B, typename T, typename F>
struct TypeSelector {
    using type = F;
};

template <typename T, typename F>
struct TypeSelector<true, T, F> {
    using type = T;
};



// ============================================================================
// 验证清单
// ============================================================================
//
// 完成以上所有练习后，确保你能够:
// 
// [ ] 理解 auto 的推导规则（与模板推导的区别）
// [ ] 理解 decltype 的三种推导规则
// [ ] 理解 decltype(auto) 的特殊行为
// [ ] 理解引用折叠的四条规则
// [ ] 理解完美转发的实现原理
// [ ] 理解常用类型特性的用途
// 
// 运行以下命令验证你的实现:
//   g++ -std=c++17 -Wall -Wextra your_code.cpp -o test && ./test
//
// ============================================================================

#endif
