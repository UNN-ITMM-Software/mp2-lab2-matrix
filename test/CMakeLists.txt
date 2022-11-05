file(GLOB hdrs "*.h*") #Добавляем в переменную hdrs все файлы с расширением .h
file(GLOB srcs "*.cpp") #Добавляем в переменную srcs все файлы с расширением .cpp

add_executable(${test} ${srcs} ${hdrs}) #Создаем проект с именем из переменной ${PROJECT_NAME}, в него добавляются файлы из переменных ${srcs} и ${hdrs}

 #Собираем проект в поддиректории lib1
target_link_libraries(${test} ${testlib}) #Подключаем к проекту с именем ${PROJECT_NAME} библиотеку с именем ${MyLib1}