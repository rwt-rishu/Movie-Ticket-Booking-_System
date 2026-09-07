#include <iostream>
#include <string>
#include <vector>
using namespace std;

// AGGREGATION: Show refers to an existing Movie.
// ASSOCIATION: Show uses an existing Screen.
// COMPOSITION: Show creates ShowSeat status objects.
class Show {
private:
    Movie* movie;
    Screen* screen;
    string startTime;
    vector<ShowSeat> showSeats;

public:
    Show(Movie* movie, Screen* screen, string startTime)
        : movie(movie), screen(screen), startTime(startTime) {
        for (Seat& seat : screen->getSeats())
            showSeats.emplace_back(&seat);
    }

    Movie* getMovie() const { return movie; }
    Screen* getScreen() const { return screen; }
    string getStartTime() const { return startTime; }
    vector<ShowSeat>& getShowSeats() { return showSeats; }

    void displaySeats() const {
        cout << "\nSeat Layout (A=AVAILABLE, B=BOOKED)\n";
        for (const ShowSeat& showSeat : showSeats) {
            cout << "Seat " << showSeat.getSeat()->getNumber()
                 << " [" << showSeat.getSeat()->getTypeName() << "] : "
                 << (showSeat.isAvailable() ? "AVAILABLE" : "BOOKED") << '\n';
        }
    }

    ShowSeat* findShowSeat(int seatNumber) {
        for (ShowSeat& showSeat : showSeats)
            if (showSeat.getSeat()->getNumber() == seatNumber)
                return &showSeat;
        return nullptr;
    }
};
