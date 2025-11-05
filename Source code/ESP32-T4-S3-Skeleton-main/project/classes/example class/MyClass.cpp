#include "MyClass.hpp"

/* Initializes my_float variable to the parameter value. */
MyClass::MyClass(float my_param_float)
{
    MyClass::my_float = my_param_float;
}

/* Returns my_float value. This documentation is only showed inside this file. */
float MyClass::my_class_function()
{
    return MyClass::my_float;
}