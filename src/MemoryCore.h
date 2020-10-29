#pragma once

#include <unordered_map>
#include <string>
#include <filesystem>

#define MCORE_NOTFOUND "NOT FOUND"

// Becareful here about file system
#ifdef _MSC_VER
#if _MSC_VER > 1912
namespace fsys = std::filesystem;
#else
namespace fsys = std::experimental::filesystem;
#endif
#else
namespace fsys = std::filesystem;
#endif

namespace mcore
{
    constexpr char *DefaultSavePath = "data.json";
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

        inline std::string GetSavePath() const { return m_JsonPath; }
        inline void SetSavePath(const std::string savePath) { m_JsonPath = fsys::absolute(savePath).string(); }

        bool InsertItem(const std::string key, const std::string value);
        std::string GetItem(const std::string key);

        void LoadMemory();
        void SaveMemory() const;

        inline bool DoesKeyExist(const std::string key) const
        {
            return m_Maindict.find(key) == m_Maindict.end() ? false : true;
        }

        inline unsigned int GetItemCount() const { return m_Maindict.size(); }
        inline ssdict &GetRefToDictionary() { return m_Maindict; }
    };
} // namespace mcore