#include "regularFile.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

RegularFile::RegularFile(const string& FileName) : name(FileName), data({}), creationTime(time(0)), dt(ctime(&creationTime)) {}
RegularFile::RegularFile(const string& FileName,vector<char> newData) : name(FileName), data(newData), creationTime(time(0)), dt(ctime(&creationTime)) {}
RegularFile::RegularFile(const RegularFile& other) : name(other.name), creationTime(time(0)), data(other.data), dt(ctime(&creationTime)) {}

void RegularFile::ls() const
{
    cout << "F "<< name << "\t\t" << dt << "    "<< data.size() << "Bytes."<< endl;
}

void RegularFile::cat(const string& fileName) const
{
    cout <<"File : " << getName() << endl;
    for(char x: data)
    {
        cout << x;
    }
}

void RegularFile::cp(const RegularFile& source)
{
    data.clear();
    for(const auto& i : source.data)
    {
        data.push_back(i);
    }
    cout << source.name << " is copied to " << name << " succesfully" << endl;
}

void RegularFile::save(ofstream& of) const
{
    of << "F " << name << " " << creationTime << " " << data.size() << "\n";
    of.write(data.data(),data.size());
    of << "\n";
}

void RegularFile::load(ifstream& in)
{
    in >> name; in.ignore();
    in >> creationTime; in.ignore();    dt = ctime(&creationTime);
    int dataSize; in >> dataSize; in.ignore();
    data.resize(dataSize);
    in.read(data.data(),dataSize); in.ignore();
}

RegularFile::~RegularFile()
{}