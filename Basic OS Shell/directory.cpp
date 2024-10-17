#include "directory.h"
#include "regularFile.h"
#include <iostream>
#include <fstream>


void Directory::ls() const
{
    cout << "D "<< "." << "\t\t" << dt;
    if(parent != nullptr)  cout << "D "<< ".." << "\t\t" << dt;
    for(auto it = data.cbegin(); it != data.cend(); ++it)
    {
        if(dynamic_cast<RegularFile*>(*it)) (*it)->ls();
        if(dynamic_cast<Directory*>(*it)) cout << "D "<< (*it)->getName() << "\t\t" << dt;
    }
}

void Directory::rm(const string& fileName)
{
    int flag = 0;
    auto it = data.begin();
    while(it != data.end())
    {
        if((*it)->getName() == fileName && dynamic_cast<RegularFile*>(*it))
        {
            delete *it;
            it = data.erase(it);
            cout << fileName << " deleted!" << endl;
            flag = 1;
        }
        else ++it;
    }
    if(flag == 0) cout << fileName << " doesn't exist in " << name << endl;
}

void Directory::rmdir(const string& dirName)
{
    int flag = 0;
    auto it = data.begin();
    while(it != data.end())
    {
        if((*it)->getName() == dirName && dynamic_cast<Directory*>(*it))
        {
            delete *it;
            it = data.erase(it);
            cout << dirName << " deleted!" << endl;
            flag = 1;
        }
        else ++it;
    }
    if(flag == 0) cout << dirName << " doesn't exist in " << name << endl;
}

void Directory::cp(const string& source,const string& destination)
{
    ifstream in; char x; vector<char> temp_data;
    File* sourceptr= is_in(source); File* destptr= is_in(destination);
    RegularFile temp_source(source);
    in.open(source); int s_flag= 0;
    if(!in.fail())
    {
        s_flag = 1;
        while(!in.eof())
        {
            in >> noskipws >> x;
            temp_data.push_back(x);
        }
        temp_data.pop_back();
        in.close();
        temp_source = RegularFile(source,temp_data);
    }
    else if(sourceptr != nullptr)
    {
        RegularFile* sptr = dynamic_cast<RegularFile*>(sourceptr);
        if(sptr!= nullptr)
        {
            temp_source = *sptr;
            s_flag = 1;
        }
    }
    if(s_flag == 0)
    {
        cout << "Source file doesn't exist!" << endl;
        return;
    }

    if(destptr!= nullptr)
    {
        RegularFile* dptr = dynamic_cast<RegularFile*>(destptr);
        if(dptr != nullptr)
        {
            dptr->cp(temp_source);
            return;
        }
    }
    RegularFile* newDestPtr = new RegularFile(destination,temp_data);
    addFile(newDestPtr);
    newDestPtr->cp(temp_source);
}

void Directory::cat(const string& fileName) const
{
    int flag = 0;
    auto it = data.begin();
    while(it != data.end())
    {
        if((*it)->getName() == fileName && dynamic_cast<RegularFile*>(*it))
        {
            (*it)->cat(fileName);
            cout << endl;
            flag = 1;
        }
        ++it;
    }
    if(flag == 0) cout << fileName << " doesn't exist in " << name << endl;
}

//void Directory::link(const string& source_fileName,const string& destination_fileName)
File* Directory::cd(const string& dirName)
{
    int flag = 0;
    if(dirName == ".." && parent != nullptr)
    {
        return parent;
    }
    if(dirName == ".")
    {
        return this;
    }
    auto it = data.begin();
    while(it != data.end())
    {
        if((*it)->getName() == dirName)
        {
            Directory* dptr = dynamic_cast<Directory*>(*it);
            if(dptr != nullptr)
            {
                flag = 1;
                return *it;
            }
        }
        ++it;
    }
    if(flag == 0) cout << dirName << " doesn't exist in " << name << endl;
    return this;
}

File* Directory::is_in(const string& name) const
{
    for(auto it = data.cbegin(); it != data.cend() ; ++it)
    {
        if((*it)->getName() == name) return *it;
    }
    return nullptr;
}

void Directory::save(ofstream& of) const           
{
    of << "D " << name << " " << creationTime << " " << data.size() << "\n";
    for(const auto& fileptr : data)
    {
        fileptr->save(of);
    }
    of << "E\n";
}

void Directory::load(ifstream& in) 
{
    in >> name; in.ignore();  in >> creationTime; in.ignore(); dt = ctime(&creationTime);
    int dataSize; in >> dataSize; in.ignore(); 
    for(size_t i = 0; i< dataSize;)
    {
        string type;
        in >> type; in.ignore();
        if(type == "D")
        {
            Directory* childDir = new Directory("",this);
            childDir->load(in);
            data.push_back(childDir);
        }
        else if(type == "F")
        {
            RegularFile* regFile = new RegularFile("");
            regFile->load(in);
            data.push_back(regFile);
        }
        if(type != "E") ++i;
    }
}

Directory::~Directory()
{
    for(auto& x :data)
    {
        delete x;
    }
}