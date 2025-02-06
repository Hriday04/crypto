cat <(grep -i "#define CHOICE" macros.c) <(grep -i "#define MEDIAN" macros.c) <(grep -i "#define ROTATE" macros.c) tester.c | gcc -xc - -Wno-pointer-to-int-cast -o test ; ./test ; echo $?
