
// Carl Pottorff
// 6/16/25
// Project 3 


#include <iostream>
#include <fstream>
#include <map>
#include <string>

class ItemTracker {
private:
    std::map<std::string, int> itemFrequency;  // Map to store items and their frequencies
    std::string inputFileName;                 // Input file name
    std::string outputFileName;                // Output file name

    // Private method to read data from input file
    void readDataFromFile() {
        std::ifstream inputFile(inputFileName);
        std::string item;

        if (inputFile.is_open()) {
            // Read each line from the file
            while (std::getline(inputFile, item)) {
                // Increment the frequency for this item
                itemFrequency[item]++;
            }
            inputFile.close();
        }
        else {
            std::cout << "Error: Unable to open input file." << std::endl;
        }
    }

    // Private method to save data to backup file
    void saveDataToFile() {
        std::ofstream outputFile(outputFileName);

        if (outputFile.is_open()) {
            // Write each item and its frequency to the file
            for (const auto& pair : itemFrequency) {
                outputFile << pair.first << " " << pair.second << std::endl;
            }
            outputFile.close();
        }
        else {
            std::cout << "Error: Unable to create backup file." << std::endl;
        }
    }

public:
    // Constructor
    ItemTracker(const std::string& inputFile, const std::string& outputFile) {
        inputFileName = inputFile;
        outputFileName = outputFile;
        readDataFromFile();  // Load data when object is created
        saveDataToFile();    // Create backup file
    }

    // Method to get frequency of a specific item
    int getItemFrequency(const std::string& item) {
        if (itemFrequency.find(item) != itemFrequency.end()) {
            return itemFrequency[item];
        }
        return 0;  // Return 0 if item not found
    }

    // Method to print all items with their frequencies
    void printAllFrequencies() {
        for (const auto& pair : itemFrequency) {
            std::cout << pair.first << " " << pair.second << std::endl;
        }
    }

    // Method to print histogram
    void printHistogram() {
        for (const auto& pair : itemFrequency) {
            std::cout << pair.first << " ";

            // Print asterisks equal to the frequency count
            for (int i = 0; i < pair.second; i++) {
                std::cout << "*";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    // Create ItemTracker object with input and output file names
    ItemTracker tracker("CS210_Project_Three_Input_File.txt", "frequency.dat");

    int choice = 0;
    std::string searchItem;

    // Main program loop
    while (choice != 4) {
        // Display menu
        std::cout << "\n===== Corner Grocer Item Tracking =====\n";
        std::cout << "1. Look up item frequency\n";
        std::cout << "2. Print all item frequencies\n";
        std::cout << "3. Print item frequency histogram\n";
        std::cout << "4. Exit program\n";
        std::cout << "Enter your choice (1-4): ";
        std::cin >> choice;

        // Process user choice
        switch (choice) {
        case 1:
            std::cout << "Enter the item to search for: ";
            std::cin.ignore();  // Clear input buffer
            std::getline(std::cin, searchItem);
            std::cout << searchItem << " frequency: " << tracker.getItemFrequency(searchItem) << std::endl;
            break;

        case 2:
            std::cout << "\nAll Item Frequencies:\n";
            tracker.printAllFrequencies();
            break;

        case 3:
            std::cout << "\nItem Frequency Histogram:\n";
            tracker.printHistogram();
            break;

        case 4:
            std::cout << "Thank you for using the Corner Grocer tracking system. Goodbye!\n";
            break;

        default:
            std::cout << "Invalid choice. Please enter a number between 1 and 4.\n";
        }
    }

    return 0;
}