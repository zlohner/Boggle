#pragma once

#include <string>
#include <vector>

#include "Resources.h"

class Node {
private:
    string value;
    bool visited;
public:
    Node(string value) : value(value) { visited = false; }
    ~Node() {}
    string getValue() { return value; }
    bool isVisited() { return visited; }
    void visit() { visited = true; }
    void unvisit() { visited = false; }
};

class Board : public vector<vector<Node>> {
public:
    Board() {}
    virtual ~Board() {}
    
    void readDictionary(char* filename);
    
    bool checkPrefix(string prefix);
    bool inBounds(int x, int y);
    
    void findWords();
    void recursiveFindWords(string previous, int x, int y);
    
    set<string>* getWords() { return &words; }
    
private:
    set<string> dictionary;
    set<string> words;
};