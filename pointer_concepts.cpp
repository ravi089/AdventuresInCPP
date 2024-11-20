#include <iostream>
using namespace std;

int add(int a, int b) {
    return a + b;
}
// Funtion pointer
int (*func_ptr)(int, int);

class Test {
    public:
        void display(int num) {
            cout << "The number is: " << num << endl;
        }
};

class ModifyPrivate {
    private:
        int value;
    public:
        ModifyPrivate(int v) : value(v) {}
        void display() const {
            cout << "Value: " << value << endl;
        }
};

// Static cast example
class BaseA {
    public:
        void show() {
            cout << "Base class" << endl;
        }
};

class DerivedA : public BaseA {
    public:
        void show() {
            cout << "Derived class" << endl;
        }
};

// Dynamic cast example
class BaseB {
    public:
        virtual void show() {
            cout << "Base class" << endl;
        }
        virtual ~BaseB() {}
};

class DerivedB : public BaseB {
    public:
        void show() {
            cout << "Derived class" << endl;
        }
};

int main() {
    // Pointer to array
    int arr[] = {1,2,3,4,5};
    int* ptr = arr;
    cout << *ptr << endl;
    cout << *(ptr + 1) << endl;
    cout << *(ptr + 2) << endl;
    
    // Function pointers
    func_ptr = add;
    cout << func_ptr(2,3) << endl;
    
    // Pointer concepts
    int x = 5;
    int y = 10;
    // Pointer to constant
    const int* ptr1 = &x;
    // *ptr1 = 10;      // Invalid because ptr1 is pointer to integer that is constant i.e it's value cannot be changed.
    ptr1 = &y;   // Valid

    int* const ptr2 = &x;
    //ptr2 = &y;  // Invalid because ptr2 is constant pointer to integer i.e pointer cannot be changed to point to anything else.
    *ptr2 = 10;     // Valid
  
    // Pointer to member function
    Test obj;
    void (Test::*fptr)(int) = &Test::display;
    (obj.*fptr)(10);
    
    // Modify private member of class
    ModifyPrivate obj(10);
    obj.display();
    
    ModifyPrivate* ptr = &obj;
    // reinterpret_cast is used to treat the address of ModifyPrivate as a byte pointer (char*), and then the pointer is moved to the location of the value data member.
    int* privateVal = reinterpret_cast<int*>(reinterpret_cast<char*>(ptr) + sizeof(ModifyPrivate) - sizeof(int));
    *privateVal = 100;
    obj.display();
    
    // Static cast
    BaseA* basePtr = new DerivedA();
    // static_cast for converting from Base* to Derived*
    DerivedA* derivedPtr = static_cast<DerivedA*>(basePtr);
    derivedPtr->show();
    delete basePtr;
    
    // Dynamic cast 
    BaseB* basePtr = new DerivedB();
    BaseB* anotherBasePTr = new BaseB();
    // Use dynamic_cast to safely cast Base* to Derived*
    // This will succeed
    DerivedB* derivedPtr = dynamic_cast<DerivedB*>(basePtr);
    derivedPtr->show();
    // This will fail
    DerivedB* invalidPtr = dynamic_cast<DerivedB*>(anotherBasePTr);
    if (!invalidPtr) {
        cout << "Cast failed!" << endl;
    }
    
    // const_cast
    const int x = 10;
    const int* ptr = &x;
    // *ptr = 100; // Error
    int* newPtr = const_cast<int*>(ptr);
    *newPtr = 100; // Valid
    
    // reinterpret_cast
    int a = 42;
    double b = 3.14;
    double* ptr = reinterpret_cast<double*>(&a);
    cout << *ptr << endl;   // Undefined behavior (corrupted data)
    
    int* ptr1 = reinterpret_cast<int*>(&b);
    cout << *ptr1 << endl;  // Undefined behavior
    
    // Little-endian representation of integer 1
    char arr[] = {0x01, 0x00, 0x00, 0x00};
    int* ptr2 = reinterpret_cast<int*>(arr);
    cout << arr << endl;
    cout << *ptr2 << endl;
    
    return 0;
}



