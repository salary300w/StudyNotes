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