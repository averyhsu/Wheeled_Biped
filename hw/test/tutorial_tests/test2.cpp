#define NDEBUG // disable asserts (must be placed before any #includes)
#undef NDEBUG //enable asserts
#include <cassert> //cpp assertion library
#include "test.hpp"

int main()
{
    assert(false);
    Foo::g_x = 5;
    std::cout <<"g_x is: "<<Foo::g_x<<'\n';
    std::cout <<  add(1,2)<<'\n';
    std::cout<<"global namespace!"<<'\n';


    return 0;
}