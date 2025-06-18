
// A Smart pointer is a composition class that is designed to manage dynamically allocated memory 
// and ensure that memory gets deleted when the smart pointer object goes out of scope.
#include<iostream>
#include<stdint.h>

template<typename T>
class Smart_ptr
{
    T* m_ptr{}; //created ptr of type T
public:
   Smart_ptr(T* ptr = nullptr) :m_ptr(ptr) 
   {
        std::cout <<"Instant created\n";
   }
   ~Smart_ptr()
   {
         delete m_ptr;
         std::cout <<"Instant deleted\n";
   }

   T* operator->() const
   {
        return m_ptr;
   }
};


class Resource
{
public:
    Resource()
    {
        std::cout <<"Resource is acquired\n";
    }

    ~Resource()
    {
        std::cout <<"Resource is destroyed\n";
    }

    void sayHi() {std::cout << "Hello from resource\n";}
};

void someFunction()
{
    Smart_ptr<Resource> inst(new Resource());

    uint8_t x {};
    
    std::cout <<"enter an integer\n";
    std::cin >> x;

    if(x ==0)
        return; // the function return early
    
    inst->sayHi();
}

int main()
{
    //someFunction();

    // A critical Flaw in smart pointer class
    Smart_ptr<Resource> inst1(new Resource());

    Smart_ptr<Resource> inst2(inst1); // due to shallow copy this statement will result in dangling ptr

    // How to fix this issue for that check move sematics


} 
