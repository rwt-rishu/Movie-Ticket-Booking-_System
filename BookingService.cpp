#include <iostream>
#include <vector>
using namespace std;

class BookingService {
private:
    PriceCalculator priceCalculator;
    TicketPrinter ticketPrinter;

public:
    Booking* bookTicket(Customer* customer, Show* show,
                         const vector<int>& seatNumbers, Payment& payment) {
        vector<ShowSeat*> selectedSeats;

        // Validate every seat before changing any seat status.
        for (int number : seatNumbers) {
            ShowSeat* seat = show->findShowSeat(number);

            if (seat == nullptr) {
                cout << "Invalid seat number: " << number << ". Booking rejected.\n";
                return nullptr;
            }

            if (!seat->isAvailable()) {
                cout << "Seat " << number << " is already BOOKED. Booking rejected.\n";
                return nullptr;
            }

            selectedSeats.push_back(seat);
        }

        double total = priceCalculator.calculate(selectedSeats);

        // Reserve only after all requested seats are validated.
        for (ShowSeat* seat : selectedSeats)
            seat->book();

        if (!payment.pay(total)) {
            for (ShowSeat* seat : selectedSeats)
                seat->cancel();

            cout << "Payment FAILED. Booking not confirmed; seats released.\n";
            return nullptr;
        }

        Booking* booking = new Booking(customer, show, selectedSeats, total);
        booking->confirm();

        ticketPrinter.printTicket(*booking);
        return booking;
    }

    void cancelBooking(Booking* booking) {
        if (booking == nullptr || !booking->isConfirmed()) {
            cout << "Booking cannot be cancelled.\n";
            return;
        }

        booking->cancel();
        cout << "Booking " << booking->getBookingId()
             << " cancelled. Seats are AVAILABLE again.\n";
    }
};
