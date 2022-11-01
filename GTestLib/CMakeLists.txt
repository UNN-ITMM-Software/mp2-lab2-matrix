file(GLOB hdrs "*.h*") #Добавляем в переменную hdrs все файлы с расширением .h
file(GLOB srcs "*.cpp") #Добавляем в переменную srcs все файлы с расширением .cpp
file(GLOB sol "*.cc")

add_library(${testlib} STATIC ${srcs} ${hdrs} ${sol}) #Создаем статическую библиотеку с именем из переменной ${MyLib1}, объявленной в родительском CMake файле (локальные переменные переносятся в наследников), в неё добавляются файлы из переменных ${srcs} и ${hdrs}

#add_executable(${vector} ${srcs} ${hdrs}) #Создаем проект с именем из переменной ${PROJECT_NAME}, в него добавляются файлы из переменных ${srcs} и ${hdrs}
 #Собираем проект в поддиректории lib1
#target_link_libraries(${vector} ${vectorlib}) #Подключаем к проекту с именем ${PROJECT_NAME} библиотеку с именем ${MyLib1}
