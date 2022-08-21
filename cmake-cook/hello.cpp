#include <iostream>
#include "Messageout_static.h"
#include "Messageout_shared.h"
#include "Messageout.h"
int main()
{
    auto A=new Moutshared::Messageout();
    auto B=new Moutstatic::Messageout();
    auto C=new Mout::Messageout();
    A->out();
    B->out();
    C->out();
    return 0;
}