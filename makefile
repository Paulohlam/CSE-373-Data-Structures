# makefile
# Author: Paul Lam
# CSE374, HW5
# Copyright 2023 Paul Lam

all: t9

t9: tnine.o trie.o
		gcc tnine.o trie.o -o t9 -std=c11 -g -Wall

tnine.o: tnine.c trienode.h
		gcc -c tnine.c -o tnine.o -std=c11 -g -Wall

trie.o: trie.c trienode.h
		gcc -c trie.c -o trie.o -std=c11 -g -Wall

clean:
		rm -f *.o t9


