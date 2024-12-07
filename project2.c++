#include <iostream>
#include <string>
#include <stack>
#include <thread>
#include <chrono>

using namespace std;

// Struct to represent each node in the tree
struct RiverNode {
    string name;            // Name of the river, dam, or location
    string info;            // Information about the node
    RiverNode* left;        // Left child (tributary)
    RiverNode* right;       // Right child (next stream or dam)
    bool isDam;             // Flag to check if it's a dam node

    // Constructor for river or dam nodes
    RiverNode(const string& name, const string& info, bool isDam = false)
        : name(name), info(info), left(nullptr), right(nullptr), isDam(isDam) {}
};

// Function to add a cute delay before printing
void pause() {
    this_thread::sleep_for(chrono::milliseconds(800));  // Cute pause for 0.8 seconds
}

// Function to print the node with a cute message
void printNodeInfo(RiverNode* node) {
    cout << "\n--- Now exploring: " << node->name << " ---\n";
    cout << node->info << endl;
    pause();
}

// Function to explore the tree interactively
void exploreTree(RiverNode* root) {
    RiverNode* currentNode = root;
    stack<RiverNode*> history;  // Stack to keep track of the user’s history (for going upstream)

    cout << "\nWelcome to the Columbia River Journey!\n";
    cout << "Let’s start our journey from the Pacific Northwest and explore the river system.\n";
    pause();
    printNodeInfo(currentNode);

    bool exploring = true;
    while (exploring) {
        if (currentNode->isDam) {
            // If the current node is a dam, display information and let the user go back or forward.
            cout << "\nYou are at the " << currentNode->name << " Dam.\n";
            cout << currentNode->info << endl;
            cout << "\nWhat would you like to do next?\n";
            cout << "1. Move downstream (go forward)\n";
            cout << "2. Move upstream (go back)\n";
            cout << "3. Quit the journey\n";
            cout << "Please enter your choice (1, 2, or 3): ";
        } else {
            // If it's a river node (tributary)
            cout << "\nYou have two choices:\n";
            cout << "1. Visit this river node (" << currentNode->name << ")\n";
            cout << "2. Move forward to the next node (dam or river)\n";
            cout << "3. Move upstream\n";
            cout << "4. Quit the journey\n";
            cout << "Please enter your choice (1, 2, 3, or 4): ";
        }
        
        int choice;
        cin >> choice;
        cin.ignore();  // Ignore any leftover input

        if (choice == 1) {
            // Visit the current node
            printNodeInfo(currentNode);
        } else if (choice == 2) {
            // Moving downstream to the next node (whether it's a river or dam)
            if (currentNode->right) {
                history.push(currentNode);
                currentNode = currentNode->right;
                printNodeInfo(currentNode);
            } else {
                cout << "\nOh no! There is no downstream node. You're at the end of the river! 🌊\n";
                pause();
            }
        } else if (choice == 3) {
            // Moving upstream: Check if there’s history to go back to
            if (!history.empty()) {
                currentNode = history.top();
                history.pop();
                printNodeInfo(currentNode);
            } else {
                cout << "\nYou’re already at the start of the journey! Can't go upstream from here. 🚶‍♀️🚶‍♂️\n";
                pause();
            }
        } else if (choice == 4) {
            cout << "\nThank you for exploring the Columbia River System with us! You've been an awesome explorer! 👋\n";
            exploring = false;
        } else {
            cout << "\nOops! That’s not a valid choice. Please try again! 😅\n";
        }
    }
}

// Create the tree structure for the Columbia River system
RiverNode* createRiverTree() {
    // Creating leaf nodes (Tributaries and Dams)
    RiverNode* willamette = new RiverNode("Willamette River", "A major tributary of the Columbia River, flowing through Oregon.");
    RiverNode* deschutes = new RiverNode("Deschutes River", "Tributary that flows into the Columbia River from the south.");
    RiverNode* johnDay = new RiverNode("John Day River", "A major tributary in Oregon that joins the Columbia River.");
    RiverNode* snake = new RiverNode("Snake River", "A large tributary of the Columbia, flowing from Wyoming and Idaho.");
    RiverNode* yakima = new RiverNode("Yakima River", "Flows into the Columbia River from the southeast.");
    RiverNode* okanogan = new RiverNode("Okanogan River", "A tributary flowing into the Columbia in Washington.");
    RiverNode* spokane = new RiverNode("Spokane River", "Flows into the Columbia River near the city of Spokane, Washington.");

    RiverNode* bonneville = new RiverNode("Bonneville Dam", "First major dam on the Columbia River, located near Portland.", true);
    RiverNode* dalles = new RiverNode("The Dalles Dam", "A dam that provides power and controls flow in the Columbia River.", true);
    RiverNode* johnDayDam = new RiverNode("John Day Dam", "A dam located near the John Day River, providing power and water regulation.", true);
    RiverNode* mcNary = new RiverNode("McNary Dam", "A large hydroelectric dam located near the Oregon-Washington border.", true);
    RiverNode* priestRapids = new RiverNode("Priest Rapids Dam", "A key dam that helps with irrigation and hydroelectric power.", true);
    RiverNode* wanapum = new RiverNode("Wanapum Dam", "Located in Washington, providing hydroelectric power and flood control.", true);
    RiverNode* rockIsland = new RiverNode("Rock Island Dam", "Located on the Columbia River near Wenatchee, Washington.", true);
    RiverNode* rockyReach = new RiverNode("Rocky Reach Dam", "Hydroelectric dam in Washington providing power to the region.", true);
    RiverNode* wells = new RiverNode("Wells Dam", "Located on the Columbia River, producing hydroelectric power.", true);
    RiverNode* chiefJoseph = new RiverNode("Chief Joseph Dam", "A major hydroelectric dam located on the Columbia River in Washington.", true);
    RiverNode* grandCoulee = new RiverNode("Grand Coulee Dam", "The largest concrete structure in the U.S., providing significant power generation.", true);

    // Connecting nodes to form the binary tree structure
    RiverNode* pacificNW = new RiverNode("Pacific Northwest", "Start of the Columbia River system.");

    pacificNW->right = snake;  // Snake River is the main tributary

    // Downstream flow from Pacific Northwest
    snake->right = yakima;   // Yakima River flows next
    yakima->right = okanogan;  // Okanogan River flows next
    okanogan->right = spokane;  // Spokane River flows last

    // Tributaries branching out
    pacificNW->left = willamette;  // Willamette River is the first major tributary
    willamette->right = deschutes;  // Deschutes River follows
    deschutes->right = johnDay;  // John Day River flows next

    // Connecting dams
    johnDay->left = bonneville;  // Bonneville Dam connects to the left
    bonneville->right = dalles;  // The Dalles Dam follows
    dalles->right = johnDayDam;
    johnDayDam->right = mcNary;
    mcNary->right = priestRapids;
    priestRapids->right = wanapum;
    wanapum->right = rockIsland;
    rockIsland->right = rockyReach;
    rockyReach->right = wells;
    wells->right = chiefJoseph;
    chiefJoseph->right = grandCoulee;

    // Returning the root of the tree (start point)
    return pacificNW;
}

int main() {
    RiverNode* root = createRiverTree();

    exploreTree(root);

    return 0;
}