# Saleae BiSS SAFETY Analyzer

Saleae BiSS SAFETY (bidirectional/serial/synchronous) Analyzer

---
&#9888; Providing FramesV2 to up-stream hLAs is currently ongoing....

---

## Difference to "normal" BISS

BISS Safety differs from "normal" BISS by simply adding more data after the CRC and before the BISS timeout (end of message).
Therefore, the BISS SAFETY standard defines a "CPW" (control position word, identical to non-safety BISS), followed by a "SPW" (safety position word).
Multiturn (MT) and singleturn (ST) data is the serial data of a frame.
They are consisting of the following data:
CPW:
+ MT (multiturn) - different number of bits depending on resolution
+ ST (singleturn) - different number of bits depending on resolution
+ notError - 1bit
+ notWarning - 1bit
+ notCRC (6 bits, CRC with 0x43 polynom) (CRC is being transmitted inverted)

SPW:
+ MT (multiturn) - different number of bits depending on resolution
+ ST (singleturn) - different number of bits depending on resolution
+ notError - 1bit
+ notWarning - 1bit
+ LifeCounter - 6bits
+ notCRC (16bits, CRC with 0x190D9 polynom) (CRC is being transmitted inverted)

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
&#9888; This heavily based on the "normal" BISS analyzer: https://github.com/saleae/biss-analyzer

---

## Getting Started

The following documentation describes how to build this analyzer locally. For more detailed information about the Analyzer SDK, debugging, CI builds, and more, check out the readme in the Sample Analyzer repository.

https://github.com/saleae/SampleAnalyzer

## Windows

Dependencies:

- Visual Studio 2019
- CMake 3.13+
- git

Build the analyzer:

```
mkdir build
cd build
cmake .. -A x64
```

Then, open the newly created solution file located here: `build\bisssafety_analyzer.sln`

Optionally, build from the command line without opening Visual Studio:

```
cmake --build .
```

```
cmake --build . --config Release
```

The built analyzer DLLs will be located here:

`build\Analyzers\Debug`

`build\Analyzers\Release`

For debug and release builds, respectively.
