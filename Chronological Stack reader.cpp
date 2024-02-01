#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

// Define a structure for storing name and time pairs
struct PairData {
    string name;
    int time;
};

int main() {
    // Get the current time point
    auto currentTimePoint = std::chrono::high_resolution_clock::now();

    // Convert the time point to milliseconds
    auto currentTimeInMillis = std::chrono::time_point_cast<std::chrono::milliseconds>(currentTimePoint);

    // Extract the time in milliseconds
    auto currentTime = currentTimeInMillis.time_since_epoch().count();
    cout<<"Init Time: "<<currentTime<<endl;
    // Create a stack of PairData
    stack<PairData> dataStack;

    // Open the CSV file
    ifstream inputFile("data.csv");

    if (!inputFile.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    // Simulate clock starting at 0 milliseconds
    int start_Time = 0;

    // Read the CSV file line by line
    string line;
    while (getline(inputFile, line)) {
        // Use a stringstream to split the line into time and name
        stringstream ss(line);
        string timeStr, name;

        getline(ss, timeStr, ',');
        getline(ss, name, ',');

        // Convert time string to integer
        int time = stoi(timeStr);

        // Simulate time passing
        this_thread::sleep_for(chrono::milliseconds(time - start_Time));

        // Update start_Time for the next iteration
        start_Time = time;

        // Create a PairData object
        PairData newData = {name, time};

        // Push the PairData onto the stack
        dataStack.push(newData);

        // Print the top element of the stack
        PairData topElement = dataStack.top();
        cout << "<" << topElement.name << ", " << topElement.time << ">" << endl;
    }
    currentTimePoint = std::chrono::high_resolution_clock::now();

    // Convert the time point to milliseconds
    currentTimeInMillis = std::chrono::time_point_cast<std::chrono::milliseconds>(currentTimePoint);

    // Extract the time in milliseconds
    currentTime = currentTimeInMillis.time_since_epoch().count();
    cout<<"End Time: "<<currentTime<<endl;
    // Close the file
    inputFile.close();

    return 0;
}
