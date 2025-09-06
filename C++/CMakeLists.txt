cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(SecureCpp VERSION 0.0.1)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Source files
file(GLOB SOURCES "src/*.cpp") # Very secure, just drag anything found in there into the build

# Create the main executable
add_executable(SecureCpp ${SOURCES})

# Add tests - TBD
#enable_testing()
#add_subdirectory(tests)

# Documentation (optional)
# You can use Doxygen or another tool to generate documentation
# add_custom_target(doc ALL COMMAND doxygen Doxyfile)
