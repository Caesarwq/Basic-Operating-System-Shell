#include "regularFile.h"
#include "directory.h"
#include <fstream>
#include <memory>
#include <limits>

#include <iostream>
using std::string;
using std::cin;
using std::cout;


int main()
{
    string command;
    Directory *rootptr = new Directory(".");
    ifstream in("shell.txt");
    if(in.is_open())
    {
        in.ignore(); in.ignore();
        rootptr->load(in);
        in.close();
    }
    Directory* cur = rootptr;
    cout << "\n                  Welcome to Shell <<<<<< type exit to terminate the program " << endl; 
    while(true)
    {
        cout << "> "; cin >> command;
        if(command == "ls")
        {
            cur->ls();
        }
        else if(command == "mkdir")
        {
            string dirName;
            cin >> dirName;
            Directory *newdir = new Directory(dirName,cur);
            cur->addFile(newdir);
        }
        else if(command == "rmdir")
        {
            string dirName;
            cin >> dirName;
            cur->rmdir(dirName);
        }
        else if(command == "rm")
        {
            string fileName;
            cin >> fileName;
            cur->rm(fileName);
        }
        else if(command == "cp" || command == "link")
        {
            string source,destination;
            cin >> source >> destination;
            cur->cp(source,destination);
        }
        else if(command == "cd")
        {
            string pathname;
            cin >> pathname;
            if(cur->cd(pathname) != nullptr)
            {
                cur = dynamic_cast<Directory*>(cur->cd(pathname));
            }
        }
        else if(command == "cat")
        {
            string fileName;
            cin >> fileName;
            cur->cat(fileName);
        }
        else if(command == "exit") break;
        else cerr << "Error : Wrong input!" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    ofstream of("shell.txt");
    rootptr->save(of);
    return 0;
}
