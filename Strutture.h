#define MAX_STRING_LENGHT 20
#include <stdio.h>
#include <stdlib.h>

//--MOSTRI--
typedef struct mostro{
	int id;
	char nome[MAX_STRING_LENGHT];
	int vita;
	int danno;
	int monete;
}Mostro;

//--OGGETTI--dovrá essere una lista
typedef struct oggetto{
	int id;
	char nome[MAX_STRING_LENGHT];
	char attributo;//pozione,arma,armatura
	int val_attributo;
	char descrizione[100];
	int quantita;
	struct Oggetto* next;
}Oggetto;
Oggetto headOggetto=malloc(sizeof(Oggetto));

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
	struct Save* next;
}Save;
Save headSave=malloc(sizeof(Save));
headSave.id=0;

static Save* creaSalvataggio(Save* s);
static void loadSalvataggio();
static Personaggio* creaPersonaggio();
static void menuSegreto();
static void menuMissioni(int scelta);
static void menuVillaggio();
static void menu();
static void doungeon(Personaggio *player,int scelta);
static void missioni(Personaggio *player,int scelta);
static void villaggio(Personaggio *player);