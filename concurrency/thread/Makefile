PRJ = hello

$(PRJ): main.o
	g++ main.o -pthread -o $(PRJ)

main.o: main.cpp ./inc/all_hed.hpp
	g++ -H -std=c++17 -I./inc -c main.cpp

header: ./inc/all_hed.hpp.gch

./inc/all_hed.hpp.gch: ./inc/all_hed.hpp
	g++ -Winvalid-pch -x c++-header -std=c++17 ./inc/all_hed.hpp

cls:
	rm -f $(PRJ) *.o a.outs ./inc/*.gch
