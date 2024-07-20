#include <iostream>
#include <vector>
#include <string>

void eliminateLeftRecursion(std::vector<std::string>& grammar) {
    // ��ÿ������ʽ���ҳ���ݹ鲢����
    for (size_t i = 0; i < grammar.size(); ++i) {
        std::string production = grammar[i];
        size_t pos = production.find("->");
        char nonTerminal = production[0];

        // ������ʽ�Ҳ��Ƿ������ݹ�
        if (production[pos + 2] == nonTerminal) {
            // ������ݹ�
            std::string newNonTerminal = "@";
            std::string newProduction = production.substr(pos + 3) + newNonTerminal;
            grammar.push_back(newNonTerminal + " -> " + newProduction.substr(1));

            // �޸�ԭ����ʽ
            grammar[i] = nonTerminal + " -> " + newProduction + newNonTerminal;
        }
    }
}

int main() {
    std::vector<std::string> grammar = { "E -> E+T", "E -> T", "T -> T*F", "T -> F", "F -> (E)", "F -> id" };

    eliminateLeftRecursion(grammar);

    for (const auto& production : grammar) {
        std::cout << production << std::endl;
    }

    return 0;
}