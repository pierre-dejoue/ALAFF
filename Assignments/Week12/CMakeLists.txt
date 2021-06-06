cmake_minimum_required(VERSION 3.18)

project(ALAFF_C
    VERSION 0.1.0
)

option(ALAFF_AVX2 "Enable AVX2 instruction set." ON)

set(NREPEATS     3      CACHE STRING "number of times each experiment is repeated.  The best time is reported.")
set(NFIRST       48     CACHE STRING "smallest size to be timed.")
set(NLAST        500    CACHE STRING "largest size to be timed.")
set(NINC         48     CACHE STRING "increment between sizes.")

set(GEMM_ORDERINGS "IJP") # "IPJ" "JIP" "JPI" "PIJ" "PJI")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(BLA_VENDOR FLAME)
find_package(BLAS)

add_subdirectory(C)
