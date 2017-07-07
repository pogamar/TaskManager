#ifndef TASK_H
#define TASK_H

#include <sqlite3.h>
#include <vector>
#include <string>

class Task
{
    private:
        Task();

    public:
        virtual ~Task();
        static Task *getTaskObj();
        int getTable(std::vector<std::vector<std::string> > &tableData, int*row, int*col, char* message, char *userSql = nullptr);
        int addItem(char *taskName, char *taskDescription, char *message);
        int updateItem(int id, char *taskName, char *taskDescription, char *message);
        int getRow(int id, char *name, std::vector<std::vector<std::string> > &tableData, char *message);
        int deleteItem(int id, char *name, char *message);

    private:
        int getDate(std::string &date);
        static int dbCallback(void *NotUsed, int argc, char **argv, char **azColName);

    private:
        static Task *_instance;
        sqlite3 *_dbCon;
};

#endif // TASK_H
