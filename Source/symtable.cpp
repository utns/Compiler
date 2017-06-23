#include <sstream>
#include <iostream>
#include "symbols.h"
#include "errors.h"

//#define NO_SYMBOL_CHECK

void SymTable::addSymbol(SymbolPtr symbol) {
    if (!symbol->isType()) {
        symbol->setOffset(size);
        size += symbol->getSize();
    }
    symbols.push_back(symbol);
    symbolsName[symbol->getName()] = symbols.size() - 1;
}

bool SymTable::haveSymbol(std::string name) {
    return symbolsName.find(name) != symbolsName.end();
}

std::string SymTable::getString(int depth) {
    std::stringstream sstream;
    for (auto symbol: symbols) {
        sstream << symbol->getString(depth);
    }
    return sstream.str();
}

SymbolPtr SymTable::getSymbol(TokenPtr token) {
//    std::cout << "name: " << token->getText() << std::endl;
    std::string name = token->getText();
    if (haveSymbol(name)) {
        return symbols[symbolsName[name]];
    } else {
        #ifndef NO_SYMBOL_CHECK
            throw WrongSymbol(token->getLine(), token->getPos(), name);
        #else
            return SymbolPtr(new SymTypeInteger());
        #endif
        
    }
}

SymbolPtr SymTable::getSymbol(std::string name) {
    if (haveSymbol(name)) {
        return symbols[symbolsName[name]];
    } else {
        #ifndef NO_SYMBOL_CHECK
            throw WrongSymbol(0, 0, name);
        #else
            return SymbolPtr(new SymTypeInteger());
        #endif
    }
}


void SymTable::checkUnique(TokenPtr token) {
    if (haveSymbol(token->getText())) {
        throw Duplicate(token->getLine(), token->getPos(), token->getText());
    }
}

std::vector<SymbolPtr> SymTable::getSymbols() {
    return symbols;
}

int SymTable::getSize() {
    return size;
}

void SymStack::addTable(SymTablePtr table) {
    tables.push_back(table);
}

SymTablePtr SymStack::top() {
    return tables.back();
}

void SymStack::pop() {
    tables.pop_back();
}

SymTablePtr SymStack::findTable(std::string symbol) {
    for (int i = tables.size() - 1; i >= 0; --i) {
        if (tables[i]->haveSymbol(symbol)) {
            return tables[i];
        }
    }
    return SymTablePtr();
}

bool SymStack::haveSymbol(std::string name) {
    return findTable(name) != SymTablePtr();
}

SymbolPtr SymStack::getSymbol(TokenPtr token) {
    std::string name = token->getText();
    if (haveSymbol(name)) {
        return findTable(name)->getSymbol(token);
    } else {
        #ifndef NO_SYMBOL_CHECK
            throw WrongSymbol(token->getLine(), token->getPos(), name);
        #else
            return SymbolPtr(new SymTypeInteger());
        #endif
    }
}
