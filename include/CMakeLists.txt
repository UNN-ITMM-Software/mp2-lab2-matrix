file(GLOB hdrs "*.h*") #Добавляем в переменную hdrs все файлы с расширением .h
file(GLOB srcs "*.cpp")#Добавляем в переменную srcs все файлы с расширением .cpp
file(GLOB txts "*.txt")#Добавляем в переменную txts все файлы с расширением .txt
file(GLOB bins "*.bin")#Добавляем в переменную bins все файлы с расширением .bin

add_library(Matrix STATIC ${srcs} ${hdrs} ${txts} ${bins})