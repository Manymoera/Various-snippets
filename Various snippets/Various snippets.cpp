#include <iostream>
#include "devtools.h"
#include "parprog.h"
#include "huffman.h"
#include "LZ77.h"
#include <fstream>
#include <string>

void main()
{
    std::ifstream file("D:\\University Labs\\Various snippets\\compression.txt"); 
    std::ofstream file_in("D:\\University Labs\\Various snippets\\comp_in.txt");
    std::string line;
    getline(file, line);
    //std::cout << "string: " << line << std::endl;
    file.close();
    //std::string text = "aboba ytdol yolo qwerty";
    /*std::string dec_text;
    std::string enc_txt;
    std::cout << '\n';
    buildHuffmanTree(line, dec_text, enc_txt);
    file_in << enc_txt << std::endl;
    file_in.close();*/

    std::string lines = "AABCBBABC";

    std::vector<int> offset;
    std::vector<int> str_size;
    std::vector<std::string> symb(lines.length(), lines);

    std::cout << symb.size() << endl;

    std::cout << lines << endl;

    lz77(lines);
}