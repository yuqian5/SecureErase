cmake_minimum_required(VERSION 3.17)
project(SecureErase)

set(CMAKE_CXX_STANDARD 14)

add_executable(SecureErase src/main.cpp src/DOD522022M.cpp include/DOD522022M.h src/DOD522022MECE.cpp include/DOD522022MECE.h src/DPE.cpp include/DPE.h src/SPE.cpp include/SPE.h src/EraseALL.cpp include/EraseALL.h)