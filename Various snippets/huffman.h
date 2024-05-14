#pragma once
#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>


struct Node
{
    char ch;
    int freq;
    Node* left, * right;
};

Node* getNode(char ch, int freq, Node* left, Node* right)
{
    Node* node = new Node();

    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;

    return node;
}

struct comp
{
    bool operator()(Node* l, Node* r)
    {
        return l->freq > r->freq;
    }
};

void encode(Node* root, std::string str,
    std::unordered_map<char, std::string>& huffmanCode)
{
    if (root == nullptr)
        return;

    if (!root->left && !root->right)
    {
        huffmanCode[root->ch] = str;
    }

    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}

std::string decode(Node* root, int& index, std::string str, std::string& dec_str)
{

    if (root == nullptr)
    {
        return dec_str;
    }
    
    // found a leaf node
    if (!root->left && !root->right)
    {
        dec_str += root->ch;
        //std::cout << dec;
        return dec_str;
    }

    index++;

    if (str[index] == '0')
        decode(root->left, index, str, dec_str);
    else
        decode(root->right, index, str, dec_str);

    return dec_str;
}

void buildHuffmanTree(std::string text, std::string& dec_str)
{
    std::unordered_map<char, int> freq;
    for (char ch : text)
    {
        freq[ch]++;
    }

    std::priority_queue<Node*, std::vector<Node*>, comp> pq;

    for (auto pair : freq)
    {
        pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
    }

    while (pq.size() != 1)
    {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();

        int sum = left->freq + right->freq;
        pq.push(getNode('\0', sum, left, right));
    }

    Node* root = pq.top();

    std::unordered_map<char, std::string> huffmanCode;
    encode(root, "", huffmanCode);

    std::cout << "Huffman Codes are :\n"
        << '\n';
    for (auto pair : huffmanCode)
    {
        std::cout << pair.first << " " << pair.second << '\n';
    }

    std::cout << "\nOriginal string was :\n"
        << text << '\n';

    std::string str = "";
    for (char ch : text)
    {
        str += huffmanCode[ch];
    }

    std::cout << "\nEncoded string is :\n"
        << str << '\n';

    int index = -1;
    std::cout << "\nDecoded string is: \n";
    while (index < (int)str.size() - 1)
    {
        dec_str = decode(root, index, str, dec_str);
    }
    std::cout << dec_str << '\n';

    while (!pq.empty()) {
        Node* t = pq.top();
        pq.pop();
        delete t;
    }
}