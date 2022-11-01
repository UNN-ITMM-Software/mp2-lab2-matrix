file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp") 

add_library(${vectorlib} STATIC ${srcs} ${hdrs}) 