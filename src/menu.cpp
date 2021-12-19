#include "menu.h"

uint getChoice(uint l_gap, uint h_gap) {
    uint num;
    do
        cin >> num;
    while((num < l_gap) || (num > h_gap));
    return num;
}

void showMainMenu() {
    cout << "\n===================\n"
                 "MENU\n"
                 "  1 ADD LIST\n"
                 "  2 INSERT LIST\n"
                 "  3 REMOVE LIST\n"
                 "  4 ADD ELEMENT\n"
                 "  5 INSERT ELEMENT\n"
                 "  6 REMOVE ELEMENT\n"
                 "  7 ORDERED ADD\n"
                 "  8 ORDERED INSERT\n"
                 "  9 SORT\n"
                 "  10 BALANCE\n"
                 "  11 RESIZE\n"
                 "  12 LOAD FROM FILE\n"
                 "  13 LOAD TO FILE\n"
                 "  0 EXIT\n"
                 "===================\n";
}

void mainMenu(TLList<string>& object) {
    int choice;
    uint selected_node;
    uint selected_elem;
    bool flag = true;
    fstream f;
    string str;
    while (flag) {
        system("clear");
        cout << object;
        showMainMenu();
        choice = getChoice(0, 13);
        switch (choice) {
            case 0:
                flag = false;
                break;
            case 1:
                system("clear");
                object.addList();
                break;
            case 2:
                system("clear");
                cout << "ENTER POSITION\n";
                selected_node = getChoice(0, object.getSize());
                object.insertList(selected_node);
                break;
            case 3:
                system("clear");
                cout << "ENTER POSITION\n";
                selected_node = getChoice(0, object.getSize() - 1);
                object.removeList(selected_node);
                break;
            case 4:
                cout << "ENTER CONTENT\n";
                cin >> str;
                object.add(&str);
                break;
            case 5:
                cout << "ENTER CONTENT\n";
                cin >> str;
                cout << "ENTER LIST NUMBER\n";
                selected_node = getChoice(0, object.getSize());
                cout << "ENTER POSITION\n";
                selected_elem = getChoice(0, object.getListSize(selected_node));
                object.insert(selected_node, selected_elem, &str);
                break;
            case 6:
                cout << "ENTER LIST NUMBER\n";
                selected_node = getChoice(0, object.getSize());
                cout << "ENTER POSITION\n";
                selected_elem = getChoice(0, object.getListSize(selected_node));
                object.remove(selected_node, selected_elem);
                break;
            case 7:
                cout << "ENTER CONTENT\n";
                cin >> str;
                object.orderedAdd(&str);
                break;
            case 8:
                cout << "ENTER CONTENT\n";
                cin >> str;
                cout << "ENTER LIST NUMBER\n";
                selected_node = getChoice(0, object.getSize());
                object.orderedInsert(selected_node, &str);
                break;
            case 9:
                system("clear");
                object.sortLists();
                break;
            case 10:
                system("clear");
                object.balance();
                break;
            case 11:
                system("clear");
                cout << "ENTER NEW SIZE\n"
                             "0 - BACK\n";
                selected_node = getChoice(0, 1000);
                object.resize(selected_node);
                break;
            case 12:
                system("clear");
                f.open(fpath, ios::binary|ios::in);
                object.loadFromBin(f);
                f.close();
                break;
            case 13:
                system("clear");
                f.open(fpath, ios::binary|ios::out);
                object.loadToBin(f);
                f.close();
                break;
        }
    }
}