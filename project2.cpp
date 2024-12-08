#include "project2.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cctype>

using namespace std;

// Constructor
BinaryTree::BinaryTree() : root(nullptr), currentParent(nullptr) {}

// Destructor
BinaryTree::~BinaryTree() {
    deleteTree(root);
}

// Recursive delete the tree
void BinaryTree::deleteTree(TreeNode* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

// Insert data into the binary tree
void BinaryTree::insert(TreeNode*& parent, TreeNode* newNode) {
    // If the current parent node is null, assign the new node as the parent
    if (parent == nullptr) {
        parent = newNode;
    } 
    // If the parent node is of type "tributary", insert the new node as the left child
    else if (parent->type == "tributary") {
        if (parent->left == nullptr) {
            parent->left = newNode;
        } 
        // Recurse to the left child if it is not null
        else {
            insert(parent->left, newNode);
        }
    } 
    // If the parent node is of type "dam", insert the new node as the right child
    else if (parent->type == "dam") {
        if (parent->right == nullptr) {
            parent->right = newNode;
        } 
        // Recurse to the right child if it is not null
        else {
            insert(parent->right, newNode);
        }
    }
}

// Insert a new node
void BinaryTree::insertNode(const string& name, const string& type, double value1, double value2, const string& year) {
    TreeNode* newNode = nullptr; // Create a new node

    // If the data is tributary, insert length and discharge into the node
    // If the data is dam, insert height and year into the node
    if (type == "tributary") {
        newNode = new TreeNode(name, type, value1, value2);
    } else if (type == "dam") {
        newNode = new TreeNode(name, type, value1, year);
    }

    if (!root) {
        root = newNode;
        currentParent = root;
    } else {
        insert(currentParent, newNode);
    }
}

// User can search their current location (case-insensitive)
TreeNode* BinaryTree::searchByName(TreeNode* node, const string& name) {
    if (!node) return nullptr;

    // Convert both the node's name and the search name to lowercase for comparison
    string nodeNameLower = node->name;
    string searchNameLower = name;

    transform(nodeNameLower.begin(), nodeNameLower.end(), nodeNameLower.begin(), ::tolower);
    transform(searchNameLower.begin(), searchNameLower.end(), searchNameLower.begin(), ::tolower);

    // Compare the lowercase names
    if (nodeNameLower == searchNameLower) return node;

    // Recursively search the left and right subtrees
    TreeNode* leftSearch = searchByName(node->left, name);
    if (leftSearch) return leftSearch;

    return searchByName(node->right, name);
}

// Add the current node to the visited nodes vector
void BinaryTree::generatePreOrder(TreeNode* node, vector<TreeNode*>& visitedNodes) {
    if (!node) return;
    visitedNodes.push_back(node);          
    // Recursively traverse the left subtree
    generatePreOrder(node->left, visitedNodes); 

    // Recursively traverse the right subtree
    generatePreOrder(node->right, visitedNodes);
}

// user can choose go forward or backward
void BinaryTree::traverseControlled() {
    while (true) {
        cout << "Enter the name of the starting node: ";
        string startName;
        cin >> startName;

        // Step 1: Search for the name in the tree
        TreeNode* current = searchByName(root, startName);
        if (!current) {
            // If the name is not found, display an error message and return
            cout << "Node with name \"" << startName << "\" not found in data. Please try again." << endl;
            return;
        }

        // Step 2: If found, generate the pre-order traversal sequence
        vector<TreeNode*> visitedNodes;
        generatePreOrder(root, visitedNodes);

        // Step 3: Locate the starting node in the traversal sequence
        int currentIndex = -1;
        for (int i = 0; i < visitedNodes.size(); i++) {
            if (visitedNodes[i] == current) {
                currentIndex = i;
                break;
            }
        }

        if (currentIndex == -1) {
            // If somehow the node isn't in the traversal, return an error
            cout << "Node with name \"" << startName << "\" not found in traversal sequence. Please try again." << endl;
            return;
        }

        // Step 4: Navigation logic
        bool exit = false;

        while (!exit) {
            // Display current node information
            current = visitedNodes[currentIndex];
            cout<<endl<<endl;
            cout << "Current node: " << current->name << endl;
            cout<<endl<<endl;
            if (current->type == "tributary") {
                cout << "Name: " << current->name << ", Type: " << current->type 
                     << ", Length: " << current->length << ", Discharge: " << current->discharge << endl;
            } else if (current->type == "dam") {
                cout << "Name: " << current->name << ", Type: " << current->type 
                     << ", Height: " << current->height << ", Year: " << current->year << endl;
            }
            cout<<endl<<endl;

            // Provide navigation options
            cout << "Enter 1 to Go Backward, 2 to Go Forward, 3 to Exit: ";
            int choice;
            cin >> choice;

            if (cin.fail()) {
                cin.clear(); // Clear the error flag on cin
                cin.ignore(1000, '\n'); // Discard invalid input
                cout << "Invalid input. Please enter 1, 2, or 3.\n";
                continue;
            }

            switch (choice) {
                case 1: { // Go backward
                    cout<<endl<<endl;
                    if (currentIndex == 0) {
                        cout << "There is no more dam and tributary before." << endl;
                        cout<<endl<<endl;
                    } else {
                        currentIndex--; // Move to the previous node
                    }
                    break;
                }
                case 2: { // Go forward
                    cout<<endl<<endl;
                    if (currentIndex == visitedNodes.size() - 1) {
                        cout << "There is no more dam and tributary after." << endl;
                        cout<<endl<<endl;
                    } else {
                        currentIndex++; // Move to the next node
                    }
                    break;
                }
                case 3: { // Exit
                    exit = true;
                    cout << "Exiting navigation.\n";
                    break;
                }
                default: {
                    cout << "Invalid choice. Please enter 1, 2, or 3.\n";
                }
            }
        }

        break; // Exit the input loop after successful navigation
    }
}


TreeNode* BinaryTree::getLastNode(TreeNode* node) {
    if (!node) return nullptr;
    while (node->right) {
        node = node->right;
    }
    return node;
}

// Print tree (pre-order traversal)
void BinaryTree::printTree(TreeNode* node) {
    if (node) {
        cout << "Name: " << node->name << ", Type: " << node->type;

        if (node->type == "tributary") {
            cout << ", Length: " << node->length << " km"
                 << ", Discharge: " << node->discharge << " m³/s";
        } else if (node->type == "dam") {
            cout << ", Height: " << node->height << " m"
                 << ", Year: " << node->year;
        }
        cout << endl << endl;
        printTree(node->left);
        printTree(node->right);
    }
}

// Read data from file and populate tree
void BinaryTree::readFile() {
    const string filename = "data.txt";
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, type, year;
        double value1 = 0, value2 = 0;

        ss >> name >> type;
        if (type == "tributary") {
            ss >> value1 >> value2;
            insertNode(name, type, value1, value2);
        } else if (type == "dam") {
            ss >> value1 >> year;
            insertNode(name, type, value1, 0, year);
        }
    }

    file.close();
    cout << "Data loaded successfully from " << filename << endl;
}

// Display all nodes
void BinaryTree::displayAll() {
    printTree(root);
}

// Menu for user interaction
void BinaryTree::menu() {
    bool exit = false;
    while (!exit) {
        cout << "\nBinary Tree Menu:" << endl;
        cout << "1. Display All datas" << endl;
        cout << "2. Start Travel" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
        case 1: // Display all data
            displayAll();
            break;
        case 2: // Start travel
            traverseControlled();
            break;
        case 3: // Exit
            exit = true;
            cout << "Exiting program." << endl;
            break;
        default: // Invalid input
            cout << "Invalid choice, please try again." << endl;
        }
    }
}

