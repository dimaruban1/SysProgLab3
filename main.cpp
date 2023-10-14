#include <iostream>
#include <fstream>
#include <string>
#include "classes/lexeme.h"
using namespace std;

int main() {
    string filename;

    while (true) {
//        cout << "Enter the filename (\'EXIT\' to actually exit): ";
//        cin >> filename;
//        if (filename == "EXIT"){
//            break;
//        }
        filename = "/home/serg/CLionProjects/SysProgLab3/code.txt";
        ifstream inputFile(filename);
        if (inputFile.is_open()) {
            string code((istreambuf_iterator<char>(inputFile)),
                        istreambuf_iterator<char>());
            Parser P(code);
            P.parseCode();
            P.printResult();
            inputFile.close();
//            cout << "File Content:\n" << code << "\n";
            break;
        } else {
            cerr << "Error opening the file. Please try again.\n";
        }
    }

    return 0;
}