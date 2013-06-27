#include <windows.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <mysql.h>   
#include <iostream>  
#pragma comment(lib,"libmysql.lib")//����MysQL��Ҫ�Ŀ�  
using namespace std;  
int main()  
{  
    const char user[] = "root";         //username  
    const char pswd[] = "0153211503";    //password  
    const char host[] = "192.168.1.101";    //or"127.0.0.1"  
    const char table[] ="testdb";       //database  
    unsigned int port = 3306;           //server port          
    MYSQL myCont;  
    MYSQL_RES *result;  
    MYSQL_ROW sql_row;  
    MYSQL_FIELD *fd;  
    char column[32][32];  
    int res;  
    mysql_init(&myCont);  
    if(mysql_real_connect(&myCont,host,user,pswd,table,port,NULL,0))  
    {  
        cout<<"connect succeed!"<<endl;  
        mysql_query(&myCont, "SET NAMES GBK"); //���ñ����ʽ  
        res=mysql_query(&myCont,"select * from testconnect");//��ѯ  
        if(!res)  
        {  
            result=mysql_store_result(&myCont);//�����ѯ�������ݵ�result  
            if(result)  
            {  
                int i,j;  
                cout<<"number of result: "<<(unsigned long)mysql_num_rows(result)<<endl;  
                for(i=0;fd=mysql_fetch_field(result);i++)//��ȡ����  
                {  
                    strcpy(column[i],fd->name);  
                }  
                j=mysql_num_fields(result);  
                for(i=0;i<j;i++)  
                {  
                    printf("%s\t",column[i]);  
                }  
                printf("\n");  
                while(sql_row=mysql_fetch_row(result))//��ȡ���������  
                {  
                    for(i=0;i<j;i++)  
                    {  
                        printf("%s\t",sql_row[i]);  
                    }  
                    printf("\n");  
                }  
            }  
        }  
        else  
        {  
            cout<<"query sql failed!"<<endl;  
        }  
    }  
    else  
    {  
        cout<<"connect failed!"<<endl;  
    }  
    if(result!=NULL) mysql_free_result(result);//�ͷŽ����Դ  
    mysql_close(&myCont);//�Ͽ�����  
    return 0;  
}