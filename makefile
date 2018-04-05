jogo.out:
	gcc -o jogo.out -g main.c personagem.c graficos.c utils.c -lSDL2

#jogo.out: personagem.o graficos.o
#	gcc -o jogo.out -c -g main.c -lSDL2
#
#personagem.o: personagem.c
#	gcc -c -g personagem.c
#
#graficos.o: graficos.c
#	gcc -c -g graficos.c

clean:
	rm *.o*