#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define MAX_STRING_LENGHT 20
int ID=0;

//--MOSTRI--
typedef struct mostro{
	int id;
	char nome[MAX_STRING_LENGHT];
	int vita;
	int danno;
	int monete;
}Mostro;

//--OGGETTI--da sistemare
typedef struct {
	int id;
	char nome[MAX_STRING_LENGHT];
	char descrizione[100];
	int quantita;
}Oggetto;

//--PERSONAGGIO--
typedef struct personaggio{
	char nome[MAX_STRING_LENGHT];
	int vita;
	int monete;
	Oggetto inventario[MAX_STRING_LENGHT];
	int missioni_compl;
}Personaggio;

//--SALVA--da sistemare
typedef struct salvataggio{
	int id;
	char data;
	char nome[MAX_STRING_LENGHT];
	int vita;
	int monete;
	Oggetto inventario[MAX_STRING_LENGHT];
	int missioni_compl;
	struct salvataggio* successivo;
}Save;

//--SALVA-CREA--da sistemare
static Save creaSalvataggio(Save* s){
	/*save.id=ID;
	for(int i=0;i<MAX_STRING_LENGHT;i++){
		save.nome[i]=player.nome[i];
	}
	save.vita=player.vita;
	save.monete=player.monete;
	save.missioni_compl=player.missioni_compl;
	int count;
	for(int i=0;i<20;i++){
		if(player.inventario->id<i){
			save.inventario[i]=player.inventario[i];
			count++;
		}
	}
	save.successivo=NULL;
	ID++;
	return save;*/
}


//--SALVA-CARICA--
static void loadSalvataggio(){
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

//--DOUNGEON--
static void doungeon(Personaggio *player,int scelta){
	int num_stanza=1;//le stanze possono essere vuote,con trappola,con mostro
	while(num_stanza<=10||/*chiavi raccolte!=3*/){
		//check vita giocatore
		if(num_stanza>7&&/*chiavi raccolte!=3*/){
			//stanza con orco obbligatoria
		}
		//genera stanza casuale (se negozio senza mob, con oggetti acquistabili)
	}
	//completamento missione=true
	villaggio(player);
}

//--MISSIONI--
static void missioni(Personaggio *player,int scelta){
	//da capire
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
			for(){
				//elenco missioni prob con array	
			}
			int sceltaMiss;
			if(player->missioni_compl!=3&&sceltaMiss==4){
				printf("Non sei abbastanza forte per questa missione");
				break;
			}
			missioni(player,sceltaMiss);
			break;
		case 2:
		    player->vita=20;
			printf("Salute restaurata\n");
			break;
		case 3:
			break;
		case 4:
			//creaSalvataggio();
			break;
		case 5:
			printf("Uscita\n");
			return;
		}
	}
	
}

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