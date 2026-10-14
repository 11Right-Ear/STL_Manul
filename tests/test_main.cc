#include "Phase0/01_template_basics/template_exercises.hpp"
#include <iostream>
#include <string>


int main(){
    Stack<char> s1;
    for(int i = 0; i < 5; i++){
        SHOW("please in char");
        PUTIN(s1);
    }
    SHOW(s1);
    Stack<char> s2 = s1;
    if(s1 == s2){
        SHOW("there are same");
    }else{
    SHOW("there diffirent");
    }
    return 0;
}