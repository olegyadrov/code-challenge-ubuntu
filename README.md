# Requirements

This task is to define an interface and implement a derived class in C++ that fetches the latest Ubuntu Cloud image information in Simplestreams format from https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json and provides methods that:

- Return a list of all currently supported Ubuntu releases.
- Return the current Ubuntu LTS version.
- Return the sha256 of the disk1.img item of a given Ubuntu release.

This will be wrapped in a CLI that outputs the above returned values depending on the option given.

The definition of the Simplestreams format is found at https://git.launchpad.net/simplestreams/tree/doc/README.

You need only be concerned with the amd64 architecture for the cloud images. You may choose to use a third party JSON parser and HTTP downloader library if you wish.

It is recommended to build the project using a CMakeLists.txt and cmake and it should be able to be built on Linux, macOS, and Windows.

Be sure to document the methods. The completed assignment should be a tarball, including build instructions in a README and ideally including a git repository to show the different development steps taken.

If you find the requirements are open to some interpretation, that is intentional and please use your best judgment on the design and implementation and explain your decisions where necessary.

# Build instructions

```
mkdir build
cmake -DCMAKE_PREFIX_PATH=<qt-installation-dir> -S ./code-challenge-ubuntu -B ./build
cd build
make
```

# Usage

```
./code-challenge-ubuntu [options]

Options:
  -c            Print the current Ubuntu LTS version
  -h <release>  Print the sha256 of the disk1.img item of a given Ubuntu release
  -r            Print a list of all currently supported Ubuntu releases
```

# Notes

For this project, I chose the Qt framework for its comprehensive benefits:

- Cross-platform support: ensures seamless operation across Linux, macOS, and Windows.
- Network and JSON capabilities: facilitates easy handling of network requests and JSON parsing, crucial for fetching the Ubuntu Cloud release and image information.
- CMake compatibility: aligns with the project's build system recommendation, simplifying the build process across different platforms.

While aware that this choice might seem to limit opportunities to showcase extensive use of the standard C++ library and modern C++ features, Qt's efficiency in network communication, JSON processing, and its cross-platform nature make it an ideal choice for this specific task. The decision was made based on project requirements, not a preference to avoid modern C++ practices. If necessary, I am fully prepared to adapt to alternative libraries or approaches that adhere more closely to the latest C++ standards.
