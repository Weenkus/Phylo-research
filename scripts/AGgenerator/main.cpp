#include <iostream>
#include <fstream>

const int MB{1000000};

using namespace std;

int main() {
    // Initialise rand and output stream
    srand((unsigned)time(NULL));

    string genomeName{"ArtificialGenome7.fasta"};
    ofstream output(genomeName);

    // Set the params and create the genome
    int size{1000*MB};
    char nucleotides[4] {'A', 'C', 'G','T'};
    output << ">gi|" << size << "|blank|blank| Artificial genome";
    for(int i{0}; i < size; ++i) {
        if(i%80 == 0)
            output << "\n";
        output << nucleotides[rand() % 4];
    }

    // Clean up
    output.close();
    return 0;
}