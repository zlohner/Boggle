#pragma once

#include <iostream>
#include <string>
#include <ctype.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <set>
#include <map>

using namespace std;

enum Error { BAD_ARGS, INVALID_FILE, INVALID_BOARD };

static void clean(string &line) {
    for (auto &c : line) { c = tolower(c); }
}