#include "ASTVisitor.h"
#include "../../lexer/Tokens.h"
#include <iostream>

namespace umbra {

PrintVisitor::PrintVisitor() : indentLevel(0) {}

PrintVisitor::~PrintVisitor() = default;

void PrintVisitor::visit(VariableDeclNode &node) {
    printIndent();
    std::cout << "VariableDeclaration:" << std::endl;
    increaseIndent();

    printIndent();
    std::cout << "Type: " << TokenManager::tokenTypeToString(node.getType()) << std::endl;

    printIndent();
    std::cout << "Name: " << node.getName() << std::endl;

    if (node.getInitializer()) {
        printIndent();
        std::cout << "Initializer: " << std::endl;
        increaseIndent();
        // to implement
        printIndent();
        std::cout << "[Expression]" << std::endl;
        decreaseIndent();
    }

    decreaseIndent();
}

void PrintVisitor::visit(ProgramNode &node) {
    printIndent();
    std::cout << "ProgramNode:" << std::endl;
    increaseIndent();

    for (const auto &statement : node.getStatements()) {
        if (statement) {
            statement->accept(*this); // Invoca el visitor sobre cada statement del programa
        }
    }

    decreaseIndent();
}

void PrintVisitor::printIndent() {
    for (int i = 0; i < indentLevel; ++i) {
        std::cout << "  ";
    }
}

void PrintVisitor::increaseIndent() { ++indentLevel; }

void PrintVisitor::decreaseIndent() { --indentLevel; }

} // namespace umbra