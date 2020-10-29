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
		return RetrieveWord(word);
	case States::UNKNOWN:
		fmt::print("[Warning]: Should not be called in UNKNOWN STATE, reverting back to LOOKUP\n");
		m_State = States::LOOKUP;
		return MCORE_NOTFOUND;
	case States::VERB:
	case States::ADJ:
	case States::ADV:
	case States::NOUN:
	case States::PREP:
	case States::PRON:
	case States::CONJ:
		AddWord(word);
		return "Added Word";
	default:
		return MCORE_NOTFOUND;
	}
}

void StateMachine::AddWord(const std::string word)
{
	if (!m_Core.InsertItem(word, StateNames[static_cast<int>(m_State)]))
	{
		fmt::print("[Warning]: Failed to insert, key[{0}] already exists\n", word);
	}
}

std::string StateMachine::RetrieveWord(const std::string word)
{
	return m_Core.GetItem(word);
}
