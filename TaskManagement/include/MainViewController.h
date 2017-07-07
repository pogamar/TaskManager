#ifndef MAINVIEWCONTROLLER_H
#define MAINVIEWCONTROLLER_H
#define _GLIBCXX_USE_C99 1
#include <string>
typedef enum {
    ADD,
    UPDATE,
    DELETE,
    SHOW
} actions;

class MainViewController
{
    public:
        MainViewController();
        virtual ~MainViewController();

        int showView();

    private:
        static int _actionCB(std::string &input, void *data);
        void addTaskVC();
        void editTaskVC();
        void deleteTaskVC();
        void tableVC();
        int getTaskIdVC();
    private:
        static bool _isFirstTime;
        bool _exit;


};

#endif // MAINVIEWCONTROLLER_H
