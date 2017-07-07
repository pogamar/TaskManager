#include "Task.h"
#include <iostream>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <sstream>

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

Task *Task::_instance = nullptr;


int Task::dbCallback(void *userData, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

Task::Task() : _dbCon(nullptr)
{
    //ctor
    int ret = sqlite3_open("TaskManagement.db", &_dbCon);
    if( ret ) {
      printf("Can't open database: %s\n", sqlite3_errmsg(_dbCon));
   }
}

Task::~Task()
{
    //dtor
}

Task* Task::getTaskObj(){
    if(nullptr == Task::_instance){
        Task::_instance = new Task();
    }
    return Task::_instance;
}

int Task::getTable(std::vector<std::vector<std::string> > &tableData, int *row, int *col, char* message, char *userSql){
    char *sql = "Select * from TASK";
    char **result;
    char *errMsg;
    int nRow, nCol;
    int ret;
    int i,j, lvl;
    if(userSql != nullptr){
        sql = userSql;
    }
    ret = sqlite3_get_table(_dbCon, sql, &result, &nRow, &nCol, &errMsg);
    *row = nRow;
    *col = nCol;
    if( ret != SQLITE_OK ){
        sqlite3_free(errMsg);
        snprintf(message, 1000, "%s",errMsg);
        return -1;
    }
    if(tableData.size() == 0){
        for(i=0; i<nCol; i++){
            std::vector<std::string> v;
            tableData.push_back(v);
        }
    }
    //for(i=0;i<nCol; i++){
    //    printf("%s\n", result[i]);
    //}
    for(i=nCol, lvl = 0; i<(nRow+1)*nCol;lvl++){
        for (j=0;j<nCol && i<(nRow+1)*nCol;j++){
            if(result[i]){
                tableData[j].push_back((const char*)result[i]);
            }
            else{
                tableData[j].push_back("");
            }
            i++;
        }
    }
    sqlite3_free_table(result);
    if(nRow == 0){
        snprintf(message, 1000, "No matching data found");
        return -1;
    }
    /*
    for(i=0; i<nRow; i++){
        for(j=0; j<nCol; j++){
            //printf("%s", tableData[i][j])
            std::cout << tableData[j][i] << "\n";
        }
    }
    //*/
    return 0;
}
int Task::getDate(std::string &date){
    time_t     rawtime;
    struct tm* timeinfo;
    time( &rawtime );
    timeinfo = localtime( &rawtime );
    date+= patch::to_string(timeinfo->tm_mday);
    date+= "/";
    date+= patch::to_string(timeinfo->tm_mon);
    date+= "/";
    date+= patch::to_string(timeinfo->tm_year + 1900);
    //std::cout << date;
    return 0;
}

int Task::addItem(char *taskName, char *taskDescription, char *message){
    std::string sql = "Insert into TASK ";
    std::string columns = "(";
    std::string values = "values (";
    std::string taskDate;
    int ret;
    char *errMsg;
    if(!(taskName || taskDescription) ||(taskName[0]*taskDescription[0] == 0)){
        snprintf(message, 100, "NAME and DESCRIPTION NULL/EMPTY");
        return -1;
    }
    if(taskName){
        columns+= "NAME";
        values+="\"";
        values+= (const char*)taskName;
        values+="\"";
    }
    if(taskDescription){
        columns+=", DESCRIPTION";
        values+=", ";
        values+="\"";
        values+= (const char*)taskDescription;
        values+="\"";
    }

    getDate(taskDate);
    columns+=", DATE_CREATED";
    values+=", \"";
    values+= taskDate;

    columns+= ") ";
    values+= "\")";

    sql+=columns + values;
    //std::cout << sql <<"\n";

    ret = sqlite3_exec(_dbCon, sql.c_str(), dbCallback, 0, &errMsg);

    if( ret != SQLITE_OK ){
        sqlite3_free(errMsg);
        snprintf(message, 1000, "Insertion unsuccessful! Error: %s",errMsg);
        return -1;
    }
    return 0;
}

int Task::getRow(int id, char *name, std::vector<std::vector<std::string> > &tableData, char *message){
    char sql[100010];
    int ret = 0;
    int row, col;

    if(id == -1 && (name == nullptr || name[0] == 0)) {
        snprintf(message, 100, "ID and NAME NULL");
        return -1;
    }
    if(id > -1){
        snprintf(sql,1000, "select * from TASK where ID == %d",id);
    }
    else {
        snprintf(sql,1000, "select * from TASK where NAME == \"%s\"",name);
    }
   // std::cout <<sql;
    ret = getTable(tableData, &row, &col, message, sql);

    return ret;
}

int Task::updateItem(int id, char *taskName, char *taskDescription, char *message){
    std::string sql = "update TASK set ";
    std::string taskDate;
    int ret;
    char *errMsg;
    if(!id){
        snprintf(message, 100, "ID NULL");
        return -1;
    }
    if(!(taskName || taskDescription) || !(taskDate[0]+taskName[0])){
        snprintf(message, 100, "NAME, DESCRIPTION NULL/EMPTY");
        return -1;
    }
    if(taskName){
        sql+= "NAME = ";
        sql+="\"";
        sql+= (const char*)taskName;
        sql+="\"";
    }
    if(taskDescription){
        sql+=", DESCRIPTION = ";
        sql+="\"";
        sql+= (const char*)taskDescription;
        sql+="\"";
    }

    getDate(taskDate);
    sql+=", DATE_UPDATED = ";
    sql+="\"";
    sql+= taskDate;
    sql+="\"";

    sql+= " where ID = ";
    sql+= patch::to_string(id);
    //std::cout << sql <<"\n";

    ret = sqlite3_exec(_dbCon, sql.c_str(), dbCallback, 0, &errMsg);

    if( ret != SQLITE_OK ){
        snprintf(message, 1000, "Update unsuccessful! Error: %s",errMsg);
        sqlite3_free(errMsg);
        return -1;
    }
    return 0;
}


int Task::deleteItem(int id, char *name, char *message){
    char sql[100010];
    int ret = 0;
    char *errMsg;
    if(id == -1 && name == nullptr) {
        snprintf(message, 100, "ID and NAME NULL");
        return -1;
    }
    if(id){
        snprintf(sql,1000, "delete from TASK where ID == %d",id);
    }
    else {
        snprintf(sql,1000, "delete from TASK where NAME == %s",name);
    }


    ret = sqlite3_exec(_dbCon, sql, dbCallback, 0, &errMsg);

    if( ret != SQLITE_OK ){
        snprintf(message, 1000, "Delete unsuccessful! Error: %s",errMsg);
        sqlite3_free(errMsg);
        return -1;
    }
    return 0;
}

