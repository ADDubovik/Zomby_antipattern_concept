cmake_minimum_required(VERSION 3.5)

project(ZombyConcept LANGUAGES CXX)

include_directories(${CMAKE_SOURCE_DIR})

set(SRC
	ComplexZomby/Impl/ComplexZomby.h
	ComplexZomby/Impl/ComplexZomby.cpp
	ComplexZomby/Impl/RandomDataSource.h
	ComplexZomby/Impl/RandomDataSource.cpp
	ComplexZomby/DataReceiver.h
	ComplexZomby/DataSource.h
	ComplexZomby/Listener.h
	SimpleZomby/SimpleZomby.h
	SimpleZomby/SimpleZomby.cpp
	WriteToConsoleListener.h
	WriteToConsoleListener.cpp
	main.cpp
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ZombyConcept ${SRC})
