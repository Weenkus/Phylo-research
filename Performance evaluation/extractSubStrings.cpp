#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

void parseSubstring(string inputFS, string outputFS, int numOfTestSamples, int subStrLen) {
    ifstream input(inputFS);

    std::string line, name, content;
    while( std::getline( input, line ).good() ){
        if( line.empty() || line[0] == '>' ){ // Identifier marker
            if( !name.empty() ){ // Print out what we read from the last entry
                std::cout << name << " : " << content.substr(0, 20) << "..." << std::endl;
                name.clear();
            }
            if( !line.empty() ){
                name = line.substr(1);
            }
            //content.clear();
        } else if( !name.empty() ){
            if( line.find(' ') != std::string::npos ){ // Invalid sequence--no spaces allowed
                name.clear();
                content.clear();
            } else {
                content += line;
            }
        }
    }
    if( !name.empty() ){ // Print out what we read from the last entry
        std::cout << name << " : " << content.substr(0, 10) << std::endl;
    }

    ofstream output(outputFS, std::ios::app);
    for(int i{0}; i < numOfTestSamples; ++i) {
        int randNum = rand() % content.length() - subStrLen - 1;
        output << content.substr(randNum, subStrLen) << endl;
    }

    output << endl << endl;
}

int main() {
    // File names
    string inputCV("/media/weenkus/The Beast/Programming/Workspace/Projects/Phylo-research/db/Canarypox.fasta"),
            inputEcoli("/media/weenkus/The Beast/Programming/Workspace/Projects/Phylo-research/db/eColi.fasta"),
            inputO("/media/weenkus/The Beast/Programming/Workspace/Projects/Phylo-research/db/Opitutaceae.fasta"),
            inputS("/media/weenkus/The Beast/Programming/Workspace/Projects/Phylo-research/db/Sulfolobus.fasta");
    string outputCV("/media/weenkus/The Beast/Programming/Workspace/Projects/Phylo-research/db/tests/CVbatch.fasta"),
            outputEcoli("/media/weenkus/The Beast/Programming/Workspace/Projects/Phylo-research/db/tests/ECbatch.fasta"),
            outputO("/media/weenkus/The Beast/Programming/Workspace/Projects/Phylo-research/db/tests/Obatch.fasta"),
            outputS("/media/weenkus/The Beast/Programming/Workspace/Projects/Phylo-research/db/tests/SIbatch.fasta");

    /* initialize random seed: */
    srand (unsigned(time(NULL)));

    cout << "READING:" << endl;
    // Generat substrings of length 10
    int subStrLen{10}, testSampleNum{10};
    parseSubstring(inputCV, outputCV, testSampleNum, subStrLen);
    parseSubstring(inputEcoli, outputEcoli, testSampleNum, subStrLen);
    parseSubstring(inputO, outputO, testSampleNum, subStrLen);
    parseSubstring(inputS, outputS, testSampleNum, subStrLen);

    // Generat substrings of length 100
    subStrLen = 100;
    parseSubstring(inputCV, outputCV, testSampleNum, subStrLen);
    parseSubstring(inputEcoli, outputEcoli, testSampleNum, subStrLen);
    parseSubstring(inputO, outputO, testSampleNum, subStrLen);
    parseSubstring(inputS, outputS, testSampleNum, subStrLen);

    // Generat substrings of length 1000
    subStrLen = 1000;
    parseSubstring(inputCV, outputCV, testSampleNum, subStrLen);
    parseSubstring(inputEcoli, outputEcoli, testSampleNum, subStrLen);
    parseSubstring(inputO, outputO, testSampleNum, subStrLen);
    parseSubstring(inputS, outputS, testSampleNum, subStrLen);

    return 0;
}

