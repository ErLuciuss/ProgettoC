#include "Strutture.h"


//sistemare i printf 
//aggiusta spada e armatura, unisci con le strutture degli oggetti 

void negozio(Personaggio *player){
    int scelta;
    int spada = 0;
    int armatura = 0;
     /*sbagliati li devo mettere nella struct ma il mio cervello è andato
    tanto per vedere come dovrebbe essere*/

    printf("\n----- NEGOZIO -----\n");
    printf("\n1. Pozione curativa (4 monete)\n2. Spada(5 monete)\n3. Armatura (10 monete)");
    printf("Seleziona un oggetto da acquistare: ");
    scanf("%d", &scelta);

    switch(scelta){
        case 1:
            if(player->monete >= 4){
                player->monete -=4;
                int dado = 1 + rand() % 6;
                player->vita += dado;
                printf("Hai acquistato la pozione curativa.\nSono stati ripristinati %d punti vita. Vita rimasta: %d\n", dado, player->vita);
            }else{
                printf("Non hai abbastanza monete!\n");
            }
            break;

        case 2:
            if(spada == 0){
                if(player->monete >= 5){
                    player->monete -=5;
                    spada = 1; 
                    printf("Hai acquistato una spada!");
                    //+1 di attacco (da vedere come aggiungerlo)
                }else{
                    printf("Non hai abbastanza monete!\n");
                }
            } else if(spada == 1){
                printf("Non puoi acquistare questo oggetto più di una volta!\n");
            } break;

        case 3:
            if(armatura == 0){
                if(player->monete >= 10){
                    player->monete -=10;
                    spada = 1; 
                    printf("Hai acquistato un'armatura!");
                    // - 1 danno
                }else{
                    printf("Non hai abbastanza monete!\n");
                }
            } else if(armatura == 1){
                printf("Non puoi acquistare questo oggetto più di una volta!\n");
            } break;
            
        default:
                printf("Scelta non valida.\n");

    }

}


int combattimento( Personaggio *player, int colpofatale, int danno, int monete){
    while(player->vita > 0){ //finchè il personaggio è in vita
        int dado = 1 + rand() % 6;
         printf("viene lanciato un dado per stabilire l'attacco dell'eroe: %d\n", dado);

        if(dado > colpofatale){
            printf("Nemico sconfitto!\n");
            player->monete += monete;
            printf("Guadagni %d monete. Monete totali: %d\n", monete, player->monete);
            return 1; //vittoria torni al "menù" missioni
        }else{
            player -> vita -= danno;
            printf("Subisci %d danni. Vita rimasta: %d\n", danno, player->vita);
        }
    }
    printf("\n=== GAME OVER ===\n"); //se esci dal loop e quindi la vita e 0 o meno
    return 0;
}

void missionMagione(Personaggio *player){
    int scelta;
    int fineMissione = 0;
    int stanzeEsplorate = 0;
    int chiave = 0;
    int vampiro = 0;

    printf("\n=== MAGIONE INFESTATA ===\n");
    printf("Obiettivo: Recupera la chiave del Castello e sconfiggi il Vampiro Superiore.\n");

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
                if(stanzeEsplorate == 10){
                    printf("Hai completato tutte le stanze della magine\n");
                    break;
                }


                stanzeEsplorate++;


                if(stanzeEsplorate == 9){
                    if(!vampiro && !chiave){
                        printf("Vampiro Superiore\n");//combattimento
                        if(combattimento(player, 4, 4, 7)){
                            vampiro = 1;
                            printf("Hai sconfitto il Vampiro Superiore!\n");
                        }
                    }
                    continue; //salta al dado
                }
                if(stanzeEsplorate == 10){
                    if(!vampiro){
                        printf("Vampiro Superiore\n");//combattimento
                        if(combattimento(player, 4, 4, 7)){
                            vampiro = 1;
                            printf("Hai sconfitto il Vampiro Superiore!\n");
                            } 
                       }else if(!chiave){
                        printf("Demone Custode\n"); //combattimento
                        if(combattimento(player, 4, 6, 10)){
                            chiave = 1;
                            printf("Hai ottenuto la chiave!");
                            }
                        }
                    }

                int dado = 1 + rand() % 6;

                printf("\nStanza %d - ", stanzeEsplorate);

                switch(dado){
                    case 1: 
                        printf("Botola Buia\n"); //trappola
                        player->vita-=3;
                        printf("Subisci 3 danni! Vita rimasta: %d\n", player->vita);
                        break;

                    case 2: 
                        printf("Pipistrello\n"); //combattimento
                        combattimento(player, 2, 2, 1);
                        break;

                    case 3:
                        printf("Zombie\n");//combattimento
                        combattimento(player, 3, 2, 2);
                        break;

                    case 4:
                        printf("Fantasma\n"); //combattimento
                        combattimento(player, 5, 2, 4);
                        break;

                    case 5:
                        printf("Vampiro Superiore\n");//combattimento
                        if(combattimento(player, 4, 4, 7)){
                            vampiro = 1;
                            printf("Hai sconfitto il Vampiro Superiore!\n");
                        }
                        break;

                    case 6:
                        printf("Demone Custode\n"); //combattimento
                        if(combattimento(player, 4, 6, 10)){
                            chiave = 1;
                            printf("Hai ottenuto la chiave!");
                        }
                        break;
                }
                if(player->vita<=0){
                    printf("\n=== GAME OVER ===\n");
                    exit(0); //chiude il programma, poi modifica che torna al menù
                }

                if(vampiro && chiave){
                    printf("\nMissione Completata!\n"),
                    player->missioni_compl++;
                    fineMissione = 1;
                    return;
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
                return;
                //paga 50 monete o vinci missione

            default:
                printf("Scelta non valida.\n");
            
        }
    }
}
