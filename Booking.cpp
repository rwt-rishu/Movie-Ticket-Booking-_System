#include <string>
#include <vector>
using namespace std;

enum class BookingStatus { PENDING, CONFIRMED, CANCELLED };

class Booking {
private:
    static int nextBookingId;
    int bookingId;
    Customer* customer;
    Show* show;
    vector<ShowSeat*> selectedSeats;
    double totalAmount;
    BookingStatus status;

public:
    Booking(Customer* customer, Show* show,
            const vector<ShowSeat*>& selectedSeats, double totalAmount)
        : bookingId(nextBookingId++), customer(customer), show(show),
          selectedSeats(selectedSeats), totalAmount(totalAmount),
          status(BookingStatus::PENDING) {}

    int getBookingId() const { return bookingId; }
    Customer* getCustomer() const { return customer; }
    Show* getShow() const { return show; }
    const vector<ShowSeat*>& getSelectedSeats() const { return selectedSeats; }
    double getTotalAmount() const { return totalAmount; }

    void confirm() { status = BookingStatus::CONFIRMED; }

    void cancel() {
        for (ShowSeat* seat : selectedSeats)
            seat->cancel();
        status = BookingStatus::CANCELLED;
    }

    bool isConfirmed() const { return status == BookingStatus::CONFIRMED; }
};

int Booking::nextBookingId = 1001;
