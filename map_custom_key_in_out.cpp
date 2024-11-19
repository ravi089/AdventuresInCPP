#include <iostream>
#include <map>
#include <vector>
using namespace std;

struct User {
    string name;
    int age;
 
    User(string n, int a) : name(n),age(a) {}
    friend ostream& operator<<(ostream& out, const User& u);
    friend istream& operator>>(istream& in, User& u);
};

ostream& operator<<(ostream& out, const User& u) {
    out << u.name;
    out << " - " << u.age << endl;
    return out;
}

istream& operator>>(istream& in, User& u) {
    cout << "Enter name - ";
    in >> u.name;
    cout << "Enter age - ";
    in >> u.age;
    return in;
}

class comp {
    public:
        bool operator()(const User& u1, const User& u2) const {
            return u1.name > u2.name;
        }
};

int main() {
    map<User,string,comp> mp;
    
    User u1("ravi", 35);
    User u2("anil", 40);
    User u3("komal", 32);
    User u4("sanjay", 38);
    
    mp.insert(make_pair(u1,"test1"));
    mp.insert(make_pair(u2,"test2"));
    mp.insert(make_pair(u3,"test3"));
    mp.insert(make_pair(u4,"test4"));
    
    map<User,string,comp>::iterator it;
    for (it = mp.begin(); it != mp.end(); ++it) {
        cout << it->first << " - " << it->second << endl;
    }
    
    return 0;
}