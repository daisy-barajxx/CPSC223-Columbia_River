#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>

using namespace std;

// TreeNode structure for binary tree
struct TreeNode {
    string name;             // Node name
    string type;             // Node type ("tributary" or "dam")
    string year;             // Year (for dams)

    double height = 0;       // Height (for dams)
    double length = 0;       // Length (for tributaries)
    double discharge = 0;    // Discharge (for tributaries)

    TreeNode* left = nullptr;  // Left child
    TreeNode* right = nullptr; // Right child

    // Constructor for tributary
    TreeNode(const string& n, const string& t, double l, double d)
        : name(n), type(t), length(l), discharge(d) {}

    // Constructor for dam
    TreeNode(const string& n, const string& t, double h, const string& y)
        : name(n), type(t), height(h), year(y) {}
};

// BinaryTree class
class BinaryTree {
private:
    TreeNode* root;           // Root of the binary tree
    TreeNode* currentParent;  // Current parent node during insertion

    // Helper functions
    void insert(TreeNode*& parent, TreeNode* newNode);     // Recursive insert function
    void deleteTree(TreeNode* node);                      // Recursively delete the tree
    void printTree(TreeNode* node);                       // Pre-order traversal to print the tree
    TreeNode* getLastNode(TreeNode* node);                // Find the last rightmost node in a subtree
    TreeNode* searchByName(TreeNode* node, const string& name);

    void generatePreOrder(TreeNode* node, vector<TreeNode*>& visitedNodes);
public:
    // Constructor and destructor
    BinaryTree();
    ~BinaryTree();

    // Tree operations
    void insertNode(const string& name, const string& type, double value1, double value2, const string& year = ""); // Insert a new node
    void readFile();        // Read data from a file to populate the tree
    void displayAll();      // Display all nodes in the tree
    void traverseControlled(); // Controlled navigation (forward/backward) with user input
    void map(); // show the map

    // Menu
    void menu();            // Display menu for user interaction
};

#endif

