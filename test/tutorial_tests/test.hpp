#pragma once
#include <iostream>

namespace Foo // Foo is defined in the global scope
{
   extern int g_x; // g_x is now inside the Foo namespace, but is still a global variable
}

int add(int, int);
