cmake_minimum_required(VERSION 3.5)

project(ZombyConcept LANGUAGES CXX)

include_directories(${CMAKE_SOURCE_DIR})

set(SRC
        ComplicatedZomby/Impl/ComplicatedZomby.h
        ComplicatedZomby/Impl/ComplicatedZomby.cpp
        ComplicatedZomby/Impl/RandomDataSource.h
        ComplicatedZomby/Impl/RandomDataSource.cpp
        ComplicatedZomby/DataReceiver.h
        ComplicatedZomby/DataSource.h
        ComplicatedZomby/Listener.h
	SimpleZomby/SimpleZomby.h
	SimpleZomby/SimpleZomby.cpp
	WriteToConsoleListener.h
	WriteToConsoleListener.cpp
	main.cpp
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ZombyConcept ${SRC})
