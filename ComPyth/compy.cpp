//IMPLEMENTATION
#include "compy.h"
#include "mainwindow.h"
#include <QDebug>
using namespace std;

COMPy::COMPy(MainWindow * w)
{
    p_w = w;
}


void COMPy::nextStep()
{
        p_w->getLine();
        p_w->addLine(">>> ");
        qDebug() << "Entered next step";

        string user_input = p_w->n_line;
        string key = "";


        size_t found, findComma, bracketFindLeft, bracketFindRight;
        size_t front = 0;

        front = user_input.find(' ');
        while (front != string::npos)
        {
            user_input.erase(front, 1);
            front = user_input.find(' ');
        }

        size_t back = user_input.find("=");
        front = 0;
        found = user_input.find("+");
        findComma = user_input.find(",");
        bracketFindLeft = user_input.find("[");
        bracketFindRight = user_input.find("]");
        if (bracketFindLeft != string::npos && bracketFindRight != string::npos && back != string::npos && bracketFindRight < back) //example: x[1] = 32
        {
            size_t anotherBracket = user_input.find("[", back + 1); //checks if there is another bracket after the = sign. example x[1] = [1,2]
            front = bracketFindLeft + 1;
            back = bracketFindRight;
            key = user_input.substr(0, bracketFindLeft); //is the substring that comes before the bracket
            iter_database = database.find(key);
            string tempIndex = user_input.substr(front, back - front); //takes the number in the [] and converts it to int
            int index = stoi(tempIndex);
            List* tempNode;
            if (anotherBracket == string::npos) //the case of x[i] = n
            {
                front = user_input.find("=") + 1;
                back = user_input.size();
                string tempData = user_input.substr(front, back - front); //gets the data that comes after the equal sign

                found = user_input.find(".", front);
                if (tempData.at(0) == '"') //if true, then the element must be a string.
                {
                    iter_database = database.find(key);
                    tempNode = iter_database->second;
                    change_item_string(tempData, tempNode, index);
                }
                else if (found < front + back) //if there is a decimal without strings it assumes double.
                {
                    iter_database = database.find(key);
                    tempNode = iter_database->second;
                    change_item_double(tempData, tempNode, index);
                }
                else //integer
                {
                    iter_database = database.find(key);
                    tempNode = iter_database->second;
                    change_item_int(tempData, tempNode, index);
                }
            }
            else //the case of x[i] = [a, b, c]
            {
                List* anotherTemp;
                bool flag = false;
                bool listHelper = true;
                int count = 0;
                front = anotherBracket + 1;
                while (front < user_input.size())
                {
                    listHelper = (count < 1 ? true : false); //the first element is just replacing the element of the linklist, but after that the other content of the new list is added to the dlink

                    string tempData = "";
                    back = user_input.find(',', front) - front;

                    if (back > user_input.size())
                    {
                        back = user_input.find(']', front) - front;
                        flag = true;
                    }
                    tempData = user_input.substr(front, back);

                    found = user_input.find(".", front);
                    if (tempData.at(0) == '"') //if true, then the element must be a string.
                    {
                        iter_database = database.find(key);
                        tempNode = iter_database->second;
                        anotherTemp = iter_at(tempNode, index);
                        if (listHelper)
                            change_item_string(tempData, anotherTemp, 0);
                        else
                        {
                            additem_string(tempData, anotherTemp->dlink);
                        }
                    }
                    else if (found < front + back) //if there is a decimal without strings it assumes double.
                    {
                        iter_database = database.find(key);
                        tempNode = iter_database->second;
                        anotherTemp = iter_at(tempNode, index);
                        if (listHelper)
                            change_item_double(tempData, anotherTemp, 0);
                        else
                        {
                            additem_double(tempData, anotherTemp->dlink);
                        }
                    }
                    else //integer
                    {
                        iter_database = database.find(key);
                        tempNode = iter_database->second;
                        anotherTemp = iter_at(tempNode, index);
                        if (listHelper)
                            change_item_int(tempData, anotherTemp, 0);
                        else
                        {
                            additem_int(tempData, anotherTemp->dlink);
                        }
                    }

                    front = user_input.find(',', front) + 1;

                    ++count;
                    if (flag)
                        break;
                }
            }


        }
        else if (back == string::npos && findComma == string::npos && bracketFindLeft != string::npos && bracketFindRight != string::npos) //the [] operator
        {
            front = bracketFindLeft;
            back = bracketFindRight;
            key = user_input.substr(0, front);
            string tempIndex = user_input.substr(front + 1, back - front - 1);
            int index = stoi(tempIndex);
            iter_database = database.find(key);

            if (index < 0)
                at(iter_database->second, size(iter_database->second) + index);//passes the node and the size of the list + the negative index
            else
                at(iter_database->second, index);
        }
        else if (back != string::npos && found != string::npos && bracketFindLeft == string::npos)// adding 2 lists
        {
            string temp = user_input.substr(0, back);
            key = temp;
            user_input.erase(0, back + 1);

            found = user_input.find("+");
            string tempLeft = user_input.substr(0, found);
            string tempRight = user_input.substr(found + 1, user_input.size() - found);
            List* tempNodeLeft = database.find(tempLeft)->second;
            List* tempNodeRight = database.find(tempRight)->second;
            database.insert(pair<string, List*>(key, NULL));
            iter_database = database.find(key);
            copyList(iter_database->second, tempNodeLeft, tempNodeRight, false);
        }
        else if (back != string::npos) //if there is an equals sign
        {
            bool flag = false;
            string temp = user_input.substr(front, back);


            key = temp;
            iter_database = database.find(key);
            if (iter_database != database.end()) //if the key is already in the database
            {
                database.erase(iter_database);
            }
            database.insert(pair<string, List*>(key, NULL));
            front = user_input.find('[') + 1;
            while (front < user_input.size())
            {
                back = user_input.find(',', front) - front;

                if (back > user_input.size())
                {
                    back = user_input.find(']', front) - front;
                    flag = true;
                }
                temp = user_input.substr(front, back);

                found = user_input.find(".", front);
                if (temp.at(0) == '"') //if true, then the element must be a string.
                {
                    iter_database = database.find(key);
                    additem_string(temp, iter_database->second);
                }
                else if (found < front + back) //if there is a decimal without strings it assumes double.
                {
                    iter_database = database.find(key);
                    additem_double(temp, iter_database->second);
                }
                else //integer
                {
                    iter_database = database.find(key);
                    additem_int(temp, iter_database->second);
                }

                front = user_input.find(',', front) + 1;


                if (flag)
                    break;
            }
        }

        iter_database = database.find(user_input);
        if (iter_database != database.end()) //if the user enters the name of a created list.
        {
            p_w->addLine("[");
            display(iter_database->second);
        }
        else if (user_input == "credits")
        {
            p_w->addLine("\tMade by Ari, Austin, Adam, Jed, and Sergio");
            p_w->addLine("\n");
        }
}

COMPy::List*& COMPy::iter_at(List* &node, const int& index)
{
    int count = 0;
    int tempIndex = index;
    if (index < 0) // negative change index
    {
        tempIndex = size(node) + index;
    }
    while (count != tempIndex)
    {
        node = node->rlink;
        ++count;
    }

    if (node == NULL)
    {
        p_w->addLine("Error subscript out of range.");
        p_w->addLine("\n");
    }
    else
        return node;
}

void  COMPy::at(List* node, int index) //positive []. example list[7];
{
    int count = 0;
    while (count != index)
    {
        node = node->rlink;
        ++count;
    }

    if (node == NULL)
    {
        p_w->addLine("Error subscript out of range.");
        p_w->addLine("\n");
    }
    else
    {

        p_w->addLine(node->string_data);
        p_w->addLine("\n");
    }
}


void COMPy::copyList(List* &node, List* objLeft, List* objRight, bool finished)
{
    if (objLeft == NULL && finished)
        return;
    else if (objLeft == NULL && !finished)
    {
        finished = true;
        copyList(node, objRight, objLeft, finished);
        return;
    }
    else
    {
        node = new List;
        node->double_data = objLeft->double_data;
        node->string_data = objLeft->string_data;
        node->int_data = objLeft->int_data;
        node->rlink = NULL;
        node->dlink = NULL;
        if (objLeft->dlink != NULL)
            copyList(node->dlink, objLeft->dlink, objRight, finished);
        else
            copyList(node->rlink, objLeft->rlink, objRight, finished);
    }
}

void COMPy::additem_double(string data, List* &node)
{
    double double_temp = stoi(data);
    if (node == NULL)
    {
        node = new List;
        node->double_data = double_temp;
        node->string_data = data;
        node->rlink = NULL;
        node->dlink = NULL;
        node->int_data = 0;
    }
    else
    {
        additem_double(data, node->rlink);
    }
}

void COMPy::additem_int(string data, List* &node)
{
    int int_temp = stoi(data);
    if (node == NULL)
    {
        node = new List;
        node->int_data = int_temp;
        node->string_data = data;
        node->rlink = NULL;
        node->dlink = NULL;
        node->double_data = 0;
    }
    else
    {
        additem_int(data, node->rlink);
    }
}

void COMPy::additem_string(string data, List* &node)
{
    if (node == NULL)
    {
        node = new List;
        node->string_data = data;
        node->rlink = NULL;
        node->dlink = NULL;
        node->double_data = 0;
        node->int_data = 0;
    }
    else
    {
        additem_string(data, node->rlink);
    }
}

void COMPy::display(const List* node)
{
    if (node == NULL)
    {
        p_w->addLine("]");
        return;
    }
    else
    {
        if (node->dlink != NULL)
        {
            p_w->addLine("[");
            p_w->addLine(node->string_data);
            p_w->addLine(", ");
            display(node->dlink);
        }
        else
        {
            p_w->addLine(node->string_data);
        }
        if (node->rlink != NULL)
            p_w->addLine(", ");
        display(node->rlink);
    }
}

int COMPy::size(List* node)
{
    int size = 0;
    while (node != NULL)
    {
        node = node->rlink;
        ++size;
    }
    return size;
}

void COMPy::change_item_int(std::string data, List* &node, const int& index)
{
    int new_int_data = stoi(data);
    int count = 0;
    int tempIndex = index;
    if (index < 0) // negative change index
    {
        tempIndex = size(node) + index;
    }
    while (count != index)// go to the node at the index
    {
        node = node->rlink;
        ++count;
    }

    if (node == NULL)
    {
        p_w->addLine("Error subscript out of range.");
        p_w->addLine("\n");
    }
    else
    {
        node->int_data = new_int_data;
        node->double_data = 0;
        node->string_data = data;
    }
}
void COMPy::change_item_double(std::string data, List* &node, const int& index)
{
    double new_double_data = stoi(data);
    int count = 0;
    int tempIndex = index;
    if (index < 0) // negative change index
    {
        tempIndex = size(node) + index;
    }
    while (count != index)// go to the node at the index
    {
        node = node->rlink;
        ++count;
    }

    if (node == NULL)
    {
        p_w->addLine("Error subscript out of range.");
        p_w->addLine("\n");
    }
    else
    {
        node->int_data = 0;
        node->double_data = new_double_data;
        node->string_data = data;
    }
}
void COMPy::change_item_string(std::string data, List* &node, const int& index)
{
    int count = 0;
    int tempIndex = index;
    if (index < 0) // negative change index
    {
        tempIndex = size(node) + index;
    }
    while (count != index)// go to the node at the index
    {
        node = node->rlink;
        ++count;
    }

    if (node == NULL)
    {
        p_w->addLine("Error subscript out of range.");
        p_w->addLine("\n");
    }
    else
    {
        node->int_data = 0;
        node->double_data = 0;
        node->string_data = data;
    }
}
