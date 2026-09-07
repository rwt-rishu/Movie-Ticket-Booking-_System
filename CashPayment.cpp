#include <iostream>
using namespace std;

class CashPayment : public Payment {
private:
    bool success;

public:
    explicit CashPayment(bool success) : success(success) {}

    bool pay(double amount) override {
        cout << "Collecting Cash of Rs. " << amount << "...\n";
        return success;
    }
};
