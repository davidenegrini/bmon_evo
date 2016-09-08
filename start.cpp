/****************************************************
                     B--Mon EVO                      
    (Black and white C written role playing game)    
                SpiritOfTheForest.org
        VERSIONE: 1.2b
        FILE: start.cpp                  
****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void menu(void);
void creastatic(void);

int main(void) {
    int checkdata;
    FILE *fp;
    if(!(fp=fopen("allocstatic.data", "r")))
         creastatic();
    menu();
    return 0;
}

void menu(void) {
    char scelta, nome[50];
    int x, y, liv, exp, forza, corporatura, magia, spada, armatura, amuleto, saved;
    FILE *fp;
    system("cls");
    printf("Benvenuto in B--Mon EVO, versione 1.2b\nQuesto e\' un BNWCRPG (Black aNd White C written Role Playing Game).\n\ng. Gioca.\nn. Nuovo PG.\ne. Esci.\nc. Crediti.\n");
    scelta = getch();
    switch(scelta) {
                   case 'n':
                        system("cls");
                        printf("CREAZIONE NUOVO PG\n\nQuesto andra\' a sovrascrivere ogni precedente salvataggio.\nAl termine di ogni inserimento premi [Invio]\n\nNome: ");
                        scanf("%s", &nome);
                        printf("\nOra devi scegliere di mettere 15 punti nelle in tre caratteristiche (almeno un punto per ciascuna):\n");
                        printf("-FORZA: la potenza con cui colpisci l\'avversario. Per aumentarla usi una spada.\n");
                        printf("-CORPORATURA: l\'imponenza della tua persona. Per aumentarla usi un\'armatura.\n");
                        printf("-MAGIA: in questo mondo alcuni esseri possiedono la magia. Per aumentarla usi un amuleto che ti aiuta ad invocare le varie divinita\'.\n");
                        system("pause");
                        do {
                           printf("\nForza: ");
                           scanf("%d", &forza);
                           printf("\nCorporatura: ");
                           scanf("%d", &corporatura);
                           printf("\nMagia: ");
                           scanf("%d", &magia);
                        } while ((forza<1) || (corporatura<1) || (magia<1) || ((forza+corporatura+magia)!=15));
                        printf("\nLa tua casa e\' ai confini del mondo conosciuto. Da li\' inizierai la tua avventura e non vi farai piu\' ritorno.\n");
                        x=1;
                        y=1;
                        printf("Inoltre non hai molta esperienza sul campo di battaglia o nelle arti magiche.\n");
                        exp=20;
                        liv=5;
                        printf("Prima di partire ti vengono dati:\n-la spada Morogh(+3);\n-l\'armatura Elwynn(+3);\n-l\'amuleto Tirisfal(+3).\nEssi ti permetteranno di camminare a testa alta per la strada e combattere se necessario.\n");
                        spada=3;
                        armatura=3;
                        amuleto=3;
                        printf("Dalla prossima volta che fai partire il gioco potrai entrare andando su \"Continua partita\".\n\n");
                        saved=69;
                        system("pause");
                        fp = fopen("userpg.data", "w");
                        fprintf(fp, "%d\n%s\n%d %d %d\n%d %d\n%d %d\n%d %d %d\nMorogh\nElwynn\nTirisfal\n", saved, nome, forza, corporatura, magia, x, y, exp, liv, spada, armatura, amuleto);
                        fclose(fp);
                        printf("\n\nOra sei pronto a partire. Buona fortuna nel tuo lungo viaggio!\n");
                        system("pause");
                        menu();
                        return;
                        break;
                   case 'g':
                        fp = fopen("userpg.data", "r");
                        fscanf(fp, "%d\n", &saved);
                        fclose(fp);
                        if (saved == 69) {
                               system("start gioco.exe");
                               system("start info.exe");
                               return;
                        } else {
                               printf("\nDevi ancora creare un PG!\n\n");
                               system("pause");
                               menu();
                               return;
                        };
                        break;
                   case 'e':
                        printf("\nHai scelto di uscire.\n");
                        system("pause");
                        exit(EXIT_SUCCESS);
                        break;
                   case 'c':
                        system("cls");
                        printf("\nCREDITS B--Mon\n\nHosting del progetto: SpiritOfTheForest.org\nPrincipale ideatore: Negrini Davide\nSviluppatori: Negrini Davide, Ceolini Enea\nTesters: Dalla Riva Nicolo\'\nRingraziamo tutti i tester e giocatori!\n\n");
                        system("pause");
                        menu();
                        return;
                        break;
                   default:
                           printf("\nNon hai premuto correttamente.\n");
                           system("pause");
                           menu();
                           return;
                           break;
    };
    return;
}

void creastatic() {
     FILE *fp;
     fp = fopen("armi.static", "w");
     fprintf(fp, "Ironforged\nModan\nWestfall\nSilverpine\nRedridge\nDuskwood\nWetlands\nStormwind\nStranglethorn\nArathi\nAlterac\nSorrows\nBlasted\nBlackrock\nPlagued\nBurning\nDeadwind\nDurotar\nDustwallow\nTeldrassil\nMulgore\nMoonglade\nDarnassus\nVeiled\nThunder\nBarrens\nOrgrimmar\nStonetalon\nAshen\nDesolace\nFeralas\nTanaris\nAzshara\nFelwood\nUnGoro\nWinterspring\nSilithus\nHowling\nBorean\nFrozen\nDragonblight\nGrizzly\nZulDrak\nSholazar\nDalaran\nCrystalsong\nIcecrown\nHrothgar\nWintergrasp\nEversong\nSilvermoon\nAzuremys\nExodar\nBloodmys\nHellfire\nZangarmarsh\nTerokkar\nNagrand\nBladeEdge\nShadowmoon\nNetherstorm\nShattrath\nQuelDanas\nRagefire\nWailing\nShadowfang\nBlackfathom\nRazorfen\nUldaman\nMaraudon\nZulFarrak\nAtalHakkar\nDireMaul\nStratholme\nScholomance\nAlterac\nHellfire\nZulGurub\nBlackwing\nAhnQiraj\nMolten\nNaxxramas\nBloodFurnace\nUnderbog\nAuchenai\nBlackMorass\nSethekk\nArcatraz\nBotanica\nMechanar\nMagister\nUtgarde\nKarazhan\nHyjal\nZulAman\nTempest\nTemple\nSunwell\nSerpentshrine\nNexus\nGruuls\nOculus\nObsidianSanctum\nAhnKahet\nArchavon\nDrakTharon\nAzjolNerub\nGundrak\nUlduar\nWarsong\n");
     fclose(fp);
     fp = fopen("mostri.static", "w");
     fprintf(fp, "Beachquill\nBeigeDragon\nCannithWasp\nCarnivorousPlant\nCatapult\nCelestialBlackBear\nCelestialDireBadger\nCelestialGiantBombardierBeetle\nCelestialHippogriff\nChampa\nChestbuster\nClockworker\nClubba\nColdDrake\nDaeijineIllithid\nDrainer\nDwarfWarrior\nElfWarrior\nFacehugger\nFastHeadcrab\nFelynDisgaea\nFiendishBoar\nFiendishCrocodile\nFiendishDireWeasel\nFiendishSnakeConstrictor\nFiendishSnakeLargeViper\nFiendishWolverine\nForgefireDestrier\nGargantuanMonstrousSpider\nGlopGenie\nGoblinWarrior\nGoblinFey\nGodslayerWarrior\nHeadcrabZombie\nHollow\nHouou\nHugeMonstrousSpider\nHumanWarrior\nKinzomspore\nKolar\nLargeCatMount\nLargeMonstrousSpider\nLivingDead\nLynx\nMushku\nMysticSnake\nNazgul\nOrcWarrior\nOstrich\nPeon\nPsychoticCharger\nReaver\nReplicatorDrone\nReplicatorScout\nRidingChocobo\nSarahakktahArmyAnts\nScorpionMount\nSoulmaskSkirmisher\nSpiderLarge\nSplinter\nSulkingFlayer\nSunglariAutosoldier\nThoughtNibbler\nUrukHaiWarrior\nVampireBatSwarm\nVampireBat\nVandal\nWarg\nWingedMantle\nXNaut\nYellowCavalryChocobo\n");
     fclose(fp);
     fp = fopen("mappa.static", "w");
     fprintf(fp, "70 23\n&==(=======================(============================(============£\n\"  \"||||||||||||||||||||||| ||||||||||||||||||||||||||||\"||||||||||||\"\n\"  ^====£     &============/===============£    &==£||||\"||\"|\"|\"|\"|\"|\"\n\"       ^=£ &=$||||||||||||||||||||||||||||\"||||\"  \"||||\"||||||||||||\"\n\"  &==£   ^=$||||||||||||||&=========£|||||\"    \"  \"||||\"|||\"|\"|\"|\"||\"\n\"||\"  ^=£|||||&=====£||||||\"|||||||||^£||||\"||||\"  \"||||\"||||||||||||\"\n\"||\"||||^==£||\"     \"||||||\"   &==£|||\"||||\"    \"  \"||||\"||\"|\"|\"|\"|\"|\"\n\"||\"|||||||^==$     \"||||||\"   \"  \"|||\"||||\"||||\"  \"||||\"||||||||||||\"\n\"  \"|||||||||||     ^======/===$  \"||||||||\"    \"  \"||||\"|||\"|\"|\"|\"||\"\n\"  ^======£  &==£  ||||      ||||||||||||||\"||||\"  \"||||\"||||||||||||\"\n\"         ^==$  ^==========================!    \"  \"||||\"||\"|\"|\"|\"|\"|\"\n\"  &====£||||||||||||||||||||||||||||||||||\"||||\"  \"||||\"||||||||||||\"\n\"||\"    ^=======£|||||||||||&============= \"    \"  \"||||\"|||\"|\"|\"|\"||\"\n\"||\"||||||||||||^£||||||||||\"              \"||||\"  \"||||)==========  \"\n\"||\"|||||||||||||^£|||||||||\"     &==£     \"    \"  \"||||\"||||||||||||\"\n\"  \"||||||||||||||\"|||||||||^£    \"  ^=====$    \"  \"||||\"  \"|||||||||\"\n\"  ^=========£    ^==========$    \"|||||||||||||\"  \"||||\"  ^======£  \"\n\"            ^£|||||||||||||||||||\"|||||||||||||\"  \"||||\"|||||||||\"  \"\n\"  &======£   ^===================$|||||||||||||\"  \"    \"|||||||||\"  \"\n\"  \"      ^£||||||||||||||||||||||||||||||||||||\"  \"    \"|||||||||\"  \"\n\"  \"       ^====================================$  ^=  =/=========$  \"\n\"  \"|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\"\n^==/=================================================================$\n");
     fclose(fp);
     fp = fopen("allocstatic.data", "w");
     fprintf(fp, "69\n");
     fclose(fp);
     fp = fopen("userpg.data", "w");
     fprintf(fp, "11\n");
     fclose(fp);
     return;
}
