#include <iostream>
#include <memory>
#include <string>
#include <functional>
#include "function2.hpp"

struct A {
    std::string str;
    A() {
        std::cout << "default construct\n";
    }

    A(std::string s):str(s){
        std::cout << "construct1:" << s << std::endl;
    }

    A(const A& a): str(a.str) {
        std::cout << "拷贝构造函数" << a.str << std::endl;
    }

    A(const A&& a) {

        std::cout << "移动构造函数" << str << std::endl;
    }

    A& operator=(const A& a) {
        str = a.str;
        std::cout << "拷贝赋值函数" << a.str << std::endl;
        return *this;
    }

    A& operator=(const A&& a) {
        str = a.str;
        std::cout << "移动赋值函数" << str << std::endl;
        return *this;
    }

    ~A() {
        std::cout << "～A\n"; 
    }


};

void f(A &&a) {
    a.str = "adsf";
    a = A("asdfadsf");
    std::cout << a.str << "  rvalue" << std::endl;
}

void f(const A &a) {
    std::cout << a.str << "const lvalue" << std::endl;
}

void f(std::string&& str) {
    str = "xxxx";
    // std::string s = std::move(str);
    std::cout << "In f: " << str << std::endl;
}

using OpFunc = fu2::unique_function<void(std::string&) &&>;

static OpFunc test_op() {
    return [](std::string &str) mutable {
        std::cout << "I am in Lambda!\n";
        std::cout << str << std::endl;
    };
}

void func_test(OpFunc&& f)
{
    std::string str("erqe");
    std::move(f)(str);
    // f(str);
}


int main(int, char**) {

    func_test(test_op());
    
    // A a1{"abc1"};
    // A b1(std::move(a1));
    // A a2{"abc2"};
    // A b2(std::move(a2));
    // A c1{"sdf1"};
    // A d1 = std::move(c1);
    // A c2{"sdf2"};
    // A d2 = std::move(c2);
 
    // A e1{"abc3"};
    // f(std::move(e1));

    // f(std::move(A("fasdf")));


    // A e2{"abc4"};
    // f(e2);


    // std::string str{"asfas"};
    // std::string s = std::move(str);
    // // std::cout << "str:" << str << std::endl;
    // std::string str1{"asfas"};
    // f(std::move(str1));
    // std::cout << "str1:" << str1 << std::endl;
}
