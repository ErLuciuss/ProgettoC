#define MAX_STRING_LENGHT 20

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
	char attributo;
	int val_attributo;
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

static Save creaSalvataggio(Save* s);
static void loadSalvataggio();
static Personaggio creaPersonaggio();
static void menuSegreto();
static void menuMissioni(int scelta);
static void menuVillaggio();
static void menu();
static void doungeon(Personaggio *player,int scelta);
static void missioni(Personaggio *player,int scelta);
static void villaggio(Personaggio *player);