#include <iostream>
#include <string>
#include <vector>
#include <ctime>  
#include <cstdlib>

class Ticket {
private:
    std::string fullName;         
    std::string purchaseTime;    
    double price;                
    std::string route;           
    bool isCurrent;               
    std::string userHistory;      
    std::string ticketStatus;    

public:
    Ticket(std::string name, std::string time, double p, std::string r, bool current, std::string history, std::string status)
        : fullName(name), purchaseTime(time), price(p), route(r), isCurrent(current), userHistory(history), ticketStatus(status) {}

    void printTicketInfo() const {
        std::cout << "Full Name: " << fullName << std::endl;
        std::cout << "Purchase Time: " << purchaseTime << std::endl;
        std::cout << "Price: " << price << " UAH" << std::endl;
        std::cout << "Route: " << route << std::endl;
        std::cout << "Current Status: " << (isCurrent ? "Valid" : "Invalid") << std::endl;
        std::cout << "User History: " << userHistory << std::endl;
        std::cout << "Ticket Status: " << ticketStatus << std::endl;
    }

    void cancelTicket() {
        ticketStatus = "Cancelled";
        isCurrent = false;
    }

    void updateStatus(std::string status) {
        ticketStatus = status;
    }

    bool isTicketCurrent() const {
        return isCurrent;
    }

    std::string getRoute() const {
        return route;
    }

    double getPrice() const {
        return price;
    }
};

std::string getCurrentTime() {
    std::time_t now = std::time(0);
    std::tm* ltm = std::localtime(&now);
    
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);
    
    return std::string(buffer);
}

void printMenu() {
    std::cout << "1. Add new ticket" << std::endl;
    std::cout << "2. Show all tickets" << std::endl;
    std::cout << "3. Cancel a ticket" << std::endl;
    std::cout << "0. Exit" << std::endl;
}

void clearConsole() {
#ifdef _WIN32
    std::system("cls");  
#else
    std::system("clear");  
#endif
}

int main() {
    std::vector<Ticket> tickets;  
    int choice;
    
    do {
        printMenu();
        std::cout << "\nChoose an option: ";
        std::cin >> choice;

        if (choice == 1) {
            std::string fullName, departurePlace, arrivalPlace, userHistory, ticketStatus;
            double price;
            bool isCurrent;
            int statusChoice;

            clearConsole();

            std::cout << "Enter full name: ";
            std::cin.ignore(); 
            std::getline(std::cin, fullName);

            std::string purchaseTime = getCurrentTime();

            std::cout << "\nEnter ticket price (in hryvnias): ";
            std::cin >> price;

            std::cout << "\nEnter departure place: ";
            std::cin.ignore();
            std::getline(std::cin, departurePlace);

            std::cout << "\nEnter arrival place: ";
            std::getline(std::cin, arrivalPlace);

            std::string route = departurePlace + " - " + arrivalPlace;

            std::cout << "\nIs the ticket current? (1 for yes, 0 for no): ";
            std::cin >> isCurrent;

            std::cout << "\nEnter user history: ";
            std::cin.ignore();
            std::getline(std::cin, userHistory);

            std::cout << "\nSelect ticket status: \n";
            std::cout << "1. Booked\n";
            std::cout << "2. Cancelled\n";
            std::cout << "3. Valid\n";
            std::cout << "4. Invalid\n";
            std::cout << "Choose status (1-4): ";
            std::cin >> statusChoice;

            switch (statusChoice) {
                case 1:
                    ticketStatus = "Booked";
                    break;
                case 2:
                    ticketStatus = "Cancelled";
                    break;
                case 3:
                    ticketStatus = "Valid";
                    break;
                case 4:
                    ticketStatus = "Invalid";
                    break;
                default:
                    std::cout << "\nInvalid choice, setting status to 'Unknown'.\n";
                    ticketStatus = "Unknown";
                    break;
            }

            clearConsole();

            tickets.emplace_back(fullName, purchaseTime, price, route, isCurrent, userHistory, ticketStatus);
            std::cout << "Ticket added successfully!\n" << std::endl;

        } else if (choice == 2) {
            if (tickets.empty()) {
                std::cout << "\nNo tickets available.\n" << std::endl;
            } else {
                clearConsole();
                for (size_t i = 0; i < tickets.size(); ++i) {
                    std::cout << "Ticket #" << i + 1 << std::endl;
                    tickets[i].printTicketInfo();
                    std::cout << "-----------------" << std::endl;
                }
            }
        } else if (choice == 3) {
            size_t index;
            std::cout << "\nEnter the ticket number to cancel: ";
            std::cin >> index;

            if (index > 0 && index <= tickets.size()) {
                tickets[index - 1].cancelTicket();
                std::cout << "\nTicket cancelled!\n" << std::endl;
            } else {
                std::cout << "\nInvalid ticket number!\n" << std::endl;
            }
        }
    } while (choice != 0);

    std::cout << "\nThanks for using my program!" << std::endl;
    return 0;
}
