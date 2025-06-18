/*
 When are the move constructor and move assignment called?
    *The move constructor and move assignment are called when those functions have been defined.
    *And the argument for construction or assignment is an rvalue. Most typically, this rvalue will be a literal or temporary value.
    *The copy constructor and copy assignment are used otherwise
    (when the argument is an lvalue, or when the argument is an rvalue and the move constructor or move assignment functions aren’t defined).

 Implicit move constructor and move assignment operator
    *The compiler will create an implicit move constructor and move assignment operator if all of the following are true:
        *There are no user-declared copy constructors or copy assignment operators.
        *There are no user-declared move constructors or move assignment operators.
        *There is no user-declared destructor.
    *These functions do a memberwise move, which behaves as follows:
        *If member has a move constructor or move assignment (as appropriate), it will be invoked.
        *Otherwise, the member will be copied.
        *Notably, this means that pointers will be copied, not moved!
*/


#include<iostream>

template<typename T>
class Smart_ptr
{
    T* m_ptr {};
public:
    Smart_ptr(T* ptr = nullptr) : m_ptr {ptr}
    {

    }

    ~Smart_ptr()
    {
        delete m_ptr;
    }

    // Copy constructor
    // Do deep copy of f_obj.m_ptr to m_ptr
    // Smart_ptr(const Smart_ptr& f_obj)
    // {
    //     m_ptr = new T;
    //     *m_ptr = *f_obj.m_ptr;
    // }

    //Copy constructor - No copying allowed
     Smart_ptr(const Smart_ptr& f_obj) = delete;

    // Move constructor
    // Transfer ownership of f_obj.m_ptr to m_ptr
    Smart_ptr(Smart_ptr&& f_obj) : m_ptr {f_obj.m_ptr}
    {
        f_obj.m_ptr = nullptr;
    }

    // Copy assignment
    // Do deep copy of f_obj.m_ptr to m_ptr
    // Smart_ptr& operator=(const Smart_ptr& f_obj)
    // {
    //     // Self-assignment detection
    //     if (&f_obj == this)
    //         return *this;

    //     // Release any resource we'are holding
    //     delete m_ptr;

    //     // Copy the resource
    //     m_ptr = new T;
    //     m_ptr = f_obj.m_ptr;

    //     return *this;
    // }

    // Copy assignment - No copying allowed
    Smart_ptr& operator=(const Smart_ptr& f_obj) = delete;

    // Move assignment
    // transfer ownership of f_obj to m_ptr
    Smart_ptr& operator=(Smart_ptr&& f_obj)
    {
        // Self assignment detection
        if ( &f_obj == this)
            return *this;
        
        // Release any resources we'are holding
        delete m_ptr;

        // Transfer ownership of f_obj.m_ptr to m_ptr
        m_ptr = f_obj.m_ptr;
        f_obj.m_ptr = nullptr;

        return *this;
    }
};


class Resource
{
public:
    Resource()
    {
        std::cout << "Resource is accquired\n";
    }

    ~Resource()
    {
        std::cout << "Resource is destroyed\n";
    }
};


Smart_ptr<Resource> generateResource()
{
    Smart_ptr<Resource> res {new Resource};
    return res;
}

int main ()
{
    Smart_ptr<Resource> mainres;
    mainres = generateResource();

    return 0;
}
