#pragma once

/**
 * @brief Example class tooltip field for documentation (hover over the "MyClass" on row 10).
 *
 * @details Another field for further detailed documentation
 * 
 * @note There are many header keywords for diffrent scenarios. Type @ to get a list (with autocomplete).
 */
class MyClass
{
    private:
        /**
         * @brief Example of a private float variable.
         */
        float my_float;


    // This is a normal comment.
    public:
        /**
         * @brief MyClass Constructor
         * 
         * @param my_param_float initial value. Gets stored in my_float.
         * 
         */
        MyClass(float my_param_float);
    

        /**
         * @brief Returns the stored my_float value.
         * 
         * @attention This documentation is what is visible when using the function. Not the comment in the MyClass.cpp file.
         */
        float my_class_function();
};