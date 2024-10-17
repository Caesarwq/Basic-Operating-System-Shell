#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "file.h"
#include <vector>
#include <string>
#include <ctime>

using namespace std;

class Directory : public File
{
    public:
        Directory(const string& dirName,Directory* parentptr = nullptr) :data({}),name(dirName), creationTime(time(0)), dt(ctime(&creationTime)),parent(parentptr) {}

        virtual string getName() const {return name;}
        virtual void setName(const string& Name) { name=Name;}
        Directory* getParent() const {return parent;}
        void setParent(Directory* newParent) { parent = newParent;}

        virtual void ls() const;
        //PRINTS THE FILES AND DIRECTORIES IN THE CURRENT DIRECTORY
        virtual void rm(const string& fileName);
        //DELETES THE FILE IN THE CURRENT DIRECTORY. IF THERE IS NOT PRINTS AN ERROR
        virtual void cp(const string& source,const string& destination);
        //TAKES SOURCE FİLE AND DESTINATION FILE NAME AS PARAMETERS
        //İF THERE IS A DESTINATION FILE NAME IN THE VIRTUAL OS WITH THE SAME NAME AS THE PARAMETER
        //IT DIRCARDS ELEMENTS OF THE ALREADY CREATED FILE AND COPIES THE SOURCE TO THE DESTINATION
        //IF NOT CREATED IT CREATES AND SETS ITS NAME AS DESTINATION PARAMETER AND COPIES THE SOURCE TO IT
        virtual void cat(const string& fileName) const;
        //PRINTS THE ELEMENTS IN THE FILE
        void addFile(File* file) {data.push_back(file);}
        //ADDS ELEMENTS TO THE CURRENT DIRECTORY WHETHER IT IS DIR OR FILE
        virtual void rmdir(const string& dirName);
        //DELETES THE DIRECTORY IN THE CURRENT DIRECTORY. IF THERE IS NOT PRINTS AN ERROR
        virtual File* cd(const string& dirName);
        //GOES INTO THE SELECTED DIRECTORY IF THERE IS NOT ANY DIRECTORY AS PARAMETER IN THE CURRENT DIRECTORY IT RETURNS CURRENT DIRECTORY AND GİVES ERROR MESSAGE
        //IF THE PARAMETER IS . IT SIMPLY RETURNS CURRENT DIRECTORY
        //IF THE PARAMETER IS .. IT RETURNS THE PREVIOUS DIRECTORY 
        File* is_in(const string& name) const;
        //CHECKS WHETHER THERE IS ANYTHING NAMED WITH THE PARAMETER NAME, IF THERE IS THEN RETURNS THE POINTER TO THAT OBJECT
        //IF NOT IT SIMPLY RETURNS NULLPTR
        virtual void save(ofstream& of) const;
        //SAVES THE CONTENT OF THE SHELL TO THE SHELL.TXT TO USE OTHER RUN
        virtual void load(ifstream& in);
        //LOAD THE CONTENT IN THE SHELL.TXT

        virtual ~Directory();

    private:
        string name;
        vector<File*> data;
        time_t creationTime;
        char* dt;
        Directory* parent;
};

#endif