#include "Strutture.h"

int magioneCompl=0;
int grottaCompl=0;
int paludeCompl=0;


//bisogna aggiungere la cosa che spariscono le missioni dopo essere completate

void menuMissioni(Personaggio *player){
	printf("----------------Missioni-----------------\n");
    printf("\n1. Palude Putrescente\n");
    if(magioneCompl!=1){
        printf("2. Magione Infestata\n");
    }
    printf("3. Grotta di Cristallo\n");
    int scelta;
    printf("Seleziona una delle opzioni del menù [1-3]: ");
    scanf("%d", &scelta);
	printf("\n-----------------------------------------\n");

    switch(scelta){
        case 1:
            paludeCompl;
            break;
        case 2:
            magioneCompl=missionMagione(player);
            break;
        case 3:
            grottaCompl=missionGrotta(player);
            break;
        default:
            printf("\nSelezione non valida\n");
    }

    if(player->missioni_compl == 3){
        missioneFinale(player);
    }
}
