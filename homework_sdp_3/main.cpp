#include <iostream>
#include <vector>
#include <fstream>
#include "polish_notation_tree.h"

void readFile(std::vector<PNTree>& trees, const char* path);

void printTreeResults(std::vector<PNTree>& trees);

int main() {

	/*
	PNTree a;
	std::vector<char> b;
	b.push_back('*');
	b.push_back(' ');
	b.push_back('-');
	b.push_back(' ');
	b.push_back('5');
	b.push_back('1');
	b.push_back(' ');
	b.push_back('2');
	b.push_back('4');
	b.push_back(' ');
	b.push_back('a');
	b.push_back('b');
	b.push_back('C');
	a.pushTree(b);
	std::vector<char> c;
	a.reversePN(c);
	c.push_back('\0');
	std::cout << c.data() << std::endl;
	c.clear();
	a.intoNormalExpression(c);
	c.push_back('\0');
	std::cout << c.data();
	std::cout << std::endl << a.PNValue() << std::endl;
	*/

	std::vector<PNTree> trees;
	char path[128];
	std::cout << "Enter path\n";
	std::cin.getline(path, 128);
	readFile(trees, path);
	printTreeResults(trees);

	return 0;

}

void readFile(std::vector<PNTree>& trees, const char* path) {

	std::ifstream reader;
	reader.open(path, std::ios::binary);
	if (!reader.is_open()) {

		std::cout << "Couldn't open file\n";
		return;

	}

	std::vector<char> buffer;
	char temp;
	int size = sizeof(temp);

	while (true) {

		reader.read((char*)&temp, size);
		if (!reader)
			break;

		if (temp == '\r' || temp == '\n') {

			if (temp == '\r')
				reader.read((char*)&temp, size);

			PNTree dummy;
			trees.push_back(dummy);
			trees[trees.size() - 1].pushTree(buffer);
			buffer.clear();
			continue;

		}

		buffer.push_back(temp);

	}

	reader.close();

}

void printTreeResults(std::vector<PNTree>& trees) {

	int size = trees.size();
	std::vector<char> buffer;
	for (int i = 0; i < size; ++i) {

		std::cout << std::endl;
		std::cout << "Reverse polish notation:\n";
		trees[i].reversePN(buffer);
		buffer.push_back('\0');
		std::cout << buffer.data() << std::endl;
		buffer.clear();

		std::cout << "Normal notation:\n";
		trees[i].intoNormalExpression(buffer);
		buffer.push_back('\0');
		std::cout << buffer.data() << std::endl;
		buffer.clear();

		std::cout << "Value:\n";
		std::cout << trees[i].PNValue() << std::endl;

	}

}
