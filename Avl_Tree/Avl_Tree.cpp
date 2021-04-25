
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

class Node {
public:
    int key;
    Node* left;
    Node* right;
    int height;
};

int max(int a, int b);

// Calculate height
int height(Node* N) {
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

// New node creation
Node* newNode(int key) {
    Node* node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return (node);
}

// Rotate right
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left),
        height(y->right)) +
        1;
    x->height = max(height(x->left),
        height(x->right)) +
        1;
    return x;
}

// Rotate left
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left),
        height(x->right)) +
        1;
    y->height = max(height(y->left),
        height(y->right)) +
        1;
    return y;
}

// Get the balance factor of each node
int getBalanceFactor(Node* N) {
    if (N == NULL)
        return 0;
    return height(N->left) -
        height(N->right);
}

// Insert a node
Node* insertNode(Node* node, int key) {
    // Find the correct postion and insert the node
    if (node == NULL)
        return (newNode(key));
    if (key < node->key)
        node->left = insertNode(node->left, key);
    else if (key > node->key)
        node->right = insertNode(node->right, key);
    else
        return node;

    // Update the balance factor of each node and
    // balance the tree
    node->height = 1 + max(height(node->left),
        height(node->right));
    int balanceFactor = getBalanceFactor(node);
    if (balanceFactor > 1) {
        if (key < node->left->key) {
            return rightRotate(node);
        }
        else if (key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }
    if (balanceFactor < -1) {
        if (key > node->right->key) {
            return leftRotate(node);
        }
        else if (key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }
    return node;
}

// Node with minimum value
Node* nodeWithMimumValue(Node* node) {
    Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Delete a node
Node* deleteNode(Node* root, int key) {
    // Find the node and delete it
    if (root == NULL)
        return root;
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if ((root->left == NULL) ||
            (root->right == NULL)) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            free(temp);
        }
        else {
            Node* temp = nodeWithMimumValue(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right,
                temp->key);
        }
    }

    if (root == NULL)
        return root;

    // Update the balance factor of each node and
    // balance the tree
    root->height = 1 + max(height(root->left),
        height(root->right));
    int balanceFactor = getBalanceFactor(root);
    if (balanceFactor > 1) {
        if (getBalanceFactor(root->left) >= 0) {
            return rightRotate(root);
        }
        else {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }
    if (balanceFactor < -1) {
        if (getBalanceFactor(root->right) <= 0) {
            return leftRotate(root);
        }
        else {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }
    return root;
}
map<int, string> vec;

void updateMap(int level, int val)
{
    map<int, string>::iterator iter = vec.find(level);
    string temp;
    if (iter == vec.end())
    {
        vec.insert(pair<int, string>(level, to_string(level) + ": " + to_string(val) + " "));
    }
    else
    {
        temp = iter->second + to_string(val) + " ";
        iter->second = temp;
    }
}
// Print the tree
void printTree(Node* root, int level) {

    if (root == NULL)
    {
        return;
    }

    updateMap(level, root->key);

    printTree(root->left, level + 1);
    printTree(root->right, level + 1);
}

vector<int> StringToVector(string numbers)
{
    stringstream numbersStringStream(numbers);
    string number;
    vector<int> numbersVector;

    while (getline(numbersStringStream, number, ' '))
    {
        numbersVector.push_back(stoi(number));
    }

    return numbersVector;

}

vector<int> GetNumbersFromFile(string filePath)
{
    // Create a text string, which is used to output the text file
    string myText;

    // Read from the text file
    ifstream MyReadFile(filePath);

    getline(MyReadFile, myText);

    int numberOfItems = stoi(myText);

    getline(MyReadFile, myText);

    // Close the file
    MyReadFile.close();

    return StringToVector(myText);

}

void WriteMapToFile(string filePath)
{
    // Create and open a text file
    ofstream MyFile(filePath);

    // Write to the file
    if (MyFile.good())
    {
        MyFile.clear();
    }

    map<int, string>::iterator it;
    for (it = vec.begin(); it != vec.end(); it++)
    {
        MyFile << it->second << endl;
    }

    // Close the file
    MyFile.close();
}

int main() {
    Node* root = NULL;

    vector<int> numbers = GetNumbersFromFile("myFile.txt");
    int n;
    for (size_t i = 0; i < numbers.size(); i++)
    {
        n = numbers.at(i);
        root = insertNode(root, n);
    }

    printTree(root, 0);

    cout << vec.size();

    WriteMapToFile("Outfile.txt");
}