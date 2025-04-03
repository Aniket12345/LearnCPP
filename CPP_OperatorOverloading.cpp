/*
    1) First, almost any existing operator in C++ can be overloaded. 
       The exceptions are: conditional (?:), sizeof, scope (::), member selector (.), pointer member selector (.*), typeid, and the casting operators.
    2) Second, you can only overload the operators that exist.
    3) Third, at least one of the operands in an overloaded operator must be a user-defined type. This means you could overload operator+(int, Mystring), but not operator+(int, double).
    4) Operators that modify their leftmost operand (e.g. pre-increment, any of the assignment operators) should generally return the leftmost operand by reference.
    5) Operators that do not modify their operands (e.g. arithmetic operators) should generally return results by value.

    Three ways to overload operator
    1) The member function way
    2) The Friend function way
    3) Normal function way.

    Best Practice:
    1)Prefer overloading operators as normal functions instead of friends if it’s possible to do so without adding additional functions.

    Note:
    1) Not everything can be overloaded as a friend function
       The assignment (=), subscript ([]), function call (()), and member selection (->) operators must be overloaded as member functions, because the language requires them to be.
       We can’t overload operator+(int, Cents) as a member function, because int isn’t a class we can add members to.
    
    2) Not everything can be overloaded as a member function
     << & >> cannot be overloaded as member function.
     reason:  Because the overloaded operator must be added as a member of the left operand. 
              In this case, the left operand is an object of type std::ostream. std::ostream is fixed as part of the standard library. We can’t modify the class declaration to add the overload as a member function of std::ostream.

    3) Important
        If you’re overloading assignment (=), subscript ([]), function call (()), or member selection (->), do so as a member function.
        If you’re overloading a unary operator, do so as a member function.
        If you’re overloading a binary operator that does not modify its left operand (e.g. operator+), do so as a normal function (preferred) or friend function.
        If you’re overloading a binary operator that modifies its left operand, but you can’t add members to the class definition of the left operand (e.g. operator<<, which has a left operand of type ostream), do so as a normal function (preferred) or friend function.
        If you’re overloading a binary operator that modifies its left operand (e.g. operator+=), and you can modify the definition of the left operand, do so as a member function.
*/

#include <iostream>

//Overloading operators +,-,*,/ using friend functions

class Cents
{
private:
    int m_cents{};
public:
    Cents(int f_cents) : m_cents(f_cents) {};

    int getCents() const
    {
        return m_cents;
    }

    // Add Cents + Cents using a friend function
    friend Cents operator+(const Cents& f_c1, const Cents& f_c2)
    {
        // we can access m_cents directly because this is a fried function
        return f_c1.m_cents + f_c2.m_cents;
    }

    friend Cents operator-(const Cents& f_c1, const Cents& f_c2)
    {
        return f_c1.m_cents - f_c2.m_cents;
    }

    friend Cents operator*(const Cents& f_c1, const Cents& f_c2)
    {
        return f_c1.m_cents * f_c2.m_cents;
    }

    friend Cents operator/(const Cents& f_c1, const Cents& f_c2)
    {
        return f_c1.m_cents / f_c2.m_cents;
    }  

    friend std::ostream& operator<<( std::ostream& f_out, const Cents& f_c1)
    {
        f_out << "value is" << f_c1.m_cents << std::endl;
        return f_out;
    }

    friend std::istream& operator>>(std::istream& f_in, Cents& f_c1)
    {
        int l_extract {};
        // this condition because of partial extraction which can occur "So better take all or noting"
        // Here not writing directly to data member instead coping it locally.
        if(f_in >> l_extract)
            f_c1.m_cents = l_extract;
        return f_in;
    }

};


//Overloading operators +,-,*,/, <<, >> using Normal functions
class Rupya
{
private:
    int m_rupya{};
public:
    Rupya(int f_rupya) : m_rupya(f_rupya) {};

    int getRupya() const
    {
        return m_rupya;
    }
};

Rupya operator+(const Rupya& f_r1, const Rupya& f_r2)
{
    // In this case  private member are access using public function interface
    return f_r1.getRupya() + f_r2.getRupya();
}

std::ostream& operator<<(std::ostream& f_out, const Rupya& f_r)
{
    f_out << f_r.getRupya();
    return f_out;
}

//Overloading operators +,-,*,/, <<, >> as member functions
class Paisa
{
private:
    int m_paisa{};
public:
    Paisa(int f_p): m_paisa(f_p) {}

    Paisa operator+(const int& f_p1)
    {
        return Paisa{m_paisa + f_p1};
    }

    Paisa operator-() const
    {
        return -m_paisa;
    }

    // << cannot overload using member function
    friend std::ostream& operator<<(std::ostream& f_out,const Paisa& f_p)
    {
        return f_out <<f_p.m_paisa;
    }

};

int main()
{
    /*============================overloading operator using friend function============================*/
    Cents cents1 {2};
    Cents cents2 {8};

    Cents centsSum {cents1 + cents2}; // invoke operator +
    Cents centsSub {centsSum - cents1}; // invoke operator -
    Cents centsMul {cents1 * cents2}; // invoke operator *
    Cents centsDvi {cents2 / cents1}; // invoke operator /

    std::cout << "I have after addition " << centsSum.getCents() << std::endl;
    std::cout << "I have after subtraction " << centsSub.getCents() << std::endl;
    std::cout << "I have after mul " << centsMul.getCents() << std::endl;
    std::cout << "I have after Division " << centsDvi.getCents() << std::endl;

    std::cout << cents1 ; // invoke operator <<
    std::cin >> cents1; // invoke operator >>

    std::cout << cents1 ; // invoke operator <<
    /*=======================================END===========================================================*/

    /*============================overloading operator normal function============================*/
    Rupya rupya1{10};
    Rupya rupya2{5};

    Rupya rupyaSum{rupya1 + rupya2};

    std::cout << " I have " << rupyaSum.getRupya() <<" Rupya after addition\n"; // invoke + operator
    std::cout << " I have " << rupyaSum <<" Rupya after addition\n"; // invoke << operator 
     /*=======================================END===========================================================*/

     /*============================overloading operator as member function============================*/
    Paisa paisap1{5};
    Paisa paisap2{5};
    Paisa paisaSum{paisap1 + 5}; // which is equivalent to paisap1.operator+(5)
    
    //Unary operator  +(positive), -(negative) & !(logical not)

    std::cout << "Paisa after using - operator" << -paisaSum << std::endl;
     /*=======================================END===========================================================*/
    return 0;


}