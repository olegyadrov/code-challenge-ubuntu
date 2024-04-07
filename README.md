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
