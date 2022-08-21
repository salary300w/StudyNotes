#include "Messageout_shared.h"
#include <iostream>

namespace Moutshared
{
    void Messageout::out()
    {
        std::cout << "使用自定义类进行打印这段话，Messageout_shared.h与Messageout_shared.cpp被封装为动态库链接到可执行文件！" << std::endl;
    }
}
