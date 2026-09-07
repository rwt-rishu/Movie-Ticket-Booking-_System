#include <iostream>
using namespace std;

class CardPayment : public Payment {
private:
    bool success;

public:
    explicit CardPayment(bool success) : success(success) {}

    bool pay(double amount) override {
        cout << "Processing Card payment of Rs. " << amount << "...\n";
        return success;
    }
};
