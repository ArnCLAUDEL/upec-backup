#
# Linux makefile
# Use with make 
#

.SUFFIXES:
.SUFFIXES: .o .asm .cpp .c

#AS=nasm
AS=yasm
ASFLAGS=  -g dwarf2 -f elf64
CFLAGS= -m64 -g
CC=gcc  
CXX=g++
CXXFLAGS=  

.asm.o:
	$(AS) $(ASFLAGS) $*.asm

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $*.cpp

.c.o:
	$(CC) -c -g $(CFLAGS) $*.c

all:  first 

first: driver.o first.o
	$(CC) $(CFLAGS) -ofirst driver.o first.o

driver.o : driver.c


clean :
	rm *.o
	rm  first

