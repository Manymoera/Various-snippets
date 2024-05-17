#pragma once
#include <string>
#include <unordered_map>
#include <utility>
#include <iostream>

struct LZ77Token {
	int offset;
	int length;
	char nextChar;
};

void lz77(std::string& lines) {
	/*
	std::unordered_map<char, std::pair<int, int>> enc;
	std::pair <int, int> p2;
	p2 = std::make_pair(10, 11);
	enc[lines[1]] = std::make_pair(11, 23);
	enc[lines[4]] = p2;
	for (auto i = enc.begin(); i != enc.end(); i++) {
		std::cout << i->first << ": " << (i -> second).first << " " << (i->second).second << endl;
	}

	//right side of search window
	std::string advance = lines;
	//left side of search window
	std::string search;
	//encryption table
	std::unordered_map<char, std::vector<std::pair<int, int>>> enc_lz;

	std::cout << advance;
	*/
	/*for (int i = 0; i < 4; i++)
		advance = advance + lines[i];

	std::cout << advance.size() << endl;;

	for (int i = 0; i < advance.length(); i++)
		std::cout << advance[i];*/
	/*std::cout << endl;

	for (int i = 0; i < 4; i++)
		advance.erase(0, 1);

	std::cout << advance.size() << endl;*/
}

class LZ77 {
public:
    LZ77(int windowSize, int lookaheadBufferSize)
        : windowSize(windowSize), lookaheadBufferSize(lookaheadBufferSize) {}

    std::vector<LZ77Token> compress(const std::string& input) {
        std::vector<LZ77Token> compressedData;
        int inputSize = input.size();
        int pos = 0;

        while (pos < inputSize) {
            int matchOffset = 0, matchLength = 0;
            findLongestMatch(input, pos, matchOffset, matchLength);

            char nextChar = pos + matchLength < inputSize ? input[pos + matchLength] : '\0';
            compressedData.push_back({ matchOffset, matchLength, nextChar });

            pos += matchLength + 1;
        }

        return compressedData;
    }

    std::string decompress(const std::vector<LZ77Token>& compressedData) {
        std::string decompressedData;
        for (const auto& token : compressedData) {
            if (token.length > 0) {
                int start = decompressedData.size() - token.offset;
                for (int i = 0; i < token.length; ++i) {
                    decompressedData += decompressedData[start + i];
                }
            }
            if (token.nextChar != '\0') {
                decompressedData += token.nextChar;
            }
        }
        return decompressedData;
    }

    void findLongestMatch(const std::string& input, int pos, int& matchOffset, int& matchLength) {
        matchOffset = 0;
        matchLength = 0;

        int start = std::max(0, pos - windowSize);
        int end = std::min(pos + lookaheadBufferSize, static_cast<int>(input.size()));

        for (int i = start; i < pos; ++i) {
            int length = 0;
            while (length < lookaheadBufferSize && pos + length < end && input[i + length] == input[pos + length]) {
                ++length;
            }
            if (length > matchLength) {
                matchLength = length;
                matchOffset = pos - i;
            }
        }
    }

private:
    int windowSize;
    int lookaheadBufferSize;
};