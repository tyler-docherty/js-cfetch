@ECHO OFF
gcc.exe -Wall -L./lib -lhttp -I ./include -o fetch.exe fetch.c 
ECHO ON
