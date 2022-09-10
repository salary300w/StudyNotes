- [C++](#c)
  - [关键字](#关键字)
    - [```explicit```](#explicit)
    - [```emplace_back```](#emplace_back)
    - [```priority_queue<>```](#priority_queue)
  - [右值引用（实现std::move语义）](#右值引用实现stdmove语义)
  - [正则表达式](#正则表达式)
# C++
## 关键字
### ```explicit```
* 只能用于修饰只有一个参数的类构造函数，除了第一个参数以外的其他参数都有默认值的时候, explicit关键字依然有效。
* 表明该构造函数是显示的，类构造函数默认情况下即声明为implicit(隐式)。
  ```C++
  Class people{
    public:
        people(int age)
        {
            _age=age;
        }
    int _age;
  };
  people p1=18;
  /*
  使用这种构造语法是可行的，编译器会进行隐式转换;
  */
  Class people{
    public:
        explicit people(int age)
        {
            _age=age;
        }
    int _age;
  };
  people p1=18;
  /*
  此时的构造语法不可行。
  使用explicit关键字的构造函数可以防止隐式转换。
  */
  ```
### ```emplace_back```
* 传入左值，执行移动构造
* 传入右值，执行拷贝构造
* 传入构造函数所需参数，在容器尾部执行原地创建
### ```priority_queue<>```
```C++
//自定义compare的写法
struct compare
{
    bool operator()(int &a, int &b)
    {
        return a > b;
    }
};
priority_queue<int, vector<int>, compare> save;
//lambda表达式写法
auto compare = [](int &a, int &b)
{ return a > b; };
priority_queue<int, vector<int>, decltype(compare)> save(compare);
```
## 右值引用（实现std::move语义）
```C++
#include <iostream>
int main()
{
    int a = 30;
    int b;
    b = (int &&)a; // 等同于b = std::move(a);执行移动构造
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    return 0;
}
```
## 正则表达式
```C++
#include "iostream"
#include <regex>
int main() {
  std::string target{"abc123"};
  std::regex rule(".*[0-9]*");
  std::smatch result;
  std::regex_match(target, result, rule);
  std::cout << result[0].str() << std::endl;
  return 0;
}
```