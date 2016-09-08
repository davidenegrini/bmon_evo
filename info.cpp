/****************************************************
                     B--Mon EVO                      
    (Black and white C written role playing game)
                SpiritOfTheForest.org
        VERSIONE: 1.2b
        FILE: info.cpp                  
****************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(void) {
    FILE *fp;
    char nome[50], nomespada[30], nomearmatura[30], nomeamuleto[30];
    int saved, forza, corporatura, magia, exp, liv, x, y, spada, armatura, amuleto;
    while(1) {
            system("cls");
            printf("INFORMAZIONI PG (aggiornato ogni 3 secondi)\n\n");
            fp = fopen("userpg.data", "r");
            fscanf(fp, "%d\n%s\n%d %d %d\n%d %d\n%d %d\n%d %d %d\n%s\n%s\n%s\n", &saved, &nome, &forza, &corporatura, &magia, &x, &y, &exp, &liv, &spada, &armatura, &amuleto, &nomespada, &nomearmatura, &nomeamuleto);
            fclose(fp);
            printf("Nome: %s\nForza: %d\nCorporatura: %d\nMagia: %d\nEsperienza: %d (%d per livello %d)\nLivello: %d\nSpada %s (+%d)\nArmatura %s (+%d)\nAmuleto %s (+%d)\n", nome, forza, corporatura, magia, exp, ((liv-4)*100)-exp, liv+1,  liv, nomespada, spada, nomearmatura, armatura, nomeamuleto, amuleto);
            printf("\nPer uscire dal gioco premi semplicemente le X in alto a destra delle finestre.\nPer cercare un mercante in zona premi il tasto \'m\'.\n");
            _sleep(3000);
    };
    return 0;
}
