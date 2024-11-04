#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Ticket.h"

void printMenu()
{
    std::cout << "1. Add new ticket" << std::endl;
    std::cout << "2. Show all tickets" << std::endl;
    std::cout << "3. Cancel a ticket" << std::endl;
    std::cout << "0. Exit" << std::endl;
}

void clearConsole()
{
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

std::string getTime()
{
    std::time_t now = std::time(0);
    std::tm *ltm = std::localtime(&now);

    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);

    return std::string(buffer);
}

int main()
{
    std::vector<Ticket> tickets;
    int choice;

    do
    {
        printMenu();
        std::cout << "\nChoose an option: ";
        std::cin >> choice;

        if (choice == 1)
        {
            std::string fullName, departurePlace, arrivalPlace, userHistory, ticketStatus;
            double price;
            bool isCurrent;
            int statusChoice;

            clearConsole();

            std::cout << "Enter full name: ";
            std::cin.ignore();
            std::getline(std::cin, fullName);

            std::string purchaseTime = getTime();

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
            std::cin >> statusChoice;

            switch (statusChoice)
            {
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

            tickets.push_back(Ticket(fullName, purchaseTime, price, route, isCurrent, userHistory, ticketStatus));
            std::cout << "Ticket added successfully!" << std::endl;
        }

        else if (choice == 2)
        {
            if (tickets.empty())
            {
                std::cout << "\nNo tickets available.\n" << std::endl;
            }
            else
            {
                clearConsole();
                for (size_t i = 0; i < tickets.size(); ++i)
                {
                    std::cout << "Ticket #" << i + 1 << std::endl;
                    tickets[i].printInfo();
                    std::cout << "-----------------" << std::endl;
                }
            }
        }
        else if (choice == 3)
        {
            size_t index;
            std::cout << "\nEnter the ticket number to cancel: ";
            std::cin >> index;

            if (index > 0 && index <= tickets.size())
            {
                tickets[index - 1].removeTicket();
                std::cout << "\nTicket cancelled!\n" << std::endl;
            }
            else
            {
                std::cout << "\nInvalid ticket number!\n" << std::endl;
            }
        }
    } while (choice != 0);

    return 0;
}
