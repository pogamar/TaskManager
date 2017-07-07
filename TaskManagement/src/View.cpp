#include "View.h"
#include <iostream>
#include "bprinter-master/include/bprinter/table_printer.h"
View* View::_instance = nullptr;

View::View()
{
    //ctor
}

View::~View()
{
    //dtor
}

View* View::getViewObject(){
    if(nullptr == View::_instance){
        View::_instance = new View();
    }
    return View::_instance;
}


void View::showGreetings(){
    std::cout << "******************* TASK MANAGER **********************" << "\n";
}

void View::showCommands(std::vector<std::string> message, int nMsg, int (*callbackFunc)(std::string &input, void* data), void* userData){
    int i;
    std::cout << "Chose any action from the following list" << std::endl;
    for(i=1; i<=nMsg; i++){
        std::cout << i <<". " << message[i-1] <<std::endl;
    }
    std::cout << "\nInsert number (1-5):" << std::endl;

    std::string str;
    int ret;
    while(1){
        std::getline(std::cin, str);
        ret = callbackFunc(str, userData);
        if(!ret)
            break;
        std::cout << "Please insert a number from the list" << std::endl;
    }
}

void View::getTaskNameDescription(std::string &task, std::string &description){
    std::cout << "Please provide the following information" << std::endl;

    std::cout << "Task Name" << std::endl;
    std::getline(std::cin, task);

    std::cout << "Task Description" << std::endl;
    std::getline(std::cin, description);
}

int View::showError(std::string message)
{
    std::cout << "ERROR: " << message <<std::endl;
    std::cout <<"\nDo you want to continue?(y/n): ";
    std::string res;
    std::getline(std::cin, res);
    std::cout <<std::endl;
    if(res[0]=='y' || res[0]=='Y'){
        return 0;
    }
    return -1;
}


void View::showMessage(std::string message)
{
    std::cout << "\n*** "<<message <<" ***\n" <<std::endl;
}

void View::getTaskName(std::string &taskName){
    std::cout << "Please insert task name" << std::endl;
    std::cout << "Task Name" << std::endl;
    std::getline(std::cin, taskName);
}

void View::showPauseView(){
    std::cout << "\nPress any key to continue\n";
    std::string str;
    std::getline(std::cin, str);
    std::cout <<std::endl;
}

void View::showTable(std::vector<std::vector<std::string> > &tableData, int row, int col){
    int i,j;

    bprinter::TablePrinter tp(&std::cout);
    tp.AddColumn("ID",20);
    tp.AddColumn("Task Name", 20);
    tp.AddColumn("Task Description", 20);
    tp.AddColumn("Date created", 20);
    tp.AddColumn("Date Updated", 20);

    tp.PrintHeader();

    for(i=0; i<row; i++){
        for(j=0; j<col; j++){
            tp << tableData[j][i];
        }
    }
    tp.PrintFooter();
}

