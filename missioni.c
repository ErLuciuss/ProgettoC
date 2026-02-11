#include "Strutture.h"


//bisogna aggiungere la cosa che spariscono le missioni dopo essere completate

void menuMissioni(Personaggio *player){
	printf("----------------Missioni-----------------\n");
    printf("\n1. Palude Putrescente\n2. Magione Infestata\n3. Grotta di Cristallo\n");
    int scelta;
    printf("Seleziona una delle opzioni del menù [1-3]: ");
    scanf("%d", &scelta);
	printf("\n-----------------------------------------\n");

    switch(scelta){
        case 1:
            break;
        case 2:
            missionMagione(player);
            break;
        case 3:
            missionGrotta(player);
            break;
        default:
            printf("\nSelezione non valida\n");
    }

    if(player->missioni_compl == 3){
        missioneFinale(player);
    }
}
