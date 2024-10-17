#ifndef REGULARFILE_H
#define REGULARFILE_H

#include <vector>
#include <iostream>
#include <ctime>
#include "file.h"

using namespace std;

class RegularFile : public File
{
    public: 
        RegularFile(const string& FileName);
        RegularFile(const string& FileName,vector<char> newData);
        RegularFile(const RegularFile& other);

        virtual string getName() const {return name;}
        virtual void setName(const string& newName) { name = newName;}
        virtual void cat(const string& fileName) const;
        virtual void cp(const RegularFile& source);
        virtual void ls() const;
        virtual void save(ofstream& of) const;
        virtual void load(ifstream& in);

        virtual ~RegularFile();

    private:
        string name;
        vector<char> data;
        time_t creationTime;
        char* dt;
};








#endif