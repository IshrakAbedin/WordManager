/* Mohammad Ishrak Abedin, ID# 160041051, Compiler Design Lab, CSE 4802 */
%{
#include "fmt/core.h"
#include "StateMachine.h"

#define AUTO_LOAD_DATA 1

#ifdef _MSC_VER
	#define YY_NO_UNISTD_H
	#include <io.h>
#endif

void printHelp();
void printAbout();

constexpr char* CommandStr = ">> ";
StateMachine* smachine;
%}

%%
\n { fmt::print("{0}", CommandStr); smachine->SetState(StateMachine::States::LOOKUP); }
^verb { smachine->SetState(StateMachine::States::VERB); }
^adj { smachine->SetState(StateMachine::States::ADJ); }
^adv { smachine->SetState(StateMachine::States::ADV); }
^noun { smachine->SetState(StateMachine::States::NOUN); }
^prep { smachine->SetState(StateMachine::States::PREP); }
^pron { smachine->SetState(StateMachine::States::PRON); }
^conj { smachine->SetState(StateMachine::States::CONJ); }
^_save { fmt::print("-- Saving to {0}\n", smachine->GetSavePath()); smachine->Save(); }
^_load { fmt::print("-- Loading from {0}\n", smachine->GetSavePath()); smachine->Load(); }
^_exit { return 0; }
^_quit { return 0; }
^_help { printHelp(); }
^_about { printAbout(); }
^_path { fmt::print("-- Working with save file {0}\n", smachine->GetSavePath()); }
[a-zA-Z]+ {
		fmt::print("{0}\n", smachine->ProcessWord(yytext));
}
. ;
%%

int yywrap(void)
{
	return 1;
}

int main(int argc, char** argv)
{
	if(argc == 1)
	{
		smachine = new StateMachine();
	}
	else if(argc == 2)
	{
		smachine = new StateMachine(argv[1]);
	}
	else
	{
		fmt::print("[ERROR]: Unknown Number of Arguments\n");
		exit(1);
	}
	
	fmt::print("-- Working with save file {0}\n", smachine->GetSavePath());
#if AUTO_LOAD_DATA = 1
	smachine->Load();
	fmt::print("-- Data Loaded\n");
#endif
	fmt::print("-- Use command <_exit> or <_quit> to quit\n");
	fmt::print("-- Use command <_help> to view commands\n");
	fmt::print("-- Use command <_about> to view developer info\n");
	fmt::print("-- Use command <_load> to load data from file\n");
	fmt::print("-- Use command <_save> to write data to file\n\n");
	smachine->SetState(StateMachine::States::LOOKUP);
	fmt::print("{0}", CommandStr);
	yylex();
	delete smachine;
	return 0;
}

void printHelp()
{
	fmt::print("=== HELP ===\n");
	fmt::print("--[H] It is HIGHLY RECOMMENDED to always use lowercase\n");
	fmt::print("--[H] Use command <_exit> or <quit> to quit\n");
	fmt::print("--[H] Use command <_help> to view commands\n");
	fmt::print("--[H] Use command <_about> to view developer info\n");
	fmt::print("--[H] Use command <_path> to view save file path\n");
	fmt::print("--[H] Use command <_load> to load data from file\n");
	fmt::print("--[H] Use command <_save> to write data to file\n");
	fmt::print("--[H] Use command <verb> followed by SPACE separated words to save verbs\n");
	fmt::print("--[H] Use command <adj> followed by SPACE separated words to save adjectives\n");
	fmt::print("--[H] Use command <adv> followed by SPACE separated words to save adverbs\n");
	fmt::print("--[H] Use command <noun> followed by SPACE separated words to save nouns\n");
	fmt::print("--[H] Use command <prep> followed by SPACE separated words to save prepositions\n");
	fmt::print("--[H] Use command <pron> followed by SPACE separated words to save pronouns\n");
	fmt::print("--[H] Use command <conj> followed by SPACE separated words to save conjunctions\n");
	fmt::print("--[H] Just write SPACE separated words to search them\n");
	fmt::print("--[H] Save file path can be set by passing single command line argument\n");
	fmt::print("--[H] If no save file has is provided, default path is used\n\n");
}

void printAbout()
{
	fmt::print("=== ABOUT ===\n");
	fmt::print("--[A] Built by Mohammad Ishrak Abedin | ID# 160041051\n\n");
}