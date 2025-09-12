#include <iostream>

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
