#include <iostream>
#include <vector>
#include "polish_notation_tree.h"

PNTree::PNTree() {

	root = nullptr;

}

PNTree::~PNTree() {

	if (root)
		destroyTree(root);

}

PNTree::PNTree(const PNTree& input) {

	if (!input.root) {

		root = nullptr;
		return;

	}

	createNode(root, input.root);

}

void PNTree::pushTree(std::vector<char>& pn) {

	int lastRead = 0;
	pushElem(pn, lastRead, root);

}

void PNTree::reversePN(std::vector<char>& output) {

	turnIntoRPN(output, root);

}

void PNTree::intoNormalExpression(std::vector<char>& output) {

	turnIntoNormalExpression(output, root);

}

int PNTree::PNValue() {

	variableNamesAndValues variableData;
	return calculateValue(root, variableData);

}

void PNTree::destroyTree(TNode* current) {

	if (current->left)
		destroyTree(current->left);

	if (current->right)
		destroyTree(current->right);

	delete current;

}

void PNTree::pushElem(std::vector<char>& pn, int& lastRead, TNode*& current) {

	int size = pn.size();
	current = new TNode;
	
	if (pn[lastRead] != '*' && pn[lastRead] != '-' && pn[lastRead] != '+') {

		for (; lastRead < size; ++lastRead) {

			if (pn[lastRead] == ' ')
				break;

			current->data.push_back(pn[lastRead]);

		}

		current->left = current->right = nullptr;
		++lastRead;
		return;

	}

	current->data.push_back(pn[lastRead++]);
	++lastRead;
	pushElem(pn, lastRead, current->left);
	pushElem(pn, lastRead, current->right);

}

void PNTree::turnIntoRPN(std::vector<char>& output, TNode* current) {

	if (current->data[0] != '*' && current->data[0] != '-' && current->data[0] != '+') {

		int size = current->data.size();
		for (int i = 0; i < size; ++i)
			output.push_back(current->data[i]);
		return;

	}

	std::vector<char> leftExpression, rightExpression;
	turnIntoRPN(leftExpression, current->left);
	turnIntoRPN(rightExpression, current->right);

	int size = leftExpression.size();
	for (int i = 0; i < size; ++i)
		output.push_back(leftExpression[i]);
	output.push_back(' ');
	size = rightExpression.size();
	for (int i = 0; i < size; ++i)
		output.push_back(rightExpression[i]);
	output.push_back(' ');
	output.push_back(current->data[0]);

}

void PNTree::turnIntoNormalExpression(std::vector<char>& output, TNode* current) {

	if (current->data[0] != '*' && current->data[0] != '-' && current->data[0] != '+') {

		int size = current->data.size();
		for (int i = 0; i < size; ++i)
			output.push_back(current->data[i]);
		return;

	}

	std::vector<char> leftExpression, rightExpression;
	turnIntoNormalExpression(leftExpression, current->left);
	turnIntoNormalExpression(rightExpression, current->right);

	int size = leftExpression.size();
	output.push_back('(');
	for (int i = 0; i < size; ++i)
		output.push_back(leftExpression[i]);
	output.push_back(current->data[0]);
	size = rightExpression.size();
	for (int i = 0; i < size; ++i)
		output.push_back(rightExpression[i]);
	output.push_back(')');

}

int PNTree::calculateValue(TNode* current, variableNamesAndValues& variableData) {

	if (current->data[0] >= '0' && current->data[0] <= '9')
		return turnIntoNumber(current->data);

	if ((current->data[0] >= 'a' && current->data[0] <= 'z') || (current->data[0] >= 'A' && current->data[0] <= 'Z')) {

		if (isAlreadyInData(current->data, variableData))
			return getVariableValue(current->data, variableData);

		current->data.push_back('\0');
		std::cout << "Enter value for variable: " << current->data.data() << std::endl;
		current->data.pop_back();
		int temp;
		std::cin >> temp;
		variableData.names.push_back(std::vector<char>(current->data));
		variableData.values.push_back(temp);
		return temp;

	}

	int output, leftOutput, rightOutput;
	leftOutput = calculateValue(current->left, variableData);
	rightOutput = calculateValue(current->right, variableData);

	switch (current->data[0]) {

	case '+':
		output = leftOutput + rightOutput;
		break;
	case '-':
		output = leftOutput - rightOutput;
		break;
	case '*':
		output = leftOutput * rightOutput;
		break;
	default:
		output = 0;

	}

	return output;

}

int PNTree::turnIntoNumber(std::vector<char>& input) {

	int powerOfTen = 1, output = 0;
	for (int i = input.size() - 1; i >= 0; --i) {

		output += (input[i] - '0') * powerOfTen;
		powerOfTen *= 10;

	}

	return output;

}

bool PNTree::isAlreadyInData(std::vector<char>& input, variableNamesAndValues& variableData) {

	int size = variableData.names.size();
	for (int i = 0; i < size; ++i)
		if (!std::strcmp(input.data(), variableData.names[i].data()))
			return true;

	return false;

}

int PNTree::getVariableValue(std::vector<char>& name, variableNamesAndValues& variableData) {

	for (int i = 0;; ++i)
		if (!std::strcmp(name.data(), variableData.names[i].data()))
			return variableData.values[i];

}

void PNTree::createNode(TNode*& current, const TNode* input) {

	current = new TNode;
	current->left = current->right = nullptr;
	int size = input->data.size();
	for (int i = 0; i < size; ++i)
		current->data.push_back(input->data[i]);

	if (input->left)
		createNode(current->left, input->left);

	if (input->right)
		createNode(current->right, input->right);

}


