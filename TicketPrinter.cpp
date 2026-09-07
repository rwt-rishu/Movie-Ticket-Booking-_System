#include <iostream>
#include <iomanip>
using namespace std;

class TicketPrinter {
public:
    void printTicket(const Booking& booking) const {
        Show* show = booking.getShow();

        cout << "\n================ TICKET ================\n";
        cout << "Booking ID : " << booking.getBookingId() << '\n';
        cout << "Customer   : " << booking.getCustomer()->getName() << '\n';
        cout << "Movie      : " << show->getMovie()->getTitle() << '\n';
        cout << "Screen     : " << show->getScreen()->getScreenNumber() << '\n';
        cout << "Start Time : " << show->getStartTime() << '\n';

        cout << "Seats      : ";
        for (ShowSeat* seat : booking.getSelectedSeats())
            cout << seat->getSeat()->getNumber() << ' ';

        cout << "\nTotal      : Rs. " << fixed << setprecision(2)
             << booking.getTotalAmount() << '\n';
        cout << "Status     : CONFIRMED\n";
        cout << "========================================\n";
    }
};
