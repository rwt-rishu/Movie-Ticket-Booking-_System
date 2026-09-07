#include <string>
using namespace std;

enum class SeatType { SILVER, GOLD, PLATINUM };

class Seat {
private:
    int number;
    SeatType type;

public:
    Seat(int number, SeatType type) : number(number), type(type) {}

    int getNumber() const { return number; }
    SeatType getType() const { return type; }

    double getPrice() const {
        switch (type) {
            case SeatType::SILVER: return 150.0;
            case SeatType::GOLD: return 250.0;
            case SeatType::PLATINUM: return 400.0;
        }
        return 0.0;
    }

    string getTypeName() const {
        switch (type) {
            case SeatType::SILVER: return "SILVER";
            case SeatType::GOLD: return "GOLD";
            case SeatType::PLATINUM: return "PLATINUM";
        }
        return "UNKNOWN";
    }
};
