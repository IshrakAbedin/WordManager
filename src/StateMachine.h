#pragma once

#include <array>
#include "MemoryCore.h"

class StateMachine
{
public:
	enum class States
	{
		LOOKUP = 0,
		UNKNOWN,
		VERB,
		ADJ,
		ADV,
		NOUN,
		PREP,
		PRON,
		CONJ,
		_COUNT // Use auto assignment for enum beginning with 0(zero), otherwise count will not work
	};
	const std::array<std::string, static_cast<int>(States::_COUNT) + 1> StateNames =
		{
			"look up",
			"unknown",
			"verb",
			"adjective",
			"adverb",
			"noun",
			"preposition",
			"pronoun",
			"conjunction",
			"_MANAGEMENT_COUNT_SHOULD_NOT_BE_USED_"};

private:
	mcore::MemoryCore m_Core;
	States m_State;

public:
	StateMachine(const std::string savePath);
	StateMachine();
	~StateMachine();

	inline std::string GetSavePath() const { return m_Core.GetSavePath(); }
	inline void SetSavePath(const std::string savePath) { return m_Core.SetSavePath(savePath); }

	inline void SetState(States state) { m_State = state; }
	inline States GetState() const { return m_State; }

	std::string ProcessWord(const std::string word);
	bool AddWord(const std::string word);
	std::string RetrieveWord(const std::string word);
	inline void Save() const { m_Core.SaveMemory(); }
	inline void Load() { m_Core.LoadMemory(); }
};
