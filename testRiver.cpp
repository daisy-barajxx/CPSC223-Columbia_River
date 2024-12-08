#include <iostream>
#include <cassert>
#include "project2.hpp"  // Include your header for the BinaryTree class

using namespace std;

int main() {
    BinaryTree tree;  // Create an instance of BinaryTree
    tree.readFile();  // Load data into the tree from the file (make sure you have this method)

    // 1. Test Insertion - User can add nodes manually with instructions
    cout << "\n--- Welcome to the Node Insertion Section ---" << endl;
    cout << "You can add nodes (either a dam or a tributary) to the system." << endl;
    cout << "Please follow the prompts below. 😊" << endl;

    string name, type, year;
    double value1, value2;  // These will hold the height/length and year/discharge
    char userChoice;  // To get the user's choice for dam or tributary

    // Insert first node
    cout << "\n--- Insert the first node ---" << endl;
    cout << "Enter the name of the dam or tributary (e.g., Bonneville, Snake): ";
    cin >> name;

    // Ask the user whether it's a dam or tributary
    cout << "Is this a (d)am or a (t)ributary? ";
    cout << "Enter 'd' for dam or 't' for tributary: ";
    cin >> userChoice;
    
    // Handle type selection and provide appropriate prompts based on the choice
    if (userChoice == 'd' || userChoice == 'D') {
        type = "dam";
        cout << "\nYou chose a DAM! 🏞️" << endl;
        cout << "Please enter the following information for the dam:" << endl;

        // Ask for height of the dam
        cout << "Enter the height of the dam (in meters): ";
        cin >> value1;

        // Ask for the year (mandatory input)
        cout << "Enter the year the dam was built (e.g., 1990): ";
        cin.ignore();  // To clear the buffer
        while (true) {
            getline(cin, year);
            if (year.empty()) {
                cout << "Oops! The year is mandatory. Please enter a valid year (e.g., 1990): ";
            } else {
                break;  // Exit the loop once a valid year is provided
            }
        }
    } else if (userChoice == 't' || userChoice == 'T') {
        type = "tributary";
        cout << "\nYou chose a TRIBUTARY! 🌊" << endl;
        cout << "Please enter the following information for the tributary:" << endl;

        // Ask for length of the tributary
        cout << "Enter the length of the tributary (in kilometers): ";
        cin >> value1;

        // Ask for discharge (flow rate) of the tributary
        cout << "Enter the discharge of the tributary (in cubic meters per second): ";
        cin >> value2;
    } else {
        cout << "Oops! Invalid option. Defaulting to 'dam'." << endl;
        type = "dam";
    }

    // Insert the first node into the tree
    tree.insertNode(name, type, value1, value2, year);

    // Insert second node
    cout << "\n--- Insert the second node ---" << endl;
    cout << "Enter the name of the dam or tributary (e.g., GrandCoulee, Yakima): ";
    cin >> name;

    // Ask the user whether it's a dam or tributary
    cout << "Is this a (d)am or a (t)ributary? ";
    cout << "Enter 'd' for dam or 't' for tributary: ";
    cin >> userChoice;
    
    // Handle type selection and provide appropriate prompts based on the choice
    if (userChoice == 'd' || userChoice == 'D') {
        type = "dam";
        cout << "\nYou chose a DAM! 🏞️" << endl;
        cout << "Please enter the following information for the dam:" << endl;

        // Ask for height of the dam
        cout << "Enter the height of the dam (in meters): ";
        cin >> value1;

        // Ask for the year (mandatory input)
        cout << "Enter the year the dam was built (e.g., 1990): ";
        cin.ignore();  // To clear the buffer
        while (true) {
            getline(cin, year);
            if (year.empty()) {
                cout << "Oops! The year is mandatory. Please enter a valid year (e.g., 1990): ";
            } else {
                break;  // Exit the loop once a valid year is provided
            }
        }
    } else if (userChoice == 't' || userChoice == 'T') {
        type = "tributary";
        cout << "\nYou chose a TRIBUTARY! 🌊" << endl;
        cout << "Please enter the following information for the tributary:" << endl;

        // Ask for length of the tributary
        cout << "Enter the length of the tributary (in kilometers): ";
        cin >> value1;

        // Ask for discharge (flow rate) of the tributary
        cout << "Enter the discharge of the tributary (in cubic meters per second): ";
        cin >> value2;
    } else {
        cout << "Oops! Invalid option. Defaulting to 'dam'." << endl;
        type = "dam";
    }

    // Insert the second node into the tree
    tree.insertNode(name, type, value1, value2, year);

    // Add more nodes automatically if needed for testing
    tree.insertNode("Bonneville", "dam", 150.3, 0, "1990");
    tree.insertNode("GrandCoulee", "dam", 200.0, 0, "2000");
    tree.insertNode("Yakima", "tributary", 100.5, 1200.2);
    tree.insertNode("Wells", "dam", 180.2, 0, "1999");
    tree.insertNode("Snake", "tributary", 250.3, 500.4);

    cout << "\nYour nodes have been successfully added! 🥳" << endl;

    // 2. Test Searching by name (case-insensitive)
    cout << "\n--- Searching for a Node ---" << endl;
    cout << "You can search for a node by name. The search is case-insensitive." << endl;
    cout << "Enter the name of the dam/tributary to search for (e.g., Bonneville or Yakima): ";
    cin >> name;
    
    TreeNode* result = tree.searchByNamePublic(name);  // Corrected to use `result`
    
    if (result) {  // Check if the node is found
        cout << "Found node: " << result->name << ", Type: " << result->type << endl;
    } else {
        cout << "Node not found. Please check the name and try again." << endl;
    }

    // 3. Test Traversing (forward/backward)
    cout << "\n--- Traversing the Tree ---" << endl;
    cout << "Now, you can traverse through the nodes. You will be able to move forward and backward." << endl;
    tree.traverseControlled();  // User will interact and navigate through nodes

    // 4. Test Map Display
    cout << "\n--- Displaying the Map ---" << endl;
    cout << "Here is a map of the tree nodes based on the data you entered:" << endl;
    tree.map();  // Should display the map in the desired format

    cout << "\nProgram execution complete! 🎉" << endl;

    return 0;
}
