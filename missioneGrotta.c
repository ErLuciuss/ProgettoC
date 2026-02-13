#include "strutture.h"

int isPadovan(int n){
    int Padovan[] = {1,1,1,2,2,3,4,5,7,9,12,16,21,28,37,49,65,86,
        114,151,200,265,351,465};
    
    int size = sizeof(Padovan)/sizeof(int);

    for(int i=0; i < size; i++){
        if(n == Padovan[i]){
            return 1;
        }
    }
    return 0;
}

int combattimentoDrago(Personaggio *player, int colpofatale, int danno, int monete){
    int dmgSpada=0;
    printf("L'eroe incontra il Drago Antico e inizia il combattimento.\n");
    while(player->vita > 0){

        dmgSpada = 0;
        for(int i=0;i<MAX_INV;i++){
            if(player->inventario[i]!=NULL){
                if(strcmp(player->inventario[i]->attributo, "arma") == 0){
                    dmgSpada = player->inventario[i]->val_attributo;//se si ha un arma il valore del danno sarà incrementato con l'attributo della spada
                }
            }
        }

        int dado = 1 + rand() % 6 + dmgSpada;

        
        printf("Viene lanciato un dado per stabilire l'attacco dell'eroe.\n Il risultato è %d\n", dado);

        if(dado >= colpofatale){
            printf("L'eroe sconfigge il drago!\n");

            player->monete += monete;
            printf("Guadagna %d monete. Monete totali: %d\n", monete, player->monete);
            printf("L'eroe ha guadagnato la spada dell'eroe!\n");


            Oggetto *o = creaOggetto(
                listaOggetti[0]->id,
                listaOggetti[0]->nome,
                listaOggetti[0]->descrizione,
                listaOggetti[0]->attributo,
                listaOggetti[0]->val_attributo,
                listaOggetti[0]->quantita
            );
            raccogliOggetto(player,o);

            printf("\nMissione Completata!\n");
            player->missioni_compl++;

            return 1;
        }
        else{
            int numero = 1 + rand() % 500;
            char risposta[10];

            printf("Il drago chiede: %d appartiene alla sequenza di Padovan (Si/No)?\n", numero);

            fgets(risposta,sizeof(risposta),stdin);
            risposta[strcspn(risposta,"\n")] = 0;

            int corretta = isPadovan(numero);

            int dmg = danno - dmgArmatura(player);
            if(dmg < 0) dmg = 0;//se il danno è minore dell' attributo dell'aramtura, viene settato a 0, altimenti risulta negativo

            if(
                (corretta && (strcmp(risposta,"si")==0)) ||
                (!corretta && (strcmp(risposta,"no")==0))
            ){
                printf("Risposta corretta! L'eroe non subisce danni!\n");
            }
            else{
                printf("Risposta sbagliata!\n");
                player->vita -= dmg;
                printf("l'eroe subisce %d danni. Punti vita rimasti: %d\n", dmg, player->vita);
            }
        }
    }

    printf("\n=== GAME OVER ===\n");
    return 0;
}

int missionGrotta(Personaggio *player){
    int scelta;
    int fineMissione = 0;
    int stanzeEsplorate = 0;

    printf("\n=== GROTTA DI CRISTALLO ===\n");
    sleep(1);
    printf("Obiettivo: Sconfiggi il drago e recupera la spada dell'eroe.\n");

    while(!fineMissione){
        printf("\n--- Menu Missione ---\n");
        sleep(1);
        printf("1) Esplora stanza del Dungeon\n");
        sleep(1);
        printf("2) Negozio\n");
        sleep(1);
        printf("3) Inventario\n");
        sleep(1);
        printf("4) Torna al Villaggio\n");
        sleep(1);
        printf("Seleziona una delle opzioni del menu [1-4]: ");
        scanf("%d",&scelta);
        while(getchar()!='\n');

        switch(scelta){

            case 1:
                stanzeEsplorate++;
                printf("\nStanza %d - ", stanzeEsplorate);

                if(stanzeEsplorate == 10){
                    printf("Drago Antico\n");

                    if(combattimentoDrago(player,5,10,12)){
                        fineMissione = 1;
                        return 1;
                    }else{
                        return -1;
                    }
                }

                int dado = 1 + rand() % 6;

                switch(dado){

                    case 1:
                        printf("Stanza vuota\n");
                        printf("La stanza non contiene nulla, l'eroe torna indietro"); //torna al menù  

                        break;

                    case 2:{
                        printf("Cristalli Cadenti\n"); //trappola
                        int dmg = 2 - dmgArmatura(player);
                        if(dmg < 0) dmg = 0;
                        player->vita -= dmg;
                        printf("L'eroe viene colpito da una trappola!\n");
                        printf("Subisce %d danni! Punti vita rimasti: %d\n", dmg, player->vita);
                        if(player->vita<=0) return -1;
                        break;
                    }

                    case 3:
                        printf("Ponte Pericolante\n");//trappola
                        player->monete -= 3;
                        if(player->monete < 0) player->monete = 0;
                        printf("Perde 3 monete! Monete rimaste: %d\n", player->monete);
                        break;

                    case 4:{
                        printf("Forziete Misterioso\n"); //trappola ---  lancia moneta
                        printf("L'eroe ha trovato un forziere\n");
                        printf("Lancia una moneta per aprirlo\n");
                        int moneta = rand()%2;
                        if(moneta==0){
                            player->monete+=10;
                            printf("È uscita Testa! Guadagna 10 monete\n");

                        }else{
                            int dmg = 2 - dmgArmatura(player);
                            if(dmg < 0) dmg = 0;
                            player->vita -= dmg;
                            printf("È uscita Croce! Subisce %d danni. Punti vita rimasti: %d\n", dmg, player->vita);

                            if(player->vita<=0) return -1;
                        }
                        break;
                    }

                    case 5:{
                        printf("Rupe scoscesa\n");//trappola
                        int dmg = (1+rand()%6) - dmgArmatura(player);
                        if(dmg < 0) dmg = 0;
                        player->vita -= dmg;
                        printf("Subisce %d danni! Punti vita rimasti: %d\n", dmg, player->vita);
                        if(player->vita<=0) return -1;
                        break;
                    }

                    case 6:
                        printf("Drago Antico\n");
                        if(combattimentoDrago(player,5,10,12)){
                            fineMissione=1;
                        }else{
                            return -1;
                        }
                }
                break;

            case 2:
                negozio(player);
                break;

            case 3:
                for(int i=0;i<MAX_INV;i++){
                    if(player->inventario[i])
                        printf("%s\n",player->inventario[i]->nome);
                }
                break;

            case 4:
                if(fineMissione==1){
                    sleep(1);
                    printf("Tornando al villaggio.");
                    fflush(stdout);
                    sleep(1);
                    printf(".");
                    fflush(stdout);
                    sleep(1);
                    printf(".\n");
                    return 1;
                }
                if(player->monete>=50){
                    printf("Vuoi pagare 50 monete per tonrare al villaggio? Si/No\n");
                    char ris[10];
                    while(getchar()!='\n');
                    fgets(ris,sizeof(ris),stdin);
                    ris[strlen(ris) -1]= '\0';
                    if(strcmp(ris,"si")==0 || strcmp(ris,"Si")==0 || strcmp(ris,"SI")==0){
                        player->monete-=50;
                        sleep(1);
                        printf("Tornando al villaggio.");
                        fflush(stdout);
                        sleep(1);
                        printf(".");
                        fflush(stdout);
                        sleep(1);
                        printf(".\n");
                        return 0;
                    }
                }else{
                    printf("Monete insufficienti\n");
                }
                break;

            default:
                printf("Scelta non valida\n");
        }
    }
    return 0;
}
