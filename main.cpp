#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

// No header files are used as required by the assignment.
// Each class is kept in its own .cpp file and included here.
// Compile this file only: g++ -std=c++17 main.cpp -o movie_booking

#include "Payment.cpp"
#include "Movie.cpp"
#include "Seat.cpp"
#include "Screen.cpp"
#include "Cinema.cpp"
#include "ShowSeat.cpp"
#include "Show.cpp"
#include "Customer.cpp"
#include "Booking.cpp"
#include "UpiPayment.cpp"
#include "CardPayment.cpp"
#include "CashPayment.cpp"
#include "PriceCalculator.cpp"
#include "TicketPrinter.cpp"
#include "BookingService.cpp"

void seedData(Cinema& cinema, vector<Movie>& movies, vector<Show>& shows) {
    movies.emplace_back("Avengers: Endgame", "English", 181);
    movies.emplace_back("3 Idiots", "Hindi", 170);
    movies.emplace_back("Stree 2", "Hindi", 149);

    Screen screen1(1);
    Screen screen2(2);

    // 10 seats per screen: 1-4 Silver, 5-7 Gold, 8-10 Platinum.
    for (int i = 1; i <= 10; ++i) {
        SeatType type = i <= 4 ? SeatType::SILVER
                       : i <= 7 ? SeatType::GOLD
                                : SeatType::PLATINUM;
        screen1.addSeat(Seat(i, type));
        screen2.addSeat(Seat(i, type));
    }

    cinema.addScreen(screen1);
    cinema.addScreen(screen2);

    // Screens are stored inside Cinema; obtain stable references after setup.
    Screen* s1 = &cinema.getScreens()[0];
    Screen* s2 = &cinema.getScreens()[1];

    shows.emplace_back(&movies[0], s1, "10:00 AM");
    shows.emplace_back(&movies[0], s2, "02:00 PM");
    shows.emplace_back(&movies[1], s1, "06:00 PM");
    shows.emplace_back(&movies[2], s2, "09:00 PM");
}

void listMovies(const vector<Movie>& movies) {
    cout << "\n===== MOVIES CURRENTLY PLAYING =====\n";
    for (size_t i = 0; i < movies.size(); ++i) {
        cout << i + 1 << ". " << movies[i].getTitle()
             << " | " << movies[i].getLanguage()
             << " | " << movies[i].getDuration() << " min\n";
    }
}

void listShowsForMovie(const vector<Movie>& movies, vector<Show>& shows) {
    listMovies(movies);

    int movieChoice;
    cout << "Choose movie: ";
    cin >> movieChoice;

    if (movieChoice < 1 || movieChoice > static_cast<int>(movies.size())) {
        cout << "Invalid movie choice.\n";
        return;
    }

    const Movie* chosen = &movies[movieChoice - 1];
    cout << "\nShows for " << chosen->getTitle() << ":\n";

    bool found = false;
    for (size_t i = 0; i < shows.size(); ++i) {
        if (shows[i].getMovie() == chosen) {
            cout << i + 1 << ". Screen " << shows[i].getScreen()->getScreenNumber()
                 << " | " << shows[i].getStartTime() << '\n';
            found = true;
        }
    }

    if (!found) cout << "No shows available.\n";
}

Show* chooseShow(vector<Show>& shows) {
    cout << "\n===== ALL SHOWS =====\n";
    for (size_t i = 0; i < shows.size(); ++i) {
        cout << i + 1 << ". " << shows[i].getMovie()->getTitle()
             << " | Screen " << shows[i].getScreen()->getScreenNumber()
             << " | " << shows[i].getStartTime() << '\n';
    }

    int choice;
    cout << "Choose show: ";
    cin >> choice;

    if (choice < 1 || choice > static_cast<int>(shows.size())) {
        cout << "Invalid show choice.\n";
        return nullptr;
    }

    return &shows[choice - 1];
}

vector<int> readSeatNumbers() {
    int count;
    cout << "Number of seats: ";
    cin >> count;

    vector<int> seatNumbers;
    if (count <= 0 || count > 10) {
        cout << "Invalid number of seats.\n";
        return seatNumbers;
    }

    for (int i = 0; i < count; ++i) {
        int number;
        cout << "Enter seat number " << i + 1 << ": ";
        cin >> number;
        seatNumbers.push_back(number);
    }
    return seatNumbers;
}

unique_ptr<Payment> createPayment() {
    cout << "\nPayment Method\n";
    cout << "1. UPI\n2. Card\n3. Cash\n";
    cout << "Choose: ";

    int choice;
    cin >> choice;

    // Demo input: 1 = successful UPI, 2 = successful Card, 3 = successful Cash.
    // Enter 9 to simulate a failed payment.
    if (choice == 1) return make_unique<UpiPayment>(true);
    if (choice == 2) return make_unique<CardPayment>(true);
    if (choice == 3) return make_unique<CashPayment>(true);

    cout << "Invalid payment choice.\n";
    return nullptr;
}

int main() {
    Cinema cinema("PVR Demo Cinema");
    vector<Movie> movies;
    vector<Show> shows;

    seedData(cinema, movies, shows);

    Customer customer("Kartik Gupta", "9876543210");
    BookingService bookingService;
    vector<Booking*> bookings;

    int choice;

    do {
        cout << "\n\n===== MOVIE TICKET BOOKING =====\n";
        cout << "1. List movies\n";
        cout << "2. List shows for a movie\n";
        cout << "3. Display seat layout\n";
        cout << "4. Book ticket\n";
        cout << "5. Cancel booking\n";
        cout << "6. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice) {
            case 1:
                listMovies(movies);
                break;

            case 2:
                listShowsForMovie(movies, shows);
                break;

            case 3: {
                Show* show = chooseShow(shows);
                if (show) show->displaySeats();
                break;
            }

            case 4: {
                Show* show = chooseShow(shows);
                if (!show) break;

                show->displaySeats();
                vector<int> seatNumbers = readSeatNumbers();

                if (seatNumbers.empty()) break;

                unique_ptr<Payment> payment = createPayment();
                if (!payment) break;

                Booking* booking = bookingService.bookTicket(
                    &customer, show, seatNumbers, *payment
                );

                if (booking) bookings.push_back(booking);
                break;
            }

            case 5: {
                if (bookings.empty()) {
                    cout << "No booking exists.\n";
                    break;
                }

                cout << "Existing bookings:\n";
                for (Booking* booking : bookings)
                    cout << booking->getBookingId() << " - "
                         << booking->getShow()->getMovie()->getTitle() << '\n';

                int id;
                cout << "Enter booking ID to cancel: ";
                cin >> id;

                Booking* found = nullptr;
                for (Booking* booking : bookings)
                    if (booking->getBookingId() == id)
                        found = booking;

                if (found) bookingService.cancelBooking(found);
                else cout << "Booking ID not found.\n";
                break;
            }

            case 6:
                cout << "Thank you!\n";
                break;

            default:
                cout << "Invalid menu choice. Please try again.\n";
        }

    } while (choice != 6);

    for (Booking* booking : bookings)
        delete booking;

    return 0;
}
