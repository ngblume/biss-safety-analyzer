# Saleae BiSS SAFETY Analyzer

Saleae BiSS SAFETY (bidirectional/serial/synchronous) Analyzer

## Difference to "normal" BISS

BISS Safety differs from "normal" BISS by simply adding more data after the CRC and before the BISS timeout (end of message).
Therefore, teh BISS SAFETY standard defines a "CPW" (control position word, identical to non-safety BISS), followed by a "SPW" (safety position word).
MT and ST are the serial data of a frame.
They are consisting of the following data:
CPW:
+ MT (multiturn) - different number of bits depending on resolution
+ ST (singleturn) - different number of bits depending on resolution
+ notError - 1 bit
+ notWarning - 1bit
+ notCRC (6 bits, CRC with 0x43 polynom) (CRC is being transmitted inverted)

SPW:
+ MT (multiturn) - different number of bits depending on resolution
+ ST (singleturn) - different number of bits depending on resolution
+ notError - 1 bit
+ notWarning - 1 bit
+ LifeCounter - 6 bits
+ notCRC (16 bits, CRC with 0x190D9 polynom) (CRC is being transmitted inverted)

Usually, the resolution is different for CPW and STW.
Common combinations are for example:
CPW:
+ MT = 0 bit (NO multiturn)
+ ST = 24 bits
SPW:
+ MT = 0 bit (NO multiturn)
+ ST = 16 bits

The lifecounter simply counts up from 0x00 (d00) to 0x3F (d63) and then rolls over.
Since CPW and STW can have different resolutions, there is a minimum number of bits, that needs to be identical for the data to be considered OK.
In the example CPW (ST=24bits) with SPW (ST=16bits), this number is given as 13.

---
&#9888; REST is identical to README from https://github.com/saleae/biss-analyzer
---

## Getting Started

The following documentation describes how to build this analyzer locally. For more detailed information about the Analyzer SDK, debugging, CI builds, and more, check out the readme in the Sample Analyzer repository.

https://github.com/saleae/SampleAnalyzer

### MacOS

Dependencies:

- XCode with command line tools
- CMake 3.13+
- git

Install command line tools after XCode is installed:

```
xcode-select --install
```

Then open XCode, open Preferences from the main menu, go to locations, and select the only option under 'Command line tools'.

Install CMake on MacOS:

1. Download the binary distribution for MacOS, `cmake-*-Darwin-x86_64.dmg`
2. Install the usual way by dragging into applications.
3. Open a terminal and run the following:

```
/Applications/CMake.app/Contents/bin/cmake-gui --install
```

_Note: Errors may occur if older versions of CMake are installed._

Build the analyzer:

```
mkdir build
cd build
cmake ..
cmake --build .
```

### Ubuntu 18.04+

Dependencies:

- CMake 3.13+
- gcc 4.8+
- git

Misc dependencies:

```
sudo apt-get install build-essential
```

Build the analyzer:

```
mkdir build
cd build
cmake ..
cmake --build .
```

### Windows

Dependencies:

- Visual Studio 2019
- CMake 3.13+
- git

**Visual Studio 2019**

_Note - newer and older versions of Visual Studio are likely to work._

Setup options:

- Workloads > Desktop & Mobile > "Desktop development with C++"

Note - if CMake has any problems with the MSVC compiler, it's likely a component is missing.

**CMake**

Download and install the latest CMake release here.
https://cmake.org/download/

**git**

Download and install git here.
https://git-scm.com/

Build the analyzer:

```
mkdir build
cd build
cmake .. -A x64
```

Then, open the newly created solution file located here: `build\biss_analyzer.sln`

Optionally, build from the command line without opening Visual Studio:

```
cmake --build .
```

The built analyzer DLLs will be located here:

`build\Analyzers\Debug`

`build\Analyzers\Release`

For debug and release builds, respectively.

