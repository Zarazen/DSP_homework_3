#ifndef _polish_notation_tree_
#define _polish_notation_tree_

class PNTree {

public:

	PNTree();
	~PNTree();
	PNTree(const PNTree& input);

	void pushTree(std::vector<char>& pn);
	void reversePN(std::vector<char>& output);
	void intoNormalExpression(std::vector<char>& output);
	int PNValue();

private:

	struct TNode {

		std::vector<char> data;
		TNode* left, * right;

	};

	struct variableNamesAndValues {

		std::vector<std::vector<char>> names;
		std::vector<int> values;

	};

	PNTree& operator=(const PNTree& input) = delete;

	void destroyTree(TNode* current);
	void pushElem(std::vector<char>& pn, int& lastRead, TNode*& current);
	void turnIntoRPN(std::vector<char>& output, TNode* current);
	void turnIntoNormalExpression(std::vector<char>& output, TNode* current);
	int calculateValue(TNode* current, variableNamesAndValues& variableData);
	int turnIntoNumber(std::vector<char>& input);
	bool isAlreadyInData(std::vector<char>& input, variableNamesAndValues& variableData);
	int getVariableValue(std::vector<char>& name, variableNamesAndValues& variableData);
	void createNode(TNode*& current, const TNode* input);

	TNode* root;

};

#endif // !_polish_notation_tree_

