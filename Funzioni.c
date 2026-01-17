#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "Strutture.h"

//--MENU-SEGRETO--
static void menuSegreto(){

}

//--MISSIONI-MENU--
static void menuMissioni(int scelta){
	printf("----------------Missioni-----------------\n");
	
	printf("-----------------------------------------\n");
}

//--VILLAGGIO-MENU--
static void menuVillaggio(){
	printf("--------------MenuVillaggio--------------\n");
	printf("Scegliere un'opzione tra le seguenti(1|5)\n");
	printf("1)Intraprendi missione\n");
	printf("2)Riposati\n");
	printf("3)Inventario\n");
	printf("4)Salva la parita\n");
	printf("5)Torna al menu principale\n");
	printf("-----------------------------------------\n");
}

//--DEFAULT-MENU--
static void menu(){
	printf("---------------DungeonKnight---------------\n");
	printf("Scegliere un'opzione tra le seguenti(1|2|3)\n");
	printf("1)Nuova Partita\n");
	printf("2)Carica Partita\n");
	printf("3)Esci\n");
	printf("--------------------------------------------\n");
}

//--TRUCCHI--
static void cheats(){

}

//--SALVA-CREA--
static Save creaSalvataggio(Save* s){
	Save* save=malloc(sizeof(Save));
	save->id=headSave->id+1;
	save->

}


//--SALVA-CARICA--
static void loadSalvataggio(){
	
}

//--SALVA-STAMPA--
static void printSalvataggio(){

}

//--PERSONAGGIO-CREA--
static Personaggio creaPersonaggio(){
	Personaggio player;
	printf("Nome:\n");
	scanf("%s",player.nome);
	player.vita=20;
	player.monete=0;
	player.missioni_compl=0;
	return player;
}

//--DOUNGEON--
static void doungeon(Personaggio *player,int scelta){
	
}

//--DOUNGEON-FINALE--
static void finalDoungeon(){

}

//--MISSIONI--
static void missioni(Personaggio *player,int scelta){
	//da capire
	//scelta dei doungeon
}

//--VILLAGGIO--
static void villaggio(Personaggio *player){
	int scelta;
	bool ciclo2=true;
	while(ciclo2){
		menuVillaggio();
		scanf("%d",&scelta);
		switch(scelta){
		case 1:
			//intraprendi missione
			break;
		case 2:
		    player->vita=20;
			printf("Salute restaurata\n");
			break;
		case 3:
			break;
		case 4:
			/*Save salva=NULL
			creaSalvataggio(salva);*/
			break;
		case 5:
			printf("Uscita\n");
			return;
		}
	}
	
}