// Move semantics in C++ is a feature introduced in C++11 that allows the efficient transfer of resources (like memory or file handles) from 
// one object to another, rather than copying them. This is particularly useful for objects that manage dynamic resources, such as std::vector, std::string, or custom classes with heap-allocated memory.
#include<iostream>

template<typename T>
class Smart_ptr
{
    T* m_ptr {};

public:
    Smart_ptr(T* f_ptr = nullptr) : m_ptr(f_ptr)
    {

    }

    ~Smart_ptr()
    {
        delete m_ptr;
    }

    bool isNull() const
    {
        return m_ptr == nullptr;
    }

    Smart_ptr& operator=(Smart_ptr& f_ptr)
    {

    }
};

class Resource
{
public:
    Resource()
    {
        std::cout <<"resource is acquired\n";
    }

    ~Resource()
    {
        std::cout <<"resource is destroyed\n";
    }
};

int main()
{
    Smart_ptr<Resource> l_ptr(new Resource());
    Smart_ptr<Resource> l_ptr1;

    std::cout << "l_ptr is" << (l_ptr.isNull() ? "null\n": "Not null\n");
    std::cout << "l_ptr1 is" << (l_ptr1.isNull() ? "null\n": "Not null\n");

    l_ptr1 = l_ptr; //copying l_ptr to l_ptr1

}