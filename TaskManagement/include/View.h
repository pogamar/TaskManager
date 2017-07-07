#ifndef VIEW_H
#define VIEW_H
#include <vector>
#include <string>

class View
{
    private:
        View();
    public:
        virtual ~View();
        static View *getViewObject();
        void showGreetings();
        void showCommands(std::vector<std::string> message, int nMsg, int (*callbackFunc)(std::string &input, void* data), void* userData);
        int showError(std::string message);
        void getTaskNameDescription(std::string &task, std::string &description);
        void showTable(std::vector<std::vector<std::string> > &tableData, int row, int col);
        void showMessage(std::string message);
        void getTaskName(std::string &taskName);
        void showPauseView();
    private:
        static View *_instance;
};

#endif // VIEW_H
