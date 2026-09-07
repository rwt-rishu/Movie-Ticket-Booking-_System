#include <vector>
using namespace std;

class PriceCalculator {
public:
    double calculate(const vector<ShowSeat*>& seats) const {
        double total = 0.0;
        for (ShowSeat* showSeat : seats)
            total += showSeat->getSeat()->getPrice();
        return total;
    }
};
