# RoboTo

RoboTo is a community fork of [Robo 3T](https://github.com/Studio3T/robomongo) (last official release: **1.4.4**), picking up where the original project left off.

The goal is to keep the tool alive, modernise its dependencies, and improve the user experience — starting with visual quality and security updates.

## Install (Linux)

```bash
bash <(curl -fsSL https://raw.githubusercontent.com/yperdoom/roboto/master/install.sh)
```

This downloads the latest release, installs to `~/.local/share/roboto`, creates a `roboto` command and adds RoboTo to your app launcher.

## Version

**RoboTo 1.0.0** — based on Robo 3T 1.4.4 (MongoDB 4.2 shell)

## What's changed from Robo 3T 1.4.4

### Visual
- **Dark mode** added as default theme (Light mode still available)
- Theme switching in Preferences — change takes effect instantly, no restart needed
- Tab bar and table view colours adapt to the active theme
- Compiled and tested on modern Arch Linux (GCC 15, Qt 5.15, OpenSSL 3.x)

### Build / Dependencies
- Builds against system OpenSSL 3.x on Linux (no bundled 1.0.x)
- Fixed several build failures introduced by GCC 15, glibc 2.34+, CMake 4.x, and SCons 4.9+
- Updated googletest CMake minimum version requirement

## Base project

Robo 3T 1.4.4 was the last release by Studio 3T before the project was discontinued.
Original source: https://github.com/Studio3T/robomongo

The embedded MongoDB shell version remains **4.2** (unchanged from Robo 3T 1.4.4).

## Building

### Prerequisites

- CMake 3.14+
- Qt 5.15
- OpenSSL 3.x (system)
- GCC 11+ (tested with GCC 15)
- Python 3.9 (for robomongo-shell build via SCons)

### Build robomongo-shell first

```bash
cd ~/mp/robomongo-shell
python -m venv .venv
source .venv/bin/activate
pip install "setuptools<46"
.venv/bin/pip install scons
bin/build
```

### Build RoboTo

```bash
cd ~/mp/roboto
bin/build
bin/install
bin/run
```

## Supported Platforms

Actively developed on:

| Platform | Status |
|---|---|
| Arch Linux x86_64 | Builds and runs |

Platforms inherited from Robo 3T 1.4.4 (untested in this fork):

| Windows | Mac | Linux |
|---|---|---|
| 64-bit 10/8.1/7 | macOS 11 / 10.15 / 10.14 | Ubuntu 20.04 / 18.04 |

## License

Copyright 2014–2021 [3T Software Labs Ltd](https://studio3t.com/). All rights reserved.
Modifications copyright 2024– RoboTo contributors.

This program is free software: you can redistribute it and/or modify it under the terms of the
GNU General Public License version 3 as published by the Free Software Foundation.

See [LICENSE](LICENSE) for the full text.
