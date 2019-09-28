cmake_minimum_required(VERSION 3.5)

project(ZombyConcept LANGUAGES CXX)

set(SRC
	ComplexZomby/ComplexZomby.h
	ComplexZomby/ComplexZomby.cpp
	ComplexZomby/DataReceiver.h
	ComplexZomby/DataSource.h
	ComplexZomby/Listener.h
	ComplexZomby/RandomDataSource.h
	ComplexZomby/RandomDataSource.cpp
	SimpleZomby/SimpleZomby.h
	SimpleZomby/SimpleZomby.cpp
	WriteToConsoleListener.h
	WriteToConsoleListener.cpp
	main.cpp
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ZombyConcept ${SRC})
