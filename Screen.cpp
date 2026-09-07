#include <vector>
using namespace std;

// COMPOSITION: Screen creates and owns its physical Seat objects.
class Screen {
private:
    int screenNumber;
    vector<Seat> seats;

public:
    Screen(int screenNumber) : screenNumber(screenNumber) {}

    void addSeat(const Seat& seat) { seats.push_back(seat); }

    int getScreenNumber() const { return screenNumber; }
    vector<Seat>& getSeats() { return seats; }
    const vector<Seat>& getSeats() const { return seats; }
};
