#include "Strutture.h"

/*da fare:
scrivere meglio i printf
aggiungere il bonus attacco nella struttura
cambia spada se equipaggiata
aggiusta la roba exit (167)

rendila int così fai se bla bla == 1 -> elimini*/

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

int combattimentoDrago( Personaggio *player, int colpofatale, int danno, int monete){
    int dmgSpada=0;
    while(player->vita > 0){ //finchè il personaggio è in vita
        for(int i=0;i<MAX_INV;i++){
            if(player->inventario[i]!=NULL){
                if(strcmp(player->inventario[i]->attributo, "arma") == 0){
                    dmgSpada=player->inventario[i]->val_attributo;
                }
            }
        }
        int dado = 1 + rand() % 6+ dmgSpada;
        

        printf("viene lanciato un dado per stabilire l'attacc0 dell'eroe: %d\n", dado);

        if(dado > colpofatale){
            printf("Hai sconfitto il drago!\n");
            player->monete += monete;
            printf("Guadagni %d monete. Monete totali: %d\n", monete, player->monete);
            printf("Hai guadagnato la spada dell'eroe (thats nerd af bro...)");
            Oggetto* o;
            o=creaOggetto(listaOggetti[0]->id,listaOggetti[0]->nome,listaOggetti[0]->descrizione,listaOggetti[0]->attributo,listaOggetti[0]->val_attributo,listaOggetti[0]->quantita);
            raccogliOggetto(player,o);
            return 1; //vittoria torni al "menù" missioni
        }else{
            int numero = 1 + rand() % 500;
            char risposta[3]; 

            printf("Il drago chiede: %d appartiene alla sequenza di Padovan (Si/No)?\n", numero);

            fgets(risposta, sizeof(risposta), stdin);
            risposta[strlen(risposta) -1]= '\0';

            int corretta = isPadovan(numero);

            if(strcmp(risposta,"si")!=0 && strcmp(risposta,"Si")!=0 &&
               strcmp(risposta,"no")!=0 && strcmp(risposta,"No")!=0){
                    printf("Risposta non valida! Considerata errata.\n");
                    player->vita -= (danno-dmgArmatura(player));
                    printf("Subisci %d danni. Vita rimasta: %d\n", (danno-dmgArmatura(player)), player->vita);
                } 
            else if((corretta && (strcmp(risposta,"si")==0 || strcmp(risposta,"Si")==0)) ||
               (!corretta && (strcmp(risposta,"no")==0 || strcmp(risposta,"No")==0))){
                printf("Risposta corretta! Non subisci danni\n");

            }else{ 
                printf("Risposta sbagliata!\n");
                player -> vita -= (danno-dmgArmatura(player));
            printf("Subisci %d danni. Vita rimasta: %d\n", (danno-dmgArmatura(player)), player->vita);
            }
        }
    }
    printf("\n=== GAME OVER ===\n"); //se esci dal loop e quindi la vita e 0 o meno
    return 0;
}




int missionGrotta(Personaggio *player){
    int scelta;
    int fineMissione = 0;
    int stanzeEsplorate = 0;
    int spada = 0;

    printf("\n=== GROTTA DI CRISTALLO ===\n");
    printf("Obiettivo: Recupera la Spada dell'Eroe.\n");

    while(!fineMissione){
        printf("\n--- Menu Missione ---\n");
        printf("1) Esplora stanza del Dungeon\n");
        printf("2) Negozio\n");
        printf("3) Inventario\n");
        printf("4) Torna al Villaggio\n");
        printf("Scelta: ");
        scanf("%d", &scelta);

        switch(scelta){
            case 1:
                printf("Esplori una stanza del Dungeon...\n");

                stanzeEsplorate++;
                
                if(stanzeEsplorate == 10){
                    if(!spada){
                        printf("Drago Antico\n");//combattimento
                        if(combattimentoDrago(player, 5, 10, 12)){
                            spada = 1;
                            printf("Hai ottenuto la spada dell'eroe!\n");
                            }
                        } continue;
                    }

                int dado =1 + rand() % 6;

                printf("\nStanza %d - ", stanzeEsplorate);

                switch(dado){
                    case 1: 
                        printf("La stanza Vuota\n"); //torna al menù
                        
                        break;

                    case 2: 
                        printf("Cristalli Cadenti\n"); //trappola
                        player->vita-=2;
                        printf("Subisci 2 danni! Vita rimasta: %d\n", player->vita);
                        break;

                    case 3:
                        printf("Ponte Pericolante\n");//trappola
                        player->monete-=3;
                        printf("Perdi 3 monete! Monete rimaste: %d\n", player->monete);
                        break;

                    case 4:
                        printf("Forziete Misterioso\n"); //trappola ---  lancia moneta
                        printf("Lancia la moneta\n");
                            int moneta = rand() % 2;
                            if(moneta == 0){
                                printf("È uscita Testa! Guadagni 10 monete\n");
                                player->monete += 10;
                            } else{
                                printf("È uscita Croce! Subisci 2 danni\n");
                                player->vita -= 2;
                            }


                        break;

                    case 5:
                        printf("Rupe scoscesa\n");//trappola
                            int dannoDado = 1 + rand() % 6;
                            player->vita -= dannoDado;
                            printf("Subisci %d danni! Vita rimasta: %d\n", dannoDado, player->vita);
                        break;

                    case 6:
                        printf("Drago Antico\n"); //combattimento
                        if(combattimentoDrago(player, 5, 10, 12)){
                            spada = 1;
                            printf("Hai ottenuto la Spada dell'eroe!");
                        }
                        break;
                }
                if(player->vita<=0){
                    printf("\n=== GAME OVER ===\n");
                    main();
                }

                if(spada){
                    printf("\nMissione Completata!\n"),
                    player->missioni_compl++;
                    fineMissione = 1;
                    return 1;
                }

                break;

            case 2:
                negozio(player);
                break;

            case 3:
                if(player->inventario[0]==NULL){
				    printf("Inventario Vuoto\n");
				    break;
			    }
			    for(int i=0;i<10;i++){
				    if(player->inventario[i]!=NULL){
					    printf("%s\n",player->inventario[i]->nome);
				    }else{
					    i=10;
				    }
			    }
                break;

            case 4:
                printf("Tornando al villaggio...\n");
                if(fineMissione==1){
                    return 1;
                }
                else if(player->monete>=50){
                    printf("Vuoi pagare 50 monete per tonrare al villaggio? 0|1\n");
                    int ris;
                    ris=scanf("%d",&ris);
                    if(ris==1){
                        player->monete-=50;
                        return 0;
                    }
                }
                else{
                    printf("Non hai abbastanza monete per andartene\n");
                }

            default:
                printf("Scelta non valida.\n");
            
            
        }    
    }
}

