#include "MemoryCore.h"

#include <fstream>
#include "fmt/core.h"
#include "nlohmann/json.hpp"

namespace mcore
{
	MemoryCore::MemoryCore(std::string saveFilePath)
		: m_Maindict(ssdict()), m_JsonPath(fsys::absolute(saveFilePath).string())
	{
	}

	MemoryCore::MemoryCore()
		: MemoryCore(DefaultSavePath)
	{
	}

	MemoryCore::~MemoryCore()
	{
	}

	bool MemoryCore::InsertItem(const std::string key, const std::string value)
	{
		if (DoesKeyExist(key))
			return false;
		else
		{
			m_Maindict[key] = value;
			return true;
		}
	}

	std::string MemoryCore::GetItem(const std::string key)
	{
		return DoesKeyExist(key) ? m_Maindict[key] : MCORE_NOTFOUND;
	}

	void MemoryCore::LoadMemory()
	{
		std::ifstream reader(m_JsonPath);

		if (reader.is_open())
		{
			nlohmann::json jsn;
			reader >> jsn;
			reader.close();
			m_Maindict = jsn.get<ssdict>();
		}
		else
		{
			fmt::print("-- [Warning]: Failed to read from save file\n");
		}
	}

	void MemoryCore::SaveMemory() const
	{
		std::ofstream writer(m_JsonPath);

		if (writer.is_open())
		{
			nlohmann::json jsn(m_Maindict);
			writer << jsn.dump(4) << "\n";
			writer.close();
		}
		else
		{
			fmt::print("-- [Warning]: Failed to write to file [{}]\n", m_JsonPath);
		}
	}
} // namespace mcore