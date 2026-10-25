/*
 * ============================================================================
 * Phase 1 - 迭代器练习
 * ============================================================================
 * 
 * 本文件包含迭代器编程的各种练习。使用 // 你的代码: 注释标注每个需要完成的部分。
 * 不要删除任何注释，只在注释下方编写你的代码。
 * 
 * 学习目标:
 *   1. 理解迭代器的概念和五种迭代器类别
 *   2. 掌握迭代器的基本操作 (*、->、++、--、==、!=)
 *   3. 掌握迭代器适配器的使用 (反向迭代器、插入迭代器、流迭代器)
 *   4. 理解 iterator_traits 的概念和作用
 *   5. 能够为自定义容器实现迭代器
 *   6. 理解迭代器失效的原因和处理方法
 * 
 * 建议完成顺序:
 *   1. 先完成迭代器基础练习
 *   2. 然后完成迭代器类别练习
 *   3. 接着完成迭代器适配器练习
 *   4. 再完成 iterator_traits 练习
 *   5. 最后完成综合练习
 * 
 * 迭代器类别层次结构:
 * 
 *   InputIterator  ──────►  OutputIterator
 *        │                       │
 *        ▼                       ▼
 *   ForwardIterator  ───►  ForwardIterator (双向迭代器的子集)
 *        │                       │
 *        ▼                       ▼
 *   BidirectionalIterator  ───►  BidirectionalIterator
 *        │                       │
 *        ▼                       ▼
 *   RandomAccessIterator  ───►  RandomAccessIterator
 * 
 * ============================================================================
 */

#ifndef ITERATOR_EXERCISES_HPP
#define ITERATOR_EXERCISES_HPP

#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>
#include <list>
#include <deque>
#include <array>
#include <string>
#include <memory>
#include <type_traits>

#define ENTER '\n';
#define SHOW(x) std::cout << x 
#define SHOWE(x) std::cout << x << '\n'
#define PUTIN(x) std::cin >> x 
#define SPACE "    "

// 辅助: 把 bool 转成可输出的 "是"/"否" 字符串
// (因为 SHOWE 是函数式宏, 形参中的逗号会被当成宏参数分隔符, 故需先算出结果再传入)
inline const char* yes_no(bool b){ return b ? "是" : "否"; }

// ============================================================================
// 第一部分: 迭代器基础 (Iterator Basics)
// ============================================================================
// 
// 迭代器是一种抽象的"指针"，用于遍历容器元素。
// 所有标准容器都提供 begin() 和 end() 方法返回迭代器。
//
// 练习 1.1: 使用迭代器遍历 vector
// 
// 提示: 
//   - 使用 auto 自动推导迭代器类型
//   - begin() 返回指向第一个元素的迭代器
//   - end() 返回指向"最后一个元素之后"的迭代器
//   - 使用 * 解引用获取元素值
// 
// 你的代码:
struct Point{
    int x = 0;
    int y = 0;
};
//构造一个vector 填充，一共有四种遍历方式
void traverse_4(std::vector<Point>& px){
    //1.正常for循环
    for(int i = 0; i < px.size(); ++i){
        SHOWE("正常for循环");
        SHOWE(px[i].x);
        SHOWE(px[i].y);
    }
    for(std::vector<Point>::iterator it = px.begin(); it != px.end(); ++it){
    //2.使用迭代器遍历
        SHOWE("使用迭代器遍历");
        SHOWE((*it).x);
        SHOWE((*it).y);
    }
    for(auto it = px.begin(); it != px.end(); ++it){
    //3.使用auto关键字
        SHOWE("使用auto关键字");
        SHOWE((*it).x);
        SHOWE((*it).y);
    }
    for(auto it : px){
    //4.auto简单写形式
        SHOWE("auto简单写形式");
        SHOWE(it.x);
        SHOWE(it.y);
    }

}





// 练习 1.2: 使用迭代器修改元素
// 
// 提示:
//   - 迭代器的 * 操作返回的是元素的引用
//   - 可以通过迭代器修改容器的元素
// 
// 你的代码:
// void 
// 练习 1.2: 使用迭代器修改元素
void exercise_1_2_modify_by_iterator(){
    SHOWE("[练习 1.2] 使用迭代器修改元素");

    std::vector<int> v{1, 2, 3, 4, 5};

    SHOWE("修改前:");
    for(auto it = v.begin(); it != v.end(); ++it){
        SHOWE(*it);
    }

    // *it 返回元素的引用，可以直接赋值修改容器中的元素
    for(auto it = v.begin(); it != v.end(); ++it){
        *it *= 10;
    }

    SHOWE("修改后(每个元素乘以10):");
    for(auto it = v.begin(); it != v.end(); ++it){
        SHOWE(*it);
    }

    // 也可以用迭代器配合箭头运算符访问成员(结构体场景)
    std::vector<Point> pts{{1, 2}, {3, 4}};
    for(auto it = pts.begin(); it != pts.end(); ++it){
        it->x += 100;
        it->y += 100;
    }
    SHOWE("Point 结构体通过 it-> 成员访问修改后:");
    for(const auto& p : pts){
        SHOWE(p.x);
        SHOWE(p.y);
    }

    // 配合算法使用迭代器区间
    std::vector<int> dst(5);
    std::copy(v.begin(), v.end(), dst.begin());
    SHOWE("std::copy 复制后的 dst:");
    for(auto it = dst.begin(); it != dst.end(); ++it){
        SHOWE(*it);
    }
}

// 练习 1.3: 使用 const_iterator 遍历常量容器
// 
// 提示:
//   - const_iterator 用于遍历常量容器
//   - 不能通过 const_iterator 修改元素
//   - 使用 cbegin() 和 cend() 获取 const_iterator
// 
// 你的代码:
void exercise_1_3_const_iterator(){
    SHOWE("[练习 1.3] 使用 const_iterator 遍历常量容器");

    const std::vector<int> cv{10, 20, 30, 40, 50};

    // cbegin()/cend() 返回 const_iterator
    std::vector<int>::const_iterator it = cv.cbegin();
    SHOWE("使用 const_iterator 遍历常量 vector:");
    for(; it != cv.cend(); ++it){
        SHOWE(*it);
    }

    // 遍历 const 容器时，begin() 本身就返回 const_iterator
    auto it2 = cv.begin();
    using ConstIt = std::vector<int>::const_iterator;
    bool same_kind = std::is_same<decltype(it2), ConstIt>::value;
    const char* yes_no = same_kind ? "是" : "否";
    SHOWE("const 容器的 begin() 返回类型也是 const_iterator:");
    SHOWE(yes_no);
    for(it2 = cv.begin(); it2 != cv.end(); ++it2){
        SHOWE(*it2);
    }

    // 反向的 const 迭代器
    SHOWE("使用 crbegin()/crend() 反向遍历:");
    for(auto rit = cv.crbegin(); rit != cv.crend(); ++rit){
        SHOWE(*rit);
    }

    // 演示: 非 const 容器的 begin() 与 cbegin() 类型不同
    std::vector<int> mv{1, 2, 3};
    using It = decltype(mv.begin());
    using CIt = decltype(mv.cbegin());
    bool same_type = std::is_same<It, CIt>::value;
    const char* same_str = same_type ? "是" : "否";
    SHOWE("非 const 容器的 begin() 与 cbegin() 是否同类型:");
    SHOWE(same_str);

    // 演示: 通过 const_iterator 修改元素是编译期错误, 这里用注释说明
    // auto bad = cv.cbegin();
    // *bad = 100;   // error: assignment of read-only location
    SHOWE("const_iterator 无法解引用赋值(编译期错误, 见源码注释)");
}


// ============================================================================
// 第二部分: 迭代器类别 (Iterator Categories)
// ============================================================================
//
// 迭代器按能力分为五种类别，每种类别支持一组特定的操作。
//
// 练习 2.1: 实现一个简单的正向迭代器 (Forward Iterator)
// 
// 正向迭代器支持:
//   - ++ (前向移动)
//   - == 和 != (相等性比较)
//   - * (解引用，只读)
// 
// 提示:
//   - 定义一个模板结构体 ForwardIterator
//   - 实现 operator++, operator*, operator==, operator!=
// 
// 你的代码:
// 练习 2.1: 实现一个简单的正向迭代器 (Forward Iterator)
//
// ForwardIterator 是一个模板类, 内部持有一个指针 ptr_, 指向元素序列中的当前位置。
// 模板参数 T 为被指向的元素类型 (可含 const 修饰)。
template<typename T>
class ForwardIterator{
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type        = typename std::remove_const<T>::type;
    using difference_type   = std::ptrdiff_t;
    using pointer           = T*;
    using reference          = T&;

    explicit ForwardIterator(T* p = nullptr) : ptr_(p) {}

    reference operator*() const { return *ptr_; }
    pointer   operator->() const { return ptr_; }

    // 前置 ++: 返回自身引用, 支持 it++ 链式
    ForwardIterator& operator++(){
        ++ptr_;
        return *this;
    }

    // 后置 ++: 返回旧值拷贝
    ForwardIterator operator++(int){
        ForwardIterator tmp(*this);
        ++ptr_;
        return tmp;
    }

    bool operator==(const ForwardIterator& rhs) const { return ptr_ == rhs.ptr_; }
    bool operator!=(const ForwardIterator& rhs) const { return ptr_ != rhs.ptr_; }

    T* raw() const { return ptr_; }

private:
    T* ptr_;
};

// 练习 2.1 演示
void exercise_2_1_forward_iterator(){
    SHOWE("[练习 2.1] ForwardIterator 实现与演示");

    int arr[] = {1, 2, 3, 4, 5};
    ForwardIterator<int> it(arr);
    ForwardIterator<int> itEnd(arr + 5);

    SHOWE("正向遍历:");
    for(; it != itEnd; ++it){
        SHOWE(*it);
    }

    // 验证 traits
    using Traits = std::iterator_traits<ForwardIterator<int>>;
    bool is_int = std::is_same<Traits::value_type, int>::value;
    bool is_fwd = std::is_same<Traits::iterator_category, std::forward_iterator_tag>::value;
    const char* f1 = is_int ? "是" : "否";
    const char* f2 = is_fwd ? "是" : "否";
    SHOWE("value_type 为 int:");
    SHOWE(f1);
    SHOWE("iterator_category 为 forward_iterator_tag:");
    SHOWE(f2);
}

// 
// 你的代码:



// 练习 2.2: 实现双向迭代器 (Bidirectional Iterator)
// 
// 双向迭代器支持:
//   - 所有正向迭代器的操作
//   - -- (后向移动)
// 
// 提示:
//   - 在正向迭代器基础上增加 operator--
//   - 双向迭代器可以反向遍历容器
// 
// 你的代码:
// 练习 2.2: BidirectionalIterator —— 在 ForwardIterator 基础上增加 operator--
template<typename T>
class BidirectionalIterator{
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type        = typename std::remove_const<T>::type;
    using difference_type   = std::ptrdiff_t;
    using pointer           = T*;
    using reference          = T&;

    explicit BidirectionalIterator(T* p = nullptr) : ptr_(p) {}

    reference operator*() const { return *ptr_; }
    pointer   operator->() const { return ptr_; }

    BidirectionalIterator& operator++(){
        ++ptr_;
        return *this;
    }
    BidirectionalIterator operator++(int){
        BidirectionalIterator tmp(*this);
        ++ptr_;
        return tmp;
    }

    // 新增: 前置 -- / 后置 --
    BidirectionalIterator& operator--(){
        --ptr_;
        return *this;
    }
    BidirectionalIterator operator--(int){
        BidirectionalIterator tmp(*this);
        --ptr_;
        return tmp;
    }

    bool operator==(const BidirectionalIterator& rhs) const { return ptr_ == rhs.ptr_; }
    bool operator!=(const BidirectionalIterator& rhs) const { return ptr_ != rhs.ptr_; }

    T* raw() const { return ptr_; }

private:
    T* ptr_;
};

// 练习 2.2 演示
void exercise_2_2_bidirectional_iterator(){
    SHOWE("[练习 2.2] BidirectionalIterator 实现与演示");

    int arr[] = {1, 2, 3, 4, 5};
    BidirectionalIterator<int> it(arr + 5);   // 指向末尾
    BidirectionalIterator<int> itBegin(arr);

    SHOWE("反向遍历:");
    for(--it; it != itBegin; --it){
        SHOWE(*it);
    }

    SHOWE("正向遍历 (与反向对称):");
    for(auto p = itBegin; p != BidirectionalIterator<int>(arr + 5); ++p){
        SHOWE(*p);
    }

    using Traits = std::iterator_traits<BidirectionalIterator<int>>;
    bool is_bidi = std::is_same<Traits::iterator_category, std::bidirectional_iterator_tag>::value;
    const char* flag = is_bidi ? "是" : "否";
    SHOWE("iterator_category 为 bidirectional_iterator_tag:");
    SHOWE(flag);
}



// 练习 2.3: 实现随机访问迭代器 (Random Access Iterator)
// 
// 随机访问迭代器支持:
//   - 所有双向迭代器的操作
//   - + 和 - (指针算术运算)
//   - += 和 -= (复合赋值)
//   - <, >, <=, >= (关系比较)
//   - [] (下标访问)
// 
// 提示:
//   - 使用指针算术实现 + 和 -
//   - 使用 std::ptrdiff_t 表示距离
//   - 关系比较基于指针偏移量
// 
// 你的代码:
// 练习 2.3: RandomAccessIterator —— 支持全部随机访问运算
//
// 注意 operator- 有两种语义, 必须重载区分, 否则会产生歧义:
//   (a) 二元: it1 - it2  -> 返回两个迭代器之间的距离 (ptrdiff_t)
//   (b) 二元: it - n      -> 返回前移 n 步后的迭代器
//   (c) 一元: -it         -> 不实现(标准也不要求)
template<typename T>
class RandomAccessIterator{
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type        = typename std::remove_const<T>::type;
    using difference_type   = std::ptrdiff_t;
    using pointer           = T*;
    using reference          = T&;

    explicit RandomAccessIterator(T* p = nullptr) : ptr_(p) {}

    reference operator*() const { return *ptr_; }
    pointer   operator->() const { return ptr_; }

    // ++ / --
    RandomAccessIterator& operator++(){
        ++ptr_;
        return *this;
    }
    RandomAccessIterator operator++(int){
        RandomAccessIterator tmp(*this);
        ++ptr_;
        return tmp;
    }
    RandomAccessIterator& operator--(){
        --ptr_;
        return *this;
    }
    RandomAccessIterator operator--(int){
        RandomAccessIterator tmp(*this);
        --ptr_;
        return tmp;
    }

    // 复合赋值
    RandomAccessIterator& operator+=(difference_type n){
        ptr_ += n;
        return *this;
    }
    RandomAccessIterator& operator-=(difference_type n){
        ptr_ -= n;
        return *this;
    }

    // 二元 +: 迭代器 + 偏移
    RandomAccessIterator operator+(difference_type n) const {
        return RandomAccessIterator(ptr_ + n);
    }
    // 二元 +: 偏移 + 迭代器 (非成员形式, 通过友元实现对称)
    friend RandomAccessIterator operator+(difference_type n, const RandomAccessIterator& it){
        return RandomAccessIterator(it.ptr_ + n);
    }

    // 二元 -: 迭代器 - 偏移  -> 返回迭代器
    RandomAccessIterator operator-(difference_type n) const {
        return RandomAccessIterator(ptr_ - n);
    }
    // 二元 -: 迭代器 - 迭代器 -> 返回距离 (ptrdiff_t)
    // 这是与上面 (b) 的关键区别: 参数是迭代器而不是整数
    difference_type operator-(const RandomAccessIterator& rhs) const {
        return ptr_ - rhs.ptr_;
    }

    // 下标访问
    reference operator[](difference_type n) const { return ptr_[n]; }

    // 关系比较: 基于指针偏移量
    bool operator==(const RandomAccessIterator& rhs) const { return ptr_ == rhs.ptr_; }
    bool operator!=(const RandomAccessIterator& rhs) const { return ptr_ != rhs.ptr_; }
    bool operator< (const RandomAccessIterator& rhs) const { return ptr_ <  rhs.ptr_; }
    bool operator<=(const RandomAccessIterator& rhs) const { return ptr_ <= rhs.ptr_; }
    bool operator> (const RandomAccessIterator& rhs) const { return ptr_ >  rhs.ptr_; }
    bool operator>=(const RandomAccessIterator& rhs) const { return ptr_ >= rhs.ptr_; }

    T* raw() const { return ptr_; }

private:
    T* ptr_;
};

// 练习 2.3 演示
void exercise_2_3_random_access_iterator(){
    SHOWE("[练习 2.3] RandomAccessIterator 实现与演示");

    int arr[] = {10, 20, 30, 40, 50};
    RandomAccessIterator<int> it(arr);
    RandomAccessIterator<int> itEnd(arr + 5);

    SHOWE("正向遍历:");
    for(auto p = it; p != itEnd; ++p){
        SHOWE(*p);
    }

    // 偏移访问
    SHOWE("it + 2 指向的元素:");
    SHOWE(*(it + 2));
    SHOWE("2 + it 指向的元素 (对称形式):");
    SHOWE(*(2 + it));
    SHOWE("it[3] 下标访问:");
    SHOWE(it[3]);
    SHOWE("it - 1 (回退一步):");
    SHOWE(*(it - 1));

    // 复合赋值
    auto p = it;
    p += 3;
    SHOWE("it += 3 之后:");
    SHOWE(*p);
    p -= 2;
    SHOWE("it -= 2 之后:");
    SHOWE(*p);

    // 二元 - 的两种语义
    std::ptrdiff_t dist = itEnd - it;      // 迭代器 - 迭代器 = 距离
    SHOWE("itEnd - it 得到的距离:");
    SHOWE(dist);
    auto shifted = itEnd - 2;               // 迭代器 - 整数 = 迭代器
    SHOWE("itEnd - 2 指向的元素:");
    SHOWE(*shifted);

    // 关系比较
    bool lt = (it <  itEnd);
    bool gt = (itEnd > it);
    bool le = (it <= it);
    bool ge = (it >= it);
    const char* s_lt = lt ? "是" : "否";
    const char* s_gt = gt ? "是" : "否";
    const char* s_le = le ? "是" : "否";
    const char* s_ge = ge ? "是" : "否";
    SHOWE("it < itEnd ?");
    SHOWE(s_lt);
    SHOWE("itEnd > it ?");
    SHOWE(s_gt);
    SHOWE("it <= it ?");
    SHOWE(s_le);
    SHOWE("it >= it ?");
    SHOWE(s_ge);

    // traits 验证
    using Traits = std::iterator_traits<RandomAccessIterator<int>>;
    bool is_ra = std::is_same<Traits::iterator_category, std::random_access_iterator_tag>::value;
    const char* flag = is_ra ? "是" : "否";
    SHOWE("iterator_category 为 random_access_iterator_tag:");
    SHOWE(flag);
}



// ============================================================================
// 第三部分: 迭代器适配器 (Iterator Adapters)
// ============================================================================
//
// 迭代器适配器将现有迭代器转换为新的迭代器类型。
//
// 练习 3.1: 使用反向迭代器 (reverse_iterator)
// 
// 反向迭代器:
//   - 反向遍历容器
//   - base() 返回对应的正向迭代器
//   - ++ 操作实际是前向移动
// 
// 提示:
//   - 使用 std::reverse_iterator
//   - 使用 rbegin() 和 rend() 获取反向迭代器
// 
// 你的代码:
// 练习 3.1: 使用 std::reverse_iterator
void exercise_3_1_reverse_iterator(){
    SHOWE("[练习 3.1] std::reverse_iterator 演示");

    std::vector<int> v{1, 2, 3, 4, 5};

    SHOWE("使用 rbegin()/rend() 反向遍历:");
    for(auto rit = v.rbegin(); rit != v.rend(); ++rit){
        SHOWE(*rit);
    }

    // reverse_iterator 的 ++ 实际是对底层正向迭代器执行 --
    SHOWE("rbegin() 的 base() 指向末尾之后:");
    auto rit = v.rbegin();
    auto base = rit.base();
    SHOWE(yes_no(base == v.end()));
    SHOWE("*rit 当前值:");
    SHOWE(*rit);

    // 观察 ++ 之后 base() 的变化
    ++rit;
    SHOWE("++rit 之后 *rit:");
    SHOWE(*rit);
    SHOWE("此时 base() == v.end()-1 ?");
    auto base2 = rit.base();
    SHOWE(yes_no(base2 == (v.end() - 1)));

    // rbegin() 的 base() 就是 end()
    SHOWE("rbegin().base() == end() ?");
    auto rb = v.rbegin();
    auto rb_base = rb.base();
    SHOWE(yes_no(rb_base == v.end()));

    // 通过反向区间做算法操作
    std::vector<int> out;
    std::copy(v.rbegin(), v.rend(), std::back_inserter(out));
    SHOWE("std::copy(rbegin, rend) 结果:");
    for(const auto& e : out){
        SHOWE(e);
    }
}



// 练习 3.2: 实现反向迭代器
// 
// 提示:
//   - 定义 ReverseIterator 类模板
//   - 保存一个正向迭代器作为内部状态
//   - 实现 base() 方法返回正向迭代器
//   - 实现反向的 ++ 和 -- 操作
// 
// 你的代码:
// 练习 3.2: 自己实现 ReverseIterator 类模板
//
// 核心思想: 反向迭代器内部保存一个"正向迭代器" cur_。
//   反向迭代器的 ++  ==  底层正向迭代器的 --
//   反向迭代器的 --  ==  底层正向迭代器的 ++
//   反向迭代器的 *   ==  *(cur_ - 1)
template<typename Iterator>
class ReverseIterator{
public:
    using iterator_type    = Iterator;
    using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;
    using value_type        = typename std::iterator_traits<Iterator>::value_type;
    using difference_type   = typename std::iterator_traits<Iterator>::difference_type;
    using pointer           = typename std::iterator_traits<Iterator>::pointer;
    using reference          = typename std::iterator_traits<Iterator>::reference;

    explicit ReverseIterator(Iterator it) : cur_(it) {}

    // base() 返回内部保存的正向迭代器
    Iterator base() const { return cur_; }

    // 解引用: 取底层迭代器的前一个元素
    reference operator*() const {
        Iterator tmp = cur_;
        return *(--tmp);
    }

    pointer operator->() const {
        Iterator tmp = cur_;
        --tmp;
        return tmp.operator->();
    }

    // 反向的 ++ : 底层 -- , 方向反转
    ReverseIterator& operator++(){
        --cur_;
        return *this;
    }
    ReverseIterator operator++(int){
        ReverseIterator tmp(*this);
        --cur_;
        return tmp;
    }

    // 反向的 -- : 底层 ++ , 方向反转
    ReverseIterator& operator--(){
        ++cur_;
        return *this;
    }
    ReverseIterator operator--(int){
        ReverseIterator tmp(*this);
        ++cur_;
        return tmp;
    }

    bool operator==(const ReverseIterator& rhs) const { return cur_ == rhs.cur_; }
    bool operator!=(const ReverseIterator& rhs) const { return cur_ != rhs.cur_; }

private:
    Iterator cur_;
};

// 练习 3.2 演示
void exercise_3_2_custom_reverse_iterator(){
    SHOWE("[练习 3.2] 自定义 ReverseIterator 演示");

    std::vector<int> v{1, 2, 3, 4, 5};

    // 构造: 用 v.end() 构造, 语义与 std::reverse_iterator 一致
    ReverseIterator<std::vector<int>::iterator> rit(v.end());
    ReverseIterator<std::vector<int>::iterator> rend(v.begin());

    SHOWE("自定义反向遍历:");
    for(; rit != rend; ++rit){
        SHOWE(*rit);
    }

    // base() 返回底层正向迭代器
    auto r0 = ReverseIterator<std::vector<int>::iterator>(v.end());
    SHOWE("base() == v.end() ?");
    SHOWE(yes_no(r0.base() == v.end()));

    // 与 std::reverse_iterator 行为对照
    std::vector<int> a, b;
    std::copy(r0, rend, std::back_inserter(a));
    std::copy(v.rbegin(), v.rend(), std::back_inserter(b));
    SHOWE("自定义实现与 std::reverse_iterator 结果一致 ?");
    SHOWE(yes_no(a == b));

    // 反向的 -- 操作
    auto rr = rend;
    --rr;
    SHOWE("rend 前退一步后 *rr (应为最后一个元素 5):");
    SHOWE(*rr);
}



// 练习 3.3: 使用插入迭代器 (Insert Iterator)
// 
// 插入迭代器包括:
//   - back_inserter: 在容器末尾插入
//   - front_inserter: 在容器开头插入
//   - inserter: 在指定位置插入
// 
// 提示:
//   - 使用 std::back_inserter, std::front_inserter, std::inserter
//   - 通过插入迭代器赋值实际是调用容器的 insert/push_back/push_front
// 
// 你的代码:
// 练习 3.3: 插入迭代器 (Insert Iterator)
void exercise_3_3_insert_iterator(){
    SHOWE("[练习 3.3] 插入迭代器演示");

    std::vector<int> src{1, 2, 3, 4, 5};

    // back_inserter: 在容器末尾插入
    std::vector<int> v1;
    std::copy(src.begin(), src.end(), std::back_inserter(v1));
    SHOWE("back_inserter 结果 (末尾依次追加):");
    for(const auto& e : v1){
        SHOWE(e);
    }

    // front_inserter: 在容器开头插入 (注意顺序会反转)
    std::deque<int> d;
    std::copy(src.begin(), src.end(), std::front_inserter(d));
    SHOWE("front_inserter 结果 (头部依次插入, 顺序反转):");
    for(const auto& e : d){
        SHOWE(e);
    }

    // inserter: 在指定位置插入
    std::vector<int> v2{100, 200};
    auto ins = std::inserter(v2, v2.begin());
    std::copy(src.begin(), src.end(), ins);
    SHOWE("inserter 结果 (在 begin() 处插入):");
    for(const auto& e : v2){
        SHOWE(e);
    }

    // inserter 在中间位置插入
    std::vector<int> v3{0, 9};
    auto mid = v3.begin() + 1;
    std::copy(src.begin(), src.end(), std::inserter(v3, mid));
    SHOWE("inserter 结果 (在中间位置插入):");
    for(const auto& e : v3){
        SHOWE(e);
    }
}



// 练习 3.4: 使用流迭代器 (Stream Iterator)
// 
// 流迭代器包括:
//   - istream_iterator: 从输入流读取
//   - ostream_iterator: 写入输出流
// 
// 提示:
//   - istream_iterator<T>(cin) 从流读取
//   - ostream_iterator<T>(cout) 写入流
//   - 可以用于算法，如 std::copy
// 
// 你的代码:
// 练习 3.4: 流迭代器 (Stream Iterator)
//
// 输入容错要点:
//   - istream_iterator 在流到达 EOF / 读取失败时, 会等于默认构造的 end 迭代器
//   - 因此必须先检查输入流状态, 失败时应优雅退出, 避免死循环
void exercise_3_4_stream_iterator(){
    SHOWE("[练习 3.4] 流迭代器演示");
    SHOWE("请输入若干个整数(以空格分隔), 回车结束:");

    // 先检查流状态, 避免在 EOF 状态下构造 istream_iterator
    std::cin.clear();
    std::cin.peek();
    if(!std::cin.good()){
        SHOWE("std::cin 当前不可用(EOF), 跳过流迭代器演示。");
        return;
    }

    std::vector<int> nums;
    std::istream_iterator<int> inIt(std::cin);
    std::istream_iterator<int> inEnd;                 // 默认构造 == end

    // 逐个读取, 用流状态做双重保险, 防止读到 EOF 时无限循环
    while(inIt != inEnd && std::cin.good()){
        nums.push_back(*inIt);
        ++inIt;
        if(!std::cin.good()){
            break;
        }
    }

    if(nums.empty()){
        SHOWE("未读取到任何有效整数, 流迭代器演示结束。");
        return;
    }

    SHOWE("读取到的整数个数:");
    SHOWE(nums.size());
    SHOWE("读取到的内容:");
    for(const auto& n : nums){
        SHOWE(n);
    }

    // ostream_iterator: 向输出流写入
    SHOWE("使用 ostream_iterator 写入到 ostringstream:");
    std::ostringstream oss;
    std::ostream_iterator<int> outIt(oss, ", ");
    std::copy(nums.begin(), nums.end(), outIt);
    SHOWE(oss.str());

    // 用 ostream_iterator 直接写 cout
    SHOWE("使用 ostream_iterator 直接写 cout:");
    std::ostream_iterator<int> coutIt(std::cout, " ");
    std::copy(nums.begin(), nums.end(), coutIt);
    SHOWE("");

    // 流迭代器同样满足 std::iterator_traits 的接口约定
    SHOWE("iterator_traits<istream_iterator<int>>::value_type 为 int ?");
    using IT = std::iterator_traits<std::istream_iterator<int>>;
    bool is_int = std::is_same<IT::value_type, int>::value;
    SHOWE(yes_no(is_int));
}



// ============================================================================
// 第四部分: iterator_traits (Iterator Traits)
// ============================================================================
//
// iterator_traits 允许泛型代码查询迭代器的特征类型。
// 标准定义了五种迭代器特征:
//   - difference_type: 两个迭代器之间的距离类型
//   - value_type: 迭代器指向的元素的类型
//   - pointer: 指向 value_type 的指针类型
//   - reference: value_type 的引用类型
//   - iterator_category: 迭代器类别标签
//
// 练习 4.1: 使用 iterator_traits
// 
// 提示:
//   - std::iterator_traits<T>::value_type 获取元素类型
//   - std::iterator_traits<T>::difference_type 获取距离类型
//   - std::iterator_traits<T>::iterator_category 获取类别
//   - 使用 std::distance 计算两个迭代器之间的距离
// 
// 你的代码:
// 练习 4.1: 使用 std::iterator_traits
void exercise_4_1_iterator_traits(){
    SHOWE("[练习 4.1] std::iterator_traits 演示");

    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8};
    std::list<int>   l{1, 2, 3, 4};

    // vector 的迭代器
    using VecIt = std::vector<int>::iterator;
    using VecTraits = std::iterator_traits<VecIt>;
    SHOWE("--- vector<int>::iterator ---");
    SHOWE("value_type 是 int ?");
    SHOWE(yes_no(std::is_same<VecTraits::value_type, int>::value));
    SHOWE("difference_type 是 std::ptrdiff_t ?");
    SHOWE(yes_no(std::is_same<VecTraits::difference_type, std::ptrdiff_t>::value));
    SHOWE("pointer 是 int* ?");
    SHOWE(yes_no(std::is_same<VecTraits::pointer, int*>::value));
    SHOWE("reference 是 int& ?");
    SHOWE(yes_no(std::is_same<VecTraits::reference, int&>::value));
    SHOWE("iterator_category 是 random_access_iterator_tag ?");
    SHOWE(yes_no(std::is_same<VecTraits::iterator_category,
                              std::random_access_iterator_tag>::value));

    // list 的迭代器
    using ListIt = std::list<int>::iterator;
    using ListTraits = std::iterator_traits<ListIt>;
    SHOWE("--- list<int>::iterator ---");
    SHOWE("iterator_category 是 bidirectional_iterator_tag ?");
    SHOWE(yes_no(std::is_same<ListTraits::iterator_category,
                              std::bidirectional_iterator_tag>::value));

    // std::distance
    SHOWE("--- std::distance ---");
    SHOWE("distance(v.begin(), v.end()) (vector, O(1)):");
    SHOWE(std::distance(v.begin(), v.end()));
    SHOWE("distance(l.begin(), l.end()) (list, O(n)):");
    SHOWE(std::distance(l.begin(), l.end()));

    // 原生指针的 traits
    using PtrTraits = std::iterator_traits<int*>;
    SHOWE("--- 原生指针 int* 的 traits ---");
    SHOWE("value_type 是 int ?");
    SHOWE(yes_no(std::is_same<PtrTraits::value_type, int>::value));
    SHOWE("iterator_category 是 random_access_iterator_tag ?");
    SHOWE(yes_no(std::is_same<PtrTraits::iterator_category,
                              std::random_access_iterator_tag>::value));

    // 反向迭代器的 traits (继承自底层迭代器)
    using RevTraits = std::iterator_traits<std::reverse_iterator<VecIt>>;
    SHOWE("--- reverse_iterator 的 traits ---");
    SHOWE("value_type 是 int ?");
    SHOWE(yes_no(std::is_same<RevTraits::value_type, int>::value));
    SHOWE("iterator_category 是 random_access_iterator_tag ?");
    SHOWE(yes_no(std::is_same<RevTraits::iterator_category,
                              std::random_access_iterator_tag>::value));
}



// 练习 4.2: 为自定义容器实现 iterator_traits
// 
// 提示:
//   - 在容器的迭代器类中定义五种类型
//   - 或使用特化 std::iterator_traits
//   - 定义 iterator_category 标签类 (std::forward_iterator_tag, etc.)
// 
// 你的代码:
// 练习 4.2: 为自定义容器实现 iterator_traits
//
// 下面实现一个最简单的"只读区间容器" IntRange, 其迭代器在类内定义了完整的
// 五种 iterator_traits 成员类型, 因此可以直接被 std::iterator_traits 识别。
class IntRange{
public:
    class const_iterator{
    public:
        // ===== 五种 iterator_traits 类型 =====
        using iterator_category = std::forward_iterator_tag;
        using value_type        = int;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const int*;
        using reference          = const int&;

        const_iterator() : ptr_(nullptr) {}
        explicit const_iterator(const int* p) : ptr_(p) {}

        reference operator*() const { return *ptr_; }
        pointer   operator->() const { return ptr_; }

        const_iterator& operator++(){
            ++ptr_;
            return *this;
        }
        const_iterator operator++(int){
            const_iterator tmp(*this);
            ++ptr_;
            return tmp;
        }

        bool operator==(const const_iterator& rhs) const { return ptr_ == rhs.ptr_; }
        bool operator!=(const const_iterator& rhs) const { return ptr_ != rhs.ptr_; }

    private:
        const int* ptr_;
    };

    IntRange(const int* first, const int* last) : first_(first), last_(last) {}

    const_iterator begin() const { return const_iterator(first_); }
    const_iterator end()   const { return const_iterator(last_); }
    const_iterator cbegin() const { return const_iterator(first_); }
    const_iterator cend()   const { return const_iterator(last_); }

private:
    const int* first_;
    const int* last_;
};

// 练习 4.2 演示
void exercise_4_2_custom_traits(){
    SHOWE("[练习 4.2] 自定义容器 iterator_traits 演示");

    int data[] = {10, 20, 30, 40};
    IntRange r(data, data + 4);

    using MyIt = IntRange::const_iterator;
    using MyTraits = std::iterator_traits<MyIt>;

    SHOWE("value_type 是 int ?");
    SHOWE(yes_no(std::is_same<MyTraits::value_type, int>::value));
    SHOWE("difference_type 是 std::ptrdiff_t ?");
    SHOWE(yes_no(std::is_same<MyTraits::difference_type, std::ptrdiff_t>::value));
    SHOWE("pointer 是 const int* ?");
    SHOWE(yes_no(std::is_same<MyTraits::pointer, const int*>::value));
    SHOWE("reference 是 const int& ?");
    SHOWE(yes_no(std::is_same<MyTraits::reference, const int&>::value));
    SHOWE("iterator_category 是 forward_iterator_tag ?");
    SHOWE(yes_no(std::is_same<MyTraits::iterator_category,
                              std::forward_iterator_tag>::value));

    // 自定义迭代器可以直接用于标准算法
    SHOWE("用标准算法遍历自定义容器:");
    std::vector<int> out;
    std::copy(r.begin(), r.end(), std::back_inserter(out));
    for(const auto& e : out){
        SHOWE(e);
    }

    SHOWE("std::distance 结果:");
    SHOWE(std::distance(r.begin(), r.end()));
}



// 练习 4.3: 使用 iterator_category 进行编译期分支
// 
// 提示:
//   - 使用 std::is_same 检查迭代器类别
//   - 或使用 if constexpr 根据类别选择算法
//   - 随机访问迭代器可以用 O(1) 算法
//   - 其他迭代器可能需要 O(n) 算法
// 
// 你的代码:
// 练习 4.3: 使用 iterator_category 进行编译期分支
//
// 通用函数: 求区间中第 n 个元素
//   - 随机访问迭代器: 直接 it + n, O(1)
//   - 双向/正向迭代器: 循环 ++  n 次, O(n)
// 通过 if constexpr 在编译期只实例化合法分支, 避免"未实例化分支"的编译错误。
template<typename Iterator>
typename std::iterator_traits<Iterator>::reference
nth_element_at(Iterator first, std::ptrdiff_t n){
    using Category = typename std::iterator_traits<Iterator>::iterator_category;

    if constexpr(std::is_same_v<Category, std::random_access_iterator_tag>){
        // 随机访问: 直接偏移, O(1)
        return *(first + n);
    }
    else if constexpr(std::is_same_v<Category, std::bidirectional_iterator_tag>
                   || std::is_same_v<Category, std::forward_iterator_tag>){
        // 其它类别: 逐个前进, O(n)
        Iterator it = first;
        for(std::ptrdiff_t i = 0; i < n; ++i){
            ++it;
        }
        return *it;
    }
    else{
        // 输入/输出迭代器: 无法多次解引用, 只能返回第一个
        return *first;
    }
}

// 另一个例子: 按类别选择"求长度"的算法
template<typename Iterator>
std::ptrdiff_t range_length(Iterator first, Iterator last){
    using Category = typename std::iterator_traits<Iterator>::iterator_category;

    if constexpr(std::is_same_v<Category, std::random_access_iterator_tag>){
        return last - first;              // O(1)
    }
    else if constexpr(std::is_same_v<Category, std::bidirectional_iterator_tag>){
        // 双向迭代器可以从末尾往回走, 但仍需逐个 --, O(n)
        std::ptrdiff_t n = 0;
        Iterator it = last;
        while(it != first){
            --it;
            ++n;
        }
        return n;
    }
    else{
        std::ptrdiff_t n = 0;             // O(n)
        for(Iterator it = first; it != last; ++it){
            ++n;
        }
        return n;
    }
}

// 练习 4.3 演示
void exercise_4_3_category_branch(){
    SHOWE("[练习 4.3] iterator_category 编译期分支演示");

    std::vector<int> v{10, 20, 30, 40, 50};
    std::list<int>   l{10, 20, 30, 40, 50};

    // 运行时观察: 随机访问用 O(1), list 用 O(n)
    SHOWE("vector (随机访问) 第 2 个元素:");
    SHOWE(nth_element_at(v.begin(), 2));
    SHOWE("list (双向) 第 2 个元素:");
    SHOWE(nth_element_at(l.begin(), 2));

    SHOWE("range_length(vector):");
    SHOWE(range_length(v.begin(), v.end()));
    SHOWE("range_length(list):");
    SHOWE(range_length(l.begin(), l.end()));

    // 用 std::is_same 在编译期检查类别
    using VecCat = std::iterator_traits<std::vector<int>::iterator>::iterator_category;
    using ListCat = std::iterator_traits<std::list<int>::iterator>::iterator_category;
    bool vec_is_ra = std::is_same<VecCat, std::random_access_iterator_tag>::value;
    bool list_is_bi = std::is_same<ListCat, std::bidirectional_iterator_tag>::value;
    SHOWE("vector::iterator 的类别是 random_access ?");
    SHOWE(yes_no(vec_is_ra));
    SHOWE("list::iterator 的类别是 bidirectional ?");
    SHOWE(yes_no(list_is_bi));

    // 编译期常量: 只有随机访问迭代器才为 true
    constexpr bool only_ra = std::is_same<VecCat, std::random_access_iterator_tag>::value;
    SHOWE("constexpr 判断 vector::iterator 是否随机访问:");
    SHOWE(yes_no(only_ra));

    // 自定义迭代器也能参与同一套分支逻辑
    SHOWE("自定义 RandomAccessIterator 第 2 个元素:");
    int arr[] = {10, 20, 30, 40, 50};
    SHOWE(nth_element_at(RandomAccessIterator<int>(arr), 2));
    SHOWE("自定义 ForwardIterator 第 2 个元素:");
    SHOWE(nth_element_at(ForwardIterator<int>(arr), 2));
}



// ============================================================================
// 第五部分: 迭代器工具函数 (Iterator Utility Functions)
// ============================================================================
//
// 标准库提供了一些迭代器工具函数:
//   - std::advance(it, n): 将迭代器前进 n 步
//   - std::distance(first, last): 计算两个迭代器之间的距离
//   - std::next(it, n): 返回前进 n 步后的迭代器
//   - std::prev(it, n): 返回后退 n 步后的迭代器
//
// 练习 5.1: 使用 std::advance
// 
// 提示:
//   - std::advance(it, n) 修改迭代器本身
//   - 对于随机访问迭代器是 O(1)，其他是 O(n)
// 
// 你的代码:
// 练习 5.1: 使用 std::advance
void exercise_5_1_advance(){
    SHOWE("[练习 5.1] std::advance 演示");

    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8};
    std::list<int>   l{1, 2, 3, 4, 5, 6, 7, 8};

    // advance 修改迭代器本身
    auto it = v.begin();
    std::advance(it, 3);
    SHOWE("vector: advance(begin, 3) 后 *it:");
    SHOWE(*it);

    // 负数步长需要双向及以上的迭代器
    std::advance(it, -2);
    SHOWE("再 advance(it, -2) 后 *it:");
    SHOWE(*it);

    // list (双向迭代器) 也可以
    auto lit = l.begin();
    std::advance(lit, 5);
    SHOWE("list: advance(begin, 5) 后 *it:");
    SHOWE(*lit);
    std::advance(lit, -3);
    SHOWE("list: 再 advance(it, -3) 后 *it:");
    SHOWE(*lit);

    // 自定义迭代器同样可用 (依赖 iterator_traits 的 difference_type)
    int arr[] = {1, 2, 3, 4, 5};
    RandomAccessIterator<int> rit(arr);
    std::advance(rit, 2);
    SHOWE("自定义 RandomAccessIterator advance 2 步后 *it:");
    SHOWE(*rit);

    ForwardIterator<int> fit(arr);
    std::advance(fit, 2);
    SHOWE("自定义 ForwardIterator advance 2 步后 *it:");
    SHOWE(*fit);
}



// 练习 5.2: 使用 std::distance 计算距离
// 
// 提示:
//   - std::distance(first, last) 不修改迭代器
//   - first 应该在 last 之前
//   - 对于随机访问迭代器是 O(1)，其他是 O(n)
// 
// 你的代码:
// 练习 5.2: 使用 std::distance 计算距离
void exercise_5_2_distance(){
    SHOWE("[练习 5.2] std::distance 演示");

    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8};
    std::list<int>   l{1, 2, 3, 4, 5, 6, 7, 8};

    // distance 不修改传入的迭代器
    auto first = v.begin();
    auto last  = v.end();
    auto d = std::distance(first, last);
    SHOWE("distance(v.begin(), v.end()):");
    SHOWE(d);
    SHOWE("调用后 first 仍指向第一个元素:");
    SHOWE(*first);

    // 局部区间的距离
    SHOWE("distance(v.begin()+2, v.begin()+6):");
    SHOWE(std::distance(v.begin() + 2, v.begin() + 6));

    // list 上的 distance (O(n))
    SHOWE("distance(l.begin(), l.end()):");
    SHOWE(std::distance(l.begin(), l.end()));

    // 自定义迭代器
    int arr[] = {1, 2, 3, 4, 5};
    SHOWE("distance(自定义 RandomAccessIterator):");
    SHOWE(std::distance(RandomAccessIterator<int>(arr),
                        RandomAccessIterator<int>(arr + 5)));
    SHOWE("distance(自定义 ForwardIterator):");
    SHOWE(std::distance(ForwardIterator<int>(arr),
                        ForwardIterator<int>(arr + 5)));

    // 返回类型是 difference_type
    using DT = std::iterator_traits<std::vector<int>::iterator>::difference_type;
    bool is_ptrdiff = std::is_same<decltype(d), DT>::value;
    SHOWE("返回类型是 difference_type (ptrdiff_t) ?");
    SHOWE(yes_no(is_ptrdiff));
}



// 练习 5.3: 使用 std::next 和 std::prev
// 
// 提示:
//   - std::next 返回新的迭代器，不修改原迭代器
//   - std::prev 同样返回新的迭代器
//   - 可以指定步数，默认为 1
// 
// 你的代码:
// 练习 5.3: 使用 std::next 和 std::prev
void exercise_5_3_next_prev(){
    SHOWE("[练习 5.3] std::next / std::prev 演示");

    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8};

    auto it = v.begin();

    // next 返回新迭代器, 不修改原迭代器
    auto it2 = std::next(it);
    SHOWE("next(begin) 指向的元素:");
    SHOWE(*it2);
    SHOWE("原迭代器仍指向第一个元素:");
    SHOWE(*it);

    // 指定步数
    SHOWE("next(begin, 3) 指向的元素:");
    SHOWE(*std::next(it, 3));

    // prev 需要双向及以上的迭代器
    auto itEnd = v.end();
    SHOWE("prev(end) 指向的元素:");
    SHOWE(*std::prev(itEnd));
    SHOWE("prev(end, 2) 指向的元素:");
    SHOWE(*std::prev(itEnd, 2));

    // 与 advance 组合: advance 修改, next 返回新值
    auto p = v.begin();
    std::advance(p, 4);
    auto q = std::next(p, 1);
    SHOWE("advance 4 步后 *p:");
    SHOWE(*p);
    SHOWE("next(p, 1) 的值:");
    SHOWE(*q);

    // 在自定义迭代器上使用
    int arr[] = {1, 2, 3, 4, 5};
    SHOWE("next(自定义 RandomAccessIterator) 的值:");
    SHOWE(*std::next(RandomAccessIterator<int>(arr), 2));
    SHOWE("prev(自定义 RandomAccessIterator) 的值:");
    SHOWE(*std::prev(RandomAccessIterator<int>(arr + 5), 1));
    SHOWE("next(自定义 ForwardIterator) 的值:");
    SHOWE(*std::next(ForwardIterator<int>(arr), 2));
}



// ============================================================================
// 第六部分: 自定义容器的迭代器实现
// ============================================================================
//
// 为自定义容器实现迭代器是理解迭代器机制的最佳方式。
//
// 练习 6.1: 为简单数组实现随机访问迭代器
// 
// 提示:
//   - 使用指针作为迭代器的基础
//   - 实现所有随机访问迭代器的操作
//   - 定义五种 iterator_traits 类型
// 
// 你的代码:
// 练习 6.1: 为简单数组实现随机访问迭代器
//
// ArrayContainer<T> 持有一个 C 风格数组, 其迭代器 ArrayIterator<T> 以指针为基础,
// 实现了完整的随机访问运算, 并定义了全部五种 iterator_traits 成员类型。
template<typename T, std::size_t N>
class ArrayContainer;

// 数组容器的随机访问迭代器
template<typename T>
class ArrayIterator{
public:
    // ===== 五种 iterator_traits 类型 =====
    using iterator_category = std::random_access_iterator_tag;
    using value_type        = typename std::remove_const<T>::type;
    using difference_type   = std::ptrdiff_t;
    using pointer           = T*;
    using reference          = T&;

    ArrayIterator() : ptr_(nullptr) {}
    explicit ArrayIterator(T* p) : ptr_(p) {}

    reference operator*() const { return *ptr_; }
    pointer   operator->() const { return ptr_; }

    // ++ / --
    ArrayIterator& operator++(){ ++ptr_; return *this; }
    ArrayIterator operator++(int){ ArrayIterator tmp(*this); ++ptr_; return tmp; }
    ArrayIterator& operator--(){ --ptr_; return *this; }
    ArrayIterator operator--(int){ ArrayIterator tmp(*this); --ptr_; return tmp; }

    // += / -=
    ArrayIterator& operator+=(difference_type n){ ptr_ += n; return *this; }
    ArrayIterator& operator-=(difference_type n){ ptr_ -= n; return *this; }

    // 二元 + : 迭代器 + 偏移
    ArrayIterator operator+(difference_type n) const { return ArrayIterator(ptr_ + n); }
    // 二元 + : 偏移 + 迭代器 (对称)
    friend ArrayIterator operator+(difference_type n, const ArrayIterator& it){
        return ArrayIterator(it.ptr_ + n);
    }
    // 二元 - : 迭代器 - 偏移 -> 迭代器
    ArrayIterator operator-(difference_type n) const { return ArrayIterator(ptr_ - n); }
    // 二元 - : 迭代器 - 迭代器 -> 距离 (ptrdiff_t)
    difference_type operator-(const ArrayIterator& rhs) const { return ptr_ - rhs.ptr_; }

    // 下标
    reference operator[](difference_type n) const { return ptr_[n]; }

    // 比较
    bool operator==(const ArrayIterator& rhs) const { return ptr_ == rhs.ptr_; }
    bool operator!=(const ArrayIterator& rhs) const { return ptr_ != rhs.ptr_; }
    bool operator< (const ArrayIterator& rhs) const { return ptr_ <  rhs.ptr_; }
    bool operator<=(const ArrayIterator& rhs) const { return ptr_ <= rhs.ptr_; }
    bool operator> (const ArrayIterator& rhs) const { return ptr_ >  rhs.ptr_; }
    bool operator>=(const ArrayIterator& rhs) const { return ptr_ >= rhs.ptr_; }

private:
    T* ptr_;
};

// 数组容器
template<typename T, std::size_t N>
class ArrayContainer{
public:
    using value_type      = T;
    using size_type       = std::size_t;
    using iterator        = ArrayIterator<T>;
    using const_iterator  = ArrayIterator<const T>;

    ArrayContainer() = default;

    iterator        begin()        { return iterator(data_); }
    iterator        end()          { return iterator(data_ + N); }
    const_iterator  begin()  const { return const_iterator(data_); }
    const_iterator  end()    const { return const_iterator(data_ + N); }
    const_iterator  cbegin() const { return const_iterator(data_); }
    const_iterator  cend()   const { return const_iterator(data_ + N); }

    size_type size() const { return N; }

    T& operator[](size_type i){ return data_[i]; }
    const T& operator[](size_type i) const { return data_[i]; }

private:
    T data_[N > 0 ? N : 1] = {};   // 避免零长度数组
};

// 练习 6.1 演示
void exercise_6_1_array_iterator(){
    SHOWE("[练习 6.1] 数组容器的随机访问迭代器演示");

    ArrayContainer<int, 5> arr;
    for(std::size_t i = 0; i < arr.size(); ++i){
        arr[i] = static_cast<int>(i + 1) * 10;
    }

    SHOWE("正向遍历:");
    for(auto it = arr.begin(); it != arr.end(); ++it){
        SHOWE(*it);
    }

    SHOWE("反向遍历:");
    for(auto it = arr.end(); it != arr.begin(); ){
        --it;
        SHOWE(*it);
    }

    SHOWE("偏移访问 arr.begin()+2:");
    SHOWE(*(arr.begin() + 2));
    SHOWE("下标访问 arr.begin()[3]:");
    SHOWE(arr.begin()[3]);
    SHOWE("距离 arr.end() - arr.begin():");
    SHOWE(arr.end() - arr.begin());

    // 修改元素
    for(auto it = arr.begin(); it != arr.end(); ++it){
        *it += 1;
    }
    SHOWE("全部 +1 后:");
    for(const auto& e : arr){
        SHOWE(e);
    }

    // traits 验证
    using Traits = std::iterator_traits<ArrayIterator<int>>;
    SHOWE("iterator_category 是 random_access_iterator_tag ?");
    SHOWE(yes_no(std::is_same<Traits::iterator_category,
                              std::random_access_iterator_tag>::value));

    // 与标准算法配合
    std::vector<int> out;
    std::copy(arr.begin(), arr.end(), std::back_inserter(out));
    SHOWE("std::copy 结果:");
    for(const auto& e : out){
        SHOWE(e);
    }

    // const 迭代器
    const ArrayContainer<int, 5>& carr = arr;
    SHOWE("const 容器遍历:");
    for(auto it = carr.begin(); it != carr.end(); ++it){
        SHOWE(*it);
    }
}



// 练习 6.2: 为单向链表实现正向迭代器
// 
// 提示:
//   - 正向迭代器只能 ++，不能 --
//   - 保存指向当前节点的指针
//   - end() 返回指向哨兵节点的迭代器
// 
// 你的代码:
// 练习 6.2: 为单向链表实现正向迭代器
//
// 单向链表的节点只有 next 指针, 无法回退, 因此迭代器只能是正向迭代器。
// 链表尾部挂一个"哨兵节点"(sentinel), end() 返回指向哨兵的迭代器。
// 这样遍历时就不需要判断 next == nullptr, 逻辑更统一。
template<typename T>
class ForwardList{
private:
    struct Node{
        T        value;
        Node*    next;
        explicit Node(const T& v) : value(v), next(nullptr) {}
    };

    Node* head_;     // 指向第一个真实节点
    Node* sentinel_; // 哨兵节点, 位于链表末尾, next 指向自身

public:
    // ===== 正向迭代器 =====
    class iterator{
    public:
        // ===== 五种 iterator_traits 类型 =====
        using iterator_category = std::forward_iterator_tag;
        using value_type        = typename std::remove_const<T>::type;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference          = T&;

        iterator() : node_(nullptr) {}
        explicit iterator(Node* n) : node_(n) {}

        reference operator*() const { return node_->value; }
        pointer   operator->() const { return &node_->value; }

        iterator& operator++(){
            node_ = node_->next;
            return *this;
        }
        iterator operator++(int){
            iterator tmp(*this);
            node_ = node_->next;
            return tmp;
        }

        bool operator==(const iterator& rhs) const { return node_ == rhs.node_; }
        bool operator!=(const iterator& rhs) const { return node_ != rhs.node_; }

        Node* node() const { return node_; }

    private:
        Node* node_;
    };

    ForwardList() : head_(nullptr) {
        sentinel_ = new Node(T());   // 哨兵
        sentinel_->next = sentinel_;
    }

    ~ForwardList(){
        // 释放所有真实节点
        Node* p = head_;
        while(p != nullptr){
            Node* nx = p->next;
            delete p;
            p = nx;
        }
        delete sentinel_;
    }

    ForwardList(const ForwardList&) = delete;
    ForwardList& operator=(const ForwardList&) = delete;

    void push_front(const T& v){
        Node* n = new Node(v);
        n->next = head_;
        head_ = n;
    }

    void push_back(const T& v){
        Node* n = new Node(v);
        if(head_ == nullptr){
            head_ = n;
            n->next = sentinel_;
            return;
        }
        Node* p = head_;
        while(p->next != sentinel_){
            p = p->next;
        }
        p->next = n;
        n->next = sentinel_;
    }

    bool empty() const { return head_ == nullptr; }

    iterator begin(){ return iterator(head_); }
    iterator end()  { return iterator(sentinel_); }

    // const 版本
    class const_iterator{
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = typename std::remove_const<T>::type;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference          = const T&;

        const_iterator() : node_(nullptr) {}
        explicit const_iterator(const Node* n) : node_(n) {}

        reference operator*() const { return node_->value; }
        pointer   operator->() const { return &node_->value; }

        const_iterator& operator++(){
            node_ = node_->next;
            return *this;
        }
        const_iterator operator++(int){
            const_iterator tmp(*this);
            node_ = node_->next;
            return tmp;
        }

        bool operator==(const const_iterator& rhs) const { return node_ == rhs.node_; }
        bool operator!=(const const_iterator& rhs) const { return node_ != rhs.node_; }

    private:
        const Node* node_;
    };

    const_iterator begin() const { return const_iterator(head_); }
    const_iterator end()   const { return const_iterator(sentinel_); }
    const_iterator cbegin() const { return const_iterator(head_); }
    const_iterator cend()   const { return const_iterator(sentinel_); }
};

// 练习 6.2 演示
void exercise_6_2_forward_list_iterator(){
    SHOWE("[练习 6.2] 单向链表的正向迭代器演示");

    ForwardList<int> fl;
    fl.push_back(1);
    fl.push_back(2);
    fl.push_back(3);
    fl.push_front(0);

    SHOWE("正向遍历:");
    for(auto it = fl.begin(); it != fl.end(); ++it){
        SHOWE(*it);
    }

    SHOWE("const 遍历:");
    const ForwardList<int>& cfl = fl;
    for(auto it = cfl.begin(); it != cfl.end(); ++it){
        SHOWE(*it);
    }

    SHOWE("通过迭代器修改元素 (*it):");
    for(auto it = fl.begin(); it != fl.end(); ++it){
        *it *= 100;
    }
    for(const auto& e : fl){
        SHOWE(e);
    }

    // traits 验证
    using Traits = std::iterator_traits<ForwardList<int>::iterator>;
    SHOWE("iterator_category 是 forward_iterator_tag ?");
    SHOWE(yes_no(std::is_same<Traits::iterator_category,
                              std::forward_iterator_tag>::value));

    // 与标准算法配合
    std::vector<int> out;
    std::copy(fl.begin(), fl.end(), std::back_inserter(out));
    SHOWE("std::copy 结果:");
    for(const auto& e : out){
        SHOWE(e);
    }

    // std::distance 对正向迭代器是 O(n)
    SHOWE("std::distance:");
    SHOWE(std::distance(fl.begin(), fl.end()));
}



// 练习 6.3: 为双向链表实现双向迭代器
// 
// 提示:
//   - 在正向迭代器基础上支持 --
//   - 保存前驱和后继指针
//   - 可以反向遍历链表
// 
// 你的代码:
// 练习 6.3: 为双向链表实现双向迭代器
//
// 双向链表节点同时保存 prev 和 next, 因此迭代器可以自由前进/后退。
// 首尾各有一个哨兵节点, end() 指向尾部哨兵。
template<typename T>
class DoublyList{
private:
    struct Node{
        T     value;
        Node* prev;
        Node* next;
        explicit Node(const T& v) : value(v), prev(nullptr), next(nullptr) {}
    };

    Node* head_;      // 头部哨兵
    Node* tail_;      // 尾部哨兵 (end())
    std::size_t size_;

public:
    // ===== 双向迭代器 =====
    class iterator{
    public:
        // ===== 五种 iterator_traits 类型 =====
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type        = typename std::remove_const<T>::type;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference          = T&;

        iterator() : node_(nullptr) {}
        explicit iterator(Node* n) : node_(n) {}

        reference operator*() const { return node_->value; }
        pointer   operator->() const { return &node_->value; }

        // 前向移动: 走 next
        iterator& operator++(){
            node_ = node_->next;
            return *this;
        }
        iterator operator++(int){
            iterator tmp(*this);
            node_ = node_->next;
            return tmp;
        }

        // 后向移动: 走 prev
        iterator& operator--(){
            node_ = node_->prev;
            return *this;
        }
        iterator operator--(int){
            iterator tmp(*this);
            node_ = node_->prev;
            return tmp;
        }

        bool operator==(const iterator& rhs) const { return node_ == rhs.node_; }
        bool operator!=(const iterator& rhs) const { return node_ != rhs.node_; }

        Node* node() const { return node_; }

    private:
        Node* node_;
    };

    DoublyList() : head_(nullptr), tail_(nullptr), size_(0){
        head_ = new Node(T());
        tail_ = new Node(T());
        head_->next = tail_;
        head_->prev = nullptr;
        tail_->prev = head_;
        tail_->next = nullptr;
    }

    ~DoublyList(){
        Node* p = head_->next;
        while(p != tail_){
            Node* nx = p->next;
            delete p;
            p = nx;
        }
        delete head_;
        delete tail_;
    }

    DoublyList(const DoublyList&) = delete;
    DoublyList& operator=(const DoublyList&) = delete;

    void push_back(const T& v){
        Node* n = new Node(v);
        n->prev = tail_->prev;
        n->next = tail_;
        tail_->prev->next = n;
        tail_->prev = n;
        ++size_;
    }

    void push_front(const T& v){
        Node* n = new Node(v);
        n->next = head_->next;
        n->prev = head_;
        head_->next->prev = n;
        head_->next = n;
        ++size_;
    }

    // 双向链表删除节点后, 只有被删节点的迭代器失效
    iterator erase(iterator pos){
        Node* n = pos.node();
        n->prev->next = n->next;
        n->next->prev = n->prev;
        iterator next_it(n->next);
        delete n;
        --size_;
        return next_it;
    }

    bool empty() const { return size_ == 0; }
    std::size_t size() const { return size_; }

    iterator begin(){ return iterator(head_->next); }
    iterator end()  { return iterator(tail_); }

    class const_iterator{
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type        = typename std::remove_const<T>::type;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference          = const T&;

        const_iterator() : node_(nullptr) {}
        explicit const_iterator(const Node* n) : node_(n) {}

        reference operator*() const { return node_->value; }
        pointer   operator->() const { return &node_->value; }

        const_iterator& operator++(){
            node_ = node_->next;
            return *this;
        }
        const_iterator operator++(int){
            const_iterator tmp(*this);
            node_ = node_->next;
            return tmp;
        }
        const_iterator& operator--(){
            node_ = node_->prev;
            return *this;
        }
        const_iterator operator--(int){
            const_iterator tmp(*this);
            node_ = node_->prev;
            return tmp;
        }

        bool operator==(const const_iterator& rhs) const { return node_ == rhs.node_; }
        bool operator!=(const const_iterator& rhs) const { return node_ != rhs.node_; }

    private:
        const Node* node_;
    };

    const_iterator begin() const { return const_iterator(head_->next); }
    const_iterator end()   const { return const_iterator(tail_); }
    const_iterator cbegin() const { return const_iterator(head_->next); }
    const_iterator cend()   const { return const_iterator(tail_); }
};

// 练习 6.3 演示
void exercise_6_3_bidirectional_list_iterator(){
    SHOWE("[练习 6.3] 双向链表的双向迭代器演示");

    DoublyList<int> dl;
    dl.push_back(1);
    dl.push_back(2);
    dl.push_back(3);
    dl.push_back(4);
    dl.push_front(0);

    SHOWE("正向遍历:");
    for(auto it = dl.begin(); it != dl.end(); ++it){
        SHOWE(*it);
    }

    SHOWE("反向遍历 (使用 operator--):");
    for(auto it = dl.end(); it != dl.begin(); ){
        --it;
        SHOWE(*it);
    }

    SHOWE("从 begin() 前进两步再后退一步:");
    auto it = dl.begin();
    std::advance(it, 2);
    SHOWE(*it);
    --it;
    SHOWE("后退一步后:");
    SHOWE(*it);

    SHOWE("const 遍历:");
    const DoublyList<int>& cdl = dl;
    for(auto cit = cdl.begin(); cit != cdl.end(); ++cit){
        SHOWE(*cit);
    }

    // traits 验证
    using Traits = std::iterator_traits<DoublyList<int>::iterator>;
    SHOWE("iterator_category 是 bidirectional_iterator_tag ?");
    SHOWE(yes_no(std::is_same<Traits::iterator_category,
                              std::bidirectional_iterator_tag>::value));

    // erase 返回下一个元素的迭代器
    SHOWE("erase 第二个元素后:");
    auto first = dl.begin();
    auto second = std::next(first);
    dl.erase(second);
    for(const auto& e : dl){
        SHOWE(e);
    }
    SHOWE("元素个数:");
    SHOWE(dl.size());
}



// ============================================================================
// 第七部分: 迭代器失效 (Iterator Invalidation)
// ============================================================================
//
// 修改容器可能导致迭代器失效，理解失效规则非常重要。
//
// 练习 7.1: 理解 vector 的迭代器失效
// 
// 提示:
//   - vector 扩容时，所有迭代器会失效
//   - 在中间插入/删除元素时，当前位置之后的迭代器会失效
//   - erase() 返回的迭代器指向被删除元素的下一个
// 
// 你的代码:
// 练习 7.1: 理解 vector 的迭代器失效
//
// 安全演示要点:
//   解引用已失效的迭代器属于未定义行为(UB), 实际运行会崩溃或读到垃圾数据。
//   因此本练习只比较迭代器所指向的内存地址, 不做解引用。
void exercise_7_1_vector_invalidation(){
    SHOWE("[练习 7.1] vector 迭代器失效演示");

    // ---- 情形 1: 扩容导致所有迭代器失效 ----
    SHOWE("--- 情形1: push_back 触发扩容, 所有迭代器失效 ---");
    std::vector<int> v;
    v.reserve(1);                       // 只预留 1 个容量, 便于触发扩容

    v.push_back(1);
    auto it = v.begin();
    const void* addr_before = &(*it);   // 记录首元素地址
    SHOWE("扩容前首元素地址:");
    SHOWE(addr_before);

    v.push_back(2);                    // 触发扩容 -> 重新分配缓冲区
    const void* addr_after = &(*v.begin());
    SHOWE("扩容后首元素地址:");
    SHOWE(addr_after);
    SHOWE("地址是否发生变化 (变化即说明迭代器已失效):");
    SHOWE(yes_no(addr_before != addr_after));
    SHOWE("注意: 此处不再解引用旧迭代器 it, 因为那是未定义行为(UB)!");

    // ---- 情形 2: 插入/删除元素使后续迭代器失效 ----
    SHOWE("--- 情形2: 插入元素后, 插入点之后的迭代器失效 ---");
    std::vector<int> v2{1, 2, 3, 4, 5};
    v2.reserve(16);                     // 预留容量, 避免扩容干扰观察

    auto it2 = v2.begin();
    std::advance(it2, 3);               // 指向元素 4
    const void* addr_v2_before = &(*it2);
    SHOWE("插入前第4个元素地址:");
    SHOWE(addr_v2_before);

    v2.insert(v2.begin() + 1, 99);      // 在中间插入, 触发元素后移
    const void* addr_v2_after = &(*(v2.begin() + 4));  // 重新获取同一位置的元素
    SHOWE("插入后同一逻辑位置(第5个)元素地址:");
    SHOWE(addr_v2_after);
    SHOWE("地址是否发生变化 (变化说明旧迭代器失效):");
    SHOWE(yes_no(addr_v2_before != addr_v2_after));

    // ---- 情形 3: erase 返回指向下一个元素的迭代器 ----
    SHOWE("--- 情形3: erase 返回的迭代器指向被删元素的下一个 ---");
    std::vector<int> v3{10, 20, 30, 40, 50};
    auto it3 = v3.begin();
    std::advance(it3, 2);               // 指向 30
    auto next_it = v3.erase(it3);       // 返回指向 40 的迭代器
    SHOWE("erase 后返回的迭代器指向:");
    SHOWE(*next_it);
    SHOWE("容器剩余内容:");
    for(const auto& e : v3){
        SHOWE(e);
    }

    // ---- 情形 4: 正确的做法 —— 修改后重新获取迭代器 ----
    SHOWE("--- 情形4: 修改容器后重新获取迭代器(正确做法) ---");
    std::vector<int> v4{1, 2, 3, 4, 5};
    v4.reserve(16);
    auto it4 = v4.begin();
    std::advance(it4, 2);
    v4.insert(v4.begin() + 1, 88);
    it4 = v4.begin();                   // 重新获取, 避免使用失效迭代器
    std::advance(it4, 3);
    SHOWE("重新获取迭代器后指向:");
    SHOWE(*it4);
}



// 练习 7.2: 理解 list 的迭代器失效
// 
// 提示:
//   - list 的迭代器在插入/删除时不会失效（除了被删除的）
//   - 只有被删除元素的迭代器会失效
//   - splice 操作不会使任何迭代器失效
// 
// 你的代码:
// 练习 7.2: 理解 list 的迭代器失效
//
// 与 vector 不同, list 的节点是独立分配的, 增删元素不会移动其它节点,
// 因此除被删除节点外, 其余迭代器全部保持有效。
void exercise_7_2_list_invalidation(){
    SHOWE("[练习 7.2] list 迭代器失效演示");

    std::list<int> l{1, 2, 3, 4, 5};

    // ---- 情形 1: 插入元素不使已有迭代器失效 ----
    SHOWE("--- 情形1: 插入元素后, 原有迭代器仍然有效 ---");
    auto it = l.begin();
    std::advance(it, 2);                // 指向 3
    const void* addr_before = &(*it);
    SHOWE("插入前指向 3 的元素地址:");
    SHOWE(addr_before);

    l.insert(l.begin(), 0);             // 在头部插入, 不会移动已有节点
    const void* addr_after = &(*it);    // 同一个迭代器仍然可以安全解引用
    SHOWE("插入后同一迭代器指向的地址:");
    SHOWE(addr_after);
    SHOWE("地址是否保持不变:");
    SHOWE(yes_no(addr_before == addr_after));
    SHOWE("该迭代器当前仍指向:");
    SHOWE(*it);

    // ---- 情形 2: 删除元素只使被删元素的迭代器失效 ----
    SHOWE("--- 情形2: 删除元素只影响被删元素的迭代器 ---");
    auto it_target = l.begin();
    std::advance(it_target, 1);         // 指向将被删除的元素
    auto it_other  = l.begin();
    std::advance(it_other, 3);          // 指向另一个元素
    const void* addr_other_before = &(*it_other);
    SHOWE("删除前, 另一元素地址:");
    SHOWE(addr_other_before);

    l.erase(it_target);
    const void* addr_other_after = &(*it_other);
    SHOWE("删除后, 另一元素地址:");
    SHOWE(addr_other_after);
    SHOWE("地址是否保持不变 (说明该迭代器未失效):");
    SHOWE(yes_no(addr_other_before == addr_other_after));
    SHOWE("该迭代器当前仍指向:");
    SHOWE(*it_other);
    SHOWE("注意: 被删除元素自身的迭代器已失效, 不能解引用!");

    // ---- 情形 3: splice 不使任何迭代器失效 ----
    SHOWE("--- 情形3: splice 不使任何迭代器失效 ---");
    std::list<int> l2{100, 200, 300};
    auto it_src = l2.begin();
    auto it_dst = l.begin();
    const void* addr_src_before = &(*it_src);
    const void* addr_dst_before = &(*it_dst);

    l.splice(l.begin(), l2);            // 把 l2 的全部元素搬到 l 的头部

    const void* addr_src_after = &(*it_src);
    const void* addr_dst_after = &(*it_dst);
    SHOWE("splice 后源迭代器地址保持不变:");
    SHOWE(yes_no(addr_src_before == addr_src_after));
    SHOWE("splice 后目标迭代器地址保持不变:");
    SHOWE(yes_no(addr_dst_before == addr_dst_after));
    SHOWE("splice 后 l 的内容:");
    for(const auto& e : l){
        SHOWE(e);
    }
    SHOWE("splice 后 l2 的内容 (已为空):");
    for(const auto& e : l2){
        SHOWE(e);
    }
    SHOWE("(以上无输出表示 l2 已为空)");

    // ---- 情形 4: 对比 vector ----
    SHOWE("--- 情形4: 对比 vector ---");
    std::vector<int> vv{1, 2, 3};
    vv.reserve(16);
    auto vit = vv.begin();
    const void* vaddr = &(*vit);
    vv.insert(vv.begin() + 1, 99);
    const void* vaddr2 = &(*(vv.begin() + 2));
    SHOWE("vector 插入后同逻辑位置地址是否变化:");
    SHOWE(yes_no(vaddr != vaddr2));
    SHOWE("结论: vector 插入会使后续迭代器失效, list 不会。");
}



// ============================================================================
// 验证清单
// ============================================================================
//
// 完成以上所有练习后，确保你能够:
// 
// [ ] 理解迭代器的概念和作用
// [ ] 掌握五种迭代器类别及其支持的操作
// [ ] 理解正向、双向、随机访问迭代器的区别
// [ ] 能够使用迭代器适配器
// [ ] 理解 iterator_traits 的概念
// [ ] 能够为自定义容器实现迭代器
// [ ] 理解迭代器失效的原因和规则
// 
// 编译验证命令（C++17）:
//   g++ -std=c++17 -Wall -Wextra -c iterator_exercises.hpp
// 
// 编译验证命令（C++20）:
//   g++ -std=c++20 -Wall -Wextra -c iterator_exercises.hpp
// 
// 运行验证（创建测试文件后）:
//   g++ -std=c++20 -Wall -Wextra test_iterator.cpp -o test && ./test
//
// ============================================================================

#endif
