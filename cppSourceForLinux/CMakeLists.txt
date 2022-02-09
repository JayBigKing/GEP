cmake_minimum_required(VERSION 3.16)
project(cppSourceForLinux)

set(CMAKE_CXX_STANDARD 14)

set(BOOST_ROOT "/usr/local/include")
set(BOOST_INCLUDEDIR ${BOOST_ROOT})
set(BOOST_LIBRARYDIR "/usr/local/lib/")
#添加头文件搜索路径
include_directories(/usr/local/include)

#添加库文件搜索路径
link_directories(/usr/local/lib/)

#add_library(sm2lib1  FunctionPreset.h FunctionPreset.cpp )
#add_library(sm2lib2 Symbol.h Symbol.cpp )

add_executable(cppSourceForLinux main.cpp Symbol.cpp Symbol.h FunctionPreset.cpp FunctionPreset.h ChromosomeRule.cpp ChromosomeRule.h
        initHelp.cpp initHelp.h Chromosome.cpp Chromosome.h ChromosomeDecoder.cpp ChromosomeDecoder.h
        SL_ChromosomeDecoder.cpp SL_ChromosomeDecoder.h SymbolSetGenerator.cpp SymbolSetGenerator.h
        GEP.cpp GEP.h SL_GEP.cpp SL_GEP.h GA_HelpFunc.cpp GA_HelpFunc.h SL_GEPTester.cpp SL_GEPTester.h
        ChromosomeShower.cpp ChromosomeShower.h)
#add_executable(cppSourceForLinux main.cpp)

#target_link_libraries(cppSourceForLinux sm2lib1)
#target_link_libraries(cppSourceForLinux sm2lib2)
target_link_libraries(cppSourceForLinux boost_thread boost_system boost_filesystem -pthread)