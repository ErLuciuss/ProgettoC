#include "Strutture.h"

//--MAIN--
int main(){
	riempiArrObj();
	bool ciclo=true;
	char invio;
	while(ciclo){
		char scelta;
		menu();
		scelta=getchar();
		while(getchar() != '\n');
		switch(scelta){
		case '1':{
			printf("-----------------------------------------\n");
			Personaggio player=creaPersonaggio();
			printf("\nnome: %s\n",player.nome);
			printf("p.vita: %d\n",player.vita);
			printf("n.monete: %d\n",player.monete);
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

			Personaggio p;
			p=loadSalvataggio(saveChoise);
			villaggio(&p);
			break;
		}
		case '3':{
			printf("-----------------------------------------\n");
			ciclo=false;
			printf("Uscita.");
			fflush(stdout);//per svuotare il buffer
			sleep(1);
			printf(".");
			fflush(stdout);
			sleep(1);
			printf(".\n");
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
				if(guess=='\n')continue;//se avesi usato while(getchar() != '\n'); per pulire il buffer dopo aver acquisito guess,
				if(guess==code[val]){   //mi mangerebbe le altre lettere del codice e quindi uscirebbe dal loop
					val++;
				}else{
					loop=false;
					printf("Codice Sbagliato\n");
				}
				if(val==len){
					loop=false;
					printf("Codice corretto!\n");
					printSalvataggio();
				}
			}
			while(getchar() != '\n');
			break;
		}
		}
	}
}