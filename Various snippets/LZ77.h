#pragma once
#include <string>
#include <unordered_map>
#include <utility>
#include <iostream>

void lz77(std::string lines) {
	std::unordered_map<std::string, std::pair<int, int>> enc;
	std::pair <int, int> p2;
	p2 = std::make_pair(10, 11);
	enc["a"] = std::make_pair(11, 23);
	enc["b"] = p2;
	for (auto i = enc.begin(); i != enc.end(); i++) {
		std::cout << i->first << ": " << (i -> second).first << " " << (i->second).second << endl;
	}
}