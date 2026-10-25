// #include "Phase0/01_template_basics/template_exercises.hpp"
// #include "Phase0/02_type_deduction/type_deduction_exercises.hpp"
#include "Phase1/01_iterator/iterator_exercises.hpp"

int main(){

	std::vector<Point> px;
	px.clear();
	int m = 0;
	px.resize(m);

	for(int i = 1; i < 5; ++i){
		Point py;
		py.x = i;
		py.y = i*i;
		px.push_back(py);
	}
	traverse_4(px);

	// ===== Phase1/01_iterator 迭代器练习 =====
	exercise_1_2_modify_by_iterator();      // 练习 1.2: 使用迭代器修改元素
	exercise_1_3_const_iterator();         // 练习 1.3: 使用 const_iterator 遍历常量容器

	exercise_2_1_forward_iterator();        // 练习 2.1: ForwardIterator
	exercise_2_2_bidirectional_iterator();  // 练习 2.2: BidirectionalIterator
	exercise_2_3_random_access_iterator();  // 练习 2.3: RandomAccessIterator

	exercise_3_1_reverse_iterator();        // 练习 3.1: std::reverse_iterator
	exercise_3_2_custom_reverse_iterator(); // 练习 3.2: 自定义 ReverseIterator
	exercise_3_3_insert_iterator();         // 练习 3.3: 插入迭代器
	exercise_3_4_stream_iterator();         // 练习 3.4: 流迭代器(需要从 stdin 输入)

	exercise_4_1_iterator_traits();         // 练习 4.1: std::iterator_traits
	exercise_4_2_custom_traits();           // 练习 4.2: 自定义容器 traits
	exercise_4_3_category_branch();         // 练习 4.3: 编译期类别分支

	exercise_5_1_advance();                 // 练习 5.1: std::advance
	exercise_5_2_distance();                // 练习 5.2: std::distance
	exercise_5_3_next_prev();               // 练习 5.3: std::next / std::prev

	exercise_6_1_array_iterator();          // 练习 6.1: 数组随机访问迭代器
	exercise_6_2_forward_list_iterator();   // 练习 6.2: 单向链表正向迭代器
	exercise_6_3_bidirectional_list_iterator(); // 练习 6.3: 双向链表双向迭代器

	exercise_7_1_vector_invalidation();     // 练习 7.1: vector 迭代器失效
	exercise_7_2_list_invalidation();       // 练习 7.2: list 迭代器失效

	return 0;
}
