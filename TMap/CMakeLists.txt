file(GLOB hdrs "*.h*") 
file(GLOB srcs "*.cpp")

add_library(${TMap} STATIC ${srcs} ${hdrs}) 


