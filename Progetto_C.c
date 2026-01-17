#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "Strutture.h"
#include "Funzioni.c"

//--MAIN--
int main(){
	int scelta;
	bool ciclo=true;
	while(ciclo){
		menu();
		scanf("%d",&scelta);
		switch(scelta){
		case 1:
			Personaggio player=creaPersonaggio();
			printf("\nnome: %s\n",player.nome);
			printf("p.vita: %d\n",player.vita);
			printf("n.monete: %d\n",player.monete);
			int count=0;
			for(int i=0;i<20;i++){
				if(player.inventario->id==i){
					count++;
				}
			}
			printf("n.oggetti: %d\n",count);
			printf("missioni compiute: %d\n",player.missioni_compl);
			villaggio(&player);
			break;
		case 2:
			loadSalvataggio();
			break;
		case 3:
			ciclo=false;
			printf("Uscita\n");
			break;
		case 4:
			menuSegreto();
			break;
		}
	}
}