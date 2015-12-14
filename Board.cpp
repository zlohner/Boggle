#include "Board.h"

void Board::readDictionary(char* filename) {
    ifstream inFile(filename);
    if(!inFile.is_open()) throw INVALID_FILE;
    
    string line;
    while(getline(inFile, line)) {
        clean(line);
        dictionary.insert(line);
    }
}

bool Board::checkPrefix(string prefix) {
    set<string>::const_iterator it = dictionary.lower_bound(prefix);
    if (it == dictionary.end()) return false;
	if (prefix.length() >= 4 && (*it) == prefix) words.insert(prefix);
    return (*it).substr(0, prefix.length()) == prefix;
}

bool Board::inBounds(int x, int y) {
    return x >= 0 && x < this->size() && y >= 0 && y < this->at(x).size();
}

void Board::findWords() {
    for (unsigned int i = 0; i < this->size(); i++) {
        for (unsigned int j = 0; j < this->at(i).size(); j++) {
            recursiveFindWords("", i, j);
        }
    }
}

void Board::recursiveFindWords(string prefix, int x, int y) {
    
    if (!inBounds(x, y))
        return;
    if (this->at(x)[y].isVisited())
        return;
    
    prefix += this->at(x)[y].getValue();
    
    if (!checkPrefix(prefix))
        return;
    
    this->at(x)[y].visit();
    for (int i = (x - 1); i <= (x + 1); i++) {
        for (int j = (y - 1); j <= (y + 1); j++) {
            recursiveFindWords(prefix, i, j);
        }
    }
    this->at(x)[y].unvisit();
}