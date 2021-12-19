#include "menu.h"

int getChoice(int l_gap, int h_gap) {
    int num;
    num = getchar() - '0';
    while((num < l_gap) || (num > h_gap)) {
        num = getchar() - '0';
        cout << num << "\n";
    }
    return num;
}

void showMainMenu() {
    std::cout << "\n===================\n"
                 "MENU\n"
                 "  1 SELECT LIST\n"
                 "  2 ADD LIST\n"
                 "  3 INSERT LIST\n"
                 "  4 REMOVE LIST\n"
                 "  5 SORT\n"
                 "  6 BALANCE\n"
                 "  7 RESIZE\n"
                 "  8 LOAD FROM FILE\n"
                 "  9 LOAD TO FILE\n"
                 "  0 EXIT\n"
                 "===================\n";
}

void mainMenu(TLList<string>& object) {
    int choice;
    uint selected_node;
    char str[50];
    bool flag = true;
    fstream f;
    while (flag) {
        showMainMenu();
        choice = getChoice(0, 8);
        switch (choice) {
            case 0:
                flag = false;
                break;
            case 1:
                break;
            case 2:
                system("clear");
                object.addList();
                break;
            case 3:
                system("clear");
                cout << "ENTER POSITION\n";
                selected_node = getChoice(0, object.getSize());
                object.insertList(selected_node);
                break;
            case 4:
                system("clear");
                std::cout << "ENTER POSITION\n";
                selected_node = getChoice(0, object.getSize() - 1);
                object.removeList(selected_node);
                break;
            case 5:
                system("clear");
                object.sortLists();
                break;
            case 6:
                system("clear");
                object.balance();
                break;
            case 7:
                system("clear");
                std::cout << "ENTER NEW SIZE\n"
                             "0 - BACK\n";
                selected_node = getChoice(0, 1000);
                object.resize(selected_node);
                break;
            case 8:
                system("clear");
                f.open(fpath, ios::binary|ios::in);
                object.loadFromBin(f);
                f.close();
                break;
            case 9:
                system("clear");
                f.open(fpath, ios::binary|ios::out);
                object.loadToBin(f);
                f.close();
                break;
        }
    }
}