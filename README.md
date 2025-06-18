
# Timber: A C++ Game Development Project
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++](https://img.shields.io/badge/Language-C++-blue)](https://en.cppreference.com/w/)
[![SFML](https://img.shields.io/badge/Library-SFML%203.0.1-orange)](https://www.sfml-dev.org/)

## Overview

**Timber** is a 2D game developed in C++ using the Simple and Fast Multimedia Library (SFML) 3.0.1. This project showcases the game development expertise of **One Frequency Games** and the AI innovation potential of **One Frequency AI**, divisions of **One Frequency, Inc.**. Inspired by "Timberman," Timber challenges players to chop a tree while avoiding falling branches under time constraints, leveraging robust C++ programming, SFML’s multimedia capabilities, and a professional development workflow.

## About One Frequency, Inc.

One Frequency, Inc. is a technology company advancing interactive entertainment and artificial intelligence. Its divisions include:
- **One Frequency Games**: Creating immersive games with engaging experiences.
- **One Frequency AI**: Developing AI solutions for enhanced gameplay, procedural content, and creative workflows.

Timber combines these efforts, delivering polished mechanics with potential for AI-driven features like adaptive difficulty or procedural level design.

## Project Goals

- Advance C++ game development with modern C++20, object-oriented design, and efficient memory management.
- Utilize SFML’s graphics, audio, and input modules for cross-platform 2D rendering and event handling.
- Establish a professional workflow with Git, CMake/Ninja, and VS Code.
- Enable future AI enhancements, aligning with One Frequency AI’s vision.
- Demonstrate One Frequency, Inc.’s commitment to high-quality game and AI development.

## Features

- Core gameplay: Chopping mechanic with a placeholder tree (brown rectangle).
- SFML 3.0.1: Modern API using `std::optional<sf::Event>` for window and input management.
- Cross-platform support: Developed on macOS, with CMake for Windows/Linux compatibility.
- Professional workflow: Git version control, CMake/Ninja builds (planned), VS Code with C++ extensions.
- Roadmap: Sprites, audio, branch mechanics, and AI-driven gameplay.

## Getting Started

### Prerequisites

- **C++ Compiler**: Clang 16.0.0 or compatible (Xcode Command Line Tools).
- **SFML 3.0.1**: Installed via Homebrew.
- **CMake**: Version 3.20 or newer.
- **Ninja**: Build system.
- **VS Code**: With C/C++, CMake Tools, and CodeLLDB extensions.

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/WillCybertron/Timber.git
   cd Timber
# Timber Game

## Installation

### Install dependencies (macOS)
```bash
brew install sfml cmake ninja
```

### Configure and build (CMake)
```bash
mkdir build
cd build
cmake -G Ninja -DCMAKE_PREFIX_PATH=/opt/homebrew ..
ninja
```

### Run the game
```bash
./timber
```

## Development Setup

### VS Code
1. Open the Timber folder
2. Run CMake: Configure and CMake: Build (Command Palette: `Cmd+Shift+P`)
3. Press `F5` to debug

### Troubleshooting
For runtime errors (`dyld: Library not loaded`):
```bash
export DYLD_LIBRARY_PATH=/opt/homebrew/lib:$DYLD_LIBRARY_PATH
```

Or:
```bash
install_name_tool -add_rpath /opt/homebrew/lib timber
```

## Project Structure
```
Timber/
├── main.cpp                    # Game logic
├── .vscode/                    # VS Code settings
│   ├── tasks.json
│   ├── c_cpp_properties.json
│   ├── launch.json
│   └── settings.json
├── CMakeLists.txt              # CMake configuration
├── assets/                     # Game assets (planned)
├── build/                      # Build artifacts
├── .gitignore                  # Excludes build files
└── README.md                   # Documentation
```

## Roadmap
- Timer-based gameplay (2-second limit)
- Chopping mechanic (Space key)
- Branch spawning and collision detection
- Sprites and audio integration
- AI-driven features (e.g., dynamic difficulty)

## Contributing
1. Fork the repository
2. Create a branch: `git checkout -b feature/<feature-name>`
3. Commit changes: `git commit -m "Add <feature>"`
4. Push: `git push origin feature/<feature-name>`
5. Open a pull request

Use Clang-Format (`brew install clang-format`) for code style consistency.

## License
MIT License. See [LICENSE](LICENSE).

## Contact
**One Frequency, Inc.**
Email: info@onefrequency.com

Developed by One Frequency Games and One Frequency AI, under One Frequency, Inc.