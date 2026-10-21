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
    return -1;
}