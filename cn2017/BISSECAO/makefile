
SRC=mainBissecao.cpp

all: ordem
	@echo "compilando e linkando bissecao"
ordem: bissecao.o mainBissecao.o
	g++ -o mainBissecao	bissecao.o mainBissecao.o

bissecao.o: bissecao.cpp
	g++ -o bissecao.o -c bissecao.cpp
mainBissecao.o: $(SRC) bissecao.h		# codigo_fonte	header1 header2 ...
	g++ -o mainBissecao.o -c $(SRC)
clean:
	rm -rf *.o
mrproper:
	rm -rf testa		