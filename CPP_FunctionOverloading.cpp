// Fortunately, C++ has an elegant solution to handle such cases. Function overloading allows us to create multiple functions with the same name,
// so long as each identically named function has different parameter types (or the functions can be otherwise differentiated). 
// Each function sharing a name (in the same scope) is called an overloaded function (sometimes called an overload for short).

// Additionally, when a function call is made to a function that has been overloaded, the compiler will try to match the function call to 
// the appropriate overload based on the arguments used in the function call. This is called overload resolution.

/*
    How overloaded functions are differentiated?
    1) Based on number of parameters.
    2) Type of parameters.

    Not differentiated in below case
    1) Return type 
    2) typedef or alias(using)

    what is name mangling?
    => When the compiler compile a function, it perfrom name mangling. which means compiled name of the function is altered based on various criteria.
       In src code two function will have same name but in compiled code both will have different name.
*/


#include<iostream>

int add(int f_a, int f_b)
{
    return f_a + f_b;
}

double add(double f_a, double f_b)
{
    return f_a + f_b;
}

//cannot overload functions distinguished by return type aloneC/C++(311)
// double add(int f_a, int f_b)
// {
//     return f_a + f_b;
// }

int main()
{
    std::cout <<"Addition of two int is = " << add(1,5) <<std::endl;
    std::cout <<"Addition of two double is = " << add(1.1,5.1) <<std::endl;

    return 0;
}