# Phase 1: 迭代器和内存管理 - 学习计划

**预计时间**: 15-20 小时  
**前置要求**: 完成 Phase 0 (模板编程基础)

---

## 目录结构

```
Phase1/
├── 01_iterator/           # 迭代器
├── 02_allocator/          # 内存分配器
├── 03_traits/             # 类型特征
└── LEARNING_PLAN.md       # 本文件
```

---

## 依赖关系图

```
┌─────────────────────────────────────────────────────────┐
│                    Phase 0 基础设施                       │
│              (模板编程 → 类型推导 → 编译期计算)             │
└─────────────────────────────────────────────────────────┘
                               │
                               ▼
┌─────────────────────────────────────────────────────────┐
│                    Phase 1                               │
│              (迭代器 → 分配器 → 类型特征)                   │
└─────────────────────────────────────────────────────────┘
                               │
                               ▼
                     ┌─────────────────┐
                     │   Phase 2       │
                     │   容器实现      │
                     └─────────────────┘
```

---

## Week 1: 迭代器 (6-8小时)

### 1.1 迭代器基础 (2小时)
- [ ] 迭代器的概念和作用
- [ ] 迭代器的基本操作 (++、--、*、->)
- [ ] 练习: 实现简单的正向迭代器

### 1.2 迭代器类别 (Iterator Categories) (2小时)
- [ ] 输入迭代器 / 输出迭代器
- [ ] 前向迭代器 (Forward Iterator)
- [ ] 双向迭代器 (Bidirectional Iterator)
- [ ] 随机访问迭代器 (Random Access Iterator)
- [ ] 练习: 实现各种迭代器类别

### 1.3 迭代器适配器 (Iterator Adapters) (2小时)
- [ ] 反向迭代器 (reverse_iterator)
- [ ] 插入迭代器 (inserter, back_inserter, front_inserter)
- [ ] 流迭代器 (istream_iterator, ostream_iterator)
- [ ] 练习: 使用和实现迭代器适配器

### 1.4 迭代器特征 (iterator_traits) (1小时)
- [ ] iterator_traits 的概念和作用
- [ ] 五种迭代器特征: difference_type, value_type, pointer, reference, iterator_category
- [ ] 练习: 为自定义容器实现 iterator_traits

---

## Week 2: 内存分配器 (5-6小时)

### 2.1 allocator 概念 (1小时)
- [ ] std::allocator 的基本概念
- [ ] allocate() 和 deallocate() 操作
- [ ] construct() 和 destroy() (C++17 前)
- [ ] 练习: 理解 allocator 的基本接口

### 2.2 自定义分配器 (1.5小时)
- [ ] 实现简单的内存池分配器
- [ ] 实现arena分配器
- [ ] 练习: 实现一个简单的池分配器

### 2.3 分配器特性和 Traits (1.5小时)
- [ ] allocator_traits 的概念
- [ ] 自定义分配器需要定义的类型和函数
- [ ] 练习: 为分配器实现 allocator_traits 支持

### 2.4 特殊分配器 (1.5小时)
- [ ] scoped_allocator_adaptor
- [ ] polymorphic_allocator (C++17)
- [ ] 练习: 使用和实现特殊的分配器

---

## Week 3: 类型特征 (Type Traits) (4-6小时)

### 3.1 类型特征基础 (1.5小时)
- [ ] type_traits 头文件简介
- [ ] 类型查询: is_pointer, is_integral, is_class, etc.
- [ ] 类型转换: remove_const, add_pointer, etc.
- [ ] 练习: 使用标准 type_traits

### 3.2 类型操作 (Type Manipulation) (1.5小时)
- [ ] conditional, enable_if
- [ ] decay, common_type
- [ ] 练习: 实现类型选择和转换工具

### 3.3 自定义类型特征 (1.5小时)
- [ ] 实现自定义的 type trait
- [ ] SFINAE 与 type traits 结合使用
- [ ] 练习: 实现 is_container trait

### 3.4 C++17/20 类型特征 (1小时)
- [ ] void_t 惯用法
- [ ] conjunction, disjunction, negation
- [ ] 练习: 使用 C++17/20 类型特征

---

## 验证标准

完成 Phase 1 后，你应当能够：

1. ✅ 理解并实现各种迭代器类别
2. ✅ 使用迭代器适配器处理不同场景
3. ✅ 为自定义容器实现迭代器
4. ✅ 理解并使用 std::allocator
5. ✅ 实现自定义内存分配器
6. ✅ 使用 type_traits 进行类型操作
7. ✅ 为 Phase 2 的容器实现打下坚实基础

---

## 常见错误清单

| 错误 | 原因 | 解决方案 |
|------|------|----------|
| 迭代器失效 | 容器修改后未更新迭代器 | 在修改容器后重新获取迭代器 |
| 迭代器类别不匹配 | 使用了不支持的操作 | 了解各迭代器类别的能力 |
| 分配器类型不匹配 | allocator_traits 未正确定义 | 实现完整的分配器接口 |
| type trait 误用 | 对 trait 返回值理解错误 | 仔细阅读 trait 的返回类型 |

---

## 下一步

完成 Phase 1 后，进入 [Phase 2: 容器实现](../CPPSTL_Learning_Plan.md#phase-2-容器实现)

- `include/cppSTL/containers/sequence/`
- `include/cppSTL/containers/associative/`
