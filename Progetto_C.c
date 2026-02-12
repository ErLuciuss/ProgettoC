#include "Strutture.h"

//--MAIN--
int main(){
	riempiArrObj();
	Personaggio player;
	bool ciclo=true;
	char invio;
	while(ciclo){
		char scelta;
		menu();
		scelta=getchar();
		switch(scelta){
		case '1':{
			printf("-----------------------------------------\n");
			player=creaPersonaggio();
			printf("\n%s\n",player.nome);
			printf("%dhp\n",player.vita);
			printf("monete: %d\n\n",player.monete);
			printf("Inventario:\n");
			for(int i=0;i<MAX_INV;i++){
				if(player.inventario[i]!=NULL)
					printf("%s\n",player.inventario[i]->nome);
			}
			villaggio(&player);
			break;
		}
		case '2':{
			printf("-----------------------------------------\n");
			printf("Scegliere un salvataggio:\n\n");
			printf("0 Ritornare al menù principale\n");
			printSalvataggio();
			printf("-----------------------------------------\n");

			int saveChoise;
			scanf("%d",&saveChoise);
			while(getchar() != '\n');
			if(saveChoise==0){
				break;
			}

			player=loadSalvataggio(saveChoise);
			villaggio(&player);
			break;
		}
		case '3':{
			printf("-----------------------------------------\n");
			if(canSave){
				printf("Vuoi salvare prima di uscire?Y/N\n");
				char saveScelta;
				saveScelta=getchar();
				if(saveScelta=='Y'||saveScelta=='y'){
				creaSalvataggio(&player);
				ciclo=false;
				sleep(1);
				printf("Uscita.");
				fflush(stdout);//per svuotare il buffer
				sleep(1);
				printf(".");
				fflush(stdout);
				sleep(1);
				printf(".\n");
				exit(EXIT_SUCCESS);
				}
			}else{
				printf("Non hai un personaggio da salvare\n");
			}
			break;
		}
		case 'W':{
			char code[]={'W','S','S','A','D','A','D','A','B',' '};
			bool loop=true;
			int val=0;
			int len=sizeof(code)/sizeof(code[0]);
			char guess;
			while(getchar() != '\n');

			while(loop){
				guess=getchar();
				while(getchar() != '\n');
				if(guess=='\n')continue;//se avesi usato while(getchar() != '\n'); per pulire il buffer dopo aver acquisito guess,
				if(guess==code[val]){   //mi mangerebbe le altre lettere del codice e quindi uscirebbe dal loop
					val++;
				}else{
					loop=false;
					printf("Codice Sbagliato\n");
					break;
				}
				if(val==len){
					loop=false;
					printf("Codice corretto!\n");
					printf("Scegliere salvataggio da modificare:\n");
					printf("0 Ritorna al menù principale\n");
					printSalvataggio();
					int saveMod;
					scanf("%d",&saveMod);
					while(getchar() != '\n');
					if(saveMod==0){
						break;
					}
					modSalvataggio(saveMod);
					break;
				}
			}
			break;
		}
		}
	}
}