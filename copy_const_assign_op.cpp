#include <iostream>
#include <cstring>
using namespace std;

class Custom {
  private:
    char* data;
  public:
    // Copy constructor - Deep copy
    Custom(const Custom& c) {
        data = new char[strlen(c.data) + 1];
        strcpy(data, c.data);
    }
    
    // Assignment operator
    Custom& operator=(const Custom& c) {
        // check for self assignment
        if (this == &c) {
            return *this   // Return *this to allow chained assignments
        }
        // Release any resource that the current object holds
        delete [] data;
        // Allocate new memory and copy the data from the other object
        data = new char[strlen(c.data) + 1];
        strcpy(data, c.data);
        
        return *this;   // Return *this to allow chained assignments
    }
};

int main() {

    return 0;
}




