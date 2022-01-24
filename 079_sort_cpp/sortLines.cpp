#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstdlib>
using namespace std;

void sortLine(istream & is){
    string line;
    vector<string> lines;

    while (getline(is, line)) {
        lines.push_back(line);
    }
    // judge if read all content
    if (!is.eof()) {
        cerr << "Read file failed" << endl;
        exit(EXIT_FAILURE);
    }
    sort(lines.begin(), lines.end());
    for (vector<string>::const_iterator it = lines.begin(); it != lines.end(); ++it) {
        cout << *it << endl;
    }
}

int main(int argc, char ** argv) {
    if (argc < 2) {
        sortLine(cin);
        return EXIT_SUCCESS;
    }
    for (int i = 0; i < argc - 1; i++) {
        ifstream ifs;
        ifs.open(argv[i+1], ifstream::in);
        if (!ifs)  {
            cerr << "Open failed" << argv[i+1] << endl;
            exit(EXIT_FAILURE);
        }
        sortLine(ifs);
        ifs.close();
    }
    return EXIT_SUCCESS;
}
