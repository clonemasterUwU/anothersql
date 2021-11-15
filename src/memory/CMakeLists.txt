set(MEMORY_SOURCE  Frame.cpp BufferManager.cpp ClockEvictionPolicy.cpp Page.cpp)
add_library(memory STATIC ${MEMORY_SOURCE})
