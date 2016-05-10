

//HEADER
#include <iostream>
#include <string>
#include <map>
#include "mainwindow.h"
#include <QString>
#include <QTextEdit>
#include <QKeyEvent>

class COMPy
{
public:
    COMPy(MainWindow * w);

    struct List
    {
        int int_data;
        double double_data;
        std::string string_data;

        List* rlink; //used for normal linked lists.
        List* dlink; //used lists inside of lists.
    };


    std::map <std::string, List*> database;
    std::map <std::string, List*>::iterator iter_database;

    void nextStep();

private:
    void at(List* node, int index);
    void copyList(List* &node, List* objLeft, List* objRight, bool finished);
    int size(List* node);

    List*& iter_at(List* &node, const int& index); //returns the node at a point

    void change_item_int(std::string data, List* &node, const int& index);
    void change_item_double(std::string data, List* &node, const int& index);
    void change_item_string(std::string data, List* &node, const int& index);

    void additem_int(std::string data, List* &node);
    void additem_double(std::string data, List* &node);
    void additem_string(std::string data, List* &node);
    void display(const List* node);

    MainWindow * p_w;

};

