#include "InputProcessor.h"     // our custom InputProcessor class
#include "OutputProcessor.h"    // our custom OutputProcessor class

#include <iostream>             // for cout, endl
#include <string>               // for string
#include <vector>               // for vector
using namespace std;            // so we don't have to type std:: every time

int main() {
    // create an input processor object
    InputProcessor iProcessor;

    // open a stream to input from
    if( !iProcessor.openStream() ) {
        // if stream failed to open, quit the program
        cerr << "Shutting down..." << endl;
        return -1;
    }
    // read the data on the stream
    iProcessor.read();
    // close the input stream
    iProcessor.closeStream();

    // retrieve all the words read from the stream
    std::vector< std::string > inputWords = iProcessor.getAllWords();

    // create an output processor object
    OutputProcessor oProcessor;
    // analyze the words and ignore the specified punctuation
    oProcessor.analyzeWords( inputWords, "?!.,;:\"()_-'&[]" );
    // open a stream to output to
    if( !oProcessor.openStream() ) {
        // if stream failed to open, quit the program
        cerr << "Shutting down..." << endl;
        return -2;
    }
    // write the data to the stream
    oProcessor.write();
    // close the output stream
    oProcessor.closeStream();

    // signal to user program has completed
    cout << "Analysis complete, check file for results" << endl;

    // end our program!
    return 0;
}