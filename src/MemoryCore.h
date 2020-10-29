#pragma once

#include <unordered_map>
#include <string>

namespace mcore
{
    using ssdict = std::unordered_map<std::string, std::string>;

    class MemoryCore
    {
    private:
        ssdict m_Maindict;
		std::string m_JsonPath;
    
    public:
		MemoryCore(std::string saveFilePath);
        MemoryCore();
        ~MemoryCore();

        bool InsertItem(const std::string key, const std::string value);
        std::string GetItem(const std::string key);

		void LoadMemory();
		void SaveMemory() const;

        inline bool DoesKeyExist(const std::string key) const 
        {
            return m_Maindict.find(key) == m_Maindict.end() ? false : true;
        }

        inline unsigned int GetItemCount() const { return m_Maindict.size(); }
        inline ssdict& GetRefToDictionary() { return m_Maindict; }
    }; 
}