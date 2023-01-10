
# Gryphon SAE Dash

## About

An electronic dash for the 2022 Gryphon Racing Team EV

## Installing Dependencies

### Setup for Raspberry Pi

Install all missing packages
```bash
sudo apt-get install python cmake libgl-dev libx11-dev libx11-xcb-dev libxcb-util-dev m4 libffi-dev
```

Ensure that the can interface on the RPi is active
```bash
sudo ip link set can0 up type can bitrate 1000000 # 1 mbps speed
```

### Setup for Windows

- Install [Python](https://docs.python.org/3/using/windows.html#using-python-on-windows) & ensure it is installed to PATH.
- Install [CMake](https://cmake.org/download/) & ensure it is installed to PATH.

### Setup for MacOS
- Ensure python3 version is up to date >3.7
- Install [CMake](https://cmake.org/download/) & ensure it is installed to PATH.


### Universal
- Install conan via pip
```bash
python -m pip install conan # or python3 on MacOS
```

## Installing Build Dependencies

Run the conan install script (`-pr` is the profile being used, the options are found in [ConanProfiles](./ConanProfiles/))
```bash
# Windows VS2019
conan install . -if build -pr:h=ConanProfiles/VS2019-Debug.ini -pr:b=ConanProfiles/VS2019-Debug.ini --build=missing -o dev="front"

# Windows VS2022
conan install . -if build -pr:h=ConanProfiles/VS2022-Debug.ini -pr:b=ConanProfiles/VS2022-Debug.ini --build=missing -o dev="front"

# MacOS clang 14
conan install . -if build -pr:h=ConanProfiles/MacOS-clang-Debug.ini -pr:b=ConanProfiles/MacOS-clang-Debug.ini --build=missing -o dev="front"

# RPi 4b (gcc 10.2)
conan install . -if build -pr:h=ConanProfiles/pi4b-Debug.ini -pr:b=ConanProfiles/pi4b-Debug.ini --build=missing -o dev="full"

# Linux gcc 12
conan install . -if build -pr:h=ConanProfiles/Linux-gcc-12-Debug.ini -pr:b=ConanProfiles/Linux-gcc-12-Debug.ini --build=missing -o dev="full"
```

* If building with `dev="back"`, Qt is not a requirement

## Building
- Run the conan build script & executables will be found in the build/bin folder.

```bash
conan build -if build .
```

## Running

```bash
source build/activate_run.sh # RPi (maybe required on other linux distros)
./build/Debug/bin/GryphonDash
source build/deactivate_run.sh # RPi (maybe required on other linux distros)
```

## Code Standards

Naming standards are as follows:
```C++
namespace PascalCase {}
class PascalCase {};
int camelCase() {};
int snake_case = 0;
```

Formatting is handled by clang format.
```bash
find ./src -iname *.hpp -o -iname *.cpp | xargs clang-format -i # In the root folder of the repo.
```

## Branch rules

- Name your branch as follows: `firstname/branchtopic`, ex. `dallas/move-from-previous-repo`
- `main` is a protected branch, and thus needs a PR to approve merging with it.

## Resources

* [<linux/can.h>](https://github.com/torvalds/linux/blob/master/include/uapi/linux/can.h)
* [SocketCAN Intro](https://copperhilltech.com/what-is-socketcan/)
* [PiCAN1](https://copperhilltech.com/pican-with-gps-gyro-accelerometer-can-bus-board-for-raspberry-pi/)/[PiCAN2](https://copperhilltech.com/pican-2-can-bus-interface-for-raspberry-pi/)
* [Raspberry Pi w/ CanBus](https://www.hackster.io/youness/how-to-connect-raspberry-pi-to-can-bus-b60235)
* Not used, but good cross reference for the SocketCAN intro: [socketcan-cpp](https://github.com/siposcsaba89/socketcan-cpp)