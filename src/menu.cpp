#include "menu.h"

#ifdef __linux__
#define clear_console_ "clear"
#else
#define clear_console_ "cls"
#endif

uint GetChoice(uint l_gap, uint h_gap, const char* msg) {
  uint num;
  do {
    cout << msg;
    cin >> num;
  } while ((num < l_gap) || (num > h_gap));
  return num;
}

void ShowListSizes(TLList<string> &object) {
  uint sz = object.getSize();
  std::cout << "Size: " << sz << "\n";
  for (uint i = 0; i < sz; i++)
    std::cout << i << " list size: " << object.getListSize(i) << "\n";
}

void ShowMainMenu() {
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

void MainMenu(TLList<string> &object) {
  int choice;
  uint selected_node;
  uint selected_elem;
  bool flag = true;
  fstream f;
  string str;
  while (flag) {
    system(clear_console_);
    cout << object << "\n";
    ShowListSizes(object);
    ShowMainMenu();
    choice = GetChoice(0, 13, "");
    switch (choice) {
      case 0:
        flag = false;
        break;
      case 1:
        system(clear_console_);
        object.addList();
        break;
      case 2:
        system(clear_console_);
        cout << object << "\n";
        ShowListSizes(object);
        selected_node = GetChoice(0, object.getSize(), "ENTER POSITION\n");
        try {
          object.insertList(selected_node);
        } catch (exception &ex) {
          cout << ex.what() << "\n";
        }
        break;
      case 3:
        system(clear_console_);
        cout << object << "\n";
        ShowListSizes(object);
        selected_node = GetChoice(0, object.getSize() - 1, "ENTER POSITION\n");
        try {
          object.removeList(selected_node);
        } catch (exception &ex) {
          cout << ex.what() << "\n";
        }
        break;
      case 4:
        cout << "ENTER CONTENT\n";
        cin >> str;
        object.add(&str);
        break;
      case 5:
        cout << "ENTER CONTENT\n";
        cin >> str;
        selected_node = GetChoice(0, object.getSize() - 1, "ENTER LIST NUMBER\n");
        selected_elem = GetChoice(0, object.getListSize(selected_node), "ENTER POSITION\n");
        try {
          object.insert(selected_node, selected_elem, &str);
        } catch (exception &ex) {
          cout << ex.what() << "\n";
        }
        break;
      case 6:
        selected_node = GetChoice(0, object.getSize() - 1, "ENTER LIST NUMBER\n");
        selected_elem = GetChoice(0, object.getListSize(selected_node) - 1, "ENTER POSITION\n");
        try {
          object.remove(selected_node, selected_elem);
        } catch (exception &ex) {
          cout << ex.what() << "\n";
        }
        break;
      case 7:
        cout << "ENTER CONTENT\n";
        cin >> str;
        object.orderedAdd(&str);
        break;
      case 8:
        cout << "ENTER CONTENT\n";
        cin >> str;
        selected_node = GetChoice(0, object.getSize(), "ENTER LIST NUMBER\n");
        object.orderedInsert(selected_node, &str);
        break;
      case 9:
        object.sort();
        break;
      case 10:
        object.balance();
        break;
      case 11:
        system(clear_console_);
        cout << object << "\n";
        ShowListSizes(object);
        selected_node = GetChoice(0, 1000, "ENTER NEW SIZE\n0 - BACK\n");
        if (selected_node != 0) object.resize(selected_node);
        break;
      case 12:
        system(clear_console_);
        f.open(fpath, ios::binary | ios::in);
        object.loadFromBin(f);
        f.close();
        break;
      case 13:
        system(clear_console_);
        f.open(fpath, ios::binary | ios::out);
        object.loadToBin(f);
        f.close();
        break;
    }
  }
}
