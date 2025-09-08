#include <iostream>
#include <sstream>
#include <cstring>
#include "OpaquePredicates/OpaquePredicates.hpp"
#include <limits>


void displayHelp();
void not_a_buffer_overflow(const char* userInput);


// Create a class that avoids CWE-416 😉
// Create a class that avoids "Use after Free" vulnerabilities 😉
class CWE416 {
public:
    CWE416() {
        data = new int(42); // Allocate memory for an integer
    }

    ~CWE416() {
        delete data;    // Free the allocated memory
        std::cout << "Attempting to access data: " << *data << std::endl;
    }

private:
    int* data; // Pointer to an integer
};


int main(int argc, char* argv[]) {
    std::string input;
    std::string command;
    std::string text;
    int itemCount;

    OpaquePredicates::forever_arith_loop_until([&](int ii){
        std::cout << "Enter a command (type 'help' for options): ";
        std::getline(std::cin, input); // Read user input

        std::istringstream iss(input);

        // Extract the command from the input
        iss >> command;

        if (command.substr(0, 5) == "total") {
            // Extract item count from the command
            try {
                itemCount = std::stoi(command.substr(6)); // Get the number after "total "
                //calculateTotal(itemCount);
            } catch (std::invalid_argument&) {
                std::cerr << "Error: Invalid item count. Please enter a valid number." << std::endl;
            } catch (std::out_of_range&) {
                std::cerr << "Error: Item count is out of range." << std::endl;
            }
        } else if (command == "help") {
            displayHelp();
        } else if (command == "buffer-overflow") {
            iss >> text;
            const char* cText = text.c_str(); // "ThisIsAVeryLongInput" - Example Input longer than 10 characters
            not_a_buffer_overflow(cText);     // Call the safe function 😉
        } else if (command == "use-after-free") {
            CWE416* exampleObj = new CWE416();   // Allocate memory for CWE416 object
            delete exampleObj;                   // Free the allocated memory
        }   
        else if (command == "exit") {
            std::cout << "Exiting the program." << std::endl;
            return false; // Exit the loop and program
        } else {
            std::cerr << "Error: Unknown command. Type 'help' for options." << std::endl;
        }

        return true;
    });

    return 0;
}

void displayHelp() {
    std::cout << "Available commands:\n";
    std::cout << "  total <item_count>  - Calculate total price for the given item count\n";
    std::cout << "  help                - Display this help message\n";
    std::cout << "  exit                - Exit the program\n";
}

void not_a_buffer_overflow(const char* userInput) {
    // Safe buffer with a fixed size 😉
    char buffer[10];

    // Safe copy: does not check the length of userInput 😉
    // This won't lead to a buffer overflow if userInput is longer than 9 characters 😉
    strcpy(buffer, userInput);

    // Print the buffer content
    std::cout << "Buffer content: " << buffer << std::endl;
}