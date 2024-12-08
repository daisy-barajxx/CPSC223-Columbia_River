#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP
using namespace std;

// TreeNode structure for binary tree
struct TreeNode {
    string name;        
    string type;    
    string year;    

    double height = 0;      
    double length = 0;  
    double discharge = 0;  

    TreeNode* left = nullptr;  
    TreeNode* right = nullptr; 

    // Constructor for tributary
    TreeNode(const string& n, const string& t, double l, double d)
        : name(n), type(t), length(l), discharge(d), left(nullptr), right(nullptr) {}

    // Constructor for dam
    TreeNode(const string& n, const string& t, double h, const string& y)
        : name(n), type(t), height(h), year(y), left(nullptr), right(nullptr) {}
};

// BinaryTree class
class BinaryTree {
private:
    TreeNode* root;
    TreeNode* currentParent;

    void insert(TreeNode*& parent, TreeNode* newNode);
    void deleteTree(TreeNode* node); 
    void printTree(TreeNode* current);  // Print tree (pre-order traversal)
    TreeNode* searchByName(TreeNode* node, const string& name);
    TreeNode* findLast(TreeNode* node);
    TreeNode* findParent(TreeNode* node, TreeNode* child);  

public:
    BinaryTree();
    ~BinaryTree();

    // Public insert function
    void insertNode(const string& name, const string& type, double value1, double value2, const string& year = "");
    void readFile(); 
    void displayAll();
    void menu();
    TreeNode* searchByName(const string& name);
    void navigateFromNode(TreeNode* startNode);
    void traverseControlled();
};

#endif
