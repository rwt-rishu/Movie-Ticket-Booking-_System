#include <iostream>
using namespace std;

enum class SeatStatus { AVAILABLE, BOOKED };

// COMPOSITION: Show owns ShowSeat status objects for that show.
class ShowSeat {
private:
    Seat* seat;
    SeatStatus status;

public:
    explicit ShowSeat(Seat* seat) : seat(seat), status(SeatStatus::AVAILABLE) {}

    bool isAvailable() const { return status == SeatStatus::AVAILABLE; }

    bool book() {
        if (!isAvailable()) return false;
        status = SeatStatus::BOOKED;
        return true;
    }

    void cancel() { status = SeatStatus::AVAILABLE; }

    Seat* getSeat() const { return seat; }
};
