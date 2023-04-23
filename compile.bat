@ECHO OFF
gcc.exe -L./lib -lhttp -I ./include -o fetch.exe fetch.c 
ECHO ON