#include "InputProcessor.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

InputProcessor::InputProcessor() {
    _allWords = {};
}

bool InputProcessor::openStream() {
    string filename;
    cout << "Enter filename: ";
    cin >> filename;
    _fileIn.open(filename);

    if(_fileIn.fail()) {
        return false;
    } else {
        return true;
    }
}

void InputProcessor::read() {
    string word;
    while(_fileIn >> word) {
        _allWords.push_back(word);
    }
}

void InputProcessor::closeStream() {
    _fileIn.close();
}

vector<string> InputProcessor::getAllWords() {
    return _allWords;
}

