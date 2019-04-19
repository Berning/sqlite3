#include<stdio.h>
#include<sqlite3.h>
#include<stdlib.h>
static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   fprintf(stderr, "%s: ", (const char*)data);
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main()
{
	//open database
	sqlite3 *db;
	int rs=sqlite3_open("test.sqlite",&db);
	if(rs)
	{
		fprintf(stderr,"can't open database:%s\n",sqlite3_errmsg(db));
		exit(0);
	}
	else
	{
		fprintf(stdout,"opened database successfully\n");
	}

	char * sql = "CREATE TABLE COMPANY("  \
         "ID INT PRIMARY KEY     NOT NULL," \
         "NAME           TEXT    NOT NULL," \
         "AGE            INT     NOT NULL," \
         "ADDRESS        CHAR(50)," \
         "SALARY         REAL );";
	
	char *zErrMsg=NULL;

	   /* Execute SQL statement */
	 int  rse = sqlite3_exec(db, sql, NULL, NULL,&zErrMsg);
  	 if( rse != SQLITE_OK ){
   	fprintf(stderr, "SQL error: %s\n", zErrMsg);
     	 sqlite3_free(zErrMsg);
   	}else{
     	 fprintf(stdout, "Table created successfully\n");
   	}

	   /* Create SQL statement */
	   sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
         "VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
         "VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
         "VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
         "VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";

       /* Execute SQL statement */
       int rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
        if( rc != SQLITE_OK ){
             fprintf(stderr, "SQL error: %s\n", zErrMsg);
             sqlite3_free(zErrMsg);
        }else{
              fprintf(stdout, "Records created successfully\n");
        }


   /* Create SQL statement */
   sql = "SELECT * from COMPANY";
   const char* data = "Callback function called";

   /* Execute SQL statement */
   int  rcs = sqlite3_exec(db, sql,callback,(void*)data, &zErrMsg);
   if( rcs != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Operation done successfully\n");
   }

	sqlite3_close(db);
	
	//create table
	
	

	return 0;
	
}
