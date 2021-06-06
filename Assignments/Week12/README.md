ALAFF with CMake on Windows
===========================

## Install BLIS Library

- Follow the links in [conda-forge/blis-feedstock](https://github.com/conda-forge/blis-feedstock) to download BLISS binaries for your platform, e.g.:

    `win-64/blis-0.8.1-h8d14728_0.tar.bz2`

- Unzip to your preferred install folder, for instance `C:\BLIS`
- Set env variable: `BLAS_ROOT = "C:\BLIS\Library"`

## Build with MSVC

With [CMake](https://cmake.org/download/). For example on Windows:

```
cd Assignments/Week12
mkdir -p build/msvc141x64
cd build/msvc141x64
cmake -G "Visual Studio 15 2017 Win64" ../..
cmake --build . --config Release
```

## Run IJP

```
cmake --build . --config Release --target run_IJP
```

## Run All Orderings

Edit variable GEMM_ORDERINGS in CMakeLists.txt to match the orderings you implemented, then rebuild:

```
cmake -G "Visual Studio 15 2017 Win64" ../..
cmake --build . --config Release --target run_all_orderings
```
