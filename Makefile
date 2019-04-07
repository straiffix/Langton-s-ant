LangAnt: 
	$(CC) end.c ant.c antpng.c -lpng -o Lants
clean:
	rm -rf *.o Lants *.png
tests:
	 ./Lants -r config -w out1.png
