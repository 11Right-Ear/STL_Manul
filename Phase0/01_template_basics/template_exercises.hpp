/*
 * ============================================================================
 * Phase 0 - 模板基础练习
 * ============================================================================
 * 
 * 本文件包含模板编程基础的各种练习。使用 // 注释标注每个需要完成的部分。
 * 不要删除任何注释，只在注释下方编写你的代码。
 * 
 * 学习目标:
 *   1. 掌握变量模板的定义和使用
 *   2. 掌握函数模板的声明、定义和调用
 *   3. 掌握类模板的设计和实现
 *   4. 理解模板特化（全特化/偏特化）
 *   5. 理解可变参数模板的基本用法
 * 
 * 建议完成顺序:
 *   1. 先完成变量模板练习
 *   2. 然后完成函数模板练习
 *   3. 接着完成类模板练习
 *   4. 最后挑战可变参数模板
 * 
 * ============================================================================
 */

// ============================================================================
// 第一部分: 变量模板 (Variable Template)
// ============================================================================
// 
// 变量模板是 C++14 引入的特性，允许定义依赖于模板参数的变量。
// 语法: template<typename T> constexpr T var_name = value;
//
// 练习 1.1: 定义一个变量模板 PI，表示圆周率
// 
// 提示: 
//   - 使用 template<typename T> 作为模板声明
//   - 使用 constexpr 确保编译期常量
//   - 使用 T 作为类型，让 PI 可以是任意浮点类型
// 
// 示例结构: 变量模板语法
//   template<typename T>
//   constexpr T 变量名 = 初始值;
// 
// 提示: 
//   - typename T 是类型模板参数
//   - constexpr 确保编译期求值
//   - 用 T{} 包裹字面量以适配不同类型
//
// 你的代码:
#ifndef TEMPLATE_EXERCISES_HPP
#define TEMPLATE_EXERCISES_HPP

#include <iostream>
#include <vector>

#define ENTER '\n'
#define SHOW(x) std::cout << x << ENTER
#define PUTIN(x) std::cin >> x  
#define SPACE "    "
template<typename T>
constexpr T pi = T{3.1415926535897932385};

// template<typename T>
// constexpr T a = T{0};
// constexpr T b = T{0};


// ============================================================================
// 第二部分: 函数模板 (Function Template)
// ============================================================================
// 
// 函数模板允许编写与类型无关的代码，编译器会根据参数类型自动生成具体函数。
// 语法: template<typename T> return_type func_name(params) { ... }
//
// 练习 2.1: 实现一个模板函数 Max，返回两个值中的较大者
// 
// 提示:
//   - 使用 template<typename T> 声明类型参数
//   - 可以使用 if constexpr (C++17) 或 std::enable_if (C++11)
//   - 确保支持任意可比较的类型
// 
// 你的代码:
template <typename T>
T Max(T a, T b){
    T c;
    return c = a >= b ? a : b;
}

template <typename T>
void readtype(){
    T a; T b;
    std::cout << "please input same type numbers: " << std::endl;
    std::cin >> a >> b;
    std::cout << "max number is: " << std::max(a, b) << std::endl;
}







// 练习 2.2: 实现一个模板函数 Swap，交换两个变量的值
// 
// 提示:
//   - 使用引用参数 & 来修改原始变量
//   - 可以使用 std::move (C++11) 优化移动语义
// 
// 你的代码:
//prompt 指针实现
// template <typename T>
// void swap(T*& a, T*& b){
//     // 这样是形参，会导致出了函数作用域即死
//     // void swap(T* a, T* b)
//     T* C = nullptr;
//     C = a;
//     std::cout << "C_add is: " << C << std::endl;
//     std::cout << "C is: " << *C << std::endl;
//     a = b;
//     std::cout << "a_add is: " << a << std::endl;
//     std::cout << "a is: " << *a << std::endl;
//     b = C;
//     std::cout << "b_add is: " << b << std::endl;
//     std::cout << "b is: " << *b << std::endl;
// }
//& std::move实现
template <typename T>
void swap(T& a, T& b){
    T c = std::move(a);
    a = std::move(b);
    b = std::move(c);
}

// template <typename T>
// void swap(T& a, T& b){
//     T c;
//     c = a;
//     a = b;
//     b = c;
// }


// ============================================================================
// 第三部分: 类模板 (Class Template)
// ============================================================================
// 
// 类模板是实现通用数据结构（如容器）的基础。
// 语法: template<typename T> class ClassName { ... };
//
// 练习 3.1: 实现一个简单的模板类 Pair，表示一对值
// 
// 提示:
//   - 需要两个模板参数 T 和 U（可以是不同类型）
//   - 实现构造函数、getter 方法
//   - 实现 first 和 second 两个公有成员
// 
// 你的代码:
template <typename T1, typename T2> 
class Pair{
    public:
    //默认构造
    Pair() = default;
    //带参数构造
    Pair(T1 x, T2 y) : first(x), second(y){}
    //深拷贝构造
    Pair(const Pair& x){
        first = x.first;
        second = x.second;

    }
    //移动构造
    Pair(Pair&& x){
        first = std::move(x.first);
        second = std::move(x.second);
    }

    ~Pair(){}

    void setFirst(T1 x) {
       first = x; 
    }
    void setSecond(T2 y) {
       second = y; 
    }
    T1 getFist() const{
        return first;
    }
    T2 getSecond() const{
        return second;
    }

    // ==========重载============
    //复制运算符 
    Pair& operator=(const Pair& x){
        first = x.first;
        second = x.second;
        return *this;
    }

    //比较运算符
    bool operator==(const Pair& x){
        return first == x.first && second == x.second;
    }
    bool operator<(const Pair& x){
        return first == x.first && second < x.second;
    }
    bool operator>(const Pair& x){
        return first == x.first && second > x.second;
    }
    friend std::ostream& operator<< (std::ostream& os, const Pair<T1, T2>& x){
        os << "First is: " << x.first \
        << SPACE << "Second is: " << x.second << std::endl;
        return os;
    };
    //Q1:为什么这里不能使用流式输出？？？ 解决方法是加friend 
    // std::ostream& operator<<(std::ostream& os, const Pair& x){
    //     os << "First is: " << x.first << "Second is: " << x.second << std::endl;
    //     return os;
    // }

    //工具函数
    void swap(Pair& x, Pair& y){
        Pair z;
        z = x;
        x = y;
        y = z;
    }
    private:
    T1 first;
    T2 second;
};

// 在类外如何声明一个模板函数？？？ 优点复杂

// template <typename T1, typename T2>
// std::ostream& operator<<(std::ostream& os, const Pair<T1,T2>& x){
//     os << "Fist is: " << x.first << "Second is: " << x.second <<std::endl;
//     return os;
// }




#endif

// 练习 3.2: 实现一个模板类 Stack，支持 push 和 pop 操作
// 
// 提示:
//   - 使用 std::vector<T> 作为内部存储
//   - 实现 push(const T&) 入栈
//   - 实现 pop() 出栈（返回栈顶元素）
//   - 实现 top() 查看栈顶元素
//   - 实现 empty() 判断是否为空
//   - 实现 size() 返回元素个数
// 
// 你的代码:
template <typename T>
class Stack{
    public:
    Stack()=default;
    Stack(std::vector<T>& x) : x_(x){
        x_ = x;
    };
    Stack(std::vector<T>&& x) : x_(x){
        x_ = std::move(x);
    };

    ~Stack(){};
    
    friend std::ostream& operator<<(std::ostream& os, const Stack<T> x){
        for(int i = x.Get().size(); i > 0; i--){
            // SHOW(i);
            os << x.Get()[i - 1]<< std::endl;
        }
        return os;
    }
    void Set(std::vector<T> x){
        x_ = x;
    }
    //Q1 为什么我不加const　他就会报错？？？
    std::vector<T> Get() const {
        return x_;
    }

//   - 实现 push(const T&) 入栈
    void push(const T& x){
       //1.借助vector方法
       x_.push_back(x); 
       //2.自己实现底层
       
    }
//   - 实现 pop() 出栈（返回栈顶元素）
    T pop(){
       //1.借助vector方法
       T value = x_.back();
       x_.pop_back();
       return value;
       //2.自己实现底层
    }

//   - 实现 top() 查看栈顶元素
    T top(){
       //1.借助vector方法
       return x_.back();
       //2.自己实现底层
    }

//   - 实现 empty() 判断是否为空
    bool empty(){
       //1.借助vector方法
       return x_.empty();
       //2.自己实现底层
    } 
//   - 实现 size() 返回元素个数
    int size(){
       //1.借助vector方法

       return x_.size();
       //2.自己实现底层
    }
    private:
    std::vector<T> x_;

};




// ============================================================================
// 第四部分: 模板特化 (Template Specialization)
// ============================================================================
//
// 模板特化允许为特定类型提供特殊实现。
// 全特化: template<> class ClassName<Type> { ... };
// 偏特化: template<typename T> class ClassName<T*> { ... };
//
// 练习 4.1: 为模板类 Stack<char> 提供全特化实现
// 
// 提示:
//   - 使用 template<> 表示全特化
//   - 可以添加特殊功能，如字符验证
//   - 保持与其他类型的接口一致
// 
// 你的代码:
template <>
class Stack<char> {
    public:
    Stack() = default;
    Stack(std::vector<char> x) : x_(x){

    }
    Stack(std::vector<char>& x) : x_(x){

    }
    Stack(std::vector<char>&& x) : x_(x){
        x_ = std::move(x);
    }

    ~Stack() = default;

    //set get
    void Set(const std::vector<char>& x){
        x_ = x;
    }
    std::vector<char> Get(){
        return x_;
    }
    // 重载流式输出
    friend std::ostream& operator<<(std::ostream& os, Stack<char>& x){
       for(int i = x.Get().size(); i > 0; i--){
        os << x.Get()[i - 1] << ENTER;
       } 
       return os;
    }
    friend std::istream& operator>>(std::istream& os, Stack<char>& x){
        char c;
        os >> c;
        x.push(c);
        return os;
    }
//   - 实现 push(const T&) 入栈
    void push(const char& x){
       //1.借助vector方法
       x_.push_back(x); 
       //2.自己实现底层
       
    }
//   - 实现 pop() 出栈（返回栈顶元素）
    char pop(){
       //1.借助vector方法
       char value = x_.back();
       x_.pop_back();
       return value;
       //2.自己实现底层
    }

//   - 实现 top() 查看栈顶元素
    char top(){
       //1.借助vector方法
       return x_.back();
       //2.自己实现底层
    }

//   - 实现 empty() 判断是否为空
    bool empty(){
       //1.借助vector方法
       return x_.empty();
       //2.自己实现底层
    } 
//   - 实现 size() 返回元素个数
    int size(){
       //1.借助vector方法

       return x_.size();
       //2.自己实现底层
    }
    //字符验证
    friend bool operator==(Stack<char>& s1, Stack<char>& s2){
        if(s1.Get().size() == s2.Get().size()){
            for(int i = s1.Get().size(); i < 0; i--){
                if(s1.Get()[i] != s2.Get()[i]) return false;
            }
        }
        return true;

    } 
    private:
    std::vector<char> x_;
};





// 练习 4.2: 为指针类型提供偏特化
// 
// 提示:
//   - 偏特化模板参数: template<typename T> class MyUniquePtr<T*>
//   - 指针版本可能有不同的行为（如解引用）
// 
// 你的代码:
// 在C++中， 偏特化（Partial specialization）必须要一个主模板
template <typename T>
class Myptr{
    public:
    Myptr(T* ptr) : ptr_(ptr){

    }
    ~Myptr(){
        delete ptr_;
    }
    T& operator*(){return *ptr_;}
    const char* GetType() const {
        SHOW("the ptr type is: ");
        return "Myptr";
    }
    // private:
    T* ptr_;
};



// ============================================================================
// 第五部分: 可变参数模板 (Variadic Template)
// ============================================================================
//
// 可变参数模板允许模板接受任意数量的参数。
// 语法: template<typename... Args> void func(Args... args) { ... }
//
// 练习 5.1: 实现一个变参函数 print()，打印所有参数
// 
// 提示:
//   - 使用 sizeof...(args) 获取参数个数
//   - 使用递归基例处理第一个参数，然后递归处理剩余参数
//   - 每个参数后打印换行或空格分隔
// 
// 你的代码:
void print() {}
template <typename T, typename ... Args> 
void print(T x, Args ... args){
    SHOW(x) << ENTER;
    print(args ...);
    
}





// 练习 5.2: 实现一个变参函数 make_unique_ptr()，创建 unique_ptr
// 
// 提示:
//   - 使用 std::make_unique (C++14) 的简化版本
//   - 使用完美转发 std::forward<Args>(args)...
//   - 返回 std::unique_ptr<T>
// 
// 你的代码:






// ============================================================================
// 第六部分: 成员模板 (Member Template)
// ============================================================================
//
// 类的成员函数也可以是模板。
//
// 练习 6.1: 为模板类添加拷贝构造模板
// 
// 提示:
//   - 在模板类中添加 template<typename U> 构造函数
//   - 从另一个不同但兼容的类型 U 构造 T
// 
// 你的代码:






// ============================================================================
// 验证清单
// ============================================================================
//
// 完成以上所有练习后，确保你能够:
// 
// [ ] 理解变量模板的语法和用途
// [ ] 理解函数模板的参数推导机制
// [ ] 理解类模板的声明和定义方式
// [ ] 理解全特化和偏特化的区别和使用场景
// [ ] 理解可变参数模板的递归展开机制
// [ ] 理解成员模板的作用
// 
// 运行以下命令验证你的实现:
//   g++ -std=c++17 -Wall -Wextra your_code.cpp -o test && ./test
//
// ============================================================================
