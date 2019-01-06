# Makefile written by Jae Hyuk Kwak
CC=g++-4.9
CFLAGS=-Wall -g -std=c++11

all: trends_google

trends_google: *.hpp *.cpp stdafx.h.gch
	$(CC) $(CFLAGS) -o trends_google -lcurl trends_google.cpp

stdafx.h.gch: stdafx.h
	$(CC) $(CFLAGS) -c stdafx.h

clean:
	rm stdafx.h.gch trends_google
