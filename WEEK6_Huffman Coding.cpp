#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <map>
#include <memory>
using namespace std;

// A class representing a node in the Huffman tree
class HuffmanNode {
public:
    char data; // character stored in the node
    int freq;  // frequency of the character
    shared_ptr<HuffmanNode> left, right;

    HuffmanNode(char data, int freq) {
        this->data = data;
        this->freq = freq;
        left = right = nullptr;
    }
};

// Comparator function for the priority queue
class Compare {
public:
    bool operator()(shared_ptr<HuffmanNode>& left, shared_ptr<HuffmanNode>& right) {
        return left->freq > right->freq; // Min-heap based on frequency
    }
};

// Function to generate Huffman codes and store them in a map
void generateHuffmanCodes(shared_ptr<HuffmanNode> root, string code, map<char, string>& huffmanCodes) {
    if (!root) return;
    
    // If it's a leaf node, save the code
    if (!root->left && !root->right) {
        huffmanCodes[root->data] = code;
    }

    // Recur for left and right subtrees
    generateHuffmanCodes(root->left, code + "0", huffmanCodes);
    generateHuffmanCodes(root->right, code + "1", huffmanCodes);
}

// Function to build the Huffman Tree and return its root
shared_ptr<HuffmanNode> buildHuffmanTree(const string& S, const vector<int>& f) {
    priority_queue<shared_ptr<HuffmanNode>, vector<shared_ptr<HuffmanNode>>, Compare> minHeap;

    // Step 1: Create a leaf node for each character and add it to the min heap
    for (int i = 0; i < S.size(); ++i) {
        minHeap.push(make_shared<HuffmanNode>(S[i], f[i]));
    }

    // Step 2: Build the Huffman Tree
    while (minHeap.size() > 1) {
        // Extract two nodes with the smallest frequency
        shared_ptr<HuffmanNode> left = minHeap.top();
        minHeap.pop();
        shared_ptr<HuffmanNode> right = minHeap.top();
        minHeap.pop();

        // Create a new internal node with these two nodes as children
        shared_ptr<HuffmanNode> newNode = make_shared<HuffmanNode>('\0', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;

        // Add the new internal node to the min heap
        minHeap.push(newNode);
    }

    // The remaining node is the root of the Huffman tree
    return minHeap.top();
}

// Function to print the Huffman codes in preorder traversal
void printPreorderHuffmanCodes(shared_ptr<HuffmanNode> root, string code) {
    if (!root) return;

    // If it's a leaf node, print its character and code
    if (!root->left && !root->right) {
        cout << code << " ";
    }

    // Recur for left and right subtrees
    printPreorderHuffmanCodes(root->left, code + "0");
    printPreorderHuffmanCodes(root->right, code + "1");
}

int main() {
    string S;
    vector<int> f;

    int N;

    // Input: Number of characters
    cout << "Enter the number of distinct characters: ";
    cin >> N;

    // Input: Characters
    cout << "Enter the characters (without spaces): ";
    cin >> S;

    // Input: Frequencies
    cout << "Enter the corresponding frequencies: ";
    f.resize(N);
    for (int i = 0; i < N; ++i) {
        cin >> f[i];
    }

    // Step 1: Build the Huffman Tree
    shared_ptr<HuffmanNode> root = buildHuffmanTree(S, f);

    // Step 2: Print the Huffman codes in preorder traversal
    cout << "Huffman Codes in Preorder Traversal: ";
    printPreorderHuffmanCodes(root, "");
    cout << endl;

    return 0;
}