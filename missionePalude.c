#include "strutture.h"

int combattimento(Personaggio *player, char* nomeNemico, int colpofatale, int danno, int monete){
    int dmgSpada=0;
    printf("\nL'eroe incontra un %s e inizia il combattimento.\n", nomeNemico);
    for(int i=0;i<MAX_INV;i++){
        if(player->inventario[i]!=NULL){
            if(strcmp(player->inventario[i]->attributo, "arma") == 0){
                dmgSpada=player->inventario[i]->val_attributo;
                break;
            }
        }
    }
    while(player->vita > 0){
        int dado = 1 + rand() % 6 + dmgSpada;
        printf("\nViene lanciato un dado per stabilire l'attacco dell'eroe.\nIl risultato è %d\n", dado);

        if(dado >= colpofatale){
            printf("\n%s sconfitto! Punti vita rimasti: %d\n", nomeNemico, player->vita);
            player->monete += monete;
            printf("L'eroe guadagna %d monete. Monete totali: %d\n", monete, player->monete);
            return 1;
        }else{
            int dmg = danno - dmgArmatura(player);
            if(dmg < 0) dmg = 0;

            player->vita -= dmg;
            printf("\nAttacco non sufficente.\n");
            printf("L'eroe subisce %d danni. Punti vita rimasti: %d\n", dmg, player->vita);
        }
    }

    return 0;
}

int missionPalude(Personaggio *player){
    int scelta;
    int fineMissione = 0;
    int stanzeEsplorate = 0;
    int orco = 0;
    
    printf("\n=== PALUDE PUTRESCENTE ===\n");
    sleep(1);
    printf("Obiettivo: Sconfiggi 3 Generali Orco.\n");

    while(!fineMissione){
        printf("\nStato di avanzamento: hai sconfitto %d su 3 Generale Orco\n", orco);
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
                if(stanzeEsplorate == 10 && orco < 3){
                    printf("Devi ancora sconfiggere i Generali Orco!\n");
                }


                stanzeEsplorate++;
                printf("\nStanza %d - ", stanzeEsplorate);
                // forzatura ==> stanze mancanti + attuale == orchi mancanti
                if((10 - stanzeEsplorate + 1) == 3-orco){
                        printf("Generale Orco\n");//combattimento
                        if(combattimento(player, "Generale Orco",6,3,12)){
                            orco++;  
                            if(orco == 3){
                                printf("\nMissione Completata!\n"),
                                player->missioni_compl++;
                                fineMissione = 1;
                                return 1;
                            }  
                        }else{
                            return -1;
                        }
                        continue;
                    }

                int dado = 1 + rand() % 6;

                switch(dado){
                    case 1: 
                        printf("Cane selvaggio\n"); //combattimento
                        if(combattimento(player, "Cane Selvaggio", 2, 1, 0)<=0){
                            return -1;
                        }
                        break;

                    case 2: 
                        printf("Goblin\n"); //combattimento
                        if(combattimento(player, "Goblin", 3, 2, 2)<=0){
                            return-1;
                        }
                        break;

                    case 3:
                        printf("Scheletro\n");//combattimento
                        if(combattimento(player, "Scheletro", 4, 2, 4)<=0){
                            return -1;
                        }
                        break;

                    case 4:
                        printf("Orco\n"); //combattimento
                        if(combattimento(player, "Orco", 3, 4, 6)<=0){
                            return -1;
                        }
                        break;

                    case 5:
                        printf("Acquitrino Velenoso\n"); //trappola
                        printf("L'eroe viene colpito da una trappola.\n");
                            int dannoDado = 1 + rand() % 6;
                            int dmg = dannoDado - dmgArmatura(player);
                            if(dmg < 0) dmg = 0;
                            player->vita -= dmg;
                            printf("Subisce %d danni! Punti vita rimasti: %d\n", dmg, player->vita);
                            if(player->vita<=0){
                                return -1;
                                }
                        break;

                    case 6:
                        printf("Generale Orco\n"); //combattimento
                        int n = 6;
                        for(int i=0;i<MAX_INV;i++){
                             if(player->inventario[i]!=NULL){
                                if(strcmp(player->inventario[i]->attributo, "arma") == 0){
                                    if(player->inventario[i]->val_attributo == 2){
                                        n = 5;
                                        }
                                    }
                                }
                            }
                        if(combattimento(player, "Generale Orco", n, 3, 12)){
                            orco++;
                            if(orco == 3){
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
                else if(player->monete>=50){
                    printf("Vuoi pagare 50 monete per tonrare al villaggio? Si/No\n");
                    char ris[3];
                    while(getchar()!='\n');
                    fgets(ris, sizeof(ris), stdin);
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
