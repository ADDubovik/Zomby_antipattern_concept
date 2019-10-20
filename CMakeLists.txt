cmake_minimum_required(VERSION 3.5)

project(ZombyConcept LANGUAGES CXX)

include_directories(${CMAKE_SOURCE_DIR})

set(SRC
	boozd/azzio/impl/random_stream.h
	boozd/azzio/impl/random_stream.cpp
	boozd/azzio/buffer.h
	boozd/azzio/io_context.h
	boozd/azzio/io_context.cpp
	boozd/azzio/stream.h
	BoozdedZomby/Impl/BoozdedZomby.h
	BoozdedZomby/Impl/BoozdedZomby.cpp
	Common/Impl/WriteToConsoleListener.h
	Common/Impl/WriteToConsoleListener.cpp
	Common/Listener.h
	Common/Manager.h
	ComplicatedZomby/Impl/ComplicatedZomby.h
	ComplicatedZomby/Impl/ComplicatedZomby.cpp
	ComplicatedZomby/Impl/RandomDataSource.h
	ComplicatedZomby/Impl/RandomDataSource.cpp
	ComplicatedZomby/DataReceiver.h
	ComplicatedZomby/DataSource.h
	PimplCyclic/PimplCyclic.h
	PimplCyclic/PimplCyclic.cpp
	SimpleCyclic/SimpleCyclic.h
	SimpleCyclic/SimpleCyclic.cpp
	SimpleZomby/SimpleZomby.h
	SimpleZomby/SimpleZomby.cpp
	SteppingZomby/SteppingZomby.h
	SteppingZomby/SteppingZomby.cpp
	main.cpp
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ZombyConcept ${SRC})
