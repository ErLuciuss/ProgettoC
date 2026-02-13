#include "strutture.h"

int missionMagione(Personaggio *player){
    int scelta;
    int fineMissione = 0;
    int stanzeEsplorate = 0;
    int chiave = 0;
    int vampiro = 0;
    
    
    printf("\n=== MAGIONE INFESTATA ===\n");
    sleep(1);
    printf("Obiettivo: Recupera la chiave del Castello e sconfiggi il Vampiro Superiore.\n");

    while(!fineMissione){
        printf("\nStato di avanzamento: Hai sconfitto %d su 1 Vampiro Superiore e hai trovato %d su 1 chiave\n ", vampiro, chiave);
        sleep(1);
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
        scanf("%d", &scelta);
        while(getchar() != '\n');

        switch(scelta){
            case 1:
                printf("Esplori una stanza del Dungeon...\n");
                if(stanzeEsplorate == 10 && !(vampiro && chiave)){
                    printf("Devi ancora sconfiggere il boss o trovare la chiave!\n");
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
                            printf("L'eroe ha ottenuto la chiave!\n");
                            if(vampiro ==1 && chiave == 1){
                                printf("\nMissione Completata!\n"),
                                player->missioni_compl++;
                                fineMissione = 1;
                                return 1;
                            }
                            }
                        }else{
                            return -1;
                        }
                    }

                int dado = 1 + rand() % 6;
                
                

                switch(dado){
                    case 1: 
                        printf("Botola Buia\n"); //trappola
                        printf("L'eroe viene colpito da una trappola.");
                        int dmg = 3 - dmgArmatura(player);
                        if(dmg < 0) dmg = 0;
                        player->vita -= dmg;
                        printf("Subisce %d danni! Punti vita rimasti: %d\n",dmg, player->vita);
                        if(player->vita<=0){
                                printf("\n=== GAME OVER ===\n");
                                }
                        break;

                    case 2: 
                        printf("Pipistrello\n"); //combattimento
                        if(combattimento(player, "Pipistrello", 2, 2, 1)<=0){
                            return -1;
                        }
                        break;

                    case 3:
                        printf("Zombie\n");//combattimento
                        if(combattimento(player, "Zombie", 3, 2, 2)<=0){
                            return -1;
                        }
                        break;

                    case 4:
                        printf("Fantasma\n"); //combattimento
                        if(combattimento(player, "Fantasma", 5, 2, 4)<=0){
                            return -1;
                        }
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
                        }else{
                            return -1;
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
                        }else{
                            return -1;
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
                //paga 50 monete o vinci missione
            
        }
    }
    return 0;
}