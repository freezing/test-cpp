cmake_minimum_required(VERSION 3.5)
project(oopcpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES main.cpp linija.cpp linija.h mreza.h stajaliste.h smer.h lokacija.h mreza.cpp stajaliste.cpp baza_stajalista.h baza_linija.h baza_linija.cpp)
add_executable(oopcpp ${SOURCE_FILES})