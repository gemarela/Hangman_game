#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "getWord.c"

#define TOLOWERCASE(x) ((x>='A' && x<='Z') ? (x=x-'A') : x)
#define LENGTHINPUT(x) ((x<1 || x>30 || x==26 || x==27) ? 1 : 0)
#define ROUNDINPUT(x) ((x<1) ? 1 : 0)

struct typeB{
	
	char *word;
	struct typeB *next;
	
};

struct typeA {
	
	char character;
	int used;
	
	struct typeA *next;
	struct typeA *previous;
};

struct typeC{
	
	char *word;
	int size;
		
	struct typeB **words;
	struct typeC *next;
};




int exeiVretheiHleksi(char* word);
int epanekinisiPaixnidiou(char input);
int egkurhEisodos(int argc,char *argv[]);

struct typeB *diavasmaLexikou(struct typeB *Broot,char *onoma_arxeiou,int megethos_leksis);
struct typeB *diagrafhLeksikou(struct typeB *leksiko);

struct typeA *dhmiourgiaGrammatwn(struct typeA *Aroot);
struct typeA *eisagwghStaXrhsimopoihmena(struct typeA *grammata,char mantepsia);
struct typeA *diagrafhGrammatwn(struct typeA *grammata);
void xrhsimopoihmenaGrammata(struct typeA *Aroot);
int hdhXrhsimopoihmenoGramma(struct typeA *grammata,char mantepsia);

struct typeC *arxikopoihshKathgoriwn(struct typeC *kathgories,struct typeB *leksiko);
struct typeC *eureshPoluplithesterhsKathgorias(struct typeC *kathgories,char neoGramma,char *trexousaKatastash);
struct typeC *uparxeiKathgoria(struct typeC *prosorinilista,char *word);
void printkathgories(struct typeC *kathgories);


int main(int argc,char *argv[]){

		char epanekinisi_paixnidiou='y',mantepsia,*agnwsth_leksi;
		int gurh_paixnidiou,megethos_leksis,i,hLeksiVrethike,tuxaiaThesi;
		
		struct typeB *leksiko=NULL;
		struct typeA *grammata=NULL;
		struct typeC *kathgories=NULL;
		
		if(!egkurhEisodos(argc,argv)){
				return 1;
		}

		megethos_leksis=atoi(argv[1]);
		
		leksiko=diavasmaLexikou(leksiko,argv[3],megethos_leksis);
		
		while(epanekinisiPaixnidiou(epanekinisi_paixnidiou)){
			
			agnwsth_leksi=(char*)malloc((megethos_leksis+1)*sizeof(char));
			for(i=0;i<megethos_leksis;i++){
				agnwsth_leksi[i]='_';
			}
			agnwsth_leksi[megethos_leksis]='\0';
			
			gurh_paixnidiou=atoi(argv[2]);
			grammata=dhmiourgiaGrammatwn(grammata);
			
			hLeksiVrethike=0;
			kathgories=arxikopoihshKathgoriwn(kathgories,leksiko);
			//printkathgories(kathgories);
			
			do{
				printf("Remaining guesses: %d\n",gurh_paixnidiou);
				xrhsimopoihmenaGrammata(grammata);
				
				printf("Word: %s\n", agnwsth_leksi);
				
				printf("Guess a letter: ");
				scanf(" %c",&mantepsia);
				while(isalpha(mantepsia)==0){
						printf("Guess a letter: ");
						scanf(" %c",&mantepsia);
				}
				
				if((mantepsia>='A' && mantepsia<='Z')){
					mantepsia=mantepsia-'A';
				}
				
				if(hdhXrhsimopoihmenoGramma(grammata,mantepsia)){
						printf("You have already guessed this letter\n");
				}else{
						grammata=eisagwghStaXrhsimopoihmena(grammata,mantepsia);
						kathgories=eureshPoluplithesterhsKathgorias(kathgories,mantepsia,agnwsth_leksi);
						strcpy(agnwsth_leksi,kathgories->word);
						printf("Category size: %d\n",kathgories->size);
						gurh_paixnidiou--;
				}
				if(gurh_paixnidiou==0){
					printf("YOU LOST! The word was ");
					srand(time(NULL));
					tuxaiaThesi=rand()%kathgories->size;
					printf("%s \n",kathgories->words[tuxaiaThesi]->word);
					
					free(kathgories->word);
					free(kathgories->words);
					free(kathgories);
					
				}
				if(exeiVretheiHleksi(agnwsth_leksi)){
						printf("YOU WON! The word is %s",agnwsth_leksi);
						hLeksiVrethike=1;
						
						free(kathgories->word);
						free(kathgories->words);
						free(kathgories);
				}
				
				
			}while(gurh_paixnidiou > 0 && hLeksiVrethike==0);
				
			grammata=diagrafhGrammatwn(grammata);
			free(agnwsth_leksi);
			printf("\n");
			printf("Play again? (y/n): ");
			scanf(" %c",&epanekinisi_paixnidiou);
		}
		
		leksiko=diagrafhLeksikou(leksiko);
		return 0;
}


/*
	Sunarthsh pou elegxei an exei vrethei h agnwsth leksi.
	Praktika koitaei an h trexousa katastash exei '_'
*/

int exeiVretheiHleksi(char* word){
		
		int i,agnwstaGrammata;
		for(i=0,agnwstaGrammata=0;i<strlen(word);i++){
			
			if(word[i]=='_'){
					agnwstaGrammata++;
			}
		}
	
		if(agnwstaGrammata==0){
				return 1;
		}else{
				return 0;
		}
}


/*
	Sunarthsh pou elegxei an exei ektelestei swsta to programma. An
	dhladh exei dothei to swsto plhthos orismatwn.
*/

int egkurhEisodos(int argc,char *argv[]){

	int gurh_paixnidiou,megethos_leksis;

	switch(argc){
			case 4:{
					megethos_leksis=atoi(argv[1]);
					while(LENGTHINPUT(megethos_leksis)){
						printf("There are no words of length %d in the dictionary. \n",megethos_leksis);
						printf("Specify a different length: ");
						scanf("%d",&megethos_leksis);
					}
					
					
					gurh_paixnidiou=atoi(argv[2]);
					while(ROUNDINPUT(gurh_paixnidiou)){
						printf("You may not have fewer than one turns.\n");
						printf("Specify a different number of turns: ");
						scanf("%d",&gurh_paixnidiou);
					}
					
					sprintf(argv[1],"%d",megethos_leksis);
					sprintf(argv[2],"%d",gurh_paixnidiou);
					
					return 1;
				}
			default:{ (argc >4) ? printf("Too many arguments\n") : printf("Insuficient argument\n") ;
					printf("./hangman LENGTH TURNS DICTIONARY\n");
					printf("\tLENGTH: requested length of mystery word. Must be >1, <30, !=26, !=27\n");
					printf("\tTURNS: requested number of turns. Must be >0\n");
					printf("\tDICTIONARY: name of dictionary file\n");
					return 0;
			}
	}	
}


/*
	Sunasthsh mou xrhsimopoieitai gia na ksanapaiksei o paikths

*/

int epanekinisiPaixnidiou(char input){

		char temp;
		temp=TOLOWERCASE(input);
		
		switch(input){
				case 'y':{return 1;}
				case 'n':{return 0;}
				default :{
						printf("Please enter y for yes or n for no.\n");
						printf("Play again? (y/n): ");
						scanf(" %c",&temp);
						return epanekinisiPaixnidiou(temp);
					}
		}
}



/* ----------------------------------------------------- */
/* ------------------ LISTA KATHGORIWN ----------------- */
/* ----------------------------------------------------- */


/*
	Sunarthsh pou diatrexei oles tis enapomhnantes lekseis kai tis kathgoriwnpoiei me vash ena
	gramma eisodou, sto telos epistrefei th poluplhthesterh kathgoria

*/

struct typeC *eureshPoluplithesterhsKathgorias(struct typeC *kathgories,char neoGramma,char *trexousaKatastash){


		struct typeB *leksi;
		struct typeC *prosorinilista=NULL,*komvosProsorinisListas=NULL,*poluplhthesterosKomvos=NULL;
		struct typeC *enalPoluplhthesterosKomvos=NULL,*telikosPoluplhthesterosKomvos=NULL,*deleteKomvos=NULL;
		
		int trexousaLeksi,megethosLeksis,megistoMegethos=1,i,plhtosKathgoriwn=0;
		
		leksi=kathgories->words[0];
		megethosLeksis=strlen(leksi->word);
		
		char *leksi_c=NULL;
		char word[megethosLeksis+1];
		word[megethosLeksis]='\0';
		leksi_c=(char*)malloc((megethosLeksis+1)*sizeof(char));
		
		// diatrexoume oles tis leksis pou exoun apomeinei sto paixnidi mesw tou pinaka deiktwn tou struct kathgoria
		for(trexousaLeksi=0;trexousaLeksi<kathgories->size;trexousaLeksi++,leksi=kathgories->words[trexousaLeksi]){
			
			strcpy(leksi_c,leksi->word);
			
			//gia kathe enapomhnousa leksi dhmiourgoume th kathgoria sthn opoia anhkei	
			for(i=0;i<megethosLeksis;i++){	
				if(leksi_c[i]==trexousaKatastash[i]){
					word[i]=trexousaKatastash[i];
				}else{
						if(leksi_c[i]==neoGramma){
							word[i]=leksi_c[i];
						}else{
							word[i]='_';
						}
				}
			}
			
			//elegxoume an uparxei hdh komvos kathgorias gia na eisagoume th leksi pou molis diavasame
			komvosProsorinisListas=uparxeiKathgoria(prosorinilista,word);
			
			//an den uparxei dimiourgoume enan kainourio komvo kai ton vazoume sthn arxh ths listas kathgoriwn
			if(komvosProsorinisListas==NULL){
								
					komvosProsorinisListas=(struct typeC*)malloc(sizeof(struct typeC));
					komvosProsorinisListas->word=(char*)malloc((megethosLeksis+1)*sizeof(char));
					strcpy(komvosProsorinisListas->word,word);
					komvosProsorinisListas->size=1;
					komvosProsorinisListas->words=(struct typeB**)malloc(komvosProsorinisListas->size*sizeof(struct typeB*));
					komvosProsorinisListas->words[0]=leksi; 	
					komvosProsorinisListas->next=prosorinilista;
					prosorinilista=komvosProsorinisListas;
					
					if(megistoMegethos<=komvosProsorinisListas->size){
							megistoMegethos=komvosProsorinisListas->size;
							poluplhthesterosKomvos=komvosProsorinisListas;
					}
					plhtosKathgoriwn++;
			
			//an uparxei au3anoume to megethos ths kathgorias kai ton pinaka deiktwn kai prosthetoume 
			//ti leksi sth kathgoria
			}else{
					komvosProsorinisListas->size++;
					komvosProsorinisListas->words=(struct typeB**)realloc(komvosProsorinisListas->words,(komvosProsorinisListas->size+1)*sizeof(struct typeB*));
					komvosProsorinisListas->words[komvosProsorinisListas->size-1]=leksi;
					
					//parallhla elegxoume kai to
					if(megistoMegethos<=komvosProsorinisListas->size){
							megistoMegethos=komvosProsorinisListas->size;
							poluplhthesterosKomvos=komvosProsorinisListas;
					}		
			}
		}
		telikosPoluplhthesterosKomvos= poluplhthesterosKomvos;
		
		
		// se periptwsh pou h kathgoria pou epistrefoume den periexei '_' koitazoume an uparxei kai allh kathgoria
		// me to idio megethos pou na exei '_' kai sunepws na mh teliwnei to paixnidi
		
		if(exeiVretheiHleksi(poluplhthesterosKomvos->word)){
			for(enalPoluplhthesterosKomvos=prosorinilista;enalPoluplhthesterosKomvos!=NULL;enalPoluplhthesterosKomvos=enalPoluplhthesterosKomvos->next){
				if((enalPoluplhthesterosKomvos!=poluplhthesterosKomvos)&&(enalPoluplhthesterosKomvos->size==poluplhthesterosKomvos->size)){
						telikosPoluplhthesterosKomvos=enalPoluplhthesterosKomvos;
				}
			}
			
		}
		
		//diagrafh olws twn komvwn pou dimiourgh8hkan ektws apo auton pou epistrefetai
		
		komvosProsorinisListas=prosorinilista;
		while(komvosProsorinisListas!=NULL){
			if(komvosProsorinisListas==telikosPoluplhthesterosKomvos){
					komvosProsorinisListas=komvosProsorinisListas->next;
			}else{
					deleteKomvos=komvosProsorinisListas;
					komvosProsorinisListas=komvosProsorinisListas->next;
					free(deleteKomvos->word);
					free(deleteKomvos->words);
					free(deleteKomvos);
			}			
		}
		
		//diagrafh tou komvou eisodou (ousiastika ths prohgoumenhs kathgorias)
		free(kathgories->word);
		free(kathgories->words);
		free(kathgories);
		
		return telikosPoluplhthesterosKomvos;
}


/*
	Sunarthsh pou dhmiourgei thn arxikh kathgoria

*/

struct typeC *arxikopoihshKathgoriwn(struct typeC *kathgories,struct typeB *leksiko){
	
		int i,wordLen;
		struct typeB *leksi=leksiko;
		wordLen=strlen(leksiko->word);
				
		kathgories=(struct typeC*)malloc(sizeof(struct typeC));
		kathgories->word=(char*)malloc((wordLen+1)*sizeof(char));
		
		for(i=0;i<wordLen;i++){
				kathgories->word[i]='_';
		}
		kathgories->word[wordLen]='\0';
		kathgories->size=0;
		kathgories->words=(struct typeB**)malloc(sizeof(struct typeB*));
		
		while(leksi!=NULL){
				
				kathgories->words[kathgories->size]=leksi;
				kathgories->size++;
				kathgories->words=(struct typeB**)realloc(kathgories->words,(kathgories->size+1)*sizeof(struct typeB*));
				leksi=leksi->next;
		}
		
		//printf("sunoliko plh8os leksewn: %d\n",kathgories->size);
		
		return kathgories;
}


/*
	Bohthitikh sunarthsh pou diatrexei mia lista kathgoriwn kai epistrefei
	ton komvo ston opoio tairiazei h leksi tou lexikou pou deinetai san
	eisodos h NULL an den uparxei tetoios komvos sth lista
*/

struct typeC *uparxeiKathgoria(struct typeC *prosorinilista,char *word){

	struct typeC *komvosProsorinisListas=prosorinilista;
	while(komvosProsorinisListas!=NULL){
		
		if(strcmp(komvosProsorinisListas->word,word)==0){
				return komvosProsorinisListas;
		}
		
		komvosProsorinisListas=komvosProsorinisListas->next;
	}
	return NULL;
}


/*

	Bohthitikh sunarthsh pou ekthpwnei oles tis lekseis mias kathgorias

*/

void printkathgories(struct typeC *kathgories){
	
	struct typeB *leksi;
	int i=0;
	
	printf("%d\n\n",kathgories->size);
	for(i=0;i<kathgories->size;i++){
		leksi=kathgories->words[i];
		printf("%s\n",leksi->word);
	}
}


/* ----------------------------------------------------- */
/* ------------------ LISTA LEKSIKOU ------------------- */
/* ----------------------------------------------------- */

/*
	Sunarthsh pou diavazei to arxeio eisodou kai dimiourgei mia lista me
	tis lekseis pou emperiexontai se auto.
*/

struct typeB *diavasmaLexikou(struct typeB *Broot,char *onoma_arxeiou,int megethos_leksis){
	
	char *epomenh_leksi=(char *)malloc(31*sizeof(char));
	struct typeB *neos_komvos=NULL;
	
	epomenh_leksi=getWord(onoma_arxeiou);
	while(epomenh_leksi!=NULL){
		if(strlen(epomenh_leksi)==megethos_leksis){
				neos_komvos=(struct typeB*)malloc(sizeof(struct typeB));
				neos_komvos->word=(char*)malloc((megethos_leksis+1)*sizeof(char));
				strcpy(neos_komvos->word,epomenh_leksi);
				neos_komvos->next=Broot;
				Broot=neos_komvos;
		}
		epomenh_leksi=getWord(onoma_arxeiou);
	}
	return Broot;
}


/*
	Sunarthsh pou diagrafei to leksiko. Kaleitai afou teliwsei to paixnidi
	kai o xrhsths epileksei na mh pai3ei allo.
*/

struct typeB *diagrafhLeksikou(struct typeB *leksiko){
	
	struct typeB *del;
	
	while(leksiko!=NULL){
		
		del=leksiko;
		leksiko=leksiko->next;
		free(del->word);
		free(del);
	}
	return NULL;	
}

/* ----------------------------------------------------- */
/* ------------------ LISTA GRAMMATWN ------------------ */
/* ----------------------------------------------------- */

/*
	Sunarthsh pou diagrafei th lista me ta used kai unused grammata

*/


struct typeA *diagrafhGrammatwn(struct typeA *grammata){
	
	struct typeA *gramma,*del;
	gramma=grammata;
	while(gramma!=NULL){
		del=gramma;
		if(gramma->next!=NULL){
				gramma->next->previous=NULL;
		}
		gramma=gramma->next;
		free(del);
	}
	return NULL;
}

/*
	Sunarthsh pou metatrepei ena gramma apo unused kai used

*/

struct typeA *eisagwghStaXrhsimopoihmena(struct typeA *grammata,char mantepsia){

	struct typeA *gramma;
	for(gramma=grammata;gramma!=NULL;gramma=gramma->next){
		if(gramma->character == mantepsia){
			gramma->used=1;
		}
	}
	return grammata;
	
}

/*
	Sunarthsh pou elegxei an ena gramma exei ksanaepilegei sto parelthon

*/

int hdhXrhsimopoihmenoGramma(struct typeA *grammata,char mantepsia){

	struct typeA *gramma;
	for(gramma=grammata;gramma!=NULL;gramma=gramma->next){
		if(gramma->character==mantepsia){
			if(gramma->used==1){
				return 1;
			}
				
		}
	}
	return 0;
}

/*
	Sunarthsh pou ektypwnei ta grammata pou exoun xrhsimopoihthei kai 
	auta pou den exoun epilegei akoma apo ton xrhsth

*/

void xrhsimopoihmenaGrammata(struct typeA *Aroot){

	struct typeA *gramma;
	printf("Used: ");
	for(gramma=Aroot;gramma!=NULL;gramma=gramma->next){
			if(gramma->used){
				printf("%c ",gramma->character);
			}
	}
	printf("\nUnused: ");
	for(gramma=Aroot;gramma!=NULL;gramma=gramma->next){
			if(!gramma->used){
				printf("%c ",gramma->character);
			}
	}
	printf("\n");
	
}

/*
	Sunarthsh pou arxikopoiei ti lista me ta grammata. Praktika ta kanei
	ola unused
*/

struct typeA *dhmiourgiaGrammatwn(struct typeA *Aroot){

		char neo_gramma_c;
		struct typeA *neo_gramma;
		
		for(neo_gramma_c='z';neo_gramma_c>='a';neo_gramma_c--){
			
			neo_gramma=(struct typeA*)malloc(sizeof(struct typeA));
			neo_gramma->character=neo_gramma_c;
			neo_gramma->used=0;
			neo_gramma->next=Aroot;
			Aroot=neo_gramma;
			if(neo_gramma->next!=NULL){
					neo_gramma->next->previous=neo_gramma;
			}
		}
		return Aroot;
}
