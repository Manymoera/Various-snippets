#include <iostream>
#include "devtools.h"
#include "parprog.h"
#include "huffman.h"
#include "LZ77.h"
#include <fstream>
#include <string>

void main()
{
    /*
    std::ifstream file("D:\\University Labs\\Various snippets\\compression.txt"); 
    std::ofstream file_in("D:\\University Labs\\Various snippets\\comp_in.txt");
    std::string line;
    getline(file, line);
    std::cout << "string: " << line << std::endl;
    file.close();
    */
    std::string line = "aboba ytdol yolo qwerty";
    std::string dec_text;
    std::string enc_txt;
    std::cout << '\n';
    buildHuffmanTree(line, dec_text);

    std::cout << endl;
    std::cout << endl;

    std::string input = "aboba ytdol yolo qwerty";
    LZ77 lz77(6, 4); // windowSize = 6, lookaheadBufferSize = 4
    std::cout << "Initial data: " << input << std::endl;

    std::vector<LZ77Token> compressedData = lz77.compress(input);

    std::cout << "Compressed data:" << std::endl;
    for (const auto& token : compressedData) {
        std::cout << "(" << token.offset << ", " << token.length << ", " << token.nextChar << ")" << std::endl;
    }

    std::string decompressedData = lz77.decompress(compressedData);
    std::cout << "Decompressed data: " << decompressedData << std::endl;
}