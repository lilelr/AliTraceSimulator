cmake_minimum_required(VERSION 3.7)
project(AliSimulator)

set(CMAKE_CXX_STANDARD 11)

set(ALI_TRACE_PRE_SOURCE_FILES AliTracePreProcesor_main.cpp AliTracePreProcessor.h AliTracePreProcessor.cpp string_helper.cpp string_helper.h collection_helper.cpp collection_helper.h )
add_executable(AliTracePreProcessor ${ALI_TRACE_PRE_SOURCE_FILES})
target_link_libraries(AliTracePreProcessor LINK_PUBLIC gflags glog)

set(ALI_TRACE_SIMULATOR_SOURCE_FILES AliSimulator_main.cpp AliSimulator.cpp AliSimulator.h SimulatedWallTime.cpp SimulatedWallTime.h AliTraceLoader.cpp AliTraceLoader.h SimulatorLinker.cpp SimulatorLinker.h EventHandler.cpp EventHandler.h ResourceStatus.cpp ResourceStatus.h ResourceRecord.cpp ResourceRecord.h)
add_executable(AliSimulator ${ALI_TRACE_SIMULATOR_SOURCE_FILES})
target_link_libraries(AliSimulator LINK_PUBLIC gflags glog)


