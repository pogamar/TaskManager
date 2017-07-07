#include <sqlite3.h>
#include <iostream>
#include "Task.h"
#include "View.h"
#include "MainViewController.h"

#include <string>
#include <vector>

#include <cstdio>

int main(){
    MainViewController *mvc = new MainViewController();
    mvc->showView();
    return 0;
}
