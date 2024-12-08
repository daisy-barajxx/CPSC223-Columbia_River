#include "project3.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>

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
        // recurse to the left child if it is not null
        else {
            insert(parent->left, newNode);
        }
    } 
    // If the parent node is of type "dam", insert the new node as the right child
    else if (parent->type == "dam") {
        if (parent->right == nullptr) {
            parent->right = newNode;
        } 
        // recurse to the right child if it is not null
        else {
            insert(parent->right, newNode);
        }
    }
}

// Insert a new node
void BinaryTree::insertNode(const string& name, const string& type, double value1, double value2, const string& year) {
    TreeNode* newNode = nullptr; // create a new node

    // if the data is tributary, insert length and discharge into the node
    // if the data is dam, insert height and year into the node
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

void BinaryTree::traverseControlled(){
    stack<TreeNode*> navigationStack;
    TreeNode* current = root;
    bool exit = false;

    while (!exit){
        cout << "Current node: " << current->name << endl;
        if(current->type == "tributary"){
            cout << "Name: " << current->name << ", Type: " << current->type << ", Length: " << current->length << ", Discharge: " << current->discharge << endl;
        }else if(current->type == "dam"){
            cout << "Name: " << current->name << ", Type: " << current->type << ", Height: " << current->height << ", Year: " << current->year << endl;
        }else{
            cout << "No more dam or tributary" << endl;
        }

        // choose go forward or go backward
        cout << "Enter 1 to Go Backward, 2 to Go Forward, 3 to Exit: ";
        int choice;
        cin >> choice;

        switch(choice){
            case 1:{
                if(navigationStack.empty()){
                    cout << "No previous node to go back to." << endl;
                }else {
                    TreeNode* previous = navigationStack.top();
                    navigationStack.pop();
                    if (current->type == "tributary") {
                        current = previous;
                    } else if (current->type == "dam") {
                        if (previous->left) {
                            TreeNode* lastNode = previous->left;
                            while (lastNode->right) {
                                lastNode = lastNode->right;
                            }
                            current = lastNode;
                        } else {
                            current = previous;
                        }
                    }
                }
                break;
            }
            case 2: { // Forward
                if (current) {
                    navigationStack.push(current); // Save the current node
                    if (current->type == "tributary" && current->left) {
                        current = current->left;
                    } else if (current->type == "dam" && current->left) {
                        current = current->left;
                    } else if (current->right) {
                        current = current->right;
                    } else {
                        cout << "No further nodes to visit.\n";
                        current = nullptr;
                    }
                } else {
                    cout << "No current node to move forward from.\n";
                }
                break;
            }
            case 3: {
                exit = true;
                cout << "Exiting navigation.\n";
                break;
            }
            default: {
                cout << "Invalid choice. Please try again.\n";
            }
        }
    }
}

// if
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
            cout << "Parsed: " << name << ", " << type << ", Length: " << value1 << ", Discharge: " << value2 << endl;
            insertNode(name, type, value1, value2);
        } else if (type == "dam") {
            ss >> value1 >> year;
            cout << "Parsed: " << name << ", " << type << ", Height: " << value1 << ", Year: " << year << endl;
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
        cout << "1. Load Data from File" << endl;
        cout << "2. Start Travel" << endl;
        cout << "3. Display All datas" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            readFile();
            break;
        }
        case 2:
            traverseControlled();
            break;
        case 3:
            displayAll();
            break;
        case 4:
            exit = true;
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice, please try again." << endl;
        }
    }
}
