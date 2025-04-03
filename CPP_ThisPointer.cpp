/*
    Note:
    this-> is equivelent to (*this).

    why this is ptr and not a reference ??
    => because when this was added to cpp reference didnot exists.

*/

#include<iostream>

class Calc
{
private:
    int m_value{};
public:
    Calc& add(int f_value)
    {
        this->m_value +=f_value;
        return *this;
    }

    Calc& sub(int f_value)
    {
        (*this).m_value -=f_value;
        return *this;
    }

    Calc& mult(int f_value)
    {
        m_value *= f_value;
        return *this;
    }

    void reset()
    {
        *this = {}; // value initialize a new object and overwrite the implicit object
    }

    friend std::ostream& operator<<(std::ostream& f_out, const Calc& f_c)
    {
        return f_out << f_c.m_value;
    }
};

int main()
{
    Calc calc{};

    calc.add(5).sub(4).mult(2); // without return of this ptr function chaining is not possible

    std::cout << "value before reset is " << calc << std::endl;

    //Resetting a class back to default state
    calc.reset();

    std::cout << "value after reset is " << calc;



    return 0;
}