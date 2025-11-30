#include <stdio.h>
#include <stdbool.h>
#include <string.h>

struct inventario{
	int id;
	char nome[10];
	char descrizione[100];
	int quantita;
};

struct personaggio{
	char nome[5];
	int vita;
	int monete;
	struct inventario oggetti[20];
	int missioni_compl;
};

static void creaPersonaggio(){
	struct personaggio player;
	player.oggetti.id=1;
	printf("%d\n",player.oggetti.id);
}

static void menuSegreto(){
	/*printf("");
	printf("");
	printf("");
	printf("");
	printf("");
	printf("");
	printf("");
	printf("");*/
}

static void menu(){
	printf("--------------DungeonKnight--------------\n");
	printf("Scegliere un'opzione tra le seguenti(1|2|3)\n");
	printf("Nuova Partita\n");
	printf("Carica Partita\n");
	printf("Esci\n");
	printf("-----------------------------------------\n");
}

int main(){
	int scelta=0;
	bool ciclo=true;
	while(ciclo){
		menu();
		scanf("%d",&scelta);
		switch(scelta){
		case 1:
			creaPersonaggio();
			break;
		case 2:
			printf("suca2\n");
			break;
		case 3:
			ciclo=false;
			printf("Uscita\n");
			break;
		case 4:
			printf("secret\n");
			break;
		}
	}
}