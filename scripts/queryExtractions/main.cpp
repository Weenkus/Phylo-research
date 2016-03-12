#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

void parseSubstring(string inputFS, string outputFS, int numOfTestSamples, int subStrLen) {
    ifstream input(inputFS);

    // Parse the FASTA file
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

    int numberOfQueriesPerFile{20};

    // Generate random substrings and print the to the output file
    for(int i{0}; i < numOfTestSamples; ++i) {
        // Create an output file
        std::string outFileName = outputFS;
        outFileName.append("_" + to_string(subStrLen) + "query" + to_string(i) + ".fasta");    // Generate a name that matches the substr length
        ofstream output(outFileName, std::ios::app);

        for(int j{0}; j < numberOfQueriesPerFile; j++) {
            // Add fasta header
            int randNum = rand() % (content.length() - subStrLen - 1) + subStrLen;
            output << ">vk|" << subStrLen << "|substring|artifical|" << outFileName << endl;
            output << content.substr(randNum, subStrLen) << endl;
        }

        output.close();
    }
}

int main() {
    // File names
    string parentDir("/home/weenkus/workspace/queries/hs-blastn-0.0.4+-src/db/");

    string inputCV(parentDir + "CV_blast/Canarypox.fasta"),
            inputEcoli(parentDir + "Ecoli_blast/eColi.fasta"),
            inputO(parentDir + "O_blast/Opitutaceae.fasta"),
            inputS(parentDir + "S_blast/Sulfolobus.fasta"),
            inputAG1(parentDir + "AG1/ArtificialGenome1.fasta"),
            inputAG2(parentDir + "AG2/ArtificialGenome2.fasta"),
            inputAG3(parentDir + "AG3/ArtificialGenome3.fasta"),
            inputAG4(parentDir + "AG4/ArtificialGenome4.fasta"),
            inputAG5(parentDir + "AG5/ArtificialGenome5.fasta"),
            inputAG6(parentDir + "AG6/ArtificialGenome6.fasta"),
            inputAG7(parentDir + "AG7/ArtificialGenome7.fasta");


    string outputCV("CV"),
            outputEcoli("EC"),
            outputO("O"),
            outputS("Sh"),
            outputAG1("AG1"),
            outputAG2("AG2"),
            outputAG3("AG3"),
            outputAG4("AG4"),
            outputAG5("AG5"),
            outputAG6("AG6"),
            outputAG7("AG7");


    /* initialize random seed: */
    srand (unsigned(time(NULL)));

    cout << "READING:" << endl;
    // Generat substrings of length 1 000
    int testSampleNum{5};
    int subStrLens[] {1000, 10000, 100000};
    for(auto len : subStrLens) {
        parseSubstring(inputCV, outputCV, testSampleNum, len);
        parseSubstring(inputEcoli, outputEcoli, testSampleNum, len);
        parseSubstring(inputO, outputO, testSampleNum, len);
        parseSubstring(inputS, outputS, testSampleNum, len);
        parseSubstring(inputAG1, outputAG1, testSampleNum, len);
        parseSubstring(inputAG2, outputAG2, testSampleNum, len);
        parseSubstring(inputAG3, outputAG3, testSampleNum, len);
        parseSubstring(inputAG4, outputAG4, testSampleNum, len);
        parseSubstring(inputAG5, outputAG5, testSampleNum, len);
        parseSubstring(inputAG6, outputAG6, testSampleNum, len);
        parseSubstring(inputAG7, outputAG7, testSampleNum, len);
    }
    return 0;
}

