<!-- Mohammad Ishrak Abedin, ID# 160041051, Compiler Design Lab, CSE 4802 -->
# Word Manager
---
### A test to check the integration between Flex and C++, while practicing the development of OS agnostic C++ projects. Also the project is just a simple Dictionary keeper of parts of speech that can load/save from JSON file.
---
### The project relies on **[PREMAKE](https://premake.github.io/)** meta build system and can be compiled in Windows or Linux using preferred build system.

## *Tools Used*
---
- [Premake 5.0 Alpha](https://premake.github.io/)
- [WinFlexBison (For Windows)](https://github.com/lexxmark/winflexbison)

*Premake and WinFlex is already provided for Windows in the respective folders.*

## *Libraries Used*
---
+ [fmtlib 7.1.0](https://github.com/fmtlib/fmt)
+ [nlohmann/json](https://github.com/nlohmann/json)

## *Packages Required for Linux*
---
+ Flex
+ GCC
+ Make
+ Premake 5.0 alpha

---
**C++ 17 or Higher is Mandatory to compile since the project uses *std::filesystem*.**

---
## *Building for Windows (MSVC/ Visual Studio)*
---
*Powershell scripts are provided to make the build process faster. One might need to change **Execution Policy** to execute ps1 scripts. Alternatively the scripts can be converted to **bat** or **com** files to execute in **cmd**. The Windows version is targeted towards **MSVC** using **Microsoft Visual Studio**. Visual Studio version **2017 or Higher** recommended. Becareful about the fsys namespace alias in **[MemoryCore.h](src/MemoryCore.h)** since C++ 2017 standard might be experimental in VS2017 and use ```std::experimental::filesystem```, but in 2019, it should use ```std::filesystem```.*

Run the following commands in step to generate project files and build the project.
```powershell
.\makedirs.ps1 # Generates output directories

.\buildlex.ps1 # Generates Application.cpp file from Application.l using win_flex\win_flex.exe

.\premake\premake5.exe vs2019 # Pass respective Visual Studio version
```
*At this point, a **Visual Studio Solution** will be generated. Use it to build the project.*

---
## *Building for Linux (GCC/ Make)*
---
*Shell Scripts are provided to make the build process faster. Install the aforementioned required packages before building.*

Run the following commands in step to generate project files and build the project.
```bash
#-- Project Generation --
sh ./makedirs.sh # Generates output directories

sh ./buildlex.sh # Generates Application.cpp file from Application.l using flex

premake5 gmake2 # Generates Makefile

#-- Building ---
# For building in Debug Mode
make config=debug
# or
# For building in Release Mode
make config=release
```
---
The project is not tested with *Clang* but it should work. Alternative one can compile with GCC in Windows environment using *mingw* or *Cygwin* or any similar system.

---
## Using the Application
---
The executable can be executed with at max one argument, which is the directory of the preferred json save file. If no json path is provided, default json file *data.json* is used which is located/created at the root directory of the executable. ```_help``` command can be used inside the executable to view *Help Menu*, which would show the following command descriptions.

```
>> _help
=== HELP ===
--[H] It is HIGHLY RECOMMENDED to always use lowercase
--[H] Use command <_exit> or <quit> to quit
--[H] Use command <_help> to view commands
--[H] Use command <_about> to view developer info
--[H] Use command <_path> to view save file path
--[H] Use command <_load> to load data from file
--[H] Use command <_save> to write data to file
--[H] Use command <verb> followed by SPACE separated words to save verbs
--[H] Use command <adj> followed by SPACE separated words to save adjectives
--[H] Use command <adv> followed by SPACE separated words to save adverbs
--[H] Use command <noun> followed by SPACE separated words to save nouns
--[H] Use command <prep> followed by SPACE separated words to save prepositions
--[H] Use command <pron> followed by SPACE separated words to save pronouns
--[H] Use command <conj> followed by SPACE separated words to save conjunctions
--[H] Just write SPACE separated words to search them
--[H] Save file path can be set by passing single command line argument
--[H] If no save file path is provided, default path is used
```
---