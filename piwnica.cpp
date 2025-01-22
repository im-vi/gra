#include <iostream>
#include <windows.h>
#include <string>
#include <conio.h>
#include <thread>
#include <winuser.h>
using namespace std;

void spacer();
void setColor(int color);
void exitMenu();
void renderMenu();
void renderStats();
void renderInput();
void openInventory();
void initializeGameState();
void changeGameState(string state);
void intro();
void playNote(int frequency, int duration);
void playIntroMusic();
void renderPlayer();
void biome1();
void biome1Battle();

string nick;
int hp = 100;
int gold = 0;
// Menu, IntroSequence, Biome1, Biome1Battle, Biome1Boss, Biome2, Biome2Store, Biome2Battle, Biome2Boss, Biome3, Biome3Store, Biome3Battle, Biome3Boss, Biome4, Biome4Store, Biome4Battle, Biome4Boss, Biome5, Biome5Store, Biome5Battle, Biome5Boss, EndSequence
string gameState;
string items[2];
int inventory[5];

int main()
{
    SetConsoleTitle("A Legend of Norvastyr");
    SetConsoleOutputCP(CP_UTF8);
    cout << "Podaj nick:" << endl;
    cout << "> "; setColor(5); cin >> nick; setColor(7);
    changeGameState("Menu");
}

void initializeGameState()
{
    if(gameState == "Menu") renderMenu();
    else if(gameState == "IntroSequence")
        {
            thread music(playIntroMusic);
            thread text(intro);

            music.join();
            text.join();
        }
    else if(gameState == "Biome1") biome1();
    else if(gameState == "Biome1Battle") biome1Battle();
}

void spacer()
{
    cout << endl;
    cout << endl;
    cout << endl;
}

void exitMenu()
{
    system("cls");
    spacer();
    spacer();
    spacer();
    cout << "                                                 ****************************" << endl;
    cout << "                                                 *                          *" << endl;
    cout << "                                                 *  NA PEWNO CHCESZ WYJŚĆ?  *" << endl;
    cout << "                                                 *          [T/N]           *" << endl;
    cout << "                                                 *                          *" << endl;
    cout << "                                                 ****************************" << endl;
    spacer();

    char inp = getch();
    switch (inp)
    {
        case 't': exit(0);
        case 'n': renderMenu();
        default: exitMenu();
    }
}

void renderMenu()
{
    system("cls");
    spacer();
    cout << "                     _______             _______  ______ _______ __   _ ______        _____  _______\n";
    cout << "                     |_____|      |      |______ |  ____ |______ | \\  | |     \\      |     | |______\n";
    cout << "                     |     |      |_____ |______ |_____| |______ |  \\_| |_____/      |_____| |      \n";
    cout << "                                                                                                   \n";
    cout << "                        __   _  _____   ______  _    _ _______ _______ _______  _   _  _______     \n";
    cout << "                        | \\  | |     | |_____/   \\  /  |_____| |______    |      \\_/   |_____/     \n";
    cout << "                        |  \\_| |_____| |     \\_   \\/   |     | ______|    |       |    |     \\_     \n";
    spacer();
    cout << "                            ******************    ******************    ******************" << endl;
    cout << "                            *                *    *                *    *                *" << endl;
    cout << "                            *    START [S]   *    *    WYJDŹ [X]   *    * STEROWANIE [T] *" << endl;
    cout << "                            *                *    *                *    *                *" << endl;
    cout << "                            ******************    ******************    ******************" << endl;
    spacer();
    cout << "                                           (C) 2025 Pahad Entertainment" << endl;

    char inp = getch();
    switch (inp)
    {
        case 'x': exitMenu(); break;
        case 's': changeGameState("IntroSequence"); break;
        case 't': renderInput(); break;
        default: renderMenu(); break;
    }
}

void renderStats()
{
    setColor(5); cout << "[ " << nick << " ] "; setColor(2); cout << "HP: " << hp; setColor(6); cout << " ZŁOTO: " << gold << endl; setColor(7);
}

void renderInput()
{
    system("cls");
    cout << "  < Wciśnij "; setColor(4); cout << "[B]"; setColor(7); cout << ", aby powrócić." << endl;
    spacer();
    setColor(4); cout << "  [I]"; setColor(7); cout << " Ekwipunek" << endl;
    setColor(4); cout << "  [A]"; setColor(7); cout << " Atak" << endl;

    char inp = getch();
    if(inp == 'b') renderMenu();
    else renderInput();
}

void intro()
{
    system("cls");
    cout << "Witaj, "; setColor(5); cout << nick; setColor(7); cout << ". ";
    Sleep(1000);
    cout << "Twoje imię zostanie zapisane w annałach Norvastyr, jeśli uda Ci się przetrwać to, co kryje się w mroku tej krainy. ";
    Sleep(3000);
    cout << "Od wieków Norvastyr było miejscem, gdzie magia i technologia walczą o dominację, a zło rośnie w siłę, żerując na słabych.";
    Sleep(3000);
    cout << endl << endl << "Twoja odwaga zostanie wystawiona na próbę. ";
    Sleep(2000);
    cout << "Czy zdołasz odkryć sekrety i pokonać potwory, które czają się w cieniu? ";
    Sleep(3000);
    cout << "Norvastyr czeka na bohatera, który odmieni jej losy... ";
    Sleep(2000);
    cout << endl << endl << "Czy jesteś nim Ty, ";
    Sleep(1000);
    setColor(5); cout << nick; setColor(7); cout << "?" << endl;
    Sleep(1000);
    spacer();
    cout << "Wciśnij dowolny klawisz, aby kontynuować." << endl;

    char inp = getch();
    if(inp == inp)
    {
        changeGameState("Biome1");
    }
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void changeGameState(string state)
{
    SetConsoleTitle(state.c_str());
    gameState = state;
    initializeGameState();
}

void renderPlayer()
{
    cout << "     █████" << endl;
    cout << "    █     █" << endl;
    cout << "   █  ◉ ◉  █" << endl;
    cout << "   █   ▄   █" << endl;
    cout << "    ███████" << endl;
    cout << "     █ █ █" << endl;
    cout << "    ███████" << endl;
    cout << "    █  █  █" << endl;
    cout << "   █   █   █" << endl;
    cout << "  ██       ██" << endl;
}

void biome1()
{
    system("cls");
    cout << "                           [ Kamienne Katakumby ]" << endl;
    Sleep(2000);
    system("cls");
    renderStats();
    spacer();
    renderPlayer();
    spacer();
    cout << " [ JESTEŚ W RUCHU. SZUKANIE PRZECIWNIKA... ] " << endl;
    Sleep(((rand()%4) * 1000) + 1000);
    system("cls");
    renderStats();
    spacer();
    renderPlayer();
    spacer();
    cout << " [ ZNALEZIONO PRZECIWNIKA. KLIKNIJ "; setColor(4); cout << "[E]"; setColor(7); cout << ", ABY ROZPOCZĄĆ WALKĘ, ALBO "; setColor(4); cout << "[L]"; setColor(7); cout << ", ABY SPRÓBOWAĆ UCIEC. ]" << endl;
    spacer();

    char inp = getch();
    switch (inp)
    {
        case 'e': changeGameState("Biome1Battle"); break;
        case 'l': cout << "ucieczka"; break;
    }
}

void biome1Battle()
{
    cout << "walka";
}

void playNote(int frequency, int duration) {
    Beep(frequency, duration);
    Sleep(100); // Pause
}

void playIntroMusic() {
    playNote(392, 400);  // G4
    playNote(349, 400);  // F4
    playNote(330, 500);  // E4
    Sleep(200); // Pause

    playNote(294, 300);  // D4
    playNote(349, 300);  // F4
    playNote(392, 400);  // G4
    Sleep(200); // Pause

    playNote(440, 400);  // A4
    playNote(392, 400);  // G4
    playNote(349, 500);  // F4
    playNote(330, 700);  // E4
}
