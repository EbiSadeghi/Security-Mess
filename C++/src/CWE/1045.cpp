#include <iostream>

// TODO - modify comments

// Parent class has a virtual destructor,
// but a derived (child) class does not explicitly declare one.
// This can lead to problems if someone expects virtual-dtor behavior
// in the child (e.g., further subclassing or resource cleanup).
class Base1045 {
public:
    virtual ~Base1045() {        // Parent has a virtual destructor
        std::cout << "Base1045::~Base1045()\n";
    }
    virtual void doWork() {
        std::cout << "Base1045::doWork()\n";
    }
};

class Child1045 : public Base1045 {
    // No explicit destructor declared here.
    // The compiler still generates a destructor for Child, and because
    // Base's destructor is virtual, Child's implicitly-generated
    // destructor is virtual as well. BUT CWE-1045 concerns the
    // expectation/maintenance risk when a child class appears to omit
    // an explicit virtual destructor while it manages resources or is
    // further subclassed.
public:
    Child1045() : buffer(new int[4]) {}
    void doWork() override {
        std::cout << "Child1045::doWork()\n";
    }
private:
    int* buffer;
    // Missing explicit destructor to delete buffer -> resource leak
    // even though the implicitly-generated destructor is virtual,
    // it doesn't free buffer because no destructor code was written.
};