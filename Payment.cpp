#include <iostream>
using namespace std;

// ABSTRACTION: Payment defines the common payment contract.
class Payment {
public:
    virtual bool pay(double amount) = 0;
    virtual ~Payment() = default;
};
