# mpss-lib

Used for fetching some data from Ubuntu Cloud streams.

## Dependencies

There are a few tools required to build the project: 
git, cmake, make, and a compiler with support for C++17.
Plus, dev packages for libssl are required to access _https://_ URLs.

One way to install these tools would be to run the following commands:

### Debian, Ubuntu:

```
sudo apt install build-essential git cmake libssl-dev
```

### Arch Linux:

```
sudo pacman -S base-devel git cmake openssl
```

### CentOS, Fedora:

```
yum install gcc gcc-c++ kernel-devel make git cmake openssl-devel
```

### MacOS:

```
brew install cmake openssl git 
export LDFLAGS="-L/opt/local/lib"
export CPPFLAGS="-I/opt/local/include/openssl"
```

Additionally, [install XCode](https://developer.apple.com/support/xcode/).

### Windows:

Perhaps, the easiest way to build will be using Visual Studio.

Additionally, you will need to install [OpenSSL](https://slproweb.com/products/Win32OpenSSL.html) and [CMake](https://cmake.org/download/), and [Git](https://git-scm.com/download/win).

Or, using [Chocolatey](https://chocolatey.org/install
), you can install all the required tools with the following command:

```
choco install cmake openssl git visualstudio2022community visualstudio2019-workload-vctools
```

## Build instructions:

Clone the repository using git or by downloading files directly.

On Linux or MacOS, run terminal.
On Windows, run Developer Command Prompt for VS 2022.

In terminal, `cd` to the repository root directory and run the following commands. Alternativel, for Windows the build script can be used, located at `./scripts/build_win_msvc2022.cmd`, setting up the release build.

First, configure the project.

```
mkdir build
cd build
cmake ..
```

Then, for Linux and MacOS, build the project using:

```
make -j9 
```

For Windows, build the project using:

```
cmake --build . -j9 
```

> Similarly, on Windows MinGW can be used for configuring and building the project. For that I personally prefer using QtCreator.

## Testing

To run tests, run `./build/[Release|Debug]/bin/test_mpsslib[.exe]`, check the build output for exact path.

## To fix later

* Add caching when downloading the stream data. For that, https://cloud-images.ubuntu.com/releases/streams/v1/index.json can be fetched, containing the latest update date for streams. It's about 50 times ligher then the stream json itself. Caching ContentDownloader can be implemented.

* Add option to build using system curl instead of building it, to speed up building.
