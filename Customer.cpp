#include <string>
using namespace std;

class Customer {
private:
    string name;
    string phone;

public:
    // Compile-time polymorphism: overloaded constructors.
    Customer(string name) : name(name), phone("Not provided") {}
    Customer(string name, string phone) : name(name), phone(phone) {}

    string getName() const { return name; }
    string getPhone() const { return phone; }
};
