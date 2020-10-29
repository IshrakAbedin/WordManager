#include "StateMachine.h"

#include "fmt/core.h"

StateMachine::StateMachine(const std::string savePath)
	: m_Core(mcore::MemoryCore(savePath)), m_State(StateMachine::States::LOOKUP)
{
	//Load();
}

StateMachine::StateMachine()
	: m_Core(mcore::MemoryCore()), m_State(StateMachine::States::LOOKUP)
{
	//Load();
}

StateMachine::~StateMachine()
{
}

std::string StateMachine::ProcessWord(const std::string word)
{
	switch (m_State)
	{
	case States::LOOKUP:
		return fmt::format("-- {0} : {1}", word, RetrieveWord(word));
	case States::UNKNOWN:
		fmt::print("[Warning]: Should not be called in UNKNOWN STATE, reverting back to LOOKUP");
		m_State = States::LOOKUP;
		return MCORE_NOTFOUND;
	case States::VERB:
	case States::ADJ:
	case States::ADV:
	case States::NOUN:
	case States::PREP:
	case States::PRON:
	case States::CONJ:
		if(AddWord(word))
			return fmt::format("-- Added \"{0}\" as \"{1}\"", word, StateNames[static_cast<int>(m_State)]);
		else
			return fmt::format("-- [Warning]: Failed to insert, key[{0}] already exists", word);
	default:
		return MCORE_NOTFOUND;
	}
}

bool StateMachine::AddWord(const std::string word)
{
	if (!m_Core.InsertItem(word, StateNames[static_cast<int>(m_State)]))
	{
		return false;
	}
	return true;
}

std::string StateMachine::RetrieveWord(const std::string word)
{
	return m_Core.GetItem(word);
}
