all: firstExecute secondExecute
firstExecute: encode.cpp
	g++ -std=c++11 -o encode encode.cpp
secondExecute: decode.cpp
	g++ -std=c++11 -o decode decode.cpp
