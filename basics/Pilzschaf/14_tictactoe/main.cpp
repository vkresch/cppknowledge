#include <iostream>
#include <stdlib.h>
#include <time.h>

char field[10];

void clearConsole(){
    system("clear");
}

void resetField(){
    for(int i=0;i<10;i++){
        field[i] = ' ';
    }
}

void drawField(){
    clearConsole();
    std::cout << ""
              << "     " << field[1] << " |  " << field[2] << " | " << field[3] << std::endl
              << "   ---|---|---" << std::endl
              << "     " << field[4] << " |  " << field[5] << " | " << field[6] << std::endl
              << "   ---|---|---" << std::endl
              << "     " << field[7] << " |  " << field[8] << " | " << field[9] << std::endl;
}

void singleplayer(){

}

void multiplayer(){
    
}

void help(){
    clearConsole();
    std::cout << "\n TIC TAC TOE\n\n HELP\n ====\n\n"
		<< " Singleplayer:\n -------------\n In Singleplayermode you play against the Computer.\n\n"
		<< " Multiplayer:\n ------------\n In Multiplayermode you play against a second player.\n Input switches between X and O.\n"
		<< " You can also play this mode, if you want to test new tactics or just want to play against yourself.\n\n"
		<< " Controls:\n ---------\n To choose a field you must enter a number between 1 and 9.\n"
		<< " The first field is in the top left corner. The second right next to it etc.\n"
		<< " With 'q' you always return to the menu or the program will be closed.\n - - -\n";    
}

void menu(){
    // Menu main loop
    while(true){
        resetField();
        char inputmenu;
        std::cout << "\n"
                  << "MENU\n\n"
                  << "1: Singleplayer\n"
                  << "2: Multiplayer\n"
                  << "3: Help\n"
                  << "4: Quit\n\n\n"
                  << "Input: ";
        std::cin >> inputmenu;

        if(inputmenu == '1'){
            singleplayer();
        } else if (inputmenu == '2'){
            multiplayer();
        } else if (inputmenu == '3'){
            help();
        } else if (inputmenu == '4' || inputmenu == 'q'){
            return;
        } else {
            clearConsole();
            std::cout << "\nInvalid Input!";
        }
    }
}

int main(){
    menu();
    return 0;        
}