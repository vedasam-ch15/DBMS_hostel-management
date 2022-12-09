//Command to Compile: g++ demo.cpp -o demo.exe -lmysql

#include <iostream>
#include <windows.h>
#include <mysql.h>

using namespace std;

MYSQL *conn;

int display1()
{
    int query_status = mysql_query(conn, "INSERT INTO STAFF (`wid`,`Name`,`salary`,`Contact no`,`designation`) VALUES ('C20B012','Preeti',20,'8765452198','Cleaning');");
    if( query_status == 1)
    {
        printf("Displaying Result\n");
    }
    MYSQL_RES *results = mysql_store_result(conn);
    MYSQL_ROW record;
    MYSQL_FIELD *fields;
    int num_fields = mysql_num_fields(results);
    fields = mysql_fetch_fields(results);
    for(int i = 0; i < num_fields; i++)
    {
        cout<<fields[i].name<<" ";
    }
    cout<<endl;
    while ((record = mysql_fetch_row(results)))
    {
        for(int i = 0; i < num_fields; i++)
        {
            char *val = record[i];
            cout<<record[i]<<" ";
        }
        cout<<endl;
    }
    mysql_free_result(results);
    return 0;
}
// gcc main.cpp -o main.exe -lmysql
int display()
{
    
    MYSQL_RES *results = mysql_store_result(conn);
    MYSQL_ROW record;
    MYSQL_FIELD *fields;
    int num_fields = mysql_num_fields(results);
    fields = mysql_fetch_fields(results);
    for(int i = 0; i < num_fields; i++)
    {
        cout<<fields[i].name<<" ";
    }
    cout<<endl;
    while ((record = mysql_fetch_row(results)))
    {
        for(int i = 0; i < num_fields; i++)
        {
            char *val = record[i];
            cout<<record[i]<<" ";
        }
        cout<<endl;
    }
    mysql_free_result(results);
    return 0;
}


int main()
{
    conn = mysql_init(NULL);
    if (conn == NULL) {
        cout<<"Error: "<<mysql_error(conn)<<endl;
        exit(1);
    }

    // mysql_real_connect(Connection Instance, Username, Password, Database, Port, Unix Socket, Client Flag)
    if (mysql_real_connect(conn, "localhost", "Veda", "Veda@1523", "Project", 3306, NULL, 0)) {
        cout<<"Connected Successfully!"<<endl;
        char query[512];
        snprintf(query, 256, "CREATE TABLE STUDENT (`Rollno` varchar(255) NOT NULL PRIMARY KEY, `Name` varchar(255), `Contact no` varchar(255), `Hno` varchar(255),`Rno` int,`InTime` datetime, `OutTime` datetime,`DP` varchar(255));"); 
        int createTableStatus = mysql_query(conn, query);
        if (createTableStatus != 0) {
            cout<<"Error while creating table: "<<mysql_error(conn)<<endl;
        }

        char query2[512];
        snprintf(query2, 512, "INSERT INTO STUDENT (`Rollno` , `Name` , `Contact no` , `Hno` , `Rno`,`InTime`,`OutTime`,`DP`) VALUES ('B20CS078', 'Veda','9876543210', 'A',274,'2022-11-12 01:20:23','2022-11-12 03:20:23',NULL),('B20CS046','Amshu','9876543211', 'B',263,'2022-11-09 00:20:23','2022-11-12 03:20:23',NULL ),('B20CS027','Atul','9876543212','C',100,'2022-11-20 11:25:23','2022-11-13 00:20:23',NULL);");
        int insertvalues2 = mysql_query(conn, query2);
        if (insertvalues2 != 0){
            cout <<"error while inserting values in student: " <<mysql_error(conn) <<"\n";
        }

        char query3[512];
        snprintf(query3,512,"CREATE TABLE STAFF (`Wid` varchar(255) NOT NULL PRIMARY KEY,`Name` varchar(255),`salary` int,`Contact no` varchar(255),`designation` varchar(255));");
        int createTableStatus2 = mysql_query(conn, query3);
        if (createTableStatus2 != 0) {
            cout<<"Error while creating table: "<<mysql_error(conn)<<endl;
        }

        char query4[512];
        snprintf(query4, 512,"INSERT INTO STAFF (`wid`,`Name`,`salary`,`Contact no`,`designation`) VALUES ('C20A012','Priya',40,'8765432198','Warden'),('C20B005','Sujitha',20,'8765432197','Security'),('C20C008','Kartik',6,'8765432197','Cleaning');");
        int insertvalues3 = mysql_query(conn, query4);
        if (insertvalues3 != 0){
            cout <<"error while inserting values in staff: " <<mysql_error(conn) <<"\n";
        }
        
        char query5[512];
        snprintf(query5, 512, "CREATE TABLE COMPLAINT (`C.id` varchar(255) NOT NULL PRIMARY KEY,`id` varchar(255),`date` date,`complaint_status` varchar(255),`complaint` varchar(255));");
        int createTableStatus3 = mysql_query(conn, query5);
        if (createTableStatus3 != 0) {
            cout<<"Error while creating table: "<<mysql_error(conn)<<endl;
        }

        char query6[512];
        snprintf(query6,512,"INSERT INTO COMPLAINT (`C.id`,`id`,`date`,`complaint_status`,`complaint`) VALUES ('D20CO001','C20C008','2022-11-01','NO','Late to work without giving reason'),('D20CO002',NULL,'2022-10-04','NO','AC not working in B hostel');");
        int insertvalues4 = mysql_query(conn, query6);
        if (insertvalues4 != 0){
            cout <<"error while inserting values in complaint: " <<mysql_error(conn) <<"\n";
        }
        display1();

        
    } else {
        cout<<"Error while connecting!"<<endl;
    }

    return 0;
}
