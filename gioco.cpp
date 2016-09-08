/****************************************************
                     B--Mon EVO                      
    (Black and white C written role playing game)
                SpiritOfTheForest.org
        VERSIONE: 1.2b
        FILE: gioco.cpp                  
****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>

#define MOSTROPROBERBA 40
#define MOSTROPROBSTRADA 1
#define PROBCHIERICO 75
#define AERBA 177
#define AOMINO 258
#define ASTRADA 32  
#define MOCLOSE 99
#define MOMERCANTE 109
#define MOGENERIC -32
#define MOVEW 72
#define MOVEA 75
#define MOVES 80
#define MOVED 77

void caricadati(void);
void salvadati(void);
void caricamappa(void);
void stampagrafica(void);
int murostop(void);
char* convgrafstr(char*);
char convgrafgen(char);
void gioco(void);
void scontro(int);
void scontrovinto(int);
void scontroperso(void);
void presentazionedivinita(void);
int aggiungiexpmostro(int);
void checklivello(void);
void aggiungiexpstrada(void);
void mercante(void);
void compratomerc(int);

char nome[50], nomespada[30], nomearmatura[30], nomeamuleto[30], mappa[100][100], mappabak[100][100];
int saved, forza, corporatura, magia, exp, liv, x, y, spada, armatura, amuleto, grandezzax, grandezzay, vita, mana;

int main(void) {
    srand((unsigned) time(NULL));
    caricadati();
    caricamappa();
    gioco();
    return 0;
}

void caricadati (void) {
     FILE *fp;
     fp = fopen("userpg.data", "r");
     fscanf(fp, "%d\n%s\n%d %d %d\n%d %d\n%d %d\n%d %d %d\n%s\n%s\n%s\n", &saved, &nome, &forza, &corporatura, &magia, &x, &y, &exp, &liv, &spada, &armatura, &amuleto, &nomespada, &nomearmatura, &nomeamuleto);
     fclose(fp);
     return;
}

void salvadati(void) {
     FILE *fp;
     fp = fopen("userpg.data", "w");
     fprintf(fp, "%d\n%s\n%d %d %d\n%d %d\n%d %d\n%d %d %d\n%s\n%s\n%s\n", saved, nome, forza, corporatura, magia, x, y, exp, liv, spada, armatura, amuleto, nomespada, nomearmatura, nomeamuleto);
     fclose(fp);
     return;
}

void caricamappa(void) {
     FILE *fp;
     fp = fopen("mappa.static", "r");
     fscanf(fp, "%d %d\n", &grandezzax, &grandezzay);
     int cai, caj;
     for (cai=0; cai<grandezzay; cai++)
        for (caj=0; caj<=grandezzax; caj++) {
            fscanf(fp, "%c", &mappa[cai][caj]);
            mappa[cai][caj] = convgrafgen(mappa[cai][caj]);
        };
     fclose(fp);
     fp = fopen("mappa.static", "r");
     fscanf(fp, "%d %d\n");
     for (cai=0; cai<grandezzay; cai++)
        for (caj=0; caj<=grandezzax; caj++) {
            fscanf(fp, "%c", &mappabak[cai][caj]);
            mappabak[cai][caj] = convgrafgen(mappabak[cai][caj]);
        };
     fclose(fp);
     return;
}

void stampagrafica(void) {
     system("cls");
     mappa[y][x]=AOMINO;
     int cai,caj;
     for(cai=0; cai<grandezzay; cai++){
          for(caj=0; caj<grandezzax; caj++)
                  printf("%c", mappa[cai][caj]);
          printf("\n");
     };
     mappa[y][x]=mappabak[y][x];
     return;
}

int murostop(void) {
    if ((mappa[y][x]!=(char)AERBA) && (mappa[y][x]!=(char)ASTRADA)) return 1;
    if ((x<0) || (y<0) || (x>=grandezzax) || (y>=grandezzay)) return 2;
    else return 0;
}

void gioco(void) {
     char move, move2;
     int moved;
     int expstrada = 0;
     while(1) {
              expstrada++;
              if (expstrada > 25) {
                    expstrada=0;
                    aggiungiexpstrada();
              };
              salvadati();
              moved=1;
              stampagrafica();
              move=getch();
              switch(move) {
                           case MOGENERIC:
                                move2=getch();
                                switch(move2) {
                                       case MOVEW:
                                            y--;
                                            if(murostop()) { y++; moved=0; };
                                            break;
                                       case MOVES:
                                            y++;
                                            if(murostop()) { y--; moved=0; };
                                            break;
                                       case MOVED:
                                            x++;
                                            if(murostop()) { x--; moved=0; };
                                            break;
                                       case MOVEA:
                                            x--;
                                            if(murostop()) { x++; moved=0; };
                                            break;
                                };
                                break;
                           case MOMERCANTE:
                                mercante();
                                moved=0;
                                break;
                           case MOCLOSE:
                                system("cls");
                                printf("STAI PER USCIRE.\n\nChiudi la finestra di informazioni premendo la X (in alto a destra).\n\n");
                                system("pause");
                                exit(EXIT_SUCCESS);
                                break;
                           default:
                                   moved=0;
                                   break;
              };
              if(moved) {
                        if ((((rand()%100) < MOSTROPROBERBA) && (mappabak[y][x] == (char)AERBA)) || (((rand()%100) < MOSTROPROBSTRADA) && (mappabak[y][x] == (char)ASTRADA))) {
                                          scontro((rand()%10)+1);
                                          return;
                        };
              };
     };
     return;
}

char* convgrafstr(char* str) {
      for (int i=0; i<strlen(str); i++)
          str[i]=convgrafgen(str[i]);
      return str;
}


char convgrafgen(char cha) {
           switch(cha) {
                                    case '|':
                                         return ((char) 177);
                                         break;
                                    case '!':
                                         return ((char) 185);
                                         break;
                                    case '"':
                                         return ((char) 186);
                                         break;
                                    case '£':
                                         return ((char) 187);
                                         break;
                                    case '$':
                                         return ((char) 188);
                                         break;
                                    case '^':
                                         return ((char) 200);
                                         break;
                                    case '&':
                                         return ((char) 201);
                                         break;
                                    case '/':
                                         return ((char) 202);
                                         break;
                                    case '(':
                                         return ((char) 203);
                                         break;
                                    case ')':
                                         return ((char) 204);
                                         break;
                                    case '=':
                                         return ((char) 205);
                                         break;
                                    case '?':
                                         return ((char) 206);
                                         break;
                                    default:
                                            return cha;
                                            break;
           };
}

void scontro(int diff) {
     int vita, mana, vitamo, forzamo, corporaturamo, livmo, forzautil, corporaturautil, magiautil, haspada, partaspad, partbspad, utile2pg, utile2mo;
     forzautil=forza+spada;
     corporaturautil=corporatura+armatura;
     magiautil=magia+amuleto;
     vita=50+((int) (amuleto*0.25));
     mana=50+((int) (amuleto*0.75));
     vitamo = 46+(rand()%10)+((int) (amuleto*0.18));
     forzamo = forza+((int) (spada*0.8))-6+(rand()%12);
     corporaturamo = corporatura+((int) (armatura*0.8))-6+(rand()%12);
     haspada=rand()%2;
     if (forzamo<1) forzamo=2;
     if (corporaturamo<1) corporaturamo=2;
     char nomemo[30], tempnomemo[30], menuazione, menumagia;
     int quanti=0, risultato, tot=0;
     int stop=0;
     FILE *fp, *fp2;
     fp = fopen("mostri.static", "r");
     fscanf(fp, "%s", &tempnomemo);
     while (!feof(fp)) {
           quanti++;
           fscanf(fp, "%s", &tempnomemo);
     };
     fclose(fp);
     srand((unsigned) time(NULL));
     risultato = rand()%quanti;
     fp2 = fopen("mostri.static", "r");
     fscanf(fp2, "%s", &nomemo);
     while (!stop) {
           if (tot == risultato)
                   stop=1;
           fscanf(fp2, "%s", &nomemo);
           tot++;
     };
     fclose(fp2);
     system("cls");
     printf("Incontri un %s che ti vuole sfidare...\n\nVita: %d\nForza: %d", nomemo, vitamo, forzamo);
     if(haspada) printf(" (possiede una spada)");
     printf("\nCorporatura: %d\n\n----------\n\n", corporaturamo);

     while (vitamo>0) {
           if (vita<1) {
                       scontroperso();
                       return;
           };

           char strq[200], strw[200], stre[200], strr[200], strt[200], stry[200], stru[200], stri[200], stro[200], strp[200], stra[200], strs[200], strd[200], strf[200], strg[200], strh[200], strj[200];

           system("pause");
           system("cls");
           sprintf(strq, "&==============(==========£\n\"VITA   ");
           sprintf(strw, "   \"          \"\n\"MANA   ");
           sprintf(stre, "   \"          \"\n)==============$          \"\n\"                         \"\n\"                         \"\n\"                         \"\n\"                         \"\n\"      &==================!\n\"      \"VITA   ");
           sprintf(strr, "       \"\n\"      ^=====(============!\n\"            \"q-Diretto   \"\n\"            \"w-Diversivo \"\n\"            \"e-Magia     \"\n\"            \"            \"\n^============/============$\n");
           printf("%s%4d%s%4d%s%4d%s\n\n", convgrafstr(strq), vita, convgrafstr(strw), mana, convgrafstr(stre), vitamo, convgrafstr(strr));
           menuazione=getch();
           switch (menuazione) {
                  case 'q':
                       if (haspada) {
                                    printf("Inizi a duellare con la spada.\n");
                                    if ((rand()%100)<3) {
                                         printf("Riesci a disarmarlo e buttarlo a terra.\n");
                                         haspada=0;
                                         vitamo-=11;
                                         forzamo-=3;
                                         if (forzamo<1) forzamo=1;
                                    } else {
                                           utile2pg=forzautil-1+(rand()%diff);
                                           utile2mo=forzamo+(rand()%diff);
                                           if (utile2pg>utile2mo) {
                                                  printf("Hai la meglio e lo ferisci.\n");
                                                  vitamo-=8;
                                           } else {
                                                  printf("Vieni ferito da un suo attacco.\n");
                                                  vita-=9;
                                           };
                                    };
                       } else {
                              printf("Ti trovi in vantaggio avendo un\'arma con cui combattere.\n");
                              partaspad=forzautil+(rand()%diff);
                              partbspad=forzamo+(rand()%diff);
                              if (partaspad>partbspad) {
                                 printf("Hai la meglio e lo ferisci gravemente.\n");
                                 vitamo-=10;
                              } else {
                                printf("Vieni scaraventato a terra da un suo attacco.\n");
                                vita-=10;
                              };
                       };
                       break;
                  case 'w':
                       printf("Ti muovi velocemente cercando di confonderlo e provi ad attaccarlo in un momento inaspettato.\n");
                       if ((corporaturamo+(rand()%14))>(corporaturautil+(rand()%14))) {
                               printf("Purtroppo riesce ad intercettare il tuo attacco.\n");
                               if ((rand()%100)<50) {
                                       printf("Cadi a terra semplicemente senza che lui ti colpisca.\n");
                                       vita-=7;
                               } else {
                                       printf("Mentre cadi a terra ti colpisce provocandoti molti danni data la vulnerabilita\' dell\'azione; tanti che la tua armatura va in pezzi.\n");
                                       corporaturautil=corporatura;
                                       vita-=11;
                               };
                       } else {
                              printf("Il colpo va a buon fine mentre lui non riesce a bloccarti.\n");
                              vitamo-=15;
                       };
                       break;
                  case 'e':
                       if(mana < 5) {
                               printf("Non hai abbastanza magia per invocare divinita\'.");
                               system("pause");
                       } else {
                           system("cls");
                           sprintf(strt, "&==============(==========£\n\"VITA   ");
                           sprintf(stry, "   \"          \"\n\"MANA   ");
                           sprintf(stru, "   \"          \"\n)==============$          \"\n\"                         \"\n\" &=====================£ \"\n\" \"");
                           sprintf(stri, " xx                  \" \"\n\" \"");
                           sprintf(stro, " xx                  \"=!\n\" \"");
                           sprintf(strp, "a-Orrore           5m\" \"\n\" \"");
                           sprintf(stra, "s-Invocazione     10m\" \"\n\" \"");
                           sprintf(strs, "d-Maledizione     15m\"=!\n\" \"");
                           sprintf(strd, "f-Dolore          25m\" \"\n\" \"");
                           sprintf(strf, "g-Torm. di saette 35m\"=!\n\" \"");
                           sprintf(strg, "h-Disintegrazione 50m\" \"\n\" ");
                           sprintf(strh, " xx                  \" \"\n\" ");
                           sprintf(strj, "^=====================$ \"\n\"            \"   Magia    \"\n\"            \"            \"\n^============/============$\n");
                           printf("%s%4d%s%4d%s", convgrafstr(strt), vita, convgrafstr(stry), mana, convgrafstr(stru));
                           if((magiautil>0) && (mana >=5))
                                       printf("%s", convgrafstr(strp));
                           else 
                                       printf("%s", convgrafstr(stri));
                           if((magiautil>10) && (mana >=10))
                                       printf("%s", convgrafstr(stra));
                           else 
                                       printf("%s", convgrafstr(stri));
                           if((magiautil>20) && (mana >=15))
                                       printf("%s", convgrafstr(strs));
                           else 
                                       printf("%s", convgrafstr(stro));
                           if((magiautil>30) && (mana >=25))
                                       printf("%s", convgrafstr(strd));
                           else 
                                       printf("%s", convgrafstr(stri));
                           if((magiautil>40) && (mana >=35))
                                       printf("%s", convgrafstr(strf));
                           else 
                                       printf("%s", convgrafstr(stro));
                           if((magiautil>100) && (mana >=50))
                                       printf("%s", convgrafstr(strg));
                           else 
                                       printf("%s", convgrafstr(strh));
                           printf("%s", convgrafstr(strj));
                           
                           menumagia=getch();
                           if ((rand()%100)<95) {
                             switch(menumagia) {
                                             case 'a':
                                                  if((magiautil>0) && (mana >=5)) {
                                                     printf("Il nemico si inorridisce cadendo a terra.\n");
                                                     vitamo-=4;
                                                     mana-=5;
                                                  } else {
                                                         printf("Non fai nulla e perdi vita sotto i colpi dell\'avversario. Inoltre hai sprecato mana.\n[Non premere tasti a caso.]\n");
                                                         vita-=7;
                                                         mana-=10;
                                                  };
                                                  break;
                                             case 's':
                                                  if((magiautil>10) && (mana >=10)) {
                                                     printf("Il nemico viene controllato dalle divinita\', diminuendone le caratteristiche [del 15%].\n");
                                                     vitamo=(int) (vitamo*0.85);
                                                     forzamo=(int) (forzamo*0.85);
                                                     corporaturamo=(int) (corporaturamo*0.85);
                                                     mana-=10;
                                                  } else {
                                                         printf("Non fai nulla e perdi vita sotto i colpi dell\'avversario. Inoltre hai sprecato mana.\n[Non premere tasti a caso.]\n");
                                                         vita-=7;
                                                         mana-=10;
                                                  };
                                                  break;
                                             case 'd':
                                                  if((magiautil>20) && (mana >=15)) {
                                                     printf("Maledici il nemico che perde vita.\n");
                                                     vitamo-=(rand()%5)+7;
                                                     mana-=15;
                                                  } else {
                                                         printf("Non fai nulla e perdi vita sotto i colpi dell\'avversario. Inoltre hai sprecato mana.\n[Non premere tasti a caso.]\n");
                                                         vita-=7;
                                                         mana-=10;
                                                  };
                                                  break;
                                             case 'f':
                                                  if((magiautil>30) && (mana >=25)) {
                                                     printf("Il nemico sente un dolore continuo dall\'interno del suo corpo, diminuendone le caratteristiche [del 50%].\n");
                                                     vitamo=(int) (vitamo*0.5);
                                                     forzamo=(int) (forzamo*0.5);
                                                     corporaturamo=(int) (corporaturamo*0.5);
                                                     mana-=25;
                                                  } else {
                                                         printf("Non fai nulla e perdi vita sotto i colpi dell\'avversario. Inoltre hai sprecato mana.\n[Non premere tasti a caso.]\n");
                                                         vita-=7;
                                                         mana-=10;
                                                  };
                                                  break;
                                             case 'g':
                                                  if((magiautil>40) && (mana >=35)) {
                                                     printf("Saette piovono dal cielo puntando sul tuo nemico che perde vita.\n");
                                                     vitamo-=((rand()%11)+27);
                                                     mana-=35;
                                                  } else {
                                                         printf("Non fai nulla e perdi vita sotto i colpi dell\'avversario. Inoltre hai sprecato mana.\n[Non premere tasti a caso.]\n");
                                                         vita-=7;
                                                         mana-=10;
                                                  };
                                                  break;
                                             case 'h':
                                                  if((magiautil>100) && (mana >=50)) {
                                                     printf("Vedi che il tuo nemico dividersi in parti che diventano polvere, riducendo al minimo le sue possibilita\'.\n");
                                                     vitamo-=((rand()%10)+41);
                                                     mana-=50;
                                                  } else {
                                                         printf("Non fai nulla e perdi vita sotto i colpi dell\'avversario. Inoltre hai sprecato mana.\n[Non premere tasti a caso.]\n");
                                                         vita-=7;
                                                         mana-=10;
                                                  };
                                                  break;
                                            default:
                                                   printf("Non fai nulla e perdi vita sotto i colpi dell\'avversario. Inoltre hai sprecato mana.\n[Non premere tasti a caso.]\n");
                                                   vita-=7;
                                                   mana-=10;
                                                   break;
                             };
                             if (mana<0) mana=0;
                             system("pause");
                             printf("\n\nDopo essersi ripreso il nemico attacca e cerchi di difenderti.\n");
                             if ((forzamo+corporaturamo)>(forza+corporatura+5+(rand()%6))) {
                                   printf("Riesce ad attaccare sebbene indebolito da forze magiche.\n");
                                   vita-=5;
                             } else {
                                   printf("Le forze gli vengono a mancare e non conclude l\'azione.\n");
                             };
                           } else {
                             printf("L\'avversario resiste alla tua forza magica, forse protetto da qualche divinita\'.\n");
                             if ((forzamo+corporaturamo)>(forza+(rand()%corporatura))) {
                                   printf("Ti attacca ferendoti.\n");
                                   vita-=7;
                             } else {
                                   printf("Non riesce pero\' ad attaccarti.\n");
                             };
                           };
                       };
                       break;
                  default:
                          printf("----------\n\n");
                          printf("Non fai nulla e perdi vita sotto i colpi dell\'avversario.\n[Non premere tasti a caso.]\n");
                          vita-=10;
                          break;
           };
     };
     scontrovinto(diff);
     return;
}

void scontrovinto(int diff) {
     char nomearma[30], tempnomearma[30];
     int probarma, aumento;
     printf("\nHAI BATTUTO L\'AVVERSARIO.\n");
     printf("Invochi alcune magie e ripari la tua armatura e la tua spada.\n");
     printf("Guadagni %d di esperienza.\n", aggiungiexpmostro(diff));
     if ((rand()%100) < 33) {
            printf("Rovistando attorno al suo corpo trovi qualcosa...\n\n");
             int quanti=0, risultato, tot=0;
             int stop=0;
             FILE *fp, *fp2;
             fp = fopen("armi.static", "r");
             fscanf(fp, "%s", &tempnomearma);
             while (!feof(fp)) {
                   quanti++;
                   fscanf(fp, "%s", &tempnomearma);
             };
             fclose(fp);
             srand((unsigned) time(NULL));
             risultato = rand()%quanti;
             fp2 = fopen("armi.static", "r");
             fscanf(fp2, "%s", &nomearma);
             while (!stop) {
                   if (tot == risultato)
                           stop=1;
                   fscanf(fp2, "%s", &nomearma);
                   tot++;
             };
             fclose(fp2);
            probarma = rand()%100;
            aumento=rand()%6;
            if (probarma < 29) {
                         spada+=aumento;
                         strcpy(nomespada, nomearma);
                         printf("Hai trovato la spada %s (+ %d) e, dopo aver lasciato la vecchia spada vicino al corpo del tuo avversario, la prendi con te.\n", nomespada, spada);
            } else if (probarma < 61) {
                         armatura+=aumento;
                         strcpy(nomearmatura, nomearma);
                         printf("Hai trovato l\'armatura %s (+ %d) e, dopo aver lasciato la vecchia armatura vicino al corpo del tuo avversario, la indossi.\n", nomearmatura, armatura);
            } else {
                         amuleto+=aumento;
                         strcpy(nomeamuleto, nomearma);
                         printf("Hai trovato l\'amuleto %s (+ %d) e, dopo aver distrutto il tuo vecchio amuleto, lo indossi.\n", nomeamuleto, amuleto);
            };
     } else {
            printf("Rovisti attorno al suo corpo e non trovi nulla che ti potrebbe aiutare.\n");
     };
     printf("\n");
     system("pause");
     _sleep(500);
     gioco();
     return;
}

void scontroperso(void) {
     system("cls");
     printf("L\'AVVERSARIO TI HA MESSO IN COMA E SE NE VA SODDISFATTO.\n");
     _sleep(500);
     if ((rand()%100) < PROBCHIERICO) {
          printf("Per tua fortuna sta passando nelle vicinanze un chierico curatore.\nSi avvicina al tuo corpo e ti stabilizza pronunciando alcuni antichi rituali.\nRiesci a rialzarti solo dopo alcune ore...\n\n[Attendi 15 secondi prima di riprendere il gioco.]");
          exp -= liv;
          if (exp<0) exp=0;
          _sleep(15000);
          system("pause");
          gioco();
     } else {
          printf("Il tuo corpo sta passando nell\'aldila\'.\nTra poco sarai presentato agli dei che ti giudicheranno.\n");
          _sleep(500);
          system("pause");
          presentazionedivinita();
     };
     return;
}

void presentazionedivinita(void) {
     FILE *fp;
     system("cls");
     printf("Ti trovi al cospetto di tutte le divinita\' che stanno confabulando sulle tue sorti...\n\n");
     _sleep(2000);
     if (liv > 7) {
        printf("Dopo averti fatto alcune domande sulle tue competenze, decidono di farti tornare in vita.\n\nTi vengono tolti due livelli ed azzerata l\'esperienza di livello acquisita.\nDopo un po\' di tempo vieni addormentato e ti risvegli dove eri entrato in coma molto stanco...\n");
        liv=liv-2;
        exp=0;
        system("pause");
        gioco();
     } else {
        printf("Essendo tu alle prime armi, le divinita\' decidono di farti reincarnare in un nuovo corpo (la tua anima non verra\' quindi sprecata).\n\n[Chiudi la finestra di informazioni prima di continuare.]\n");
        fp = fopen("userpg.data", "w");
        fprintf(fp, "11\n");
        fclose(fp);
        system("pause");
        system("start start.exe");
        exit(EXIT_SUCCESS);
     };
     return;
}

int aggiungiexpmostro(int diff) {
    int aggiunta=0;
    if ((liv>11) && (liv<50)) {
            aggiunta += diff*(liv-1);
    } else {
            aggiunta += diff*10;
    };
    if (liv>=50)
       aggiunta=50+diff;
    if (aggiunta<1) aggiunta=1;
    exp+=aggiunta;
    checklivello();
    return aggiunta;
}

void checklivello(void) {
     if (exp>=(100*(liv-4))) {
          liv++;
          forza=(int) (forza/(liv-5)*(liv-4));
          corporatura=corporatura+1+(rand()%((int) (liv/2)));
          magia=(int) (magia/(liv-5)*(liv-4));
          magia++;
          exp=0;
     };
     return;
}

void aggiungiexpstrada(void) {
     exp+=(int) (liv/5);
     checklivello();
     srand((unsigned) (time(NULL)+exp));
     return;
}

void mercante(void) {
     if (liv<8) {
                system("cls");
                printf("Non hai raggiunto il livello necessario (livello 8) per poter cercare un mercante e poter acquistare armi, armature o amuleti.\n");
                system("pause");
                return;
     };
     if ((rand()%100) < 65) {
            system("cls");
            printf("Trovi nelle vicinanze un mercante che trasporta su un carro diverse cose.\nDopo esservi presentati l\'uno all\'altro inizia a mostrarti la merce di tuo interesse.\n\n");
            char nomearma[30], tempnomearma[30], sceltacomprare;
            int probarma, aumento, expcosto, tipoproposto;
             int quanti=0, risultato, tot=0;
             int stop=0;
             FILE *fp, *fp2;
             fp = fopen("armi.static", "r");
             fscanf(fp, "%s", &tempnomearma);
             while (!feof(fp)) {
                   quanti++;
                   fscanf(fp, "%s", &tempnomearma);
             };
             fclose(fp);
             srand((unsigned) time(NULL));
             risultato = rand()%quanti;
             fp2 = fopen("armi.static", "r");
             fscanf(fp2, "%s", &nomearma);
             while (!stop) {
                   if (tot == risultato)
                           stop=1;
                   fscanf(fp2, "%s", &nomearma);
                   tot++;
             };
             fclose(fp2);
            probarma = rand()%100;
            aumento=rand()%6;
            expcosto=(18+(rand()%5))*(liv-6);
            if (probarma < 29) {
                         tipoproposto=1;
                         printf("Ti mostra la spada %s (+ %d) e dice che ti costera\' %d punti esperienza o due livelli senza modificare le caratteristiche (nel caso tu non avessi abbastanza punti esperienza liberi del livello).\n", nomearma, spada+aumento, expcosto);
            } else if (probarma < 61) {
                         tipoproposto=2;
                         printf("Ti mostra l\'armatura %s (+ %d) e dice che ti costera\' %d punti esperienza o due livelli senza modificare le caratteristiche (nel caso tu non avessi abbastanza punti esperienza liberi del livello).\n", nomearma, armatura+aumento, expcosto);
            } else {
                         tipoproposto=3;
                         printf("Ti mostra l\'amuleto %s (+ %d) e dice che ti costera\' %d punti esperienza o due livelli senza modificare le caratteristiche (nel caso tu non avessi abbastanza punti esperienza liberi del livello).\n", nomearma, amuleto+aumento, expcosto);
            };
            printf("Accetti la proposta\?\n[Per accettare premi \'s\'; per rifiutare premi un qualsiasi altro tasto.]\n");
            sceltacomprare=getch();
            if (sceltacomprare == 's') {
                if (tipoproposto == 1) {
                             spada+=aumento;
                             strcpy(nomespada, nomearma);
                             compratomerc(expcosto);
                             printf("Hai acquistato la spada %s (+ %d) e gli regali la tua precedente in cambio della disponibilita\'.\n", nomespada, spada);
                } else if (tipoproposto == 2) {
                             armatura+=aumento;
                             strcpy(nomearmatura, nomearma);
                             compratomerc(expcosto);
                             printf("Hai acquistato l\'armatura %s (+ %d) e gli regali la tua precedente in cambio della disponibilita\'.\n", nomearmatura, armatura);
                } else {
                             amuleto+=aumento;
                             strcpy(nomeamuleto, nomearma);
                             compratomerc(expcosto);
                             printf("Hai acquistato l\'amuleto %s (+ %d) e distruggi il tuo precedente.\n", nomeamuleto, amuleto);
                };
            };
            printf("Saluti ringraziando il mercante e ritorni sui tuoi passi...\n");
            system("pause");
     } else {
            system("cls");
            printf("Purtroppo non vedi nessuno attorno a te che ti possa aiutare...\n[Attendi 2 secondi per il tempo impiegato a cercare nelle vicinanze.]\n");
            _sleep(2000);
            system("pause");
     };
     return;
}

void compratomerc(int pxnec) {
     if (exp<pxnec) liv-=2;
     else exp-=pxnec;
     return;
}
