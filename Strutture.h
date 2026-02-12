#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

#define MAX_STRING_LENGHT 200
#define MAX_INV 10
#define MAX_OBJS 30

extern int magioneCompl;
extern int grottaCompl;
extern int paludeCompl;

//--MOSTRI--
typedef struct mostro{
	int id;
	char nome[MAX_STRING_LENGHT];
	int vita;
	int danno;
	int monete;
}Mostro;

//--OGGETTI--
typedef struct oggetto{
	int id;
	char nome[MAX_STRING_LENGHT];
	char attributo[MAX_STRING_LENGHT];//pozione,arma,armatura
	int val_attributo;//se pozione: quanto cura, se arma: quanti danni
	char descrizione[MAX_STRING_LENGHT];
	int quantita;
}Oggetto;
extern Oggetto* listaOggetti[MAX_OBJS];
extern int numOggetti;

//--PERSONAGGIO--
typedef struct personaggio{
	char nome[MAX_STRING_LENGHT];
	int vita;
	int monete;
	Oggetto* inventario[MAX_INV];
	int missioni_compl;
}Personaggio;

void creaSalvataggio(Personaggio* p);
Personaggio loadSalvataggio(int scelta);
void printSalvataggio();
void modSalvataggio(int scelta);
Personaggio creaPersonaggio();
void menuMissioni(Personaggio *player);
void menuVillaggio();
void menu();
int dmgArmatura(Personaggio* player);
void negozio(Personaggio *player);
int missionPalude(Personaggio *player);
int combattimento( Personaggio *player,char* nomeNemico, int colpofatale, int danno, int monete);
int missionMagione(Personaggio *player);
int isPadovan(int n);
int combattimentoDrago( Personaggio *player, int colpofatale, int danno, int monete);
int missionGrotta(Personaggio *player);
void missioneFinale(Personaggio *player);
void missioni(Personaggio *player,int scelta);
void villaggio(Personaggio *player);
int inventarioFull(Personaggio *p);
void addOggetto(Personaggio *p, Oggetto *o);
int trovaSlot(Personaggio *p);
void scartaOggetto(Personaggio *p, int slot);
void raccogliOggetto(Personaggio *p, Oggetto *nuovo);
Oggetto* creaOggetto(int id,const char* nome, const char* descrizione, const char* attributo, int val_att,int quantita);
void riempiArrObj();
int main();