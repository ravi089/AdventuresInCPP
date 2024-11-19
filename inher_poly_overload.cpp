#include <iostream>
#include <vector>
using namespace std;

class Shape {
    public:
        Shape() {
            cout << "Shape constructor called." << endl;
        }
        virtual ~Shape() {
            cout << "Shape destructor called." << endl;
        }
        // Pure virtual function to be overridden by derived classes
        virtual void draw() = 0;
};

class Color {
    protected:
        string color;
    public:
        // Constructor initializer list. This is also called as conversion constructor as it's converting 
		// from string to Color. 
        Color(const string& c) : color(c) {
            cout << "Color constructor called for color: " << color << endl;
        }
        virtual ~Color() {
            cout << "Color destructor called." << endl;
        }
        void setColor(const string& c) { color = c; }
        string getColor() const { return color; }
};

// Multiple inheritance
class Rectangle : public Shape, public Color {
    private:
        int height, width;
    public:
        // Constructor using both base class constructors
        Rectangle(int h, int w, const string& c) : Shape(), Color(c), height(h), width(w) {
            cout << "Rectangle constructor called." << endl;
        }
        virtual ~Rectangle() {
            cout << "Rectangle destructor called." << endl;
        }
        
        void draw() {
            cout << "Drawing Rectangle of size " << width << " x " << height
                  << " with color " << color << endl;
        }
        // Operator Overloading: '+' to add two rectangles
        Rectangle operator+(const Rectangle& other) const {
            int newHeight = this->height + other.height;
            int newWidth = this->width + other.width;
            string newColor = (this->color == other.color) ? this->color : "mixed";
            return Rectangle(newHeight, newWidth, newColor);
        }
        // Operator Overloading: '==' to compare two rectangles
        bool operator==(const Rectangle& other) const {
            return this->width == other.width && this->height == other.height && this->color == other.color;
        }
        void printDetails() const {
            cout << "Rectangle: " << width << " x " << height
                  << ", Color: " << color << endl;
        }
};

class Circle : public Shape, public Color {
    private:
        int radius;
    public:
        Circle(int r, const Color& c) : Shape(), Color(c), radius(r) {
            cout << "Circle constructor called." << endl;
        }
        virtual ~Circle() { 
            cout << "Circle destructor called." << endl; 
        }
        void draw() {
            cout << "Drawing Circle with radius " << radius
                  << " and color " << getColor() << endl;
        }
        void printDetails() {
            cout << "Circle: Radius = " << radius << ", Color = " << getColor() << endl;
        }
};

// Virtual Inheritance Example: A common base class for a more complex inheritance hierarchy
class Base {
    public:
        Base() { cout << "Base constructor called." << endl; }
        virtual ~Base() { cout << "Base destructor called." << endl; }
        virtual void display() const {
            cout << "Base class display method." << endl;
        }
};

class DerivedA : virtual public Base {
    public:
        DerivedA() { cout << "DerivedA constructor called." << endl; }
        virtual ~DerivedA() { cout << "DerivedA destructor called." << endl; }
        virtual void display() const {
                cout << "DerivedA class display method." << endl;
            }
};

class DerivedB : virtual public Base {
    public:
        DerivedB() { cout << "DerivedB constructor called." << endl; }
        virtual ~DerivedB() { cout << "DerivedB destructor called." << endl; }
        virtual void display() const {
                cout << "DerivedB class display method." << endl;
            }
};

// Derived class from both DerivedA and DerivedB
class DerivedC : public DerivedA, public DerivedB {
    public:
        DerivedC() { cout << "DerivedC constructor called." << endl; }
        virtual ~DerivedC() { cout << "DerivedC destructor called." << endl; }
        virtual void display() const {
                cout << "DerivedC class display method." << endl;
            }
};

int main() {
    Rectangle rect1(10,20,"Blue");
    Rectangle rect2(5,15,"Green");
    // In the implicit conversion sequence of one type to another, there is a rule that states: At most, 
	// only one user defined conversion can be applied. But here there are 2 conversions one from const char* 
	// to string and then string to color. So to get rid of that error one implicit conversion is removed. 
	// Also remember the use of explicit in constructor. if used then no automatic conversion would take place.
    Circle circle(25,string("Yellow"));
    
    // Polymorphism
    vector<Shape*> shapes;
    shapes.push_back(&rect1);
    shapes.push_back(&circle);
    
    vector<Shape*>::iterator it;
    for (it = shapes.begin(); it != shapes.end(); ++it) {
        (*it)->draw();    // Polymorphic behavior
    }
    // Operator Overloading
    Rectangle rect3 = rect1 + rect2;
    rect3.printDetails();
    // Comparison 
    if (rect1 == rect2) {
        cout << "rect1 and rect2 are identical." << endl;
    } else {
        cout << "rect1 and rect2 are not identical." << endl;
    }
    // Virtual Inheritance
    DerivedC obj;
    obj.display();      // Calls DerivedC's display
    return 0;
}