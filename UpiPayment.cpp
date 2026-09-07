#include <iostream>
using namespace std;

// INHERITANCE + RUNTIME POLYMORPHISM.
class UpiPayment : public Payment {
private:
    bool success;

public:
    explicit UpiPayment(bool success) : success(success) {}

    bool pay(double amount) override {
        cout << "Processing UPI payment of Rs. " << amount << "...\n";
        return success;
    }
};
