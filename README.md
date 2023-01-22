# closedfish [![CMake](https://github.com/closedfish/closedfish/actions/workflows/cmake.yml/badge.svg)](https://github.com/closedfish/closedfish/actions/workflows/cmake.yml)
The main repository for Closedfish. 

The aim of this project is to create a chess engine, to improve the
`stockfish` engine by making stronger assumptions on closed positions.

The project works by evaluating a closedness coefficient for every input chess board,
and using that information to either call the preexisting Stockfish, or our new Closedfish algorithm. 

## Building Instructions

This project is a CMake project, so a C++ compiler (`gcc` recommended in general, `mingw` recommended for Windows as `x86_64-12.2.0-release-posix-seh-ucrt-rt_v10-rev2` is tested, and it compiles successfully), `make`, and `cmake` installed. Note that `g++17` standard is required. The project building process is summarized (and automated) in [a GitHub Action](https://github.com/closedfish/closedfish/blob/main/.github/workflows/cmake.yml). Here are the simple instructions:

1. Clone the repository, make sure all submodules are cloned (this includes `stockfish` and `vcpkg`).
2. Download the NNUE data file by navigating into `external/stockfish/src` and running `make net`.
3. (optional) Compile the Stockfish project (see [detailed information](https://github.com/official-stockfish/Stockfish) for a description of compilation on different machine architectures). For a simple, standard and portable configuration, one should run `make -j build ARCH=x86-64`.
4. Navigate back to the project directory, and run `cmake -B build`. (Build variants can be configured between `Debug` and `Release`)
5. Run `cmake --build build` to actually build the executable. (The option whether to build the main executable or not, and whether to build the test or not, can be set in `CMakeLists.txt` in the topmost directory)
6. Look for the compiled binary `Executable.exe` (or any other matching executable extension for other operating systems), which should be at : `build/app/Debug/Executable.exe`.

## Members (name surname, github username, trello username, [role])

- Sirawit Pongnakintr, plumsirawit, plumsirawit, [git leader]
- Rali Lahlou, Apllify, ralilahlou
- Ba Cong Vu, souhhcong, souhhcong
- Cassidy Kevorkian-Mielly, Cassidy-Kevorkian, Cassidy Kevorkian-Mielly [code the evaluation function ai for the switch]
- Flahaut Ariel, arielflt, flahautariel, [member]
- Antonia Baies, abaiesu, abaiesu
- Shirelle Benamou, shirellebenamou, shirellebenamou
- Yoshimi-Théophile Etienne, Yoshimi-Theophile, yoshimitheophile
- Aarrya Saraf, AarryaSaraf, AarryaSaraf. [leader]
- Dimitrije Zdrale, D-2n, @dimitrije32, [UI]
- Etienne Leroy, etienne-leroy, etienneleroy8, [member]


## Teams

### Algorithm

- Rali Lahlou
- Ba Cong Vu
- Sirawit Pongnakintr
- Antonia Baies
- Yoshimi-Théophile Etienne
- Aarrya Saraf

### Switch

- Cassidy Kevorkian
- Andrei Bornea
- Nadja Zivkovic

### App
- Razvan Pucasu
- Dimitrije Zdrale

### Data & Testing

- Etienne Leroy
- Ariel Flahaut
- Shirelle Benamou
