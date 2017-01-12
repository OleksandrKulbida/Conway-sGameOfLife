#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>
#include <conio.h>

#define STR 50
#define CLN 50


typedef enum{
    DEAD    = 0,
    LIVE    = 1,
    BORNED  = 3,
    DYING   = 4,
}eConditionOfCell;

typedef enum{
    eGlider      = 0,
    eBlinker     = 1,
    eCross       = 2,
    eKokSGalax   = 3,
    ePentadeca   = 4,
    eSpaceShip   = 5,
    eReturn      = 6,
    eNumberOfConfigurayions = 7,
}eConditions;

typedef enum{
    RandMap         = 0,
    Map             = 1,
    Configurations  = 2,
    Exit            = 3,
}eMenu;

typedef enum{
    kUp     = 72,
    kDown   = 80,
    kEnter  = 13,
    kEsc    = 27,
}eKey;

HANDLE gconsoleHandle = 0;

void drawMap(int array[STR][CLN]);
void drawMenu(int counterMenu);
void drawClearMenu();
void drawClearMap(int array[STR][CLN]);
void drawConfigurationMenu(int counterMenu);
void drawClearConfigurationMenu();

void ranMap(int array[STR][CLN]);
int calculateNeighbor(int array[STR][CLN], int i, int j);

int checkupIp(int i);
int checkupIm(int i);
int checkupJp(int j);
int checkupJm(int j);
int checkCounterMenu(int counterMenu);
int checkupCounterConfigurationMenu(int counterMenu);
int checkupCounterMenu(int counterMenu);
bool checkupEndRandMap(int array[STR][CLN], bool play);

int mainMenu();
int configurationMenu();

void initConsoleForMenu() {
    CONSOLE_CURSOR_INFO curInfo;
    curInfo.bVisible = FALSE;
    curInfo.dwSize   = 1;
    system("mode con lines=55 cols=60");
    gconsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorInfo(gconsoleHandle, &curInfo);

}
void initConsoleForRandMap() {
    CONSOLE_CURSOR_INFO curInfo;
    curInfo.bVisible = FALSE;
    curInfo.dwSize   = 1;
    system("mode con lines=55 cols=60");
    gconsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorInfo(gconsoleHandle, &curInfo);
}

/* Configurations */
void Glider(int array[STR][CLN], int i, int j){
    array[0+i][1+j] = LIVE;
    array[1+i][2+j] = LIVE;
    array[2+i][0+j] = LIVE;
    array[2+i][1+j] = LIVE;
    array[2+i][2+j] = LIVE;
}
void Blinker(int array[STR][CLN], int i, int j){
    array[0+i][1+j] = LIVE;
    array[1+i][1+j] = LIVE;
    array[2+i][1+j] = LIVE;
}
void Cross(int array[STR][CLN], int i, int j){
    array[1+i][3+j] = LIVE;
    array[1+i][4+j] = LIVE;
    array[1+i][5+j] = LIVE;
    array[1+i][6+j] = LIVE;
    array[2+i][3+j] = LIVE;
    array[2+i][6+j] = LIVE;
    array[3+i][1+j] = LIVE;
    array[3+i][2+j] = LIVE;
    array[3+i][3+j] = LIVE;
    array[3+i][6+j] = LIVE;
    array[3+i][7+j] = LIVE;
    array[3+i][8+j] = LIVE;
    array[4+i][1+j] = LIVE;
    array[4+i][8+j] = LIVE;
    array[5+i][1+j] = LIVE;
    array[5+i][8+j] = LIVE;
    array[6+i][1+j] = LIVE;
    array[6+i][2+j] = LIVE;
    array[6+i][3+j] = LIVE;
    array[6+i][6+j] = LIVE;
    array[6+i][7+j] = LIVE;
    array[6+i][8+j] = LIVE;
    array[7+i][3+j] = LIVE;
    array[7+i][6+j] = LIVE;
    array[8+i][3+j] = LIVE;
    array[8+i][4+j] = LIVE;
    array[8+i][5+j] = LIVE;
    array[8+i][6+j] = LIVE;

}
void KokSGalaxy(int array[STR][CLN], int i, int j){
    array[0+3+i][3+3+j] = LIVE;
    array[0+3+i][4+3+j] = LIVE;
    array[0+3+i][5+3+j] = LIVE;
    array[0+3+i][6+3+j] = LIVE;
    array[0+3+i][7+3+j] = LIVE;
    array[0+3+i][8+3+j] = LIVE;
    array[0+3+i][9+3+j] = LIVE;
    array[1+3+i][3+3+j] = LIVE;
    array[1+3+i][4+3+j] = LIVE;
    array[1+3+i][5+3+j] = LIVE;
    array[1+3+i][6+3+j] = LIVE;
    array[1+3+i][7+3+j] = LIVE;
    array[1+3+i][8+3+j] = LIVE;
    array[1+3+i][9+3+j] = LIVE;
    array[0+3+i][0+3+j] = LIVE;
    array[1+3+i][0+3+j] = LIVE;
    array[2+3+i][0+3+j] = LIVE;
    array[3+3+i][0+3+j] = LIVE;
    array[4+3+i][0+3+j] = LIVE;
    array[5+3+i][0+3+j] = LIVE;
    array[6+3+i][0+3+j] = LIVE;
    array[0+3+i][1+3+j] = LIVE;
    array[1+3+i][1+3+j] = LIVE;
    array[2+3+i][1+3+j] = LIVE;
    array[3+3+i][1+3+j] = LIVE;
    array[4+3+i][1+3+j] = LIVE;
    array[5+3+i][1+3+j] = LIVE;
    array[6+3+i][1+3+j] = LIVE;
    array[9+3+i][0+3+j] = LIVE;
    array[9+3+i][1+3+j] = LIVE;
    array[9+3+i][2+3+j] = LIVE;
    array[9+3+i][3+3+j] = LIVE;
    array[9+3+i][4+3+j] = LIVE;
    array[9+3+i][5+3+j] = LIVE;
    array[9+3+i][6+3+j] = LIVE;
    array[8+3+i][0+3+j] = LIVE;
    array[8+3+i][1+3+j] = LIVE;
    array[8+3+i][2+3+j] = LIVE;
    array[8+3+i][3+3+j] = LIVE;
    array[8+3+i][4+3+j] = LIVE;
    array[8+3+i][5+3+j] = LIVE;
    array[8+3+i][6+3+j] = LIVE;
    array[3+3+i][8+3+j] = LIVE;
    array[4+3+i][8+3+j] = LIVE;
    array[5+3+i][8+3+j] = LIVE;
    array[6+3+i][8+3+j] = LIVE;
    array[7+3+i][8+3+j] = LIVE;
    array[8+3+i][8+3+j] = LIVE;
    array[9+3+i][8+3+j] = LIVE;
    array[3+3+i][9+3+j] = LIVE;
    array[4+3+i][9+3+j] = LIVE;
    array[5+3+i][9+3+j] = LIVE;
    array[6+3+i][9+3+j] = LIVE;
    array[7+3+i][9+3+j] = LIVE;
    array[8+3+i][9+3+j] = LIVE;
    array[9+3+i][9+3+j] = LIVE;

}
void Pentadecathlon(int array[STR][CLN], int i, int j){
    array[3+2+i][4+j] = LIVE;
    array[8+2+i][4+j] = LIVE;
    array[1+2+i][5+j] = LIVE;
    array[2+2+i][5+j] = LIVE;
    array[4+2+i][5+j] = LIVE;
    array[5+2+i][5+j] = LIVE;
    array[6+2+i][5+j] = LIVE;
    array[7+2+i][5+j] = LIVE;
    array[9+2+i][5+j] = LIVE;
    array[10+2+i][5+j] = LIVE;
    array[3+2+i][6+j] = LIVE;
    array[8+2+i][6+j] = LIVE;
}
void SpaceShip(int array[STR][CLN], int i, int j){
    array[0+i][0+j] = LIVE;
    array[1+i][0+j] = LIVE;
    array[2+i][0+j] = LIVE;
//    array[3+i][0+j] = LIVE;
    array[2+i][1+j] = LIVE;
    array[3+i][1+j] = LIVE;
    array[0+i][2+j] = LIVE;
    array[1+i][2+j] = LIVE;
    array[2+i][2+j] = LIVE;
//    array[3+i][2+j] = LIVE;
}

int checkupIp(int i){
   int n = 0;
   if(i+1 == STR){
       n = -1;
   }else{
       n = i;
   }
   return n;
}
int checkupIm(int i){
   int n = 0;
   if(i-1 < 0){
       n = STR;
   }else{
       n = i;
   }
   return n;
}
int checkupJp(int j){
    int m = 0;
    if(j+1 == CLN){
        m = -1;
    }else{
        m = j;
    }
    return m;
}
int checkupJm(int j){
    int m = 0;
    if(j-1 < 0){
        m = CLN;
    }else{
        m = j;
    }
    return m;
}
int calculateNeighbor(int array[STR][CLN], int i, int j, int condition){
    int counterNeighbors = 0, cip, cim, cjp, cjm;

    cip = checkupIp(i);
    cim = checkupIm(i);
    cjp = checkupJp(j);
    cjm = checkupJm(j);

    if(array[cip+1][j] == condition){
        counterNeighbors++;
    }
    if(array[cim-1][j] == condition){
        counterNeighbors++;
    }
    if(array[i][cjp+1] == condition){
        counterNeighbors++;
    }
    if(array[i][cjm-1] == condition){
        counterNeighbors++;
    }
    if(array[cip+1][cjp+1] == condition){
        counterNeighbors++;
    }
    if(array[cim-1][cjm-1] == condition){
        counterNeighbors++;
    }
    if(array[cip+1][cjm-1]  == condition){
        counterNeighbors++;
    }
    if(array[cim-1][cjp+1]  == condition){
        counterNeighbors++;
    }
    return counterNeighbors;
}
void born(int array[STR][CLN]){
    int i, j, counter;
    for (i = 0; i < STR; ++i){
        for (j = 0; j < CLN; ++j) {
            counter = calculateNeighbor(array, i, j, LIVE);
            if(array[i][j] == DEAD){
                if(counter == 3){
                    array[i][j] = BORNED;
                }
            }
        }
    }
}
void dying(int array[STR][CLN]){
    int i, j, counter;

    for (i = 0; i < STR; ++i){
        for (j = 0; j < CLN; ++j) {
            counter = calculateNeighbor(array, i, j, LIVE) + calculateNeighbor(array, i, j, DYING);
            if(array[i][j] == LIVE){
                if(counter != 2 && counter != 3){
                    array[i][j] = DYING;
                }
            }
        }
    }
}
void destinyOfCell(int array[STR][CLN]){
    int i, j;

    born(array);
    dying(array);
    for (i = 0; i < STR; ++i){
        for (j = 0; j < CLN; ++j) {
            if(array[i][j] == BORNED){
                array[i][j] = LIVE;
                }
            else if(array[i][j] == DYING){
                array[i][j] = DEAD;
                }
        }
    }
}


/* =>Main menu<= */
int mainMenu(){

    int counterMenu = 0;
    for(;;){
    counterMenu = checkupCounterMenu(counterMenu);
    drawMenu(counterMenu );
    switch(getch()){
      case kUp:
        counterMenu--;
        break;
      case kDown:
        counterMenu++;
        break;
      case kEnter:
        drawClearMenu();
        return counterMenu;
        break;
      case kEsc:
        drawClearMenu();
        return counterMenu = Exit;
        return 0;
        break;
        default:
            printf("\n");
            break;
    }
  }
}
void drawMenu(int counterMenu){
        int array[4];
        array[0] = RandMap;
        array[1] = Map;
        array[2] = Configurations;
        array[3] = Exit;

        int i = 0;
        COORD pos;

    for(i = 0; i < 4; i++){
            pos.X = 0;
            pos.Y = i;
            SetConsoleCursorPosition(gconsoleHandle, pos);
            switch(array[i]){
                case RandMap:
                if(counterMenu == 0){
                    printf("    =>RAND MAP<=    ");
                }else{
                    printf("    rand map     ");
                }
                break;
                case Map:
                if(counterMenu == 1){
                    printf("    =>MAP<= ");
                }else{
                    printf("    map    ");
                }
                break;
                case Configurations:
                if(counterMenu == 2){
                    printf("    =>CONFIGURATIONS<=  ");
                }else{
                    printf("    configurations    ");
                }
                break;
                case Exit:
                if(counterMenu == 3){
                    printf("    =>EXIT<=    ");
                }else{
                    printf("    exit    ");
                }
                break;
                default:
                    printf("\n");
                    break;
        }
    printf("\n");
    }
}
void drawClearMenu(){
    int i, array[4];
    COORD pos;

    for(i = 0; i < 4; i++){
        array[i]=0;
        pos.X = 0;
        pos.Y = i;
        SetConsoleCursorPosition(gconsoleHandle, pos);
        switch(array[i]){
            case 0:
                printf("                      ");
            break;
        }
    }
}
int checkupCounterMenu(int counterMenu){
    if(counterMenu < 0){
        counterMenu = 3;
    }
    if(counterMenu > 3){
        counterMenu = 0;
    }
        return counterMenu;
    }

/* =>RandMap<= */
void ranMap(int array[STR][CLN]){
    int i,j;
    srand(time(0));
    for(i = 0; i < STR; i++) {
        for(j = 0; j < CLN; j++) {
            array[i][j] = 0 + rand() % 2;
        }
    }
}
void drawMap(int array[STR][CLN]){
    int i = 0, j = 0;
    COORD pos;

    for(i = 0; i < STR; i++){
        for(j = 0; j < STR; j++){
            pos.X = j;
            pos.Y = i;
            SetConsoleCursorPosition(gconsoleHandle, pos);
            switch(array[i][j]){
            case 0:
                printf(" ");
                break;
            case 1:
                printf("%c", 219);
                break;
            }
        }
        printf("\n");
    }
}
void drawClearMap(int array[STR][CLN]){
    int i = 0, j = 0;
    COORD pos;

    for(i = 0; i < STR; i++){
        for(j = 0; j < STR; j++){
            pos.X = i;
            pos.Y = j;
            SetConsoleCursorPosition(gconsoleHandle, pos);
            switch(array[i][j]){
            case 0:
                printf(" ");
                break;
            case 1:
                printf(" ");
                break;
            }
        }
        printf("\n");
    }
}
bool conditionRandMap(bool play){
    int map[STR][CLN] = {0};
     ranMap(map);
    KokSGalaxy(map, 0, 0);
     while(play == true){
         drawMap(map);
         Sleep(70);
         destinyOfCell(map);
         play = checkupEndRandMap(map, play);
     }
     drawClearMap(map);
     return play;
}
bool checkupEndRandMap(int array[STR][CLN], bool play){
    int counter = 0, i, j;
    for(i = 0; i < STR; i++){
        for(j = 0; j < STR; j++){
           counter = counter + array[i][j];
        }
    }
    if(counter != 0){
        play = true;
    }else{
        play = false;
    }
    return play;
}

/* =>Map<= */
bool mapOfConfigurations(bool play){
    int map[STR][CLN] = {0};
    Glider(map, 0, 0);
    Cross(map, 10, 10);
    Pentadecathlon(map, 10, 30);
     while(play == true){
         drawMap(map);
         Sleep(10);
         destinyOfCell(map);
         play = checkupEndRandMap(map, play);
     }
     drawClearMap(map);
     return play;
}
bool checkupEndMapOfConfigurations(int array[STR][CLN], bool play){
    int counter = 0, i, j;
    for(i = 0; i < STR; i++){
        for(j = 0; j < STR; j++){
           counter = counter + array[i][j];
        }
    }
    if(counter != 0){
        play = true;
    }else{
        play = false;
    }
    return play;
}


/* =>Configuration<= */
bool conditionsMap(bool play, int conditionOfConfigurations){
    int map[STR][CLN] = {0};
    if(conditionOfConfigurations == eGlider){
        Glider(map, 0, 0);
        }
    if(conditionOfConfigurations == eBlinker){
        Blinker(map, 2, 2);
        }
    if(conditionOfConfigurations == eCross){
        Cross(map, 0, 0);
        }
    if(conditionOfConfigurations == eKokSGalax){
        KokSGalaxy(map, 0, 0);
        }
    if(conditionOfConfigurations == ePentadeca){
        Pentadecathlon(map, 0, 0);
        }
    if(conditionOfConfigurations == eSpaceShip){
        SpaceShip(map, 5, 5);
        }
    if(conditionOfConfigurations == eReturn){
        play = false;
       }
     while(play == true){
         drawMap(map);
         Sleep(60);
         destinyOfCell(map);
         play = checkupEndRandMap(map, play);
     }
     drawClearMap(map);
     return play;
}
void drawConfigurationMenu(int counterMenu){
        int array[eNumberOfConfigurayions];
        array[0] = eGlider   ;
        array[1] = eBlinker  ;
        array[2] = eCross    ;
        array[3] = eKokSGalax;
        array[4] = ePentadeca;
        array[5] = eSpaceShip;
        array[6] = eReturn;

        int i = 0;
        COORD pos;

    for(i = 0; i < eNumberOfConfigurayions; i++){
            pos.X = 0;
            pos.Y = i;
            SetConsoleCursorPosition(gconsoleHandle, pos);
            switch(array[i]){
                case eGlider:
                if(counterMenu == eGlider){
                    printf("    =>GLIDER<=    ");
                }else{
                    printf("    glider     ");
                }
                break;
                case eBlinker:
                if(counterMenu == eBlinker){
                    printf("    =>BLINKER<= ");
                }else{
                    printf("    blinker    ");
                }
                break;
                case eCross:
                if(counterMenu == eCross){
                    printf("    =>CROSS<=  ");
                }else{
                    printf("    cross    ");
                }
                break;
                case eKokSGalax:
                if(counterMenu == eKokSGalax){
                    printf("    =>KOKS GALAXY<=    ");
                }else{
                    printf("    koks galaxy    ");
                }
                break;
                case ePentadeca:
                if(counterMenu == ePentadeca){
                    printf("    =>PENTADECA<=    ");
                }else{
                    printf("    pentadeca    ");
                }
                break;
                case eSpaceShip:
                if(counterMenu == eSpaceShip){
                    printf("    =>SPACE SHIP<=    ");
                }else{
                    printf("    space ship    ");
                }
                break;
                case eReturn:
                if(counterMenu == eReturn){
                    printf("    =>RETURN<=    ");
                }else{
                    printf("    return    ");
                }
                break;
                default:
                    printf("\n");
                    break;
        }
    printf("\n");
    }
}
void drawClearConfigurationMenu(){
    int i, array[eNumberOfConfigurayions];
    COORD pos;

    for(i = 0; i < eNumberOfConfigurayions; i++){
        array[i]=0;
        pos.X = 0;
        pos.Y = i;
        SetConsoleCursorPosition(gconsoleHandle, pos);
        switch(array[i]){
            case 0:
                printf("                          ");
            break;
        }
    }
}
int checkupCounterConfigurationMenu(int counterMenu){
    if(counterMenu < 0){
        counterMenu = eNumberOfConfigurayions - 1;
    }
    if(counterMenu > eNumberOfConfigurayions - 1){
        counterMenu = 0;
    }
        return counterMenu;
    }
int configurationMenu(){

    int counterMenu = 0;
    for(;;){
    counterMenu = checkupCounterConfigurationMenu(counterMenu);
    drawConfigurationMenu(counterMenu );
    switch(getch()){
      case kUp:
        counterMenu--;
        break;
      case kDown:
        counterMenu++;
        break;
      case kEnter:
        drawClearConfigurationMenu();
        return counterMenu;
        break;
      case kEsc:
        break;
        default:
            printf("\n");
            break;
    }
  }
}

/**/
int main(void) {
    int condition = 0, conditionForConfigerations = 0;

    initConsoleForMenu();
    while(condition != Exit){
        condition = mainMenu();
        bool play = true;
        if(condition == RandMap){
            initConsoleForRandMap();
            while(play == true){
               play = conditionRandMap(play);
            }
        }if(condition == Map){
            initConsoleForRandMap();
            while(play == true){
               play = mapOfConfigurations(play);
            }
        }if(condition == Configurations){
            initConsoleForRandMap();
                conditionForConfigerations = configurationMenu();

                conditionsMap(play, conditionForConfigerations);
                }

    }
    return 0;
}
