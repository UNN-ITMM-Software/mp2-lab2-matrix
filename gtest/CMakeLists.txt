file(GLOB hdrs "*.h*") 
file(GLOB srcs "*.cpp") 
file(GLOB sol "*.cc")

add_library(${testlib} STATIC ${srcs} ${hdrs} ${sol}) 