file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp") 
add_executable(${test} ${srcs} ${hdrs})

target_link_libraries(${test} ${testlib}) 
