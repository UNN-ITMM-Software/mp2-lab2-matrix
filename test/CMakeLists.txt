file(GLOB hdrs "*.h*") #Добавляем в переменную hdrs все файлы с расширением .h
file(GLOB srcs "*.cpp")#Добавляем в переменную srcs все файлы с расширением .h

add_executable(test ${srcs} ${hdrs}) #Создаем проект с именем test в него добавляются файлы из переменных ${srcs} , ${hdrs}
target_include_directories(test PUBLIC ../include ../gtest)
target_link_libraries(test Matrix gtest) #Подключаем к проекту с именем main библиотеки LibImage, gtest