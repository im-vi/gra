#include <iostream>
#include <windows.h>
#include <string>
#include <conio.h>
#include <thread>
#include <winuser.h>
#include <vector>
#include <array>
#include <sstream>
#include <ctime>
using namespace std;

void BOSS1_battle();
void bandit_battle();
void mirror_battle();
void child_battle();
void mushroom_battle();
/////////////////////////////////////////////////////////////////
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
std::vector<std::string> splitString(const std::string& input, char delimiter);
void playNote(int frequency, int duration);
void playIntroMusic();
void renderPlayer();
void biome1(); void Biome1();
void biome1Battle();

string nick;
int HP = 100; int maxHP = 100; int DMG = 10;
int gold = 0; int lvl = 0; int XP = 99; int maxXP = 100;
// Menu, IntroSequence, Biome1, Biome1Battle, Biome1Boss, Biome2, Biome2Store, Biome2Battle, Biome2Boss, Biome3, Biome3Store, Biome3Battle, Biome3Boss, Biome4, Biome4Store, Biome4Battle, Biome4Boss, Biome5, Biome5Store, Biome5Battle, Biome5Boss, EndSequence
string gameState;
string items[] = {"Patyk|5|0|0", "Kamień|8|10|0", "Kawałek Szkła|12|50|0", "Młotek|25|150|0"};
int inventory[5];


int main()
{
    srand(time(NULL));
    SetConsoleTitle("A Legend of Norvastyr");
    SetConsoleOutputCP(CP_UTF8);
    cout << "Podaj nick:" << endl;
    cout << "> "; setColor(5); cin >> nick; setColor(7);
    changeGameState("Biome1");
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
    setColor(5); cout << "[ " << nick << " ] "; setColor(9); cout << lvl << " lvl"; setColor(7); cout << "|"; setColor(9);cout << " XP: " << XP << "/" << maxXP; setColor(2); cout << " HP: " << HP << "/" << maxHP; setColor(6); cout << " ZŁOTO: " << gold; setColor(7);
    if(XP >= maxXP){
        lvl++;
        XP = 0;
        maxHP = maxHP + (25 * lvl);
        HP = HP + (25 * lvl);
        maxXP = maxXP + ((maxXP*0.5)*lvl);
    }
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
    cout << "     █████     " << endl;
    cout << "    █     █    " << endl;
    cout << "   █  ◉ ◉  █   " << endl;
    cout << "   █   ▄   █   " << endl;
    cout << "    █     █    " << endl;
    cout << "    ▄█████▄    " << endl;
    cout << "   █  ███  █   " << endl;
    cout << "     ▄███▄     " << endl;
    cout << "    █     █    " << endl;
    cout << "   ▄█     █▄   " << endl;
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
    cout << " [ ZNALEZIONO PRZECIWNIKA. KLIKNIJ "; setColor(4); cout << "[E]"; setColor(7); cout << ", ABY ROZPOCZĄĆ WALKĘ ]" << endl;
    spacer();

    char inp;
    do
    inp = getch();
    while(inp!='e');
    switch (inp)
    {
        case 'e': changeGameState("Biome1Battle"); break;
    }
}

void Biome1()
{
    system("cls");
    renderStats();
    spacer();
    renderPlayer();
    spacer();
    cout << " [ ZNALEZIONO PRZECIWNIKA. KLIKNIJ "; setColor(4); cout << "[E]"; setColor(7); cout << ", ABY ROZPOCZĄĆ WALKĘ ]" << endl;
    spacer();

    char inp;
    do
    inp = getch();
    while(inp!='e');
    switch (inp)
    {
        case 'e': changeGameState("Biome1Battle"); break;
    }
}

void biome1Battle()
{
   int randomMOB = rand()% 101;
   if(randomMOB <= 55) // 55%
    mushroom_battle();
    else if(randomMOB <= 80) // 25%
    child_battle();
    else if(randomMOB <= 95) // 15%
    mirror_battle();
    else if(randomMOB <= 99) // 4%
    bandit_battle();
    else if(randomMOB <= 100) // boss 1%
        BOSS1_battle();
}

void mushroom_battle()
{
    int HP_mushroom = 25;
    int reward_mushroom = rand()%5 + 1;
    int xp_mushroom = rand()%5 + 1;
    system("cls");
    renderStats();
    cout << "       |       [ GRZYB ] "; setColor(4); cout << "HP: " << HP_mushroom << "/25"; setColor(7);
    spacer();
    cout << "     █████                                             " << endl;
    cout << "    █     █                                            " << endl;
    cout << "   █   ◉ ◉ █                                           " << endl;
    cout << "   █   ▄   █                                           " << endl;
    cout << "    █     █                                  ▄▄▄▄▄▄    " << endl;
    cout << "    ▄█████▄                               ▄██████████▄ " << endl;
    cout << "   █  ███  █                              ██◉ ████◉ ██ " << endl;
    cout << "     ▄███▄                                █████▄▄█████ " << endl;
    cout << "    █     █                                   ████     " << endl;
    cout << "   ▄█     █▄                                  ████     " << endl;
    Sleep(500);
    cout << " [ KLIKNIJ "; setColor(4); cout << "[A]"; setColor(7); cout << ", ABY UDERZYĆ ]" << endl;
    Sleep(1500);
    do{
        Sleep(500);
    system("cls");
    renderStats();
    cout << "       |       [ GRZYB ] "; setColor(4); cout << "HP: " << HP_mushroom << "/25"; setColor(7);
    spacer();
    cout << "     █████                                             " << endl;
    cout << "    █     █                                            " << endl;
    cout << "   █   ◉ ◉ █                                           " << endl;
    cout << "   █   ▄   █                                           " << endl;
    cout << "    █     █                                  ▄▄▄▄▄▄    " << endl;
    cout << "    ▄█████▄                               ▄██████████▄ " << endl;
    cout << "   █  ███  █                              ██◉ ████◉ ██ " << endl;
    cout << "     ▄███▄                                █████▄▄█████ " << endl;
    cout << "    █     █                                   ████     " << endl;
    cout << "   ▄█     █▄                                  ████     " << endl;
    char atk;
    do
    atk = getch();
    while(atk!='a');
    switch (atk)
    {
        case 'a':  HP_mushroom = HP_mushroom - DMG; break;
    }
    cout << endl << "[ PRZECIWNIK MA " << HP_mushroom << "/" << "25 HP ]" << endl;
    Sleep(200);
    if(HP_mushroom <= 0){
        cout << "[ POKONAŁEŚ GRZYBA!]" << endl << endl;
        cout << "[ OTRZYMAŁEŚ: " << reward_mushroom << " ZŁOTA ORAZ " << xp_mushroom << "XP";
        gold = gold + reward_mushroom;
        XP = XP + xp_mushroom;
        Sleep(2000);
        Biome1();
    }
            else{
        HP = HP - 3;
        cout << "[ STRACIŁEŚ 3 HP]" << endl;
        Sleep(200);
            }
    if(HP <= 0){
        cout << "[ UMARŁEŚ... STRACIŁEŚ CZĘŚĆ SWOICH ZAROBKÓW ]";
        gold = gold - (gold/20);
        HP = maxHP*0.5;
        Sleep(2000);
        Biome1();
    }
    }while(HP_mushroom >= 0);
}
void child_battle()
{
    int HP_child = 50;
    int reward_child = rand()%11 + 5;
    int xp_child = rand()%11 + 5;
    system("cls");
    renderStats();
    spacer();
    cout << "     █████                                             " << endl;
    cout << "    █     █                                            " << endl;
    cout << "   █   ◉ ◉ █                                           " << endl;
    cout << "   █   ▄   █                                           " << endl;
    cout << "    █     █                                  ▄▀▀▀▀▄    " << endl;
    cout << "    ▄█████▄                                  █◉ ◉ █    " << endl;
    cout << "   █  ███  █                                  ▀██▀   ▄ " << endl;
    cout << "     ▄███▄                                ▄▄▀██████▀▀  " << endl;
    cout << "    █     █                                  ██████    " << endl;
    cout << "   ▄█     █▄                                ▄██▀▀██▄   " << endl;
    Sleep(500);
    cout << " [ KLIKNIJ "; setColor(4); cout << "[A]"; setColor(7); cout << ", ABY UDERZYĆ ]" << endl;
    Sleep(1500);
    do{
        Sleep(1250);
    system("cls");
    renderStats();
    cout << "       |       [ ZŁE DZIECKO ] "; setColor(4); cout << "HP: " << HP_child << "/50"; setColor(7);
    spacer();
    cout << "     █████                                             " << endl;
    cout << "    █     █                                            " << endl;
    cout << "   █   ◉ ◉ █                                           " << endl;
    cout << "   █   ▄   █                                           " << endl;
    cout << "    █     █                                  ▄▀▀▀▀▄    " << endl;
    cout << "    ▄█████▄                                  █◉ ◉ █    " << endl;
    cout << "   █  ███  █                                  ▀██▀   ▄ " << endl;
    cout << "     ▄███▄                                ▄▄▀██████▀▀  " << endl;
    cout << "    █     █                                  ██████    " << endl;
    cout << "   ▄█     █▄                                ▄██▀▀██▄   " << endl;
    char atk;
    do
    atk = getch();
    while(atk!='a');
    switch (atk)
    {
        case 'a':  HP_child = HP_child - DMG; break;
    }
    cout << endl << "[ PRZECIWNIK MA " << HP_child << "/" << "50 HP ]" << endl;
    Sleep(500);
    if(HP_child <= 0){
        cout << "[ POKONAŁEŚ ZŁE DZIECKO!]" << endl << endl;
        cout << "[ OTRZYMAŁEŚ: " << reward_child << " ZŁOTA ORAZ " << xp_child << "XP";
        gold = gold + reward_child;
        XP = XP + xp_child;
        Sleep(2000);
        Biome1();
    }
            else{
        HP = HP - 8;
        cout << "[ STRACIŁEŚ 8 HP]" << endl;
        Sleep(500);
            }
    if(HP <= 0){
        cout << "[ UMARŁEŚ... STRACIŁEŚ CZĘŚĆ SWOICH ZAROBKÓW ]";
        gold = gold - (gold/20);
        HP = maxHP*0.5;
        Sleep(2000);
        Biome1();
    }
    }while(HP_child >= 0);
}
void mirror_battle()
{
    int HP_mirror = 125;
    int reward_mirror = rand()%11 + 15;
    int xp_mirror = rand()%11 + 15;
    system("cls");
    renderStats();
    spacer();
    cout << "     █████                                             " << endl;
    cout << "    █     █                                            " << endl;
    cout << "   █   ◉ ◉ █                                  ▄▀▀▀▀▀▀▄ " << endl;
    cout << "   █   ▄   █                                  █░░░◉░◉█ " << endl;
    cout << "    █     █                                   █░◉░░░░█ " << endl;
    cout << "    ▄█████▄                                   █░░░░◉░█ " << endl;
    cout << "   █  ███  █                                  █░◉░░░░█ " << endl;
    cout << "     ▄███▄                                    █░░░◉░░█ " << endl;
    cout << "    █     █                                   ▀▄▄▄▄▄▄▀ " << endl;
    cout << "   ▄█     █▄                                  █      █ " << endl;
    Sleep(500);
    cout << " [ KLIKNIJ "; setColor(4); cout << "[A]"; setColor(7); cout << ", ABY UDERZYĆ ]" << endl;
    Sleep(1500);
    do{
        Sleep(1250);
    system("cls");
    renderStats();
    cout << "       |       [ LUSTRO ] "; setColor(4); cout << "HP: " << HP_mirror << "/125"; setColor(7);
    spacer();
    cout << "     █████                                             " << endl;
    cout << "    █     █                                            " << endl;
    cout << "   █   ◉ ◉ █                                  ▄▀▀▀▀▀▀▄ " << endl;
    cout << "   █   ▄   █                                  █░░░◉░◉█ " << endl;
    cout << "    █     █                                   █░◉░░░░█ " << endl;
    cout << "    ▄█████▄                                   █░░░░◉░█ " << endl;
    cout << "   █  ███  █                                  █░◉░░░░█ " << endl;
    cout << "     ▄███▄                                    █░░░◉░░█ " << endl;
    cout << "    █     █                                   ▀▄▄▄▄▄▄▀ " << endl;
    cout << "   ▄█     █▄                                  █      █ " << endl;
    char atk;
    do
    atk = getch();
    while(atk!='a');
    switch (atk)
    {
        case 'a':  HP_mirror = HP_mirror - DMG; break;
    }
    cout << endl << "[ PRZECIWNIK MA " << HP_mirror << "/" << "125 HP ]" << endl;
    Sleep(500);
    if(HP_mirror <= 0){
        cout << "[ POKONAŁEŚ SWOJE ODBICIE!]" << endl << endl;
        cout << "[ OTRZYMAŁEŚ: " << reward_mirror << " ZŁOTA ORAZ " << xp_mirror << "XP";
        gold = gold + reward_mirror;
        XP = XP + xp_mirror;
        Sleep(2000);
        Biome1();
    }
            else{
        HP = HP - DMG;
        cout << "[ STRACIŁEŚ " << DMG << " HP ]" << endl;
        Sleep(500);
            }
    if(HP <= 0){
        cout << "[ UMARŁEŚ... STRACIŁEŚ CZĘŚĆ SWOICH ZAROBKÓW ]";
        gold = gold - (gold/20);
        HP = maxHP*0.5;
        Sleep(2000);
        Biome1();
    }
    }while(HP_mirror >= 0);
}
void bandit_battle()
{
    int HP_bandit = 150;
    int reward_bandit = rand()%26 + 25;
    int xp_bandit = rand()%26 + 25;
    system("cls");
    renderStats();
    spacer();
    cout << "     █████                                   ▄▄▄▄▄   " << endl;
    cout << "    █     █                                 █     █  " << endl;
    cout << "   █   ◉ ◉ █                               █ ◉ ◉   █ " << endl;
    cout << "   █   ▄   █                               █▓▓▓▓▓▓▓█ " << endl;
    cout << "    █     █                              ▐  █▓▓▓▓▓█  " << endl;
    cout << "    ▄█████▄                              ▐  ▄▀███▀▄  " << endl;
    cout << "   █  ███  █                             █▄▀  ███  █ " << endl;
    cout << "     ▄███▄                               ▀   ▄███▄   " << endl;
    cout << "    █     █                                 █     █  " << endl;
    cout << "   ▄█     █▄                               ▄█     █▄ " << endl;
    Sleep(500);
    cout << " [ KLIKNIJ "; setColor(4); cout << "[A]"; setColor(7); cout << ", ABY UDERZYĆ ]" << endl;
    Sleep(1500);
    do{
        Sleep(1250);
    system("cls");
    renderStats();
    cout << "       |       [ BANDYTA ] "; setColor(4); cout << "HP: " << HP_bandit << "/150"; setColor(7);
    spacer();
    cout << "     █████                                   ▄▄▄▄▄   " << endl;
    cout << "    █     █                                 █     █  " << endl;
    cout << "   █   ◉ ◉ █                               █ ◉ ◉   █ " << endl;
    cout << "   █   ▄   █                               █▓▓▓▓▓▓▓█ " << endl;
    cout << "    █     █                              ▐  █▓▓▓▓▓█  " << endl;
    cout << "    ▄█████▄                              ▐  ▄▀███▀▄  " << endl;
    cout << "   █  ███  █                             █▄▀  ███  █ " << endl;
    cout << "     ▄███▄                               ▀   ▄███▄   " << endl;
    cout << "    █     █                                 █     █  " << endl;
    cout << "   ▄█     █▄                               ▄█     █▄ " << endl;
    char atk;
    do
    atk = getch();
    while(atk!='a');
    switch (atk)
    {
        case 'a':  HP_bandit = HP_bandit - DMG; break;
    }
    cout << endl << "[ PRZECIWNIK MA " << HP_bandit << "/" << "150 HP ]" << endl;
    Sleep(500);
    if(HP_bandit <= 0){
        cout << "[ POKONAŁEŚ BANDYTĘ!]" << endl << endl;
        cout << "[ OTRZYMAŁEŚ: " << reward_bandit << " ZŁOTA ORAZ " << xp_bandit << "XP";
        gold = gold + reward_bandit;
        XP = XP + xp_bandit;
        Sleep(2000);
        Biome1();
    }
            else{
        HP = HP - 15;
        cout << "[ STRACIŁEŚ 15 HP]" << endl;
        Sleep(500);
            }
    if(HP <= 0){
        cout << "[ UMARŁEŚ... STRACIŁEŚ CZĘŚĆ SWOICH ZAROBKÓW ]";
        gold = gold - (gold/20);
        HP = maxHP*0.5;
        Sleep(2000);
        Biome1();
    }
    }while(HP_bandit >= 0);
}
void BOSS1_battle()
{
    system("cls");
    spacer();
    cout << "                                           " << endl;
    cout << "    ██████   ▄█████▄  ▄████▄  ▄████▄   █   " << endl;
    cout << "    ██    █  █▀   ▀█  █       █        █   " << endl;
    cout << "    ██████   █  ■  █  ▀████▄  ▀████▄   █   " << endl;
    cout << "    ██    █  █▄   ▄█       █       █   ▀   " << endl;
    cout << "    ██████   ▀█████▀  ▀████▀  ▀████▀   ■   " << endl;
    cout << "                                           " << endl;
    Sleep(2500);
    int HP_GOLEM = 300;
    int reward_GOLEM = rand()%76 + 75;
    int xp_GOLEM = rand()%76 + 75;
    int unik_GOLEM = rand()%4;
    system("cls");
    renderStats();
    spacer();
    cout << "                                   ▄▀▀▀▀▀▀▀▀▀▄                 " << endl;
    cout << "                                  █░ ░  ░  ░░ █                " << endl;
    cout << "                                 █   █ ░ █  ░░ █               " << endl;
    cout << "                                █ ░░      ░    ░█              " << endl;
    cout << "                                █░  █▀█▀█▀█▀█ ░ █              " << endl;
    cout << "                                 █ ░ ▄ ▄ ▄ ▄   █               " << endl;
    cout << "                                  █ ▀▀▀▀▀▀▀▀▀░█                " << endl;
    cout << "                               ████████████████████            " << endl;
    cout << "     █████                   ███▀▀██░█░░█░░█░░██▀▀███          " << endl;
    cout << "    █     █                 ███   ███░░█░░░░░███   ███         " << endl;
    cout << "   █   ◉ ◉ █               ██░█   ██░█░░░█░░█░██    █░██       " << endl;
    cout << "   █   ▄   █              ████    ███░█░░░░█░███     ████      " << endl;
    cout << "    █     █              ██░██      ██████████       ██░██     " << endl;
    cout << "    ▄█████▄              █░░██        ██████         ██░░█     " << endl;
    cout << "   █  ███  █             ████        ███  ███         ████     " << endl;
    cout << "     ▄███▄                ▀▀        ███    ███         ▀▀      " << endl;
    cout << "    █     █                        ███▀    ▀███                " << endl;
    cout << "   ▄█     █▄                     ▄████▄    ▄████▄              " << endl;
    Sleep(500);
    cout << " [ KLIKNIJ "; setColor(4); cout << "[A]"; setColor(7); cout << ", ABY UDERZYĆ ]" << endl;
    Sleep(1500);
    do{
        Sleep(1250);
    system("cls");
    renderStats();
    cout << "       |       [ GOLEM ] "; setColor(4); cout << "HP: " << HP_GOLEM << "/300"; setColor(7);
    spacer();
    cout << "                                   ▄▀▀▀▀▀▀▀▀▀▄                 " << endl;
    cout << "                                  █░ ░  ░  ░░ █                " << endl;
    cout << "                                 █   █ ░ █  ░░ █               " << endl;
    cout << "                                █ ░░      ░    ░█              " << endl;
    cout << "                                █░  █▀█▀█▀█▀█ ░ █              " << endl;
    cout << "                                 █ ░ ▄ ▄ ▄ ▄   █               " << endl;
    cout << "                                  █ ▀▀▀▀▀▀▀▀▀░█                " << endl;
    cout << "                               ████████████████████            " << endl;
    cout << "     █████                   ███▀▀██░█░░█░░█░░██▀▀███          " << endl;
    cout << "    █     █                 ███   ███░░█░░░░░███   ███         " << endl;
    cout << "   █   ◉ ◉ █               ██░█   ██░█░░░█░░█░██    █░██       " << endl;
    cout << "   █   ▄   █              ████    ███░█░░░░█░███     ████      " << endl;
    cout << "    █     █              ██░██      ██████████       ██░██     " << endl;
    cout << "    ▄█████▄              █░░██        ██████         ██░░█     " << endl;
    cout << "   █  ███  █             ████        ███  ███         ████     " << endl;
    cout << "     ▄███▄                ▀▀        ███    ███         ▀▀      " << endl;
    cout << "    █     █                        ███▀    ▀███                " << endl;
    cout << "   ▄█     █▄                     ▄████▄    ▄████▄              " << endl;
    char atk;
    do
    atk = getch();
    while(atk!='a');
    switch (atk)
    {
        case 'a':
            if(unik_GOLEM >= 2)
                HP_GOLEM = HP_GOLEM - DMG;
            else{
                cout << "[ GOLEM ZROBIŁ UNIK";
                Sleep(300);
                cout << ". ";
                Sleep(300);
                cout << ". ";
                Sleep(300);
                cout << ". ]";
                Sleep(500);
                }
                unik_GOLEM = rand()%4; break;
        default: cout << "[ STRACIŁEŚ OKAZJĘ NA ATAK... A PRZECIWNIK JĄ WYKORZYSTAŁ ]" << endl; Sleep(1500); break;
    }
    cout << endl << "[ PRZECIWNIK MA " << HP_GOLEM << "/" << "300 HP ]" << endl;
    Sleep(500);
    if(HP_GOLEM <= 0){
        cout << "[ POKONAŁEŚ PIERWSZEGO BOSSA GOLEM'a!]" << endl << endl;
        cout << "[ OTRZYMAŁEŚ: " << reward_GOLEM << " ZŁOTA ORAZ " << xp_GOLEM << "XP";
        gold = gold + reward_GOLEM;
        XP = XP + xp_GOLEM;
        Sleep(2000);
        Biome1();
    }
            else{
        HP = HP - 10;
        cout << "[ STRACIŁEŚ 10 HP]" << endl;
        Sleep(500);
            }
    if(HP <= 0){
        cout << "[ UMARŁEŚ... STRACIŁEŚ CZĘŚĆ SWOICH ZAROBKÓW ]";
        gold = gold - (gold/20);
        HP = maxHP*0.5;
        Sleep(2000);
        Biome1();
    }
    }while(HP_GOLEM >= 0);
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

std::vector<std::string> splitString(const std::string& input, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(input);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        result.push_back(token);
    }

    return result;
}
