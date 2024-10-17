#ifndef FILE_H
#define FILE_H

#include <string>
#include <fstream>

using namespace std;

class File 
{
    public:
        File() = default;
        virtual void ls() const = 0;
        virtual void cat(const string& fileName) const  = 0;
        virtual string getName() const = 0;
        virtual void setName(const string& newName) = 0;
        virtual void save(ofstream& of) const = 0;
        virtual void load(ifstream& in) = 0;
        virtual ~File() = default;
};




#endif
