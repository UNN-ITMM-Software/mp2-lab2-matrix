file(GLOB hdrs "*.h*") #Добавляем в переменную hdrs все файлы с расширением .h
file(GLOB srcs "*.cpp")#Добавляем в переменную srcs все файлы с расширением .cpp

add_executable(samples ${srcs} ${hdrs}) #Создаем проект с именем main в него добавляются файлы из переменных ${srcs} , ${hdrs} и тд
target_include_directories(samples PUBLIC ../include)
set_target_properties(Matrix PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(samples Matrix)