jogo.out:
	gcc -o jogo.out -g main.c personagem.c graficos.c defs.c controle.c lista.c -lSDL2 -lSDL2_image -lSDL2_ttf

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
