#include <sqlite3.h>
#include <iostream>
#include "Task.h"
#include "View.h"
#include "MainViewController.h"

#include <string>
#include <vector>

#include <cstdio>

int main(){
int x;
//std::string str;
//std::getline(std::cin, str);
//std::cout << str[0] <<"____" <<str[1] <<"*****"<<int(str[1]) <<std::endl;
    char err[10000];
    int a, b;
    std::vector<std::vector<std::string> > tableData;
    Task *tk = Task::getTaskObj();

    MainViewController *mvc = new MainViewController();
    mvc->showView();
    //tk->addItem("rabib", "noor", err);
    //tk->getRow(-1, "rabib", tableData, err);
    //tk->getTable(tableData,&a, &b, err);
   // std::cout << tableData[0][0] << " ";
   // std::cout << tableData[1][0]<< " ";
   // std::cout << tableData[2][0]<< " ";
   // std::cout << tableData[3][0]<< " ";
   // std::cout << tableData[4][0]<< " " <<std::endl;

    //View *v = View::getViewObject();
    //v->showTable(tableData,a,b);


    //std::string ss ="";
    //printf("\n\n***%s***",nullptr);
    return 0;
}
