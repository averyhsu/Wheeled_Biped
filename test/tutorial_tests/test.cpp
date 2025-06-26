// This function is declared as static, and can now be used only within this file
// Attempts to access it from another file via a function forward declaration will fail
namespace Foo // Foo is defined in the global scope
{
     int g_x =0; // g_x is now inside the Foo namespace, but is still a global variable
}
int add(int x, int y)
{
    return x + y;
}