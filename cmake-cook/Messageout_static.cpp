#include "Messageout_static.h"
#include <iostream>

namespace Moutstatic
{
    void Messageout::out()
    {
        std::cout << "使用自定义类进行打印这段话，Messageout_static.h与Messageout_static.cpp被封装为静态库链接到可执行文件！" << std::endl;
    }
}
