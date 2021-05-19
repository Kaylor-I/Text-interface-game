#simple rule -compile and link in one go
#note:header files are not passed to compiler -they are
#are only included in source dile!!! However, they may
#may appear in dependency list
game: main.cpp cboard.h cboard.cpp 
	g++ -Wall -ggdb -o game main.cpp cboard.cpp 


#clean up -handy to enforce recomplation
clean:
	rm *~ *# game
