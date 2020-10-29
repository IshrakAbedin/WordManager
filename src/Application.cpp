#include <vector>
#include <iostream>
#include "fmt/core.h"
#include "MemoryCore.h"

int main()
{
    auto core = mcore::MemoryCore("data/data.json");
    std::vector<std::string> keys = {"M", "N", "O", "O"};
    //for(auto key : keys)
    //{
    //    if(!core.InsertItem(key, key + "ap"))
    //    {
    //        //std::cout << "Failed to insert item " << key << std::endl;
    //        fmt::print("Failed to insert item {0}\n", key);
    //    }
    //}
	core.LoadMemory();
    keys.push_back("D");
    for(auto key : keys)
    {
        //std::cout << "Retrieved Item for Key " << key << " : " << core.GetItem(key) << std::endl;
        fmt::print("Retrived [Key : Value] = [{0} : {1}]\n", key, core.GetItem(key));
    }
	core.SaveMemory();
	std::cin.get();
    return 0;
}