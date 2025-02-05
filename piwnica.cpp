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
void escapeEnemy();
int rarityToColor(int rar);
void playNote(int frequency, int duration);
void playIntroMusic();
void renderPlayer();
void death();
void biome1(); void Biome1();
void biome1Battle();
void openStore();
void dropItem();
void assignToInventory(int item);
void buyItem(int* offer);
void buyItemConfirmation(int item);
void equipItem();

string nick;
int HP = 100; int maxHP = 100; int DMG = 5;
int gold = 100; int lvl = 0; int XP = 99; int maxXP = 100;
int heldItem;
// Menu, IntroSequence, Biome1, Biome1Battle, Biome1Boss, Biome2, Biome2Battle, Biome2Boss, Biome3, Biome3Battle, Biome3Boss, Biome4, Biome4Battle, Biome4Boss, Biome5, Biome5Battle, Biome5Boss, EndSequence
string gameState;
string items[] = {"-|0|0|0", "Patyk|5|0|0", "Kamień|8|10|0", "Kawałek Szkła|12|50|0", "Młotek|25|150|0", "Zardzewiały Ostrz|5|10|0", "Żelazny Kieł|12|50|1", "Cienistożerca|20|150|2, Żarowy Rzeźnik|30|300|3", "Runiczne Ostrze Norvastyru|50|700|4", "Zwiastun Zagłady|80|1500|5", "Rozłupana Siekiera|6|15|0", "Bojowy Topór|14|70|1", "Mroźny Rzeźnik|22|180|2", "Płomienny Topór Wojenny|35|350|3", "Gromowładca|55|800|4", "Gniew Tytana|85|1600|5", "Pęknięta Różdżka|4|8|0", "Zaklęty Dębowy Kostur|10|40|1", "Więziacz Otchłani|18|130|2", "Niebiańskie Berło|28|270|3", "Dominacja Arcymaga|48|650|4", "Kataklizm Arkanisty|75|1400|5"};
int inventory[5];

int main()
{
    srand(time(NULL));
    SetConsoleTitle("A Legend of Norvastyr");
    SetConsoleOutputCP(CP_UTF8);
    inventory[0] = 1;
    inventory[1] = 0;
    inventory[2] = 2;
    inventory[3] = 0;
    inventory[4] = 0;
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

void escapeEnemy()
{
    system("cls");
    spacer();
    Sleep(500);
    cout << "     [ Uciekłeś od przeciwnika. Wstyd... ]" << endl;
    spacer();
    Sleep(1000);
    changeGameState("Biome1");

}

void death()
{
    system("cls");
    spacer();
    Sleep(500);
    cout << "     [ Zostałeś pokonany. ]" << endl;
    Sleep(100);
    renderStats();
    spacer();
    cout << "Wciśnij dowolny klawisz, aby kontynuować." << endl;

    char inp = getch();
    if(inp == inp)
    {
        changeGameState("Menu");
    }
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
    cout << " [ ZNALEZIONO PRZECIWNIKA. ] " << endl << endl;
    setColor(4); cout << "  [E]"; setColor(7); cout << " Rozpocznij walkę" << endl;
    setColor(4); cout << "  [I]"; setColor(7); cout << " Otwórz ekwipunek" << endl;
    setColor(4); cout << "  [S]"; setColor(7); cout << " Odwiedź sklep" << endl;
    spacer();

    char inp = getch();
    switch (inp)
    {
        case 'e': changeGameState("Biome1Battle"); break;
        case 'i': openInventory(); break;
        default: Biome1(); break;
    }
}

void Biome1()
{
    system("cls");
    renderStats();
    spacer();
    renderPlayer();
    spacer();
    cout << " [ ZNALEZIONO PRZECIWNIKA. ] " << endl << endl;
    setColor(4); cout << "  [E]"; setColor(7); cout << " Rozpocznij walkę" << endl;
    setColor(4); cout << "  [I]"; setColor(7); cout << " Otwórz ekwipunek" << endl;
    setColor(4); cout << "  [S]"; setColor(7); cout << " Odwiedź sklep" << endl;
    spacer();

    char inp = getch();
    switch (inp)
    {
        case 'e': changeGameState("Biome1Battle"); break;
        case 'i': openInventory(); break;
        case 'u': escapeEnemy(); break;
        case 's': openStore(); break;
        default: Biome1(); break;
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
    int run_mushroom = rand()%5+1;
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
    cout << " [ KLIKNIJ "; setColor(4); cout << "[U]"; setColor(7); cout << ", ABY UCIEC ]" << endl;
    Sleep(1750);
    do{
        Sleep(1000);
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
    while(atk!='a' && atk!='u');
    switch (atk)
    {
        case 'a':  HP_mushroom = HP_mushroom - DMG; break;
        case 'u':
            if(run_mushroom >= 3)
                escapeEnemy();
            else{
                cout << "[ PRZECIWNIK NIE POZWOLIŁ CI UCIEC";
                Sleep(300);
                cout << ". ";
                Sleep(300);
                cout << ". ";
                Sleep(300);
                cout << ". ]";
                Sleep(300);
                };
                run_mushroom = rand()%5+1; break;
    }
    cout << endl << "[ PRZECIWNIK MA " << HP_mushroom << "/" << "25 HP ]" << endl;
    Sleep(100);
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
        Sleep(100);
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
    int run_child = rand()%5+1;
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
    cout << " [ KLIKNIJ "; setColor(4); cout << "[U]"; setColor(7); cout << ", ABY UCIEC ]" << endl;
    Sleep(1750);
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
    while(atk!='a' && atk!='u');
    switch (atk)
    {
        case 'a':  HP_child = HP_child - DMG; break;
        case 'u':
            if(run_child >= 3)
                escapeEnemy();
            else{
                cout << "[ PRZECIWNIK NIE POZWOLIŁ CI UCIEC";
                Sleep(300);
                cout << ". ";
                Sleep(300);
                cout << ". ";
                Sleep(300);
                cout << ". ]";
                Sleep(300);
                };
                run_child = rand()%5+1; break;
    }
    cout << endl << "[ PRZECIWNIK MA " << HP_child << "/" << "50 HP ]" << endl;
    Sleep(100);
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
        Sleep(100);
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
    int run_mirror = rand()%5+1;
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
    cout << " [ KLIKNIJ "; setColor(4); cout << "[U]"; setColor(7); cout << ", ABY UCIEC ]" << endl;
    Sleep(1750);
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
    while(atk!='a' && atk!='u');
    switch (atk)
    {
        case 'a':  HP_mirror = HP_mirror - DMG; break;
        case 'u':
            if(run_mirror >= 3)
                escapeEnemy();
            else{
                cout << "[ PRZECIWNIK NIE POZWOLIŁ CI UCIEC";
                Sleep(300);
                cout << ". ";
                Sleep(300);
                cout << ". ";
                Sleep(300);
                cout << ". ]";
                Sleep(300);
                };
                run_mirror = rand()%5+1; break;
    }
    cout << endl << "[ PRZECIWNIK MA " << HP_mirror << "/" << "125 HP ]" << endl;
    Sleep(100);
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
        Sleep(100);
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
    int run_bandit = rand()%5+1;
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
    cout << " [ KLIKNIJ "; setColor(4); cout << "[U]"; setColor(7); cout << ", ABY UCIEC ]" << endl;
    Sleep(1750);
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
    while(atk!='a' && atk!='u');
    switch (atk)
    {
        case 'a':  HP_bandit = HP_bandit - DMG; break;
        case 'u':
            if(run_bandit >= 3)
                escapeEnemy();
            else{
                cout << "[ PRZECIWNIK NIE POZWOLIŁ CI UCIEC";
                Sleep(300);
                cout << ". ";
                Sleep(300);
                cout << ". ";
                Sleep(300);
                cout << ". ]";
                Sleep(300);
                };
                run_bandit = rand()%5+1; break;
    }
    cout << endl << "[ PRZECIWNIK MA " << HP_bandit << "/" << "150 HP ]" << endl;
    Sleep(100);
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
        Sleep(100);
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
    cout << " [ BRAK MOŻLIWOŚCI UCIECZKI ] " << endl;
    Sleep(1750);
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
    Sleep(100);
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
        Sleep(100);
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

int rarityToColor(int rar)
{
    switch (rar)
    {
        case 0: return 8; break;
        case 1: return 2; break;
        case 2: return 1; break;
        case 3: return 5; break;
        case 4: return 6; break;
        case 5: return 14; break;
    }
}

void openInventory()
{
    system("cls");
    cout << "  < Wciśnij "; setColor(4); cout << "[B]"; setColor(7); cout << ", aby powrócić." << endl;
    spacer();
    cout << "  [ EKWIPUNEK ]" << endl;
    spacer();
    char delimiter = '|';
    for(int i = 0; i < sizeof(inventory)/sizeof(inventory[0]); i++)
    {
        std::vector<std::string> item = splitString(items[inventory[i]], delimiter);
        if(stoi(item[1]) != 0)
        {
            setColor(rarityToColor(stoi(item[3]))); cout << "  [ " << i+1 << ". " << item[0] << " | "; setColor(1); cout << "OBRAŻENIA: " << item[1]; setColor(7); cout << " ]" << endl; setColor(7);
        }
        else
        {
            setColor(rarityToColor(stoi(item[3]))); cout << "  [ " << i+1 << ". " << item[0] << " ]" << endl; setColor(7);
        }
    }
    spacer();
    setColor(4); cout << "  [W]"; setColor(7); cout << " Wyrzuć przedmiot" << endl;

    char inp = tolower(getch());
    if(inp == 'b') Biome1();
    else if(inp == 'w') dropItem();
    else openInventory();
}

void openStore()
{
    int storeOffer[] = {5, 10, 3, 16, 9};
    system("cls");
    cout << "  < Wciśnij "; setColor(4); cout << "[B]"; setColor(7); cout << ", aby powrócić." << endl << endl;
    setColor(6); cout << "  [ ZŁOTO NA KONCIE: " << gold << " ]" << endl << endl << endl; setColor(7);
    cout << "  [ SKLEP ]" << endl;
    spacer();
    char delimiter = '|';
    for(int i = 0; i < 5; i++)
    {
        std::vector<std::string> item = splitString(items[storeOffer[i]], delimiter);
        setColor(rarityToColor(stoi(item[3]))); cout << "  [ " << i+1 << ". " << item[0] << " | "; setColor(1); cout << "OBRAŻENIA: " << item[1]; setColor(rarityToColor(stoi(item[3]))); cout << " | "; setColor(6); cout << "CENA: " << item[2]; setColor(rarityToColor(stoi(item[3]))); cout << " ]" << endl; setColor(7);
    }
    spacer();
    setColor(4); cout << endl << "  [K]"; setColor(7); cout << " Kup przedmiot" << endl << endl;
    char inp = getch();
    switch (inp)
    {
        case 'b': Biome1(); break;
        case 'k': buyItem(storeOffer); break;
        default: openStore(); break;
    }
}

void dropItem()
{
    system("cls");
    openInventory();
    cout << "  --------------------------------------------" << endl;
    setColor(4); cout << endl << "  [X]"; setColor(7); cout << " Anuluj" << endl << endl;
    setColor(4); cout << "  UWAGA! "; setColor(7); cout << "Wyrzucenie przedmiotu z ekwipunku jest równoznaczne z jego zniszczeniem." << endl;
    cout << "  Tej akcji nie można cofnąć." << endl << endl;
    cout << "  Kliknij przycisk od 1 do 5, aby wyrzucić przedmiot." << endl;
    char delItem = tolower(getch());
    switch (delItem)
    {
        case '1': inventory[0] = 0; break;
        case '2': inventory[1] = 0; break;
        case '3': inventory[2] = 0; break;
        case '4': inventory[3] = 0; break;
        case '5': inventory[4] = 0; break;
        case 'x': openInventory(); break;
        default: openInventory(); break;
    }
}

void assignToInventory(int item)
{
    int i = 0;
    do
    {
        i++;
    }
    while(inventory[i] != 0);
    inventory[i] = item;
}

void buyItem(int* offer)
{
    cout << "  --------------------------------------------" << endl;
    setColor(4); cout << endl << "  [X]"; setColor(7); cout << " Anuluj" << endl << endl;
    setColor(4); cout << "  UWAGA! "; setColor(7); cout << "Tej akcji nie można cofnąć." << endl << endl;
    cout << "  Kliknij przycisk od 1 do 5, aby kupić przedmiot." << endl;
    char inp = getch();
    switch (inp)
    {
        case '1': buyItemConfirmation(offer[0]); break;
        case '2': buyItemConfirmation(offer[1]); break;
        case '3': buyItemConfirmation(offer[2]); break;
        case '4': buyItemConfirmation(offer[3]); break;
        case '5': buyItemConfirmation(offer[4]); break;
        case 'x': openStore(); break;
        default: buyItem(offer); break;
    }
}

void buyItemConfirmation(int item)
{
    char delimiter = '|';
    std::vector<std::string> itemToGet = splitString(items[item], delimiter);
    cout << "  --------------------------------------------" << endl;
    if(stoi(itemToGet[2]) > gold)
    {
        cout << "  Niewystarczające środki, aby kupić "; setColor(rarityToColor(stoi(itemToGet[3]))); cout << itemToGet[0]; setColor(7); cout << "." << endl;
        Sleep(1000);
        openStore();
    }
    else
    {
        setColor(4); cout << endl << "  [X]"; setColor(7); cout << " Anuluj" << endl;
        setColor(4); cout << endl << "  [C]"; setColor(7); cout << " Potwierdź" << endl << endl;
        setColor(4); cout << "  UWAGA! "; setColor(7); cout << "Tej akcji nie można cofnąć." << endl << endl;
        cout << "  Kupujesz: "; setColor(rarityToColor(stoi(itemToGet[3]))); cout << itemToGet[0] << endl; setColor(7);
        cout << "  Ta operacja odejmie " << itemToGet[2] << " złota z twojego konta." << endl;
        char inp = tolower(getch());
        switch (inp)
        {
            case 'c': gold -= stoi(itemToGet[2]); assignToInventory(item); openStore(); break;
            case 'x': openStore(); break;
            default: buyItemConfirmation(item); break;
        }
    }
}

void equipItem()
{

}
