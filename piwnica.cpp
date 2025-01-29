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

string nick;
int HP = 100; int maxHP = 100; int DMG = 5;
int gold = 0;
// Menu, IntroSequence, Biome1, Biome1Battle, Biome1Boss, Biome2, Biome2Store, Biome2Battle, Biome2Boss, Biome3, Biome3Store, Biome3Battle, Biome3Boss, Biome4, Biome4Store, Biome4Battle, Biome4Boss, Biome5, Biome5Store, Biome5Battle, Biome5Boss, EndSequence
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
    setColor(5); cout << "[ " << nick << " ] "; setColor(2); cout << "HP: " << HP << "/" << maxHP; setColor(6); cout << " ZŁOTO: " << gold; setColor(7);
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
    if(gameState == "Biome1")
        changeGameState("Menu");

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
    setColor(4); cout << "  [U]"; setColor(7); cout << " Ucieknij" << endl;
    spacer();

    char inp = getch();
    switch (inp)
    {
        case 'e': changeGameState("Biome1Battle"); break;
        case 'i': openInventory(); break;
        case 'u': escapeEnemy();
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
    setColor(4); cout << "  [U]"; setColor(7); cout << " Ucieknij" << endl;
    spacer();

    char inp = getch();
    switch (inp)
    {
        case 'e': changeGameState("Biome1Battle"); break;
        case 'i': openInventory(); break;
        case 'u': escapeEnemy(); break;
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
    int HP_mushroom = 25;
    int reward_mushroom = rand()%4 + 1;
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

    cout << endl << "[ GRZYB MA " << HP_mushroom << "/" << "25 HP ]" << endl;
    cout << " [ KLIKNIJ "; setColor(4); cout << "[A]"; setColor(7); cout << ", ABY UDERZYĆ ]" << endl;
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
    char atk = getch();
    switch (atk)
    {
        case 'a': HP_mushroom = HP_mushroom - DMG; break;
        default: cout << "[ STRACIŁEŚ OKAZJĘ NA ATAK... A PRZECIWNIK JĄ WYKORZYSTAŁ ]" << endl; Sleep(1500); break;
    }
    cout << endl << "[ PRZECIWNIK MA " << HP_mushroom << "/" << "25 HP ]" << endl;
    Sleep(100);
    if(HP_mushroom <= 0){
        cout << "[ POKONAŁEŚ GRZYBA!]" << endl << endl;
        cout << "[ OTRZYMAŁEŚ: " << reward_mushroom << " ZŁOTA ]";
        gold = gold + reward_mushroom;
        Sleep(2000);
        biome1();
    }
            else{
        HP = HP - 3;
        cout << "[ STRACIŁEŚ 3 HP]" << endl;
        Sleep(500);
            }
    if(HP <= 0){
        cout << "[ UMARŁEŚ... ]";
        Sleep(2000);
        death();
    }
    }while(HP_mushroom >= 0);
}
void child_battle()
{
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
    int HP_child = 50;
    cout << endl << "[ ZŁE DZIECKO MA " << HP_child << "/" << "50 HP ]" << endl;
}
void mirror_battle()
{
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
    int HP_mirror = 75;
    cout << endl << "[ LUSTRO MA " << HP_mirror << "/" << "75 HP ]" << endl;
}
void bandit_battle()
{
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
    int HP_bandit = 150;
    cout << endl << "[ BANDYTA MA " << HP_bandit << "/" << "150 HP ]" << endl;
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
    system("cls");
    renderStats();
    spacer();
    cout << "                                                       " << endl;
    cout << "                                                       " << endl;
    cout << "                                                       " << endl;
    cout << "                                                       " << endl;
    cout << "                                                       " << endl;
    cout << "     █████                                             " << endl;
    cout << "    █     █                                            " << endl;
    cout << "   █   ◉ ◉ █                                           " << endl;
    cout << "   █   ▄   █                                           " << endl;
    cout << "    █     █                                            " << endl;
    cout << "    ▄█████▄                                            " << endl;
    cout << "   █  ███  █                                           " << endl;
    cout << "     ▄███▄                                             " << endl;
    cout << "    █     █                                            " << endl;
    cout << "   ▄█     █▄                                           " << endl;
    Sleep(500);
    int HP_BOSS1 = 300;
    cout << endl << "[ PRZECIWNIK MA " << HP_BOSS1 << "/" << "300 HP ]" << endl;
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
        setColor(rarityToColor(stoi(item[3]))); cout << "  [ " << i+1 << ". " << item[0] << " ]" << endl; setColor(7);
    }

    char inp = getch();
    if(inp == 'b') Biome1();
    else openInventory();
}
