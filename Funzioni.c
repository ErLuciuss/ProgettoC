#include "Strutture.h"
Oggetto* listaOggetti[MAX_OBJS];
int numOggetti=0;
int magioneCompl=0;
int grottaCompl=0;
int paludeCompl=0;
bool canSave=false;

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
    fprintf(createSave,"%d | %s | %dhp | monete:%d | %d | %d | %d | ",
            id,
            p->nome,
            p->vita,
            p->monete,
            paludeCompl,
            magioneCompl,
            grottaCompl
        );

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
    canSave=true;
    // Leggi i dati
    if (sscanf(line, "%d | %199s | %dhp | monete:%d | %d | %d | %d | ",
               &id_save,
               p.nome,
               &p.vita,
               &p.monete,
               &paludeCompl,
               &magioneCompl,
               &grottaCompl) != 7) {
        fclose(lookSave);
        printf("Errore formato file\n");
        exit(EXIT_FAILURE);
    }
    p.missioni_compl=paludeCompl+magioneCompl+grottaCompl;
    // Inizializza inventario
    for (int i = 0; i < 10; i++) {
        p.inventario[i] = NULL;
    }

	char *obj = line;
    while((obj = strchr(obj,'[')) != NULL){
        Oggetto *o = malloc(sizeof(Oggetto));
        sscanf(obj,"[%d|%[^|]|%d]",
               &o->id,
               o->nome,
               &o->quantita);
        addOggetto(&p,listaOggetti[o->id-1]);
        obj++;
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

//--SALVA-SOVRASCRIVI--
void sovrascriviSalvataggio(int index, Personaggio *p){

    FILE *lookFile = fopen("savefile.txt", "r");
    FILE *modFile = fopen("temp.txt", "w");

    if(!lookFile || !modFile){
        perror("Errore file");
        return;
    }

    char line[500];
    int id;

    while(fgets(line, sizeof(line), lookFile)){

        if(sscanf(line, "%d", &id) == 1 && id == index){

            time_t now = time(NULL);
            struct tm *t = localtime(&now);
            char dataOra[64];
            strftime(dataOra, sizeof(dataOra), "%d/%m/%Y %H:%M:%S", t);

            fprintf(modFile,"%d | %s | %dhp | monete:%d | %d | %d | %d | ",
                id,
                p->nome,
                p->vita,
                p->monete,
                paludeCompl,
                magioneCompl,
                grottaCompl
            );

            for(int i=0;i<MAX_INV;i++){
                if(p->inventario[i]){
                    fprintf(modFile,"[%d|%s|%d] ",
                        p->inventario[i]->id,
                        p->inventario[i]->nome,
                        p->inventario[i]->quantita);
                }
            }

            fprintf(modFile,"| %s\n", dataOra);
        }
        else{
            fputs(line, modFile); // copia riga originale
        }
    }

    fclose(lookFile);
    fclose(modFile);

    remove("savefile.txt");
    rename("temp.txt", "savefile.txt");
}

//--SALVA-MODIFICA--
void modSalvataggio(int scelta){
    Personaggio p = loadSalvataggio(scelta);

    FILE *lookSave = fopen("savefile.txt","r");
    if(!lookSave){
        printf("File Vuoto\n");
        return;
    }

    char line[400];
    for(int i=1;i<=scelta;i++){
        if(!fgets(line,sizeof(line),lookSave)){
            printf("Salvataggio non esistente\n");
            fclose(lookSave);
            return;
        }
    }
    p=loadSalvataggio(scelta);
    fclose(lookSave);

    printf("%s\n", line);

    bool loop = true;
    while(loop){
        printf("\nCosa modificare?\n");
        printf("1 Nome\n");
        printf("2 Vita\n");
        printf("3 Soldi\n");
        printf("4 Missioni completate\n");
        printf("5 Inventario\n");
        printf("0 Conferma ed esci\n");
        printf("Scelta: ");

        char modChoise = getchar();
        while(getchar()!='\n');

        switch(modChoise){
            case '1':{
                printf("Nuovo nome: ");
                scanf("%199s", p.nome);
                while(getchar()!='\n');
                break;
            }
            case '2':{
                printf("Nuova vita: ");
                scanf("%d", &p.vita);
                while(getchar()!='\n');
                break;
            }
            case '3':{
                printf("Nuovi soldi: ");
                scanf("%d", &p.monete);
                while(getchar()!='\n');
                break;
            }
            case '4':{
                bool ciclo=true;
                char* scelta=(char*)malloc(sizeof(char));
                while(ciclo){
                    printf("Scegliere cosa modificare valore delle missioni:\nPalude:%d\nMagione:%d\nGrotta:%d\n0)fine modifica\n",paludeCompl,magioneCompl,grottaCompl);
                    scanf(" %s",scelta);
                    while(getchar()!='\n');
                    if(strcmp(scelta, "0") == 0){
                        ciclo=false;
                        p.missioni_compl=paludeCompl+magioneCompl+grottaCompl;
                        break;
                    }else if(strcmp(scelta, "Palude") == 0||strcmp(scelta, "palude") == 0){
                        if(paludeCompl==0){
                            paludeCompl=1;
                        }else{
                            paludeCompl=0;
                        }
                    }else if(strcmp(scelta, "Magione") == 0||strcmp(scelta, "magione") == 0){
                        if(magioneCompl==0){
                            magioneCompl=1;
                        }else{
                            magioneCompl=0;
                        }
                    }else{
                        if(grottaCompl==0){
                            grottaCompl=1;
                        }else{
                            grottaCompl=0;
                        }
                    }
                    
                }
                break;
            }
            case '5':{
                modInventario(&p);
                break;
            }
            case '0':
                loop = false;
                break;
        }
    }
    sovrascriviSalvataggio(scelta,&p);
    villaggio(&p);
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

        if(sscanf(line, "%d [%[^]]] %s %d [%[^]]] %d",&id, nome, att, &v_att, desc, &qnt) == 6){
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

    //quando verrà trovata la sapda dell'eroe, essa sostituisce la spada già presente nell'inventario
    for(int i=0;i<MAX_INV;i++){
                if(p->inventario[i]!=NULL){
                    if(strcmp(p->inventario[i]->attributo, "arma") == 0){
                        p->inventario[i]=new;
                    }
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

//--INVENTARIO-AGGIUNGI-OGGETTO-MODIFICA--
void addObjInventario(Personaggio *p){

    printf("\n--- Oggetti disponibili ---\n");

    for(int i=0;i<numOggetti;i++){
        printf("%d) %s | %s | base q:%d\n",
               i+1,
               listaOggetti[i]->nome,
               listaOggetti[i]->attributo,
               listaOggetti[i]->quantita);
    }

    printf("0 Annulla\nScelta: ");

    char scelta = getchar();

    if(scelta == '0') return;

    int idx = scelta - '1';

    if(idx < 0 || idx >= numOggetti){
        printf("Scelta non valida\n");
        return;
    }

    int qnt;
    if(strcmp(listaOggetti[idx]->attributo, "armatura") == 0||strcmp(listaOggetti[idx]->attributo, "arma") == 0){
        qnt=1;
    }else{
        printf("Quantità da aggiungere: ");
        scanf("%d",&qnt);
        while(getchar()!='\n');
    }

    Oggetto *nuovo = creaOggetto(
        listaOggetti[idx]->id,
        listaOggetti[idx]->nome,
        listaOggetti[idx]->descrizione,
        listaOggetti[idx]->attributo,
        listaOggetti[idx]->val_attributo,
        qnt
    );

    raccogliOggetto(p, nuovo);
}

//--INVENTARIO-MODIFICA--
void modInventario(Personaggio *p){

    bool loop = true;
    while(loop){
        printf("\n--- Inventario ---\n");

        for(int i=0;i<MAX_INV;i++){
            if(p->inventario[i])
                printf("%d) %s | q:%d | at:%s\n", i+1,
                        p->inventario[i]->nome,
                        p->inventario[i]->quantita,
                        p->inventario[i]->attributo);
            else
                printf("%d) [vuoto]\n", i+1);
        }
        printf("A) Aggiungi oggetto\n");
        printf("0 Torna indietro\n");
        printf("Scelta: ");

        char scelta = getchar();
        if(scelta == 'A' || scelta == 'a'){
            addObjInventario(p);
            continue;
        }
        while(getchar()!='\n');
        if(scelta == '0'){
            loop = false;
            break;
        }

        int slot = scelta - '1';

        if(slot < 0 || slot >= MAX_INV || p->inventario[slot] == NULL){
            printf("Slot non valido\n");
            continue;
        }

        printf("\nOggetto: %s\n", p->inventario[slot]->nome);
        printf("1 Cambia quantità\n");
        printf("2 Elimina oggetto\n");
        printf("0 Annulla\n");
        printf("Scelta: ");

        char azione = getchar();
        while(getchar()!='\n');

        switch(azione){
            case '1':{
                if(strcmp(p->inventario[slot]->nome ,"armatura") == 0||strcmp(p->inventario[slot]->attributo, "arma") == 0){
                    printf("Quantità non modificabile");
                    break;
                }else{
                    printf("Nuova quantità: ");
                    scanf("%d", &p->inventario[slot]->quantita);
                    while(getchar()!='\n');
                    break;
                }
            }

            case '2':{
                free(p->inventario[slot]);
                p->inventario[slot] = NULL;
                printf("Oggetto rimosso\n");
                break;
            }

            case '0':
                break;
        }
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
    canSave=true;
	return p;
}

//--DANNO-ARMATURA--
int dmgArmatura(Personaggio* player){
    for(int i=0;i<MAX_INV;i++){
        if(player->inventario[i]!=NULL){
            if(strcmp(player->inventario[i]->attributo, "armatura") == 0){
                return player->inventario[i]->val_attributo;
            }
        }
    }
    return 0;
}


//--VILLAGGIO--
void villaggio(Personaggio *p){
	char scelta;
	char invio;
	bool ciclo2=true;
	while(ciclo2){
		menuVillaggio();
		scanf("%c",&scelta);
		printf("-----------------------------------------\n");
		switch(scelta){
		case '1':{
            menuMissioni(p);
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
					printf("%s | %d | %s\n", p->inventario[i]->nome,p->inventario[i]->quantita,p->inventario[i]->descrizione);
			}
			break;
		}
		case '4':{
            sleep(1);
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
			return;
		}
		}
	}
	
}