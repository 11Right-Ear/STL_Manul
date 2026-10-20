/*
 * ============================================================================
 * Phase 1 - 类型特征练习
 * ============================================================================
 * 
 * 本文件包含类型特征编程的各种练习。使用 // 你的代码: 注释标注每个需要完成的部分。
 * 不要删除任何注释，只在注释下方编写你的代码。
 * 
 * 学习目标:
 *   1. 理解 type_traits 头文件提供的类型查询工具
 *   2. 掌握类型转换 traits (remove_cv, add_pointer 等)
 *   3. 理解 conditional, enable_if 等条件类型
 *   4. 能够实现自定义的 type trait
 *   5. 掌握 SFINAE 与 type traits 的结合使用
 *   6. 了解 C++17/20 的新 type_traits
 * 
 * 建议完成顺序:
 *   1. 先完成类型查询 traits 练习
 *   2. 然后完成类型转换 traits 练习
 *   3. 接着完成条件类型练习
 *   4. 再完成自定义 trait 练习
 *   5. 最后完成 SFINAE 和 C++17/20 特性练习
 * 
 * type_traits 分类:
 *   - 类型查询: is_pointer, is_integral, is_class, etc.
 *   - 类型转换: remove_cv, add_pointer, remove_reference, etc.
 *   - 条件类型: conditional, enable_if
 *   - 关系运算: is_same, is_base_of, is_convertible
 *   - 组合逻辑: conjunction, disjunction, negation
 * 
 * ============================================================================
 */

#ifndef TRAITS_EXERCISES_HPP
#define TRAITS_EXERCISES_HPP

#include <iostream>
#include <type_traits>
#include <vector>
#include <list>
#include <string>
#include <memory>
#include <array>

#define ENTER '\n';
#define SHOW(x) std::cout << x 
#define SHOWE(x) std::cout << x << '\n'
#define PUTIN(x) std::cin >> x 
#define SPACE "    "

// ============================================================================
// 第一部分: 类型查询 traits (Type Query Traits)
// ============================================================================
//
// 类型查询 traits 用于在编译期查询类型的属性。
//
// 练习 1.1: 使用 is_pointer 检查指针类型
// 
// 提示: 
//   - std::is_pointer<T>::value 返回 true 如果 T 是指针类型
//   - 包括 raw pointer, member pointer, 但不包括 smart pointer
//   - 使用 static_assert 验证结果
// 
// 你的代码:



// 练习 1.2: 使用 is_integral 检查整型类型
// 
// 提示:
//   - std::is_integral<T>::value 返回 true 如果 T 是整数类型
//   - 包括 bool, char, short, int, long, long long 等
//   - 不包括浮点数
// 
// 你的代码:



// 练习 1.3: 使用 is_floating_point 检查浮点类型
// 
// 提示:
//   - std::is_floating_point<T>::value 返回 true 如果 T 是浮点类型
//   - 包括 float, double, long double
// 
// 你的代码:



// 练习 1.4: 使用 is_array, is_enum, is_class 检查复合类型
// 
// 提示:
//   - std::is_array<T>::value 检查是否是数组
//   - std::is_enum<T>::value 检查是否是枚举
//   - std::is_class<T>::value 检查是否是类/结构体/联合体
// 
// 你的代码:



// 练习 1.5: 使用 is_same 检查类型相等
// 
// 提示:
//   - std::is_same<T, U>::value 返回 true 如果 T 和 U 是同一类型
//   - 注意 const/volatile 修饰也会影响结果
//   - 可以结合 remove_cv 使用
// 
// 你的代码:



// ============================================================================
// 第二部分: 类型转换 traits (Type Transformation Traits)
// ============================================================================
//
// 类型转换 traits 用于在编译期转换类型。
//
// 练习 2.1: 使用 remove_const 和 add_const
// 
// 提示: 
//   - std::remove_const<T>::type 移除 const
//   - std::add_const<T>::type 添加 const
//   - 注意 const T 和 T const 是等价的
// 
// 你的代码:



// 练习 2.2: 使用 remove_pointer 和 add_pointer
// 
// 提示:
//   - std::remove_pointer<T>::type 移除指针
//   - std::add_pointer<T>::type 添加指针
//   - T -> T*
// 
// 你的代码:



// 练习 2.3: 使用 remove_reference 和 add_reference
// 
// 提示:
//   - std::remove_reference<T>::type 移除引用
//   - std::add_lvalue_reference<T>::type 添加左值引用
//   - std::add_rvalue_reference<T>::type 添加右值引用
//   - 注意: add_reference 对已存在的引用不会再添加
// 
// 你的代码:



// 练习 2.4: 使用 remove_cv 移除 cv 限定符
// 
// 提示:
//   - std::remove_cv 同时移除 const 和 volatile
//   - 相当于 remove_const + remove_volatile
// 
// 你的代码:



// 练习 2.5: 使用 decay 进行类型退化
// 
// 提示:
//   - std::decay<T>::type 进行类型退化
//   - 数组退化为指针
//   - 函数退化为函数指针
//   - 移除 cv 限定符和引用
// 
// 你的代码:



// ============================================================================
// 第三部分: 条件类型 (Conditional Types)
// ============================================================================
//
// 条件类型根据条件在编译期选择类型。
//
// 练习 3.1: 使用 std::conditional 实现类型选择
// 
// 提示: 
//   - std::conditional<Condition, T, U>::type
//   - 如果 Condition 为 true，选择 T；否则选择 U
//   - Condition 必须是 std::integral_constant<bool, ...> 或 bool
// 
// 你的代码:



// 练习 3.2: 使用 std::enable_if 实现函数重载控制
// 
// 提示:
//   - std::enable_if<Condition, T>::type 如果 Condition 为 true
//   - 通常放在函数返回类型或模板参数中
//   - 用于实现编译期函数选择
// 
// 你的代码:



// 练习 3.3: 实现一个类型选择器模板
// 
// 提示:
//   - 实现模板函数，如果 T 是指针类型返回指向的值，否则返回 T 本身
//   - 结合 is_pointer 和 conditional
// 
// 你的代码:



// 练习 3.4: 使用 common_type 实现类型提升
// 
// 提示:
//   - std::common_type<T, U>::type 返回两者的共同类型
//   - 例如 int 和 double 的 common_type 是 double
//   - 使用 std::decay 处理类型
// 
// 你的代码:



// ============================================================================
// 第四部分: 自定义 Type Traits
// ============================================================================
//
// 实现自定义的 type trait 来扩展类型特征库。
//
// 练习 4.1: 实现 is_pointer_to_member trait
// 
// 提示:
//   - 检查类型是否是成员指针
//   - 使用 std::is_member_pointer
//   - 成员指针包括成员函数指针和成员对象指针
// 
// 你的代码:



// 练习 4.2: 实现 is_container trait
// 
// 提示:
//   - 检查类型是否是容器（类似 STL 容器）
//   - 检查是否有 value_type, iterator, begin(), end()
//   - 使用 SFINAE 或 void_t 技巧
// 
// 你的代码:



// 练习 4.3: 实现 is_complete_type trait
// 
// 提示:
//   - 检查类型是否完整（已定义，不只是声明）
//   - 可以通过 sizeof 检查
//   - 不完整的类型无法进行 sizeof
// 
// 你的代码:



// 练习 4.4: 实现 is_template_instantiation trait
// 
// 提示:
//   - 检查类型是否是特定模板的实例化
//   - 例如 is_vector<T>::value 检查 T 是否是 std::vector
//   - 使用 SFINAE 提取模板参数
// 
// 你的代码:



// ============================================================================
// 第五部分: SFINAE 与 Type Traits
// ============================================================================
//
// SFINAE (Substitution Failure Is Not An Error) 与 type traits 结合使用。
//
// 练习 5.1: 使用 enable_if 实现函数重载
// 
// 提示:
//   - 创建两个重载函数，一个处理整数，一个处理浮点数
//   - 使用 enable_if 控制哪个函数被选中
// 
// 你的代码:



// 练习 5.2: 使用 void_t 实现 SFINAE
// 
// 提示:
//   - void_t<T1, T2, ...> 将所有类型映射为 void
//   - 利用 SFINAE，只有有效的类型组合才匹配
//   - 常用于检测成员是否存在
// 
// 你的代码:



// 练习 5.3: 检测类是否有特定成员
// 
// 提示:
//   - 使用 void_t 检测 size() 方法是否存在
//   - 使用declval 模拟对象构造
// 
// 你的代码:



// 练习 5.4: 检测类是否可迭代
// 
// 提示:
//   - 检测 begin() 和 end() 方法是否存在
//   - 检测返回类型是否是迭代器
// 
// 你的代码:



// ============================================================================
// 第六部分: C++17/20 Type Traits
// ============================================================================
//
// C++17 和 C++20 引入了新的 type traits。
//
// 练习 6.1: 使用 conjunction, disjunction, negation
// 
// 提示:
//   - std::conjunction<B1, B2, ...>: 所有都是 true 才为 true
//   - std::disjunction<B1, B2, ...>: 任一为 true 则为 true
//   - std::negation<B>: 取反
//   - C++17 特性
// 
// 你的代码:



// 练习 6.2: 使用 std::is_void 检查 void 类型
// 
// 提示:
//   - std::is_void<T>::value 检查是否是 void
//   - 常用于模板元编程的边界条件
// 
// 你的代码:



// 练习 6.3: 使用 std::is_function 检查函数类型
// 
// 提示:
//   - std::is_function<T>::value 检查是否是函数类型
//   - 注意成员函数和普通函数的处理不同
//   - 使用 std::is_member_function_pointer 处理成员函数
// 
// 你的代码:



// 练习 6.4: 使用 C++20 的 concepts 简化 traits (可选)
// 
// 提示:
//   - concepts 是 C++20 引入的概念约束
//   - 比 SFINAE 更清晰的错误信息
//   - 使用 requires 子句
// 
// 你的代码:



// ============================================================================
// 第七部分: Type Traits 综合应用
// ============================================================================
//
// 综合运用 type traits 解决实际问题。
//
// 练习 7.1: 实现类型安全的向下转型
// 
// 提示:
//   - 使用 is_base_of 检查继承关系
//   - 使用 static_cast 进行向下转型
//   - 在编译期确保转型安全
// 
// 你的代码:



// 练习 7.2: 实现通用的序列化函数
// 
// 提示:
//   - 根据类型特征选择不同的序列化方式
//   - 整数类型和浮点类型处理不同
//   - 容器类型需要遍历元素
// 
// 你的代码:



// 练习 7.3: 实现类型的编译期反射
// 
// 提示:
//   - 使用 index_sequence 处理参数包
//   - 使用 tuple_size 获取元素个数
//   - 使用 get<N> 获取元素
// 
// 你的代码:



// ============================================================================
// 验证清单
// ============================================================================
//
// 完成以上所有练习后，确保你能够:
// 
// [ ] 理解并使用标准库提供的 type traits
// [ ] 掌握类型查询 traits (is_*, is_same 等)
// [ ] 掌握类型转换 traits (remove_*, add_*, decay 等)
// [ ] 理解 conditional 和 enable_if 的用法
// [ ] 能够实现自定义的 type trait
// [ ] 掌握 SFINAE 与 type traits 的结合使用
// [ ] 了解 C++17/20 的新 type traits
// 
// 编译验证命令（C++17）:
//   g++ -std=c++17 -Wall -Wextra -c traits_exercises.hpp
// 
// 编译验证命令（C++20）:
//   g++ -std=c++20 -Wall -Wextra -c traits_exercises.hpp
// 
// 运行验证（创建测试文件后）:
//   g++ -std=c++20 -Wall -Wextra test_traits.cpp -o test && ./test
//
// ============================================================================

#endif
