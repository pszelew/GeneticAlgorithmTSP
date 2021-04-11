#include "DataLoader.hh"
#include <fstream>

using std::ifstream;
using std::getline;
using std::stoi;

DataLoader::DataLoader(): loadedData(Task()){}

Task DataLoader::loadData(string filename){
    ifstream testFile;
    string line;
    testFile.open(filename);
    
    if(testFile.is_open())
    {
        while (std::getline(testFile, line))
        {
            if(line.find("NAME : ") != string::npos)
            {
                this->loadedData.setName(line.substr(7));
            }

            if(line.find("DIMENSION : ") != string::npos)
            {
                this->loadedData.setTaskSize(stoi(line.substr(12)));
            }

            if(line.find("NODE_COORD_SECTION") != string::npos)
            {
                for(int i=0; i<this->loadedData.getTaskSize(); i++)
                {
                    getline(testFile, line);
                    int idx = line.find(" ");
                    line = line.substr(idx+1);
                    idx = line.find(" ");

                    int first = stoi(line.substr(0, idx));

                    int second = stoi(line.substr(idx+1));

                    this->loadedData.getCoordsMod().push_back(pair<int, int>(first, second));       
                }
            }
        }
    }
    
    return this->loadedData;
}
