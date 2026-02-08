#include "Strutture.h"
Oggetto* listaOggetti[MAX_OBJS];
int numOggetti=0;

//--MISSIONI-MENU--
void menuMissioni(int scelta){
	printf("----------------Missioni-----------------\n");
	
	printf("-----------------------------------------\n");
}

//--VILLAGGIO-MENU--
void menuVillaggio(){
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
void menu(){
	printf("---------------DungeonKnight---------------\n");
	printf("Scegliere un'opzione tra le seguenti(1|2|3)\n");
	printf("1)Nuova Partita\n");
	printf("2)Carica Partita\n");
	printf("3)Esci\n");
	printf("--------------------------------------------\n");
}

//--SALVA-CREA--
void creaSalvataggio(Personaggio* p) {
    int id = 0;
    FILE *lookSave = fopen("savefile.txt", "r");
    FILE *createSave = fopen("savefile.txt", "a");

    if (createSave == NULL) {
        perror("Errore apertura file");
        return;
    }

    // Se il file esiste, leggi l'ultimo ID
    if (lookSave != NULL) {
        char *line = NULL;
        size_t len = 0;
        int temp_id;

        while (getline(&line, &len, lookSave) != -1) {
            if (sscanf(line, "%d", &temp_id) == 1) {
                id = temp_id;  // tiene l'ultimo
            }
        }
        free(line);
        fclose(lookSave);
    }
    id++; // nuovo salvataggio

    //mi salvo la data e l'ora del salvataggio
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char dataOra[64];
    strftime(dataOra, sizeof(dataOra), "%d/%m/%Y %H:%M:%S", t);

    // Scrittura dati base
    fprintf(createSave,"%d | %s | %dhp | monete:%d | missioni completate:%d | ",
            id,
            p->nome,
            p->vita,
            p->monete,
            p->missioni_compl);

    // Scrittura inventario
    for(int i = 0; i < 10; i++){
		if(p->inventario[i] != NULL){
			fprintf(createSave,"[%d|%s|%d] ",
				p->inventario[i]->id,
				p->inventario[i]->nome,
				p->inventario[i]->quantita);
		}
	}

    fprintf(createSave,"| %s\n",dataOra);
    fclose(createSave);
}


//--SALVA-CARICA--
Personaggio loadSalvataggio(int scelta){
	Personaggio p;
    FILE *lookSave = fopen("savefile.txt", "r");

    if (lookSave == NULL) {
        perror("Errore apertura file");
        exit(EXIT_FAILURE);
    }
    char line[400];
    int id_save;
    // Vai alla riga scelta
    for (int i = 1; i <= scelta; i++) {
        if (fgets(line, sizeof(line), lookSave) == NULL) {
            fclose(lookSave);
            printf("Salvataggio non esistente\n");
            exit(EXIT_FAILURE);
        }
    }
    // Leggi i dati
    if (sscanf(line, "%d %199s %dhp monete:%d missioni completate:%d",
               &id_save,
               p.nome,
               &p.vita,
               &p.monete,
               &p.missioni_compl) != 5) {
        fclose(lookSave);
        printf("Errore formato file\n");
        exit(EXIT_FAILURE);
    }
    // Inizializza inventario
    for (int i = 0; i < 10; i++) {
        p.inventario[i] = NULL;
    }

	char *ptr = line;
    while((ptr = strchr(ptr,'[')) != NULL){
        Oggetto *o = malloc(sizeof(Oggetto));
        sscanf(ptr,"[%d|%[^|]|%d]",
               &o->id,
               o->nome,
               &o->quantita);
        addOggetto(&p,o);
        ptr++;
    }

    fclose(lookSave);
    return p;
}

//--SALVA-STAMPA--
void printSalvataggio(){
	FILE *lookSave=fopen("savefile.txt","r");
	if(lookSave==NULL){
		printf("File Vuoto\n");
		return;
	}
	char *line=NULL;
	size_t len=0;
	while(getline(&line,&len,lookSave)!=-1){
		printf("%s",line);
	}
	fclose(lookSave);
	return;
}

//--OGGETTO-CREA--
Oggetto* creaOggetto(int id,const char* nome, const char* descrizione, const char* attributo, int val_att,int quantita){
    Oggetto* o = malloc(sizeof(Oggetto));
    if(!o){
        return NULL;
    }
    o->id=id;
    strncpy(o->nome, nome, MAX_STRING_LENGHT);
    o->nome[MAX_STRING_LENGHT-1] = '\0';
    strncpy(o->descrizione, descrizione, MAX_STRING_LENGHT);
    o->descrizione[MAX_STRING_LENGHT-1] = '\0';
    strncpy(o->attributo, attributo, MAX_STRING_LENGHT);
    o->attributo[MAX_STRING_LENGHT-1] = '\0';
    o->val_attributo = val_att;
    o->quantita = quantita;
    return o;
}

//--OGGETTO-RIEMPI-ARRAY--
void riempiArrObj(){
    FILE* lookObj=fopen("oggetti.txt","r");
    if (!lookObj) {
        perror("Errore apertura file");
        exit(EXIT_FAILURE);
    }
    char line[256];
    while(fgets(line, sizeof(line), lookObj) && numOggetti < MAX_OBJS){
        int id, v_att, qnt;
        char nome[MAX_STRING_LENGHT];
        char att[MAX_STRING_LENGHT];
        char desc[MAX_STRING_LENGHT];

        if(sscanf(line, "%d %s %s %d [%[^]]] %d",&id, nome, att, &v_att, desc, &qnt) == 6){
            listaOggetti[numOggetti] = creaOggetto(id, nome, desc, att, v_att, qnt);
            numOggetti++;
        }
    }
    fclose(lookObj);
}

//--INVENTARIO-TROVA-SLOT--
int trovaSlot(Personaggio *p){
    for(int i=0;i<MAX_INV;i++){
        if(p->inventario[i]==NULL)
            return i;
    }
    return -1;
}

//--INVENTARIO-PIENO--
int inventarioFull(Personaggio *p){
    return trovaSlot(p) == -1;
}

//--INVENTARIO-AGGIUNGI-OGGETTO--
void addOggetto(Personaggio *p, Oggetto *o){
    int slot = trovaSlot(p);
    if(slot != -1)
        p->inventario[slot] = o;
}

//--INVENTARIO-SCARTA-OGGETTO--
void scartaOggetto(Personaggio *p, int slot){
    if(slot<0 || slot>=MAX_INV || p->inventario[slot]==NULL)
        return;

    free(p->inventario[slot]);
    p->inventario[slot] = NULL;
}

//--INVENTARIO-RACCOGLI-OGGETTO--
void raccogliOggetto(Personaggio *p, Oggetto *new) {

    // check duplicati, se presenti ne nomma le quantità
    for (int i = 0; i < MAX_INV; i++) {
        if (p->inventario[i] != NULL &&
            strcmp(p->inventario[i]->nome, new->nome) == 0) {
            p->inventario[i]->quantita += new->quantita;
            printf("Hai aggiunto %d %s! Ora ne hai %d\n",new->quantita,new->nome,p->inventario[i]->quantita);
            free(new); // l'oggetto temporaneo non serve più
            return;
        }
    }

    int slot = trovaSlot(p);
    if (slot != -1) {
        p->inventario[slot] = new;
        printf("Hai trovato %s!\n", new->nome);
        return;
    }

    // Nel caso di inventario pieno, lo stampa e chiede cosa si vuole fare
    printf("\nInventario pieno!\n");
    for (int i = 0; i < MAX_INV; i++) {
        printf("%d %s | quantità: %d\n", i + 1,p->inventario[i]->nome,p->inventario[i]->quantita);
    }
    printf("0 Lascia oggetto\nScelta: ");

    int scelta;
    scanf("%d", &scelta);
    while (getchar() != '\n'); // svuota buffer
    if (scelta == 0) {
        free(new);
        printf("Oggetto lasciato.\n");
        return;
    }
    // Sostituzione dell'oggetto scelto
    if (scelta > 0 && scelta <= MAX_INV) {
        scartaOggetto(p, scelta - 1);
        p->inventario[scelta - 1] = new;
        printf("Oggetto sostituito!\n");
    } else {
        printf("Scelta non valida, oggetto lasciato.\n");
        free(new);
    }
}

//--PERSONAGGIO-CREA--
Personaggio creaPersonaggio(){
	
	Personaggio p;
	printf("Nome:\n");
	scanf("%s",(char*)p.nome);
    while(getchar() != '\n'); // svuota buffer
	p.vita=20;
	p.monete=0;
	p.missioni_compl=0;

	for(int i=0;i<MAX_INV;i++){
		p.inventario[i]=NULL;
	}

	return p;
}

//--DOUNGEON--
void doungeon(Personaggio *p,int scelta){
	
}

/*--DOUNGEON-FINALE--
void finalDoungeon(){

}*/

//--MISSIONI--
void missioni(Personaggio *p,int scelta){
	//da capire
	//scelta dei doungeon
}


//--VILLAGGIO--
void villaggio(Personaggio *p){
	char scelta;
	char invio;
	bool ciclo2=true;
	while(ciclo2){
		menuVillaggio();
		scelta=getchar();
    	while(getchar() != '\n'); // svuota buffer
		printf("-----------------------------------------\n");
		switch(scelta){
		case '1':{
			printf("Le missioni sono momentaneamente disabilitate\n");
            Oggetto* nuovo = creaOggetto(
            listaOggetti[0]->id,
            listaOggetti[0]->nome,
            listaOggetti[0]->descrizione,
            listaOggetti[0]->attributo,
            listaOggetti[0]->val_attributo,
            listaOggetti[0]->quantita
            );
            printf("%d\n",listaOggetti[0]->id);
            printf("%d\n",nuovo->id);
            raccogliOggetto(p,nuovo);
			//intraprendi missione
			break;
		}
		case '2':{
		    p->vita=20;
			printf("Salute restaurata\n");
			break;
		}
		case '3':{
			if(p->inventario[0]==NULL){
				printf("Inventario Vuoto\n");
				break;
			}
			for(int i=0;i<MAX_INV;i++){
				if(p->inventario[i]!=NULL)
					printf("%s | %d\n", p->inventario[i]->nome,p->inventario[i]->quantita);
			}
			break;
		}
		case '4':{
			printf("Salvataggio partita.");
			fflush(stdout);
			sleep(1);
			printf(".");
			fflush(stdout);
			sleep(1);
			printf(".\n");
            creaSalvataggio(p);
			break;
		}
		case '5':{
			ciclo2=false;
			printf("Ritorno al menù principale.");
			fflush(stdout);
			sleep(1);
			printf(".");
			fflush(stdout);
			sleep(1);
			printf(".\n");
			//crea un "autosalvtaggio" in caso si torni al menù senza salvare
			creaSalvataggio(p);
			return;
		}
		}
	}
	
}