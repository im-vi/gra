#include <iostream>
#include <windows.h>
#include <string>
#include <conio.h>
#include <winuser.h>
#include <vector>
#include <array>
#include <sstream>
#include <ctime>
using namespace std;

void BOSS1_battle();
void bandit_battle(int emaxHP, int edmg, string callback);
void mirror_battle(int emaxHP, string callback);
void child_battle(int emaxHP, int edmg, string callback);
void mushroom_battle(int emaxHP, int edmg, string callback);
void BOSS2_battle();
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
void renderPlayer();
void biomeNameIntroduction(string biomeName);
void backToBiome();
void biomeControls(bool lookForEnemies);
void biome1(); void Biome1();
void healMenu(int storeOffer);
void healItemConfirmation(int value, int price, int* offer);
void heal(int value);
void biome1Battle();
void openStore(int storeOffer[]);
void dropItem();
void assignToInventory(int item);
void buyItem(int* offer);
void buyItemConfirmation(int item, int* offer);
void equipItem();
void equipItemConfirmation(int position);
void biome2();
void Biome2();
void biome2Battle();

string nick;
int HP = 90; int maxHP = 100; int DMG = 5;
int gold = 590015209; int lvl = 0; int XP = 99; int maxXP = 100;
int heldItem = 0;
// Menu, IntroSequence, Biome1, Biome1Battle, Biome1Boss, Biome2, Biome2Battle, Biome2Boss, Biome3, Biome3Battle, Biome3Boss, EndSequence
string gameState;
string items[] = {"-|0|0|0", "Patyk|5|0|0", "Kamień|8|20|0", "Kawałek Szkła|15|75|0", "Młotek|25|150|0", "Żarowy Rzeźnik|30|0|2", "Zardzewiały Ostrz|35|225|1", "Żelazny Kieł|50|475|1", "Diabelskie Ostrze|66|666|2", "Runiczne Ostrze Norvastyru|70|900|3", "Zwiastun Zagłady|80|1500|3", "Rozłupana Siekiera|95|2000|3", "Bojowy Topór|110|2800|3", "Mroźny Rzeźnik|115|0|4", "Płomienny Topór Wojenny|120|3500|2", "Gromowładca|135|4200|3", "Gniew Tytana|150|5555|5", "Pęknięta Różdżka|145|0|4", "Zaklęty Dębowy Kostur|165|7000|3", "Niebiańskie Berło|177|7777|5", "Więziacz Otchłani|180|8000|4", "Dominacja Arcymaga|200|11111|5", "Kataklizm Arkanisty|999|99999|6"};
int inventory[5];
int defeatedEnemies = 5;
bool introducedToBiomeName = false;

int main()
{
    srand(time(NULL));
    SetConsoleTitle("A Legend of Norvastyr");
    SetConsoleOutputCP(CP_UTF8);
    inventory[0] = 1;
    inventory[1] = 0;
    inventory[2] = 0;
    inventory[3] = 0;
    inventory[4] = 0;
    cout << "Podaj nick:" << endl;
    cout << "> "; setColor(5); cin >> nick; setColor(7);
    changeGameState("Biome1");
}

void initializeGameState()
{
    if(gameState == "Menu") renderMenu();
    else if(gameState == "IntroSequence") intro();
    else if(gameState == "Biome1") biome1();
    else if(gameState == "Biome1Battle") biome1Battle();
    else if(gameState == "Biome1Boss") BOSS1_battle();
    else if(gameState == "Biome2") biome2();
    else if(gameState == "Biome2Battle") biome2Battle();
    else if(gameState == "Biome2Boss") BOSS2_battle();
}

void spacer()
{
    cout << endl << endl << endl;
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
    setColor(5); cout << "[ " << nick << " ] "; setColor(9); cout << "LVL: " << lvl; setColor(9);cout << " XP: " << XP << "/" << maxXP; setColor(2); cout << " HP: " << HP << "/" << maxHP; setColor(4); cout << " OBRAŻENIA: " << DMG; setColor(6); cout << " ZŁOTO: " << gold; setColor(7);
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
    if(gameState == "Biome1Battle")
        changeGameState("Biome1");

}

void biomeNameIntroduction(string biomeName)
{
    if(!introducedToBiomeName)
    {
        system("cls");
        cout << "                           [ " << biomeName << " ]" << endl;
        Sleep(2000);
        system("cls");
        introducedToBiomeName = true;
    }
}

void backToBiome()
{
    if(gameState == "Biome1") Biome1();
    else if(gameState == "Biome2") Biome2();
}

void biomeControls(bool lookForEnemies)
{
    if(lookForEnemies)
    {
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
    }
    else
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
    }
}

void biome1()
{
    system("cls");
    biomeNameIntroduction("Kamienne Katakumby");
    biomeControls(true);
    int biomeOffer[] = {2, 3, 4, 6, 7, 8, 9, 10, 11};

    char inp = getch();
    switch (inp)
    {
        case 'e': changeGameState("Biome1Battle"); break;
        case 'i': openInventory(); break;
        case 's': openStore(biomeOffer); break;
        default: Biome1(); break;
    }
}

void Biome1()
{
    system("cls");
    biomeControls(false);
    int biomeOffer[] = {2, 3, 4, 6, 7, 8, 9, 10, 11};

    char inp = getch();
    switch (inp)
    {
        case 'e': changeGameState("Biome1Battle"); break;
        case 'i': openInventory(); break;
        case 's': openStore(biomeOffer); break;
        default: Biome1(); break;
    }
}

void biome1Battle()
{
   int randomMOB = rand()% 101;
   if(defeatedEnemies == 5)
    changeGameState("Biome1Boss");
    else if(randomMOB <= 55) // 55%
        mushroom_battle(25, 3, "Biome1");
    else if(randomMOB <= 80) // 25%
        child_battle(50, 8, "Biome1");
    else if(randomMOB <= 95) // 15%
        mirror_battle(125, "Biome1");
    else if(randomMOB <= 99) // 4%
        bandit_battle(150, 15, "Biome1");
    else if(randomMOB <= 100) // boss 1%
        changeGameState("Biome1Boss");
}

void mushroom_battle(int emaxHP, int edmg, string callback)
{
    int run_mushroom = rand()%5+1;
    int HP_mushroom = emaxHP;
    int reward_mushroom = rand()%5 + 1;
    int xp_mushroom = rand()%5 + 1;
    system("cls");
    renderStats();
    cout << "       |       [ GRZYB ] "; setColor(4); cout << "HP: " << HP_mushroom << "/" << emaxHP; setColor(7);
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
    spacer();
    cout << " [ KLIKNIJ "; setColor(4); cout << "[A]"; setColor(7); cout << ", ABY UDERZYĆ ]" << endl;
    cout << " [ KLIKNIJ "; setColor(4); cout << "[U]"; setColor(7); cout << ", ABY UCIEC ]" << endl;
    spacer();
    do{
        system("cls");
        renderStats();
        cout << "       |       [ GRZYB ] "; setColor(4); cout << "HP: " << HP_mushroom << "/" << emaxHP; setColor(7);
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
        spacer();
        cout << " [ KLIKNIJ "; setColor(4); cout << "[A]"; setColor(7); cout << ", ABY UDERZYĆ ]" << endl;
        cout << " [ KLIKNIJ "; setColor(4); cout << "[U]"; setColor(7); cout << ", ABY UCIEC ]" << endl;
        spacer();
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
        cout << endl << "[ PRZECIWNIK MA " << HP_mushroom << "/" << emaxHP << " HP ]" << endl;
        Sleep(100);
        if(HP_mushroom <= 0){
            cout << "[ POKONAŁEŚ GRZYBA! ]" << endl << endl;
            cout << "[ OTRZYMAŁEŚ: " << reward_mushroom << " ZŁOTA ORAZ " << xp_mushroom << "XP" << " ]";
            gold = gold + reward_mushroom;
            XP = XP + xp_mushroom;
            Sleep(2000);
            defeatedEnemies++;
            changeGameState(callback);
        }
                else{
            HP = HP - edmg;
            cout << "[ STRACIŁEŚ " << edmg << " HP ]" << endl;
            Sleep(100);
                }
        if(HP <= 0){
            cout << "[ UMARŁEŚ... STRACIŁEŚ CZĘŚĆ SWOICH ZAROBKÓW ]";
            gold = gold - (gold/20);
            HP = maxHP*0.5;
            Sleep(2000);
            introducedToBiomeName = false;
            changeGameState(callback);
        }
    }while(HP_mushroom >= 0);
}
void child_battle(int emaxHP, int edmg, string callback)
{
    int run_child = rand()%5+1;
    int HP_child = emaxHP;
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
    spacer();
    cout << " [ KLIKNIJ "; setColor(4); cout << "[A]"; setColor(7); cout << ", ABY UDERZYĆ ]" << endl;
    cout << " [ KLIKNIJ "; setColor(4); cout << "[U]"; setColor(7); cout << ", ABY UCIEC ]" << endl;
    spacer();
    do{
        system("cls");
        renderStats();
        cout << "       |       [ ZŁE DZIECKO ] "; setColor(4); cout << "HP: " << HP_child << "/" << emaxHP; setColor(7);
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
        spacer();
        cout << " [ KLIKNIJ "; setColor(4); cout << "[A]"; setColor(7); cout << ", ABY UDERZYĆ ]" << endl;
        cout << " [ KLIKNIJ "; setColor(4); cout << "[U]"; setColor(7); cout << ", ABY UCIEC ]" << endl;
        spacer();
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
        cout << endl << "[ PRZECIWNIK MA " << HP_child << "/" << emaxHP << " HP ]" << endl;
        Sleep(100);
        if(HP_child <= 0){
            cout << "[ POKONAŁEŚ ZŁE DZIECKO!]" << endl << endl;
            cout << "[ OTRZYMAŁEŚ: " << reward_child << " ZŁOTA ORAZ " << xp_child << "XP" << " ]";
            gold = gold + reward_child;
            XP = XP + xp_child;
            Sleep(2000);
            defeatedEnemies++;
            changeGameState(callback);
        }
                else{
            HP = HP - edmg;
            cout << "[ STRACIŁEŚ " << edmg << " HP ]" << endl;
            Sleep(100);
                }
        if(HP <= 0){
            cout << "[ UMARŁEŚ... STRACIŁEŚ CZĘŚĆ SWOICH ZAROBKÓW ]";
            gold = gold - (gold/20);
            HP = maxHP*0.5;
            Sleep(2000);
            introducedToBiomeName = false;
            changeGameState(callback);
        }
    }while(HP_child >= 0);
}
void mirror_battle(int emaxHP, string callback)
{
    int run_mirror = rand()%5+1;
    int HP_mirror = emaxHP;
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
    spacer();
    cout << " [ KLIKNIJ "; setColor(4); cout << "[A]"; setColor(7); cout << ", ABY UDERZYĆ ]" << endl;
    cout << " [ KLIKNIJ "; setColor(4); cout << "[U]"; setColor(7); cout << ", ABY UCIEC ]" << endl;
    spacer();
    do{
        system("cls");
        renderStats();
        cout << "       |       [ LUSTRO ] "; setColor(4); cout << "HP: " << HP_mirror << "/" << emaxHP; setColor(7);
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
        spacer();
        cout << " [ KLIKNIJ "; setColor(4); cout << "[A]"; setColor(7); cout << ", ABY UDERZYĆ ]" << endl;
        cout << " [ KLIKNIJ "; setColor(4); cout << "[U]"; setColor(7); cout << ", ABY UCIEC ]" << endl;
        spacer();
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
            cout << "[ POKONAŁEŚ SWOJE ODBICIE! ]" << endl << endl;
            cout << "[ OTRZYMAŁEŚ: " << reward_mirror << " ZŁOTA ORAZ " << xp_mirror << "XP" << " ]";
            gold = gold + reward_mirror;
            XP = XP + xp_mirror;
            Sleep(2000);
            defeatedEnemies++;
            changeGameState(callback);
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
            introducedToBiomeName = false;
            changeGameState(callback);
        }
    }while(HP_mirror >= 0);
}
void bandit_battle(int emaxHP, int edmg, string callback)
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
    spacer();
    cout << " [ KLIKNIJ "; setColor(4); cout << "[A]"; setColor(7); cout << ", ABY UDERZYĆ ]" << endl;
    cout << " [ KLIKNIJ "; setColor(4); cout << "[U]"; setColor(7); cout << ", ABY UCIEC ]" << endl;
    spacer();
    do{
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
        spacer();
        cout << " [ KLIKNIJ "; setColor(4); cout << "[A]"; setColor(7); cout << ", ABY UDERZYĆ ]" << endl;
        cout << " [ KLIKNIJ "; setColor(4); cout << "[U]"; setColor(7); cout << ", ABY UCIEC ]" << endl;
        spacer();
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
            cout << "[ POKONAŁEŚ BANDYTĘ! ]" << endl << endl;
            cout << "[ OTRZYMAŁEŚ: " << reward_bandit << " ZŁOTA ORAZ " << xp_bandit << "XP" << " ]";
            gold = gold + reward_bandit;
            XP = XP + xp_bandit;
            Sleep(2000);
            defeatedEnemies++;
            changeGameState(callback);
        }
                else{
            HP = HP - 15;
            cout << "[ STRACIŁEŚ 15 HP ]" << endl;
            Sleep(100);
                }
        if(HP <= 0){
            cout << "[ UMARŁEŚ... STRACIŁEŚ CZĘŚĆ SWOICH ZAROBKÓW ]";
            gold = gold - (gold/20);
            HP = maxHP*0.5;
            Sleep(2000);
            introducedToBiomeName = false;
            changeGameState(callback);
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
    spacer();
    cout << " [ KLIKNIJ "; setColor(4); cout << "[A]"; setColor(7); cout << ", ABY UDERZYĆ ]" << endl;
    cout << " [ BRAK MOŻLIWOŚCI UCIECZKI ] " << endl;
    spacer();
    do{
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
        spacer();
        cout << " [ KLIKNIJ "; setColor(4); cout << "[A]"; setColor(7); cout << ", ABY UDERZYĆ ]" << endl;
        cout << " [ BRAK MOŻLIWOŚCI UCIECZKI ] " << endl;
        spacer();
        char atk;
        do
        atk = getch();
        while(atk!='a' && atk!='u');
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
            case 'u': cout << "[ BRAK MOŻLIWOŚCI UCIECZKI. ]" << endl; Sleep(200); break;
            default: cout << "[ STRACIŁEŚ OKAZJĘ NA ATAK... A PRZECIWNIK JĄ WYKORZYSTAŁ ]" << endl; Sleep(1500); break;
        }
        cout << endl << "[ PRZECIWNIK MA " << HP_GOLEM << "/" << "300 HP ]" << endl;
        Sleep(100);
        if(HP_GOLEM <= 0){
            cout << "[ POKONAŁEŚ PIERWSZEGO BOSSA GOLEM'a! ]" << endl << endl;
            cout << "[ OTRZYMAŁEŚ: " << reward_GOLEM << " ZŁOTA ORAZ " << xp_GOLEM << "XP" << " ]";
            gold = gold + reward_GOLEM;
            XP = XP + xp_GOLEM;
            Sleep(2000);
            defeatedEnemies = 0;
            introducedToBiomeName = false;
            changeGameState("Biome2");
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
            changeGameState("Biome1");
        }
    }while(HP_GOLEM >= 0);
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
        case 6: return 15; break;
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
            setColor(rarityToColor(stoi(item[3]))); cout << "  [ " << i+1 << ". " << item[0] << " | "; setColor(1); cout << "OBRAŻENIA: " << item[1]; setColor(rarityToColor(stoi(item[3]))); cout << " ]"; setColor(7);
            if(i == heldItem)
            {
                setColor(2); cout << " [ WYPOSAŻONY ]"; setColor(7);
            }
            cout << endl;
        }
        else
        {
            setColor(rarityToColor(stoi(item[3]))); cout << "  [ " << i+1 << ". " << item[0] << " ]" << endl; setColor(7);
        }
    }
    spacer();
    setColor(4); cout << "  [W]"; setColor(7); cout << " Wyrzuć przedmiot" << endl;
    setColor(4); cout << "  [E]"; setColor(7); cout << " Wyposaż przedmiot" << endl;

    char inp = tolower(getch());
    if(inp == 'b') backToBiome();
    else if(inp == 'w') dropItem();
    else if(inp == 'e') equipItem();
    else openInventory();
}

void healMenu(int* storeOffer)
{
    system("cls");
    cout << "  < Wciśnij "; setColor(4); cout << "[B]"; setColor(7); cout << ", aby powrócić do sklepu." << endl << endl;
    setColor(6); cout << "  [ ZŁOTO NA KONCIE: " << gold << " ]" << endl;
    setColor(2); cout << "  [ HP: " << HP << "/" << maxHP << " ]" << endl << endl << endl; setColor(7);
    cout << "  [ LECZENIE ]" << endl;
    spacer();
    setColor(2); cout << "  [ 1. ULECZ +10HP ]"; setColor(6); cout << "\tCENA: 5" << endl;
    setColor(2); cout << "  [ 2. ULECZ +15HP ]"; setColor(6); cout << "\tCENA: 10" << endl;
    setColor(2); cout << "  [ 3. ULECZ +20HP ]"; setColor(6); cout << "\tCENA: 15" << endl;
    setColor(2); cout << "  [ 4. ULECZ +50HP ]"; setColor(6); cout << "\tCENA: 40" << endl;
    setColor(2); cout << "  [ 5. ULECZ +100HP ]"; setColor(6); cout << "\tCENA: 80" << endl;
    spacer();
    setColor(7);
    cout << "  Kliknij przycisk od 1 do 5, aby kupić przedmiot." << endl;
    char inp = getch();
    switch (inp)
    {
        case 'b': openStore(storeOffer); break;
        case '1': healItemConfirmation(10, 5, storeOffer); break;
        case '2': healItemConfirmation(15, 10, storeOffer); break;
        case '3': healItemConfirmation(20, 15, storeOffer); break;
        case '4': healItemConfirmation(50, 40, storeOffer); break;
        case '5': healItemConfirmation(100, 90, storeOffer); break;
        default: healMenu(storeOffer); break;
    }
}

void healItemConfirmation(int value, int price, int* offer)
{
    if(price > gold)
    {
        cout << "  Niewystarczające środki, aby uleczyć "; setColor(2); cout << value << "HP"; setColor(7); cout << "." << endl;
        Sleep(1000);
        openStore(offer);
    }
    else
    {
        cout << "  Leczysz: "; setColor(2); cout << value << "HP" << endl; setColor(7);
        cout << "  Ta operacja odejmie " << price << " złota z twojego konta." << endl;
        setColor(4); cout << "  UWAGA! "; setColor(7); cout << "Tej akcji nie można cofnąć." << endl << endl;
        setColor(4); cout << endl << "  [X]"; setColor(7); cout << " Anuluj" << endl;
        setColor(4); cout << endl << "  [C]"; setColor(7); cout << " Potwierdź" << endl << endl;
        char inp = tolower(getch());
        switch (inp)
        {
            case 'c': gold -= price; heal(value); healMenu(offer); break;
            case 'x': healMenu(offer); break;
            default: healItemConfirmation(value, price, offer); break;
        }
    }
}

void heal(int value)
{
    if(HP + value > maxHP) HP = maxHP;
    else HP += value;
}


void openStore(int storeOffer[])
{
    system("cls");
    cout << "  < Wciśnij "; setColor(4); cout << "[B]"; setColor(7); cout << ", aby powrócić." << endl << endl;
    setColor(6); cout << "  [ ZŁOTO NA KONCIE: " << gold << " ]" << endl << endl << endl; setColor(7);
    cout << "  [ SKLEP ]" << endl;
    spacer();
    setColor(12); cout << "  [ 0. WCIŚNIJ [0] ABY PRZEJŚĆ DO SKLEPU Z LECZENIEM ]" << endl; setColor(7);
    char delimiter = '|';
    for(int i = 0; i < 9; i++)
    {
        std::vector<std::string> item = splitString(items[storeOffer[i]], delimiter);
        setColor(rarityToColor(stoi(item[3]))); cout << "  [ " << i+1 << ". " << item[0] << " | "; setColor(1); cout << "OBRAŻENIA: " << item[1]; setColor(rarityToColor(stoi(item[3]))); cout << " | "; setColor(6); cout << "CENA: " << item[2]; setColor(rarityToColor(stoi(item[3]))); cout << " ]" << endl; setColor(7);
    }
    spacer();
    setColor(4); cout << endl << "  [K]"; setColor(7); cout << " Kup przedmiot" << endl << endl;
    char inp = getch();
    switch (inp)
    {
        case 'b': backToBiome(); break;
        case 'k': buyItem(storeOffer); break;
        case '0': healMenu(storeOffer); break;
        default: openStore(storeOffer); break;
    }
}

void dropItem()
{
    cout << "  --------------------------------------------" << endl;
    setColor(4); cout << endl << "  [X]"; setColor(7); cout << " Anuluj" << endl << endl;
    setColor(4); cout << "  UWAGA! "; setColor(7); cout << "Wyrzucenie przedmiotu z ekwipunku jest równoznaczne z jego zniszczeniem." << endl;
    cout << "  Tej akcji nie można cofnąć." << endl << endl;
    cout << "  Kliknij przycisk od 1 do 5, aby wyrzucić przedmiot." << endl;
    char delItem = tolower(getch());
    switch (delItem)
    {
        case '1': inventory[0] = 0; openInventory(); break;
        case '2': inventory[1] = 0; openInventory(); break;
        case '3': inventory[2] = 0; openInventory(); break;
        case '4': inventory[3] = 0; openInventory(); break;
        case '5': inventory[4] = 0; openInventory(); break;
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
    cout << "  Kliknij przycisk od 1 do 9, aby kupić przedmiot." << endl;
    char inp = getch();
    switch (inp)
    {
        case '1': buyItemConfirmation(offer[0], offer); break;
        case '2': buyItemConfirmation(offer[1], offer); break;
        case '3': buyItemConfirmation(offer[2], offer); break;
        case '4': buyItemConfirmation(offer[3], offer); break;
        case '5': buyItemConfirmation(offer[4], offer); break;
        case '6': buyItemConfirmation(offer[5], offer); break;
        case '7': buyItemConfirmation(offer[6], offer); break;
        case '8': buyItemConfirmation(offer[7], offer); break;
        case '9': buyItemConfirmation(offer[8], offer); break;
        case 'x': openStore(offer); break;
        default: buyItem(offer); break;
    }
}

void buyItemConfirmation(int item, int* offer)
{
    char delimiter = '|';
    std::vector<std::string> itemToGet = splitString(items[item], delimiter);
    cout << "  --------------------------------------------" << endl;
    if(stoi(itemToGet[2]) > gold)
    {
        cout << "  Niewystarczające środki, aby kupić "; setColor(rarityToColor(stoi(itemToGet[3]))); cout << itemToGet[0]; setColor(7); cout << "." << endl;
        Sleep(1000);
        openStore(offer);
    }
    else
    {
        cout << "  Kupujesz: "; setColor(rarityToColor(stoi(itemToGet[3]))); cout << itemToGet[0] << endl; setColor(7);
        cout << "  Ta operacja odejmie " << itemToGet[2] << " złota z twojego konta." << endl;
        setColor(4); cout << "  UWAGA! "; setColor(7); cout << "Tej akcji nie można cofnąć." << endl << endl;
        setColor(4); cout << endl << "  [X]"; setColor(7); cout << " Anuluj" << endl;
        setColor(4); cout << endl << "  [C]"; setColor(7); cout << " Potwierdź" << endl << endl;
        char inp = tolower(getch());
        switch (inp)
        {
            case 'c': gold -= stoi(itemToGet[2]); assignToInventory(item); openStore(offer); break;
            case 'x': openStore(offer); break;
            default: buyItemConfirmation(item, offer); break;
        }
    }
}

void equipItem()
{
    cout << "  --------------------------------------------" << endl;
    setColor(4); cout << endl << "  [X]"; setColor(7); cout << " Anuluj" << endl << endl;
    cout << "  Kliknij przycisk od 1 do 5, aby wyposażyć przedmiot." << endl;
    char inp = getch();
    switch (inp)
    {
        case '1': equipItemConfirmation(0); break;
        case '2': equipItemConfirmation(1); break;
        case '3': equipItemConfirmation(2); break;
        case '4': equipItemConfirmation(3); break;
        case '5': equipItemConfirmation(4); break;
        case 'x': openInventory(); break;
        default: equipItem(); break;
    }
}

void equipItemConfirmation(int position)
{
    char delimiter = '|';
    std::vector<std::string> itemToEquip = splitString(items[inventory[position]], delimiter);
    cout << "  --------------------------------------------" << endl;
    if(inventory[position] == 0)
    {
        cout << "  Na tej pozycji nie ma żadnego przedmiotu." << endl;
        Sleep(1000);
        openInventory();
    }
    else
    {
        cout << "  Wyposażono: "; setColor(rarityToColor(stoi(itemToEquip[3]))); cout << itemToEquip[0] << endl; setColor(7);
        heldItem = position;
        DMG = stoi(itemToEquip[1]);
        Sleep(1000);
        openInventory();
    }
}

void biome2()
{
    system("cls");
    biomeNameIntroduction("Zamrożona Twierdza");
    biomeControls(true);
    int biomeOffer[] = {12, 13, 14, 15, 16, 17, 18, 19, 20};

    char inp = getch();
    switch (inp)
    {
        case 'e': changeGameState("Biome2Battle"); break;
        case 'i': openInventory(); break;
        case 's': openStore(biomeOffer); break;
        default: Biome2(); break;
    }
}

void Biome2()
{
    system("cls");
    biomeControls(false);
    int biomeOffer[] = {12, 13, 14, 15, 16, 17, 18, 19, 20};

    char inp = getch();
    switch (inp)
    {
        case 'e': changeGameState("Biome2Battle"); break;
        case 'i': openInventory(); break;
        case 's': openStore(biomeOffer); break;
        default: Biome2(); break;
    }
}

void biome2Battle()
{
   int randomMOB = rand()% 101;
   if(defeatedEnemies == 7)
    changeGameState("Boss2Battle");
    else if(randomMOB <= 55) // 55%
        mushroom_battle(40, 10, "Biome2");
    else if(randomMOB <= 80) // 25%
        child_battle(50, 9, "Biome2");
    else if(randomMOB <= 95) // 15%
        mirror_battle(200, "Biome2");
    else if(randomMOB <= 99) // 4%
        bandit_battle(300, 30, "Biome2");
    else if(randomMOB <= 100) // boss 1%
        changeGameState("Boss2Battle");
}

void BOSS2_battle()
{
    cout << "walka z bossem";
}
