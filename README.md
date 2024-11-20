# module-demo
C++ modules were introduced in the 2020 language revision, but few compilers
had any support for it until recently. As of 2024, Clang 18.10+ and the
very latest Microsoft Visual C++ have tolerable support and GNU is coming in
close behind.

Unfortunately, although the compilers are beginning to support it the tooling
is lagging behind.  As of CMake 3.30, though, there's a marginally acceptable
level of support in CMake.

This repo will show you how to make use of it.

## Building
On Fedora 41 you'll need to first `dnf install` the following packages:

* `clang` (for compiling)
* `lldb` (for debugging)
* `boost-*` (for the Boost library runtimes)
* `boost-*-devel` (to get all the Boost header files)
* `libstdcxx` (Clang’s module-aware C++ standard library runtime)
* `libstdcxx-devel` (header files for `libstdcxx`)
* `ninja` (for building)
* `git` (for obtaining source code)

Once that’s all done:

```
$ git clone git@github.com:rjhansen/module-demo.git
$ cd module-demo
$ mkdir build
$ cd build
$ cmake -S .. \
        -B . \
        -DCMAKE_CXX_COMPILER=clang++ \
        -DCMAKE_CXX_FLAGS_INIT=-stdlib=libc++ \
        -DCMAKE_BUILD_TYPE=Release \
        -G Ninja \
        -Wno-dev
$ ninja
$ ninja test
$ sudo ninja install
```

This will drop a modularized `libhello.so` into your `/usr/lib64`
directory and a `hello.h` into `/usr/include`.  At that point you’ll
have an example of how to use C++ modules and incorporate them into
a modern toolchain.

## Flag explanations

### -S ..
The `CMakeLists.txt` file is located one directory above `build`.

### -B .
Use the current directory (`build`) for all build artifacts.

### -DCMAKE_CXX_COMPILER=clang++
As of this writing only Clang 18.10+ and the very latest Microsoft
Visual Studio compilers can create or consume C++ modules.  There are a
lot of caveats on both.

### -DCMAKE_CXX_FLAGS_INIT=stdlib=libc++
As of this writing Clang requires you to use their libc++, nobody
else’s, for modules. (libc++ is not normally installed.  On Fedora, for
instance, I had to install packages `libcxx` and `libcxx-devel`.)

### -DCMAKE_BUILD_TYPE=Release
… or `Debug`, as you wish.

### -G Ninja
Generate a Ninja build script.  As of CMake 3.30, Ninja is the only
build tool that supports C++ modules.

### -Wno-dev
We’re using CMake features that can only be described as “under active
development”.  As such, CMake will throw a number of warnings unless
that particular warning category is suppressed.

## More warnings
As of this writing the shared libraries for the Boost unit test
framework are incompatible with C++ modules.  The header-only version
works fine, though.