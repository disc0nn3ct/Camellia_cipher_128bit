c=gcc
all:
	@echo "================================================================="
	$(c) -o test.o main.c camellia_128_bit.c -lgcrypt 	
	./test.o
	@echo "================================================================="
test:
	$(c) -o test.o main.c camellia_128_bit.c -lgcrypt 	
	./test.o
clean: 
	rm -rf *.o
