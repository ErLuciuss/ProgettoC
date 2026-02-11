#include "Strutture.h"

void missioneFinale(Personaggio *player){
                printf("\n=== MISSIONE FINALE ===\n");
                printf("Obiettivo: Sconfiggi Signore Oscuro.\n");
                int winPlayer = 0;
                int winSignoreOscuro = 0;
                int round = 1;

         while(winPlayer < 3 && winSignoreOscuro < 3 && round <= 5){
                int scelta;
                printf("Scontro finale | Round %d su 5 | Eroe %d - Signore Oscuro %d\n", round, winPlayer, winSignoreOscuro);
                printf("\nMosse Disponibili\n1. Scudo\n2. Magia\n3. Spada\n");
                printf("\nSeleziona una delle opzioni del menù [1-3]: ");
                scanf("%d", &scelta);
                if(scelta < 1 || scelta > 3){
                    printf("Scelta non valida");
                    continue;
                }


                int SignoreOscuro = 1 + rand() % 3;

                switch(scelta){

                    case 1:
                    switch(SignoreOscuro){
                        case 1:
                            printf("\nIl signore Oscuro nel frattempo ha scelto lo scudo\n");
                            printf("\nEntrambi utilizzano lo scudo. Il round viene anullato\n");
                            break;
                        case 2:
                            printf("\nIl signore Oscuro nel frattempo ha scelto la magia\n");
                            printf("\nL'Eroe prova a difendersi ma il Signore Oscuro lo colpisce. Il signore Oscuro si aggiudica il round\n");
                            winSignoreOscuro++;
                            round++;
                            break;
                        case 3:
                            printf("\nIl signore Oscuro nel frattempo ha scelto la spada\n");
                            printf("\nL'Eroe para e si difende dalla spada del Signore Oscuro. l'Eroe si aggiudica il round\n");
                            winPlayer++;
                            round++;
                            break;
                        }
                        break;

                    case 2:
                        switch(SignoreOscuro){
                        case 1:
                            printf("\nIl signore Oscuro nel frattempo ha scelto lo scudo\n");
                            printf("\nL'Eroe utilizza la magia per attaccare le difese del Signore Oscuro. l'Eroe si aggiudica il round\n");
                            winPlayer++;
                            round++; 
                            break;
                        case 2:
                            printf("\nIl signore Oscuro nel frattempo ha scelto la magia\n");
                            printf("\nEntrambi utilizzano la magia. Il round viene anullato\n");
                            break;
                        case 3:
                            printf("\nIl signore Oscuro nel frattempo ha scelto la spada\n");
                            printf("\nL'Eroe non riesce a difendersi dalla spada del Signore Oscuro e lo colpisce. Il signore Oscuro si aggiudica il round\n");
                            winSignoreOscuro++;
                            round++;
                         break;
                        }
                        break;
                
                    case 3:
                    switch(SignoreOscuro){
                        case 1:
                            printf("\nIl signore Oscuro nel frattempo ha scelto lo scudo\n");
                            printf("\nL'Eroe attacca il Signore Oscuro, ma lui riesce a difendersi. Il signore Oscuro si aggiudica il round\n");
                            winSignoreOscuro++;
                            round++;
                            break;
                        case 2:
                            printf("\nIl signore Oscuro nel frattempo ha scelto la magia\n");
                            printf("\nL'Eroe attacca il Signore Oscuro, che non riesce a difendersi. l'Eroe si aggiudica il round\n");
                            winPlayer++;
                            round++; 
                            break;
                        case 3:
                            printf("\nIl signore Oscuro nel frattempo ha scelto la spada\n");
                            printf("\nEntrambi utilizzano la spada. Il round viene anullato\n");
                            break;
                        }
                        break;
                }
            }

            if(winPlayer == 3){
                printf("\nCongratulazioni hai vinto!\n");
                exit(EXIT_SUCCESS);
            }else if(winSignoreOscuro == 3){
                printf("\n=== GAME OVE R===\n");
                main();
            }
        }