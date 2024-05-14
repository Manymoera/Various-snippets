#include <iostream>
#include "devtools.h"
#include "parprog.h"
#include "huffman.h"
using namespace std;

void main()
{
    char str[] = "occurrences";
    char str_1[] = "prepinstaff";
    int freq1[256] = { 0 };

    char_freq(str_1, freq1);

    std::cout << "\n";

    for (int i = 0; i < 256; i++) {
        if (freq1[i] != 0) {
            cout << char(i) << " : " << freq1[i] << endl;
        }
    }

    std::cout << "\n";
    string text = "aboba ytdol yolo qwerty";
    string dec_text;
    std::cout << '\n';
    buildHuffmanTree(text, dec_text);
}