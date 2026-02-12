#include "Strutture.h"


 

void negozio(Personaggio *player){
    int scelta;
    int spada = 0;
    int armatura = 0;
   

    printf("\n----- NEGOZIO -----\n");
    printf("monete giorcaore:%d\n",player->monete);
    printf("\n1. Pozione curativa (4 monete)\n2. Spada(5 monete|acquistabile solo una volta)\n3. Armatura (10 monete|acquistabile solo una volta)\n");
    printf("Seleziona un oggetto da acquistare: ");
    scanf("%d", &scelta);

    switch(scelta){
        case 1:
            if(player->monete >= 4){
                player->monete -=4;
                int dado = 1 + rand() % 6;
                player->vita += dado;
                if(player->vita>20){
                    printf("Vita curata al massimo!\n");
                    player->vita=20;
                    break;
                }
                printf("Hai acquistato la pozione curativa.\nSono stati ripristinati %d punti vita. Vita rimasta: %d\n", dado, player->vita);
            }else{
                printf("Non hai abbastanza monete!\n");
            }
            break;

        case 2:
            for(int i=0;i<MAX_INV;i++){
                if(player->inventario[i]!=NULL){
                    if(strcmp(player->inventario[i]->attributo, "arma") == 0){
                        spada=1;
                    }
                }
            }
            if(spada == 0){   
                if(player->monete >= 5){
                    player->monete -=5;
                    Oggetto* o;
                    o=creaOggetto(listaOggetti[1]->id,listaOggetti[1]->nome,listaOggetti[1]->descrizione,listaOggetti[1]->attributo,listaOggetti[1]->val_attributo,listaOggetti[1]->quantita);
                    raccogliOggetto(player,o);
                    printf("Hai acquistato una spada!\n");
                    //+1 di attacco (da vedere come aggiungerlo)
                }else{
                    printf("Non hai abbastanza monete!\n");
                }
            } else if(spada == 1){
                printf("Non puoi acquistare questo oggetto più di una volta!\n");
            } break;

        case 3:
            for(int i=0;i<MAX_INV;i++){
                if(player->inventario[i]!=NULL){
                    if(strcmp(player->inventario[i]->attributo, "armatura") == 0){
                        armatura=1;
                    }
                }
            }
            if(armatura == 0){
                if(player->monete >= 10){
                    player->monete -=10;
                    Oggetto* o;
                    o=creaOggetto(listaOggetti[2]->id,listaOggetti[2]->nome,listaOggetti[2]->descrizione,listaOggetti[2]->attributo,listaOggetti[2]->val_attributo,listaOggetti[2]->quantita);
                    raccogliOggetto(player,o);
                    printf("Hai acquistato un'armatura!\n");
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


int missionMagione(Personaggio *player){
    int scelta;
    int fineMissione = 0;
    int stanzeEsplorate = 0;
    int chiave = 0;
    int vampiro = 0;
    
    
    printf("\n=== MAGIONE INFESTATA ===\n");
    printf("Obiettivo: Recupera la chiave del Castello e sconfiggi il Vampiro Superiore.\n");

    while(!fineMissione){
        printf("Stato di avanzamento: Hai sconfitto %d su 1 Vampiro Superiore e hai trovato %d  su 1 chiave\n ", vampiro, chiave);
        printf("\n--- Menu Missione ---\n");
        printf("1) Esplora stanza del Dungeon\n");
        printf("2) Negozio\n");
        printf("3) Inventario\n");
        printf("4) Torna al Villaggio\n");
        printf("Seleziona una delle opzioni del menu [1-4]: ");
        scanf("%d", &scelta);

        switch(scelta){
            case 1:
                printf("Esplori una stanza del Dungeon...\n");
                if(stanzeEsplorate == 10){
                    printf("Hai completato tutte le stanze della magine\n");
                    break;
                }


                stanzeEsplorate++;
                printf("\nStanza %d - ", stanzeEsplorate);


                if(stanzeEsplorate == 9){
                    if(!vampiro && !chiave){
                        printf("Vampiro Superiore\n");//combattimento
                        if(combattimento(player, "Vampiro Superiore", 4, 4, 7)){
                            vampiro = 1;
                        }
                        continue;
                    }
                    
                }
                if(stanzeEsplorate == 10){
                    if(!vampiro){
                        printf("Vampiro Superiore\n");//combattimento
                        if(combattimento(player, "Vampiro Superiore", 4, 4, 7)){
                            vampiro = 1;
                            if(vampiro ==1 && chiave == 1){
                                printf("\nMissione Completata!\n"),
                                player->missioni_compl++;
                                fineMissione = 1;
                                return 1;
                            }
                            } 
                            continue;
                       }else if(!chiave){
                        printf("Demone Custode\n"); //combattimento
                        if(combattimento(player, "Demone Custode", 4, 6, 10)){
                            chiave = 1;
                            Oggetto* o;
                            o=creaOggetto(listaOggetti[3]->id,listaOggetti[3]->nome,listaOggetti[3]->descrizione,listaOggetti[3]->attributo,listaOggetti[3]->val_attributo,listaOggetti[3]->quantita);
                            raccogliOggetto(player,o);
                            printf("L'eroe ha ottenuto la chiave!");
                            if(vampiro ==1 && chiave == 1){
                                printf("\nMissione Completata!\n"),
                                player->missioni_compl++;
                                fineMissione = 1;
                                return 1;
                            }
                            }
                        }
                    }

                int dado = 1 + rand() % 6;

                

                switch(dado){
                    case 1: 
                        printf("Botola Buia\n"); //trappola
                        printf("L'eroe viene colpito da una trappola.");
                        player->vita-=(3-dmgArmatura(player));;
                        printf("Subisce %d danni! Punti vita rimasti: %d\n", (3-dmgArmatura(player)), player->vita);
                        if(player->vita<=0){
                                printf("\n=== GAME OVER ===\n");
                                main();
                                }
                        break;

                    case 2: 
                        printf("Pipistrello\n"); //combattimento
                        combattimento(player, "Pipistrello", 2, 2, 1);
                        break;

                    case 3:
                        printf("Zombie\n");//combattimento
                        combattimento(player, "Zombie", 3, 2, 2);
                        break;

                    case 4:
                        printf("Fantasma\n"); //combattimento
                        combattimento(player, "Fantasma", 5, 2, 4);
                        break;

                    case 5:
                        printf("Vampiro Superiore\n");//combattimento
                        if(combattimento(player, "Vampiro Superiore", 4, 4, 7)){
                            vampiro = 1;
                            if(vampiro ==1 && chiave == 1){
                                printf("\nMissione Completata!\n"),
                                player->missioni_compl++;
                                fineMissione = 1;
                                return 1;
                            }
                        }
                        break;

                    case 6:
                        printf("Demone Custode\n"); //combattimento
                        if(combattimento(player, "Demone Custode", 4, 6, 10)){
                            chiave = 1;
                            printf("L'eroe ha ottenuto la chiave!");

                            if(vampiro == 1 && chiave == 1){
                                printf("\nMissione Completata!\n"),
                                player->missioni_compl++;
                                fineMissione = 1;
                                return 1;
                }
                        }
                        break;
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
                else if(player->monete>=50){
                    printf("Vuoi pagare 50 monete per tonrare al villaggio? Si/No\n");

                    char risposta[3];

                    fgets(risposta, sizeof(risposta), stdin);
                    risposta[strlen(risposta) -1]= '\0';

                    if(strcmp(risposta,"si")==0 || strcmp(risposta,"Si")==0 || strcmp(risposta,"SI")==0){
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
                }
                else{
                    printf("Non hai abbastanza monete per andartene\n");
                }
                //paga 50 monete o vinci missione

            default:
                printf("Scelta non valida.\n");
            
        }
    }
    return 0;
}