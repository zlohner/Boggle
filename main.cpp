#include <iostream>

#include <math.h>
#include <string>
#include <vector>

#include "Resources.h"
#include "Board.h"

using namespace std;

bool checkArgs(int argc, char* argv[]) {
    if (argc != 4) return false;
    else return true;
}

Board readBoard(char* filename) {
    Board b;
    
    ifstream inFile(filename);
    if (!inFile.is_open()) throw INVALID_FILE;
    
    vector<string> cubes;
    string cube;
    while (inFile >> cube) {
        clean(cube);
        cubes.push_back(cube);
    }
    
    double dimensionD = sqrt(cubes.size());
    int dimension = (int)dimensionD;
    if (dimensionD != dimension) throw INVALID_BOARD;
    
    for (unsigned int i = 0; i < dimension; i++) {
        vector<Node> row;
        for (unsigned int j = 0; j < dimension; j++) {
            row.push_back(Node(cubes[(dimension * i) + j]));
        }
        b.push_back(row);
    }
    
    return b;
}

void writeFile(char* filename, Board b) {
    ofstream outFile(filename);
    if (!outFile.is_open()) throw INVALID_FILE;
    for (unsigned int i = 0; i < b.size(); i++) {
        for (unsigned int j = 0; j < b[i].size(); j++) {
            outFile << b[i][j].getValue();
            if (j < b[i].size() - 1) outFile << " ";
        }
        outFile << endl;
    }
    outFile << endl;
    set<string>* words = b.getWords();
    for (set<string>::const_iterator it = words->begin(); it != words->end(); it++) {
        outFile << (*it) << endl;
    }
}

int main(int argc, char* argv[]) {
    
    try {
        if (!checkArgs(argc, argv)) throw BAD_ARGS;
        Board b = readBoard(argv[2]);
        b.readDictionary(argv[1]);
        b.findWords();
        writeFile(argv[3], b);
    }
    catch (Error e) {
        if (e == BAD_ARGS) {
            cout << "ERROR - USAGE: Boggle [dictionary_file] [board_file] [output_file] (" << argc << ")" << endl;
        }
        else if (e == INVALID_FILE) {
            cout << "ERROR: could not open file" << endl;
        }
        else if (e == INVALID_BOARD) {
            cout << "ERROR: invalid board" << endl;
        }
    }
    
    return 0;
}