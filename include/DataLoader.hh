#ifndef DATALOADER_HH
#define DATALOADER_HH


#include <string>
#include "Task.hh"


class DataLoader
{
    public:
        DataLoader();
        Task loadData(string filename);
        Task getLoadedData(){return loadedData;}
    private:
        Task loadedData;
};

#endif