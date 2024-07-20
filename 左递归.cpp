#include <iostream>
#include <vector>
#include <string>

void eliminateLeftRecursion(std::vector<std::string>& grammar) {
    // 从每个产生式中找出左递归并消除
    for (size_t i = 0; i < grammar.size(); ++i) {
        std::string production = grammar[i];
        size_t pos = production.find("->");
        char nonTerminal = production[0];

        // 检查产生式右侧是否存在左递归
        if (production[pos + 2] == nonTerminal) {
            // 消除左递归
            std::string newNonTerminal = "@";
            std::string newProduction = production.substr(pos + 3) + newNonTerminal;
            grammar.push_back(newNonTerminal + " -> " + newProduction.substr(1));

            // 修改原产生式
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