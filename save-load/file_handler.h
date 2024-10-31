#ifndef FILE_HANDLER_H_
#define FILE_HANDLER_H_

#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

class FileHandler {
private:
    string filename;
    ifstream infile;
    ofstream outfile;

public:
    FileHandler(const string& fname) : filename(fname) {}

    void openForRead();

    void openForWrite();

    void write(const json& j);

    void read(json& j);

    void closeRead();

    void closeWrite();

    ~FileHandler() {
        closeRead();
        closeWrite();
    }
};

#endif