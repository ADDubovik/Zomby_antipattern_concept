cmake_minimum_required(VERSION 3.5)

project(ZombyConcept LANGUAGES CXX)

include_directories(${CMAKE_SOURCE_DIR})

set(SRC_COMMON
	Common/Impl/WriteToConsoleListener.h
	Common/Impl/WriteToConsoleListener.cpp
	Common/Listener.h
	Common/Manager.h
)

set(SRC_BOOZD
	boozd/azzio/impl/random_stream.h
	boozd/azzio/impl/random_stream.cpp
	boozd/azzio/buffer.h
	boozd/azzio/io_context.h
	boozd/azzio/io_context.cpp
	boozd/azzio/stream.h
)

set(SRC
	BoozdedZomby/Impl/BoozdedZomby.h
	BoozdedZomby/Impl/BoozdedZomby.cpp
	ComplicatedZomby/Impl/ComplicatedZomby.h
	ComplicatedZomby/Impl/ComplicatedZomby.cpp
	ComplicatedZomby/Impl/RandomDataSource.h
	ComplicatedZomby/Impl/RandomDataSource.cpp
	ComplicatedZomby/DataReceiver.h
	ComplicatedZomby/DataSource.h
	SteppingZomby/SteppingZomby.h
	SteppingZomby/SteppingZomby.cpp
	main.cpp
)

set(SRC_SIMPLE_CYCLIC
	SimpleCyclic/SimpleCyclic.h
	SimpleCyclic/SimpleCyclic.cpp
	SimpleCyclic/main.cpp
)

set(SRC_PIMPL_CYCLIC
	PimplCyclic/PimplCyclic.h
	PimplCyclic/PimplCyclic.cpp
	PimplCyclic/main.cpp
)

set(SRC_SIMPLE_ZOMBY
	SimpleZomby/SimpleZomby.h
	SimpleZomby/SimpleZomby.cpp
	SimpleZomby/main.cpp
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Common_lib ${SRC_COMMON})
add_library( boozd_lib ${SRC_BOOZD})

add_executable(SimpleCyclic ${SRC_SIMPLE_CYCLIC})
add_executable( PimplCyclic  ${SRC_PIMPL_CYCLIC})

add_executable(SimpleZomby ${SRC_SIMPLE_ZOMBY})
add_dependencies(SimpleZomby Common_lib)
target_link_libraries(SimpleZomby Common_lib)

add_executable(ZombyConcept ${SRC})
add_dependencies(ZombyConcept Common_lib boozd_lib)
target_link_libraries(ZombyConcept Common_lib boozd_lib)
