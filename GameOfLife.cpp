#include <iostream>
#include  <vector>
#include <cstdlib>
#include <cstdio>

#include <windows.h>

using namespace std;

#define ALIVE true
#define DEAD false

int printChar = 254;

class GameOfLiFe{
    vector <vector <bool> > matrix;
    vector <vector <bool> > previous;

    int width , height;

    bool isValidPosition(int x, int y){
        if(x >= 0 && x < height && y >= 0 && y < width){
            return true;
        }
        return false;
    }

    vector <vector <bool> > generateEmpty(int matrix_width,int matrix_height){
            vector <vector <bool> > empT;
            for(int i = 0; i < matrix_height; i++){
                vector <bool> temp;
                for(int j = 0; j < matrix_width; j++){
                    temp.push_back(DEAD);
                }
                empT.push_back(temp);
            }
            return empT;
    }

    bool deadOrAlive(int pos_x, int pos_y){
        int subsetX[] = {-1,-1,-1,0,0,1,1,1};
        int subsetY[] = {-1,0,1,-1,1,-1,0,1};

        int liveCount = 0;

        for(int i = 0; i < 8; i++){
            int neighborPosX = pos_x + subsetX[i];
            int neighborPosY = pos_y + subsetY[i];

            if(isValidPosition(neighborPosX,neighborPosY)){
                if(matrix[neighborPosX][neighborPosY] == ALIVE){
                    liveCount++;
                }
            }
        }

        if(liveCount < 2 || liveCount > 3){
            return DEAD;
        }
        else if(liveCount == 3)
        {
            return ALIVE;
        }
        else
        {
            return matrix[pos_x][pos_y];
        }

    }

    public:
        GameOfLiFe(int matrix_width, int matrix_height){
            matrix = generateEmpty(matrix_width,matrix_height);
            previous = generateEmpty(matrix_width,matrix_height);
            width = matrix_width;
            height = matrix_height;
        }
        GameOfLiFe(vector <vector <bool> > initial_state){
            matrix = initial_state;
            width = matrix.size();
            height = matrix[0].size();
        }

        bool updateState(int pos_x, int pos_y, bool state){
            if(isValidPosition(pos_x, pos_y)){
                matrix[pos_x][pos_y] = state;
                return true;
            }
            else{
                return false;
            }
        }

        void print(){
            system("cls");
            for(int i = 0; i < height; i++){
                for(int j = 0; j < width; j++){
                    if(matrix[i][j] == ALIVE){
                        cout<<char(printChar);
                    }
                    else
                    {
                        cout<<" ";
                    }

                }
                cout<<"\n";
            }
        }

        void updateScreen(HANDLE hConsole, COORD coordCur){
            for(int i = 0; i < height; i++){
                for(int j = 0; j < width; j++){
                    if(previous[i][j] != matrix[i][j]){
                        coordCur.X = j;
                        coordCur.Y = i;
                        SetConsoleCursorPosition(hConsole, coordCur);
                        if(matrix[i][j] == ALIVE){
                            printf("%c",char(printChar));
                        }
                        else{
                            printf(" ");
                        }
                    }
                }
            }
            coordCur.X = 0;
            coordCur.Y = height;
            SetConsoleCursorPosition(hConsole, coordCur);


        }

        void fillWithRandom(){
            for(int i = 0; i < height; i++){
                for(int j = 0; j < width; j++){
                    if(rand() % 6 == 0){
                        matrix[i][j] = ALIVE;
                    }
                }
            }
        }

        void fillAll(){
            bool flip = DEAD;
            for(int i = 0; i < height; i++){
                for(int j = 0; j < width; j++){
                    if(i == j || i == 1 || j == 1){
                        matrix[i][j] = ALIVE;
                    }
                }
            }
        }

        void gliderSE(int osX = 0, int osY = 0){
            updateState(osX,osY,ALIVE);
            updateState(osX+1,osY,ALIVE);
            updateState(osX+2,osY,ALIVE);
            updateState(osX+2,osY+1,ALIVE);
            updateState(osX+1,osY+2,ALIVE);
        }

        void blaster(int osX = 0, int osY = 0){
            updateState(osX,1+osY,ALIVE);
            updateState(1+osX,osY,ALIVE);
            updateState(1+osX,1+osY,ALIVE);
            updateState(1+osX,2+osY,ALIVE);
            updateState(2+osX,osY,ALIVE);
            updateState(2+osX,2+osY,ALIVE);
            updateState(3+osX,1+osY,ALIVE);
        }

        void oscillatorV(int osX = 0, int osY = 0){
            updateState(osX,osY,ALIVE);
            updateState(osX+1,osY,ALIVE);
            updateState(osX+2,osY,ALIVE);
            updateState(osX+3,osY,ALIVE);
            updateState(osX+4,osY,ALIVE);
            updateState(osX+5,osY,ALIVE);
            updateState(osX+6,osY,ALIVE);
            updateState(osX+7,osY,ALIVE);
            updateState(osX+8,osY,ALIVE);
            updateState(osX+9,osY,ALIVE);
        }

        void oscillatorH(int osX = 0, int osY = 0){
            updateState(osX+4,osY,ALIVE);
            updateState(osX+4,osY+1,ALIVE);
            updateState(osX+4,osY+2,ALIVE);
            updateState(osX+4,osY+3,ALIVE);
            updateState(osX+4,osY+4,ALIVE);
            updateState(osX+4,osY+5,ALIVE);
            updateState(osX+4,osY+6,ALIVE);
            updateState(osX+4,osY+7,ALIVE);
            updateState(osX+4,osY+8,ALIVE);
            updateState(osX+4,osY+9,ALIVE);
        }

        void gliderGunSW(int osX,int osY){
            updateState(osX+2,osY,ALIVE);
            updateState(osX+3,osY,ALIVE);
            updateState(osX+2,osY+1,ALIVE);
            updateState(osX+3,osY+1,ALIVE);

            updateState(osX+2,osY+9,ALIVE);
            updateState(osX+2,osY+10,ALIVE);
            updateState(osX+3,osY+8,ALIVE);
            updateState(osX+3,osY+10,ALIVE);
            updateState(osX+4,osY+8,ALIVE);
            updateState(osX+4,osY+9,ALIVE);

            updateState(osX+4,osY+9+7,ALIVE);
            updateState(osX+4,osY+9+8,ALIVE);
            updateState(osX+5,osY+9+7,ALIVE);
            updateState(osX+5,osY+9+9,ALIVE);
            updateState(osX+6,osY+9+7,ALIVE);

            updateState(osX,osY+23,ALIVE);
            updateState(osX,osY+24,ALIVE);
            updateState(osX+1,osY+22,ALIVE);
            updateState(osX+1,osY+24,ALIVE);
            updateState(osX+2,osY+22,ALIVE);
            updateState(osX+2,osY+23,ALIVE);

            updateState(osX,osY+24+10,ALIVE);
            updateState(osX,osY+24+11,ALIVE);
            updateState(osX+1,osY+24+10,ALIVE);
            updateState(osX+1,osY+24+11,ALIVE);

            updateState(osX+1+6,osY+24+11,ALIVE);
            updateState(osX+1+6,osY+24+11+1,ALIVE);
            updateState(osX+1+7,osY+24+11,ALIVE);
            updateState(osX+1+7,osY+24+11+2,ALIVE);
            updateState(osX+1+8,osY+24+11,ALIVE);

            updateState(osX+1+11,osY+24,ALIVE);
            updateState(osX+1+11,osY+24+1,ALIVE);
            updateState(osX+1+11,osY+24+2,ALIVE);
            updateState(osX+1+12,osY+24,ALIVE);
            updateState(osX+1+13,osY+24+1,ALIVE);
        }

        void longPat(int osX = 0, int osY = 0){
            updateState(osX+5,osY,ALIVE);
            updateState(osX+5,osY+2,ALIVE);
            updateState(osX+4,osY+2,ALIVE);

            updateState(osX+3,osY+4,ALIVE);
            updateState(osX+2,osY+4,ALIVE);
            updateState(osX+1,osY+4,ALIVE);

            updateState(osX,osY+6,ALIVE);
            updateState(osX+1,osY+6,ALIVE);
            updateState(osX+1,osY+7,ALIVE);
            updateState(osX+2,osY+6,ALIVE);

        }

        void diagonalDecan(int osX, int osY){
            for(int i = 0; i < 12; i++){
                updateState(osX+i,osY+i,ALIVE);
            }
        }

        void live(){
            vector <vector <bool> > newState;
            newState = generateEmpty(width,height);

            for(int i = 0; i < height; i++){
                for(int j = 0; j < width; j++){
                    newState[i][j] = deadOrAlive(i,j);
                }
            }
            previous = matrix;
            matrix = newState;

        }


};

int main(){

    int userChoice = 0;

    int delay = 60;

    int defaultX = 80, defaultY = 27;

    while(userChoice > 6 || userChoice < 1){
    cout<<"Welcome to John Conway's Game of Life!\n\n1. Glider\n2. Blaster\n3. Oscillator\n4. Gosper's Glider Gun\n5. Random \n6. Fill All\n7. Change Display Character: Current(\'"<<char(printChar)
    <<"\')\n8. Change Matrix Size: Current("<<defaultX<<"x"<<defaultY<<")\n9. Change Delay(in milliseconds): Current("<<delay<<" ms)\n\nENTER YOUR CHOICE: ";
    cin>>userChoice;

        if(userChoice > 9 || userChoice < 1){
            cout<<"Invalid Choice! Try Again!\a";
            Sleep(1000);
            system("cls");
        }
        if(userChoice == 7){
            int temp = 0;
            while(temp < 1 || temp > 254){
                cout<<"Enter ASCII of character to print: ";
                cin>>temp;
                if(temp < 1 || temp > 254){
                    cout<<"Invalid Character! Try Again\a\n";
                    Sleep(1000);
                }
            }
            printChar = temp;
            cout<<"\nValue Updated!";
            Sleep(500);
            system("cls");
        }
        if(userChoice == 8){
            int temp = 0;
            while(temp < 70 || temp > 150){
                cout<<"Enter Width(70 - 150) :";
                cin>>temp;
                if(temp < 70 || temp > 150){
                    cout<<"Value out of Range! Try again!\a\n";
                    Sleep(1000);
                }
            }
            defaultX = temp;
            temp = 0;
            while(temp < 25 || temp > 60){
                cout<<"Enter Height(25 - 60) :";
                cin>>temp;
                if(temp < 25 || temp > 60){
                    cout<<"Value out of Range! Try again!\a\n";
                    Sleep(1000);
                }
            }
            defaultY = temp;
            cout<<"\nValue updated!";
            Sleep(500);
            system("cls");
        }
        if(userChoice == 9){
            int temp = -1;
            while(temp < 0 || temp > 15000){
                cout<<"Enter Delay (in milliseconds): ";
                cin>>temp;
                if(temp < 0 || temp > 15000){
                    cout<<"Impractical Delay! Try again! Values Accepted 0-15000.\a\n";
                    Sleep(1000);
                }
            }
            delay = temp;
            cout<<"\nValue Updated!";
            Sleep(500);
            system("cls");
        }
    }

    GameOfLiFe game(defaultX,defaultY);

    int osX, osY;
    int userSeed = 0;
    switch(userChoice){
        case 1:
            //Glider
            osX = 0;
            osY = 60;
            game.gliderSE(osX,osY);
            break;
        case 2:
            //Blaster
            osX = 10;
            osY = 40;
            game.blaster(osX,osY);
            break;
        case 3:
            //Oscillator
            osX = 15;
            osY = 24;
            game.oscillatorV(osX,osY);
            //game.longPat(osX,osY);

            osY += 12;
            game.oscillatorH(osX,osY);
            break;
        case 4:
            //Glider Gun
            osX = 4;
            osY = 10;
            game.gliderGunSW(osX,osY);
            break;
        case 5:
            //Random Universe
            cout<<"Enter Universe Seed: ";
            cin>>userSeed;
            srand(userSeed);
            game.fillWithRandom();
            break;
        case 6:
            game.fillAll();

            break;
    }
    system("cls");

    int iteration = 0;

    cout<<"Game of Life:";
    Sleep(800);
    game.print();
        if(userChoice == 1){
            cout<<"\n\nPattern: Glider";
        }
        else if(userChoice == 2){
            cout<<"\n\nPattern: Blaster";
        }
        else if(userChoice == 3){
            cout<<"\n\nPattern: Oscillator";
        }
        else if(userChoice == 4){
            cout<<"\n\nPattern: Gosper's Glider Gun";
        }
        else if(userChoice == 5){
            cout<<"\n\nPattern: Random\nWorld Seed: "<<userSeed;
        }
        else if(userChoice == 5){
            cout<<"\n\nPattern: Fill All";
        }
        cout<<"\nWorld Size: "<<defaultX<<"x"<<defaultY;
        cout<<"\nFrame Delay : "<<delay;

    Sleep(3000);

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            if (!hConsole){
                cout<<"Unable to get Handle";
                return 0x77FF;
            }
    CONSOLE_SCREEN_BUFFER_INFO csbi = {0};
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    COORD coordCur = csbi.dwCursorPosition;
    try{

        while(1){
            game.live();
            game.updateScreen(hConsole,coordCur);
            cout<<"\n Iteration Count: "<<++iteration<<"\r";
            Sleep(delay);

        }
    }
    catch(exception e){
        cout<<"Exception Occurred";
    }
    CloseHandle(hConsole);
}
