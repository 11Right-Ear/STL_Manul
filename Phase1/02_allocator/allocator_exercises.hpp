/*
 * ============================================================================
 * Phase 1 - 内存分配器练习
 * ============================================================================
 * 
 * 本文件包含内存分配器编程的各种练习。使用 // 你的代码: 注释标注每个需要完成的部分。
 * 不要删除任何注释，只在注释下方编写你的代码。
 * 
 * 学习目标:
 *   1. 理解 std::allocator 的概念和作用
 *   2. 掌握 allocator 的基本接口 (allocate, deallocate, construct, destroy)
 *   3. 理解 allocator_traits 的概念和作用
 *   4. 能够实现自定义的内存分配器
 *   5. 理解内存池分配器的原理和实现
 *   6. 了解特殊的分配器 (scoped_allocator_adaptor, polymorphic_allocator)
 * 
 * 建议完成顺序:
 *   1. 先完成 allocator 基础练习
 *   2. 然后完成自定义分配器练习
 *   3. 接着完成 allocator_traits 练习
 *   4. 再完成内存池分配器练习
 *   5. 最后完成特殊分配器练习
 * 
 * allocator 基本接口:
 *   - allocate(n): 分配能容纳 n 个对象的未初始化内存
 *   - deallocate(p, n): 释放内存，指针 p 必须是 allocate 返回的
 *   - construct(p, args): 在未初始化的内存 p 构造对象 (C++17 前)
 *   - destroy(p): 销毁对象 (C++17 前)
 * 
 * C++17 后 construct/destroy 被废弃，推荐使用:
 *   - std::uninitialized_copy, std::uninitialized_fill 等
 *   - ::new (p) T(args) 进行构造
 *   - p->~T() 进行销毁
 * 
 * ============================================================================
 */

#ifndef ALLOCATOR_EXERCISES_HPP
#define ALLOCATOR_EXERCISES_HPP

#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <string>
#include <type_traits>
#include <cstddef>
#include <cstdlib>
#include <new>

#define ENTER '\n';
#define SHOW(x) std::cout << x 
#define SHOWE(x) std::cout << x << '\n'
#define PUTIN(x) std::cin >> x 
#define SPACE "    "

// ============================================================================
// 第一部分: std::allocator 基础
// ============================================================================
//
// std::allocator 是 STL 容器默认使用的分配器。
// 它提供了内存分配和对象构造/销毁的接口。
//
// 练习 1.1: 使用 std::allocator 分配内存
// 
// 提示: 
//   - 使用 std::allocator<T>::allocate(n) 分配 n 个 T 类型的未初始化内存
//   - allocate 返回 T* 指针
//   - 分配的内存是未初始化的，需要手动构造对象
//   - 必须调用 deallocate 释放内存
// 
// 你的代码:



// 练习 1.2: 使用 allocator 构造和销毁对象 (C++17 前)
// 
// 提示:
//   - 使用 allocator.construct(p, args) 在 p 指向的内存构造对象
//   - 使用 allocator.destroy(p) 销毁对象
//   - C++17 后这些函数被废弃，使用 placement new 和显式析构
//   - 记住包含 <new> 头文件以使用 placement new
// 
// 你的代码:



// 练习 1.3: 使用 C++17 的 uninitialized 系列函数
// 
// 提示:
//   - std::uninitialized_copy(begin, end, dest): 从范围复制到未初始化内存
//   - std::uninitialized_fill(begin, end, value): 用值填充未初始化内存
//   - std::uninitialized_default_construct(begin, end): 默认构造
//   - std::destroy(begin, end): 销毁所有对象
// 
// 你的代码:



// 练习 1.4: 使用 allocator 的 traits
// 
// 提示:
//   - std::allocator_traits<Alloc> 提供了一组静态函数
//   - traits::allocate(alloc, n) 分配内存
//   - traits::deallocate(alloc, p, n) 释放内存
//   - traits::construct(alloc, p, args) 构造对象
//   - traits::destroy(alloc, p) 销毁对象
// 
// 你的代码:



// ============================================================================
// 第二部分: 自定义分配器
// ============================================================================
//
// 自定义分配器需要满足特定的接口要求。
// 最小接口只需 allocate 和 deallocate。
// 完整接口还需要定义类型和函数。
//
// 练习 2.1: 实现最简单的自定义分配器
// 
// 提示:
//   - 定义模板类 SimpleAllocator
//   - 必须提供 allocate(size_t n) 方法
//   - 必须提供 deallocate(T* p, size_t n) 方法
//   - 使用 ::operator new 和 ::operator delete
// 
// 你的代码:



// 练习 2.2: 实现完整的标准分配器接口
// 
// 标准分配器需要定义:
//   - value_type: 分配器管理的类型
//   - allocate(size_type n): 分配内存
//   - deallocate(pointer p, size_type n): 释放内存
//   - construct(pointer p, const_reference val): 构造对象 (可选)
//   - destroy(pointer p): 销毁对象 (可选)
// 
// 提示:
//   - 使用 static_assert 确保类型匹配
//   - 考虑异常安全性
// 
// 你的代码:



// 练习 2.3: 使用 allocate_with_boundary 进行对齐分配
// 
// 提示:
//   - 有些场景需要对齐内存 (如 SIMD 对齐)
//   - 使用 alignas 或 posix_memalign/aligned_alloc
//   - C++17 提供 std::align_val_t 用于对齐
// 
// 你的代码:



// ============================================================================
// 第三部分: 内存池分配器 (Memory Pool Allocator)
// ============================================================================
//
// 内存池分配器预先分配一大块内存，从中分配小对象。
// 优点: 减少系统调用，提高分配/释放效率，减少碎片。
//
// 练习 3.1: 实现固定大小块内存池
// 
// 设计要点:
//   - 预先分配一个大内存块
//   - 将内存划分为固定大小的块
//   - 使用链表管理空闲块
//   - allocate() 从空闲链表取出一块
//   - deallocate() 将块归还空闲链表
// 
// 提示:
//   - 定义 Block 结构，包含指向下一个空闲块的指针
//   - 使用联合体复用空闲块的空间存储指针
//   - 处理内存池耗尽的情况
// 
// 你的代码:



// 练习 3.2: 实现可变大小块内存池 (简单版本)
// 
// 设计要点:
//   - 使用多个固定大小池管理不同大小的请求
//   - 或使用最佳适配策略
// 
// 提示:
//   - 可以参考 Doug Lea 的 malloc 实现
//   - 维护多个空闲链表，每个链表管理特定大小的块
// 
// 你的代码:



// 练习 3.3: 使用内存池分配器优化 vector
// 
// 提示:
//   - 使用自定义分配器创建 vector
//   - 对比默认分配器和内存池分配器的性能
//   - 可以使用 std::chrono 测量时间
// 
// 你的代码:



// ============================================================================
// 第四部分: allocator_traits
// ============================================================================
//
// allocator_traits 是分配器和 STL 容器之间的桥梁。
// 它提供了一组标准化的接口，即使分配器没有实现某些方法，
// traits 也可以提供默认实现。
//
// 练习 4.1: 使用 allocator_traits 查询分配器属性
// 
// allocator_traits 提供的类型:
//   - allocator_type: 分配器类型
//   - value_type: 分配的元素类型
//   - pointer, const_pointer, reference, const_reference, etc.
//   - size_type: 大小类型
//   - difference_type: 指针距离类型
// 
// 提示:
//   - 使用 std::allocator_traits<Alloc>::... 访问
// 
// 你的代码:



// 练习 4.2: 实现支持 rebind 的分配器
// 
// rebind 允许将一种类型的分配器转换为另一种类型的分配器。
// 例如: std::list<T, Alloc> 内部需要为节点分配内存，
//       它使用 std::allocator_traits<Alloc>::rebind<Node>::other
// 
// 提示:
//   - 在分配器中定义 struct rebind { using other = ...; };
//   - 或者让 allocator_traits 使用默认实现
// 
// 你的代码:



// 练习 4.3: 实现带有状态的分配器
// 
// 提示:
//   - 分配器可以有成员变量存储状态
//   - 例如: 记录分配次数、统计信息等
//   - 两个容器可以使用同一个分配器实例（共享状态）
// 
// 你的代码:



// ============================================================================
// 第五部分: 特殊的分配器
// ============================================================================
//
// 标准库提供了一些特殊的分配器用于特定场景。
//
// 练习 5.1: 使用 scoped_allocator_adaptor
// 
// scoped_allocator_adaptor 用于嵌套容器的内存管理。
// 例如: vector<vector<int>> 需要内外层都使用分配器。
// 
// 提示:
//   - 使用 std::scoped_allocator_adaptor<OuterAlloc, InnerAlloc...>
//   - 内部容器自动使用外部容器的分配器
//   - C++17 特性
// 
// 你的代码:



// 练习 5.2: 使用 polymorphic_allocator (C++17)
// 
// polymorphic_allocator 允许在运行时改变分配策略。
// 它内部使用 std::pmr::memory_resource 实现。
// 
// 提示:
//   - 使用 std::pmr::polymorphic_allocator
//   - 使用 std::pmr::vector, std::pmr::string 等容器
//   - 可以设置不同的 memory_resource
// 
// 你的代码:



// 练习 5.3: 实现自定义的 memory_resource
// 
// 提示:
//   - 继承 std::pmr::memory_resource
//   - 实现 do_allocate, do_deallocate, do_is_equal
//   - 可以创建简单的内存池实现
// 
// 你的代码:



// ============================================================================
// 第六部分: RAII 和分配器
// ============================================================================
//
// 将分配器与 RAII 模式结合可以实现自动内存管理。
//
// 练习 6.1: 实现 RAII 内存管理类
// 
// 提示:
//   - 模板类管理一个指向 T 类型的指针
//   - 在构造时分配内存并构造对象
//   - 在析构时销毁对象并释放内存
//   - 使用自定义分配器
// 
// 你的代码:



// 练习 6.2: 实现 unique_ptr 风格的分配器感知指针
// 
// 提示:
//   - std::unique_ptr 不是分配器感知的
//   - 可以自定义 deleter 并实现类似功能
//   - deleter 可以包含分配器状态
// 
// 你的代码:



// ============================================================================
// 第七部分: 分配器的高级话题
// ============================================================================
//
// 练习 7.1: 实现线程安全的分配器 (简单版本)
// 
// 提示:
//   - 使用 mutex 保护共享状态
//   - 注意分配/释放操作的原子性
//   - 简单的实现可能成为性能瓶颈
// 
// 你的代码:



// 练习 7.2: 实现带有诊断信息的分配器
// 
// 提示:
//   - 记录分配大小、分配位置（__FILE__, __LINE__）
//   - 记录分配/释放的统计信息
//   - 可以检测内存泄漏
// 
// 你的代码:



// ============================================================================
// 验证清单
// ============================================================================
//
// 完成以上所有练习后，确保你能够:
// 
// [ ] 理解 std::allocator 的概念和作用
// [ ] 掌握 allocate/deallocate 的用法
// [ ] 理解 C++17 前后构造/销毁对象方式的变化
// [ ] 能够实现自定义分配器
// [ ] 理解 allocator_traits 的概念和作用
// [ ] 能够实现内存池分配器
// [ ] 了解特殊分配器 (scoped_allocator_adaptor, polymorphic_allocator)
// 
// 编译验证命令（C++17）:
//   g++ -std=c++17 -Wall -Wextra -c allocator_exercises.hpp
// 
// 编译验证命令（C++20）:
//   g++ -std=c++20 -Wall -Wextra -c allocator_exercises.hpp
// 
// 运行验证（创建测试文件后）:
//   g++ -std=c++20 -Wall -Wextra test_allocator.cpp -o test && ./test
//
// ============================================================================

#endif
