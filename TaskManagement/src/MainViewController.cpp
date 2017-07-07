#include "MainViewController.h"

#include <vector>
#include <cstdlib>
#include <iostream>
#include <cstdio>

#include "View.h"
#include "Task.h"

bool MainViewController::_isFirstTime = 1;

MainViewController::MainViewController() : _exit(false)
{
    //ctor
}

MainViewController::~MainViewController()
{
    //dtor
}
int MainViewController::showView(){
    View *view = View::getViewObject();
    if(_isFirstTime){
        view->showGreetings();
        _isFirstTime = false;
    }
    std::vector<std::string> options;
    options.push_back("Add Task");
    options.push_back("Edit Task");
    options.push_back("Delete Task");
    options.push_back("List all Tasks");
    options.push_back("Exit Program");

    while(1){
        view->showCommands(options, 5, _actionCB, static_cast <void*> (this));
        if(_exit)
            break;
    }
    return 0;
}

int MainViewController::_actionCB(std::string &input, void* data){
    if(!(input[0] >= '0' && input[0] <= '9' && input[1] == 0))
        return -1;
    MainViewController *mainVC = static_cast<MainViewController*>(data);

    int mode = input[0]-'0';
    switch (mode){
    case 1:
        mainVC->addTaskVC();
        break;
    case 2:
        mainVC->editTaskVC();
        break;
    case 3:
        mainVC->deleteTaskVC();
        break;
    case 4:
        mainVC->tableVC();
        break;
    case 5:
        mainVC->_exit = true;
        break;
    default:
        return -1;
    }
    return 0;
}

void MainViewController::addTaskVC(){
    View *view = View::getViewObject();
    std::string taskname;
    std::string taskDesc;
    char errMsg[10000];
    int ret = 1;

    view->showMessage("Add new task");
    Task *tsk = Task::getTaskObj();
    while(ret) {
        view->getTaskNameDescription(taskname, taskDesc);
        ret = tsk->addItem((char*)taskname.c_str(), (char*)taskDesc.c_str(), errMsg);
        if(ret){
            if(view->showError((const char *)errMsg)){
                return;
            }
        }
        else break;
    }
    view->showMessage("Successfully added");
}

int MainViewController::getTaskIdVC(){
    View *view = View::getViewObject();
    std::string taskname;
    std::vector<std::vector<std::string> > tableData;
    char errMsg[10000];
    int ret = 1;
    int tableId = 0;


   // view->getTaskName(taskname, "");
    Task *tsk = Task::getTaskObj();

    while(ret) {
        view->getTaskName(taskname);
        ret = tsk->getRow(-1, (char*)taskname.c_str(), tableData, errMsg);
        if(ret){
            if(view->showError((const char *)errMsg) == -1){
                return -1;
            }
        }
        else break;
    }
    //std::cout << tableData[0][0];
    view->showTable(tableData,1,5);
    return atoi(tableData[0][0].c_str());
}

void MainViewController::editTaskVC(){
    View *view = View::getViewObject();
    int taskId;
    int ret = 1;
    char errMsg[10000];
    std::string taskname;
    std::string taskDesc;

    view->showMessage("Edit Task");
    taskId = getTaskIdVC();
    if(taskId == -1)
        return;
    Task *tsk = Task::getTaskObj();
    while(ret) {
        view->getTaskNameDescription(taskname, taskDesc);
        ret = tsk->updateItem(taskId, (char*)taskname.c_str(), (char*)taskDesc.c_str(), errMsg);
        if(ret){
            if(view->showError((const char *)errMsg)  == -1){
                return;
            }
        }
        else break;
    }
    view->showMessage("Update Successful");
}


void MainViewController::deleteTaskVC(){
    View *view = View::getViewObject();
    int taskId;
    int ret = 1;
    char errMsg[10000];

    //taskId = getTaskIdVC();
    view->showMessage("Delete Task");
    Task *tsk = Task::getTaskObj();
     while(ret) {
        taskId = getTaskIdVC();
        if(taskId == -1)
            return;
        ret = tsk->deleteItem(taskId, nullptr, errMsg);
        if(ret){
            if( view->showError((const char *)errMsg) == -1){
                return;
            }

        }
        else break;
    }
    view->showMessage("Successfully Deleted");
}

void MainViewController::tableVC(){
     std::vector<std::vector<std::string> > tableData;
     int row;
     int col;
     char errMsg[10000];

     View *view = View::getViewObject();
     Task *tsk = Task::getTaskObj();

     view->showMessage("Task List");
     tsk->getTable(tableData,&row, &col, errMsg);
     view->showTable(tableData, row, col);

     view->showPauseView();
}
