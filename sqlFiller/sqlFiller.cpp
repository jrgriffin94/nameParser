#include <iostream>
#include <cstdio>
#include <string>

#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>

using namespace std;

const int MAX_CHAR = 1024;

int main()
{
	SQLSMALLINT     RecNumber;
	SQLCHAR *       SQLState;
	SQLINTEGER *    NativeErrorPtr;
	SQLCHAR *       MessageText;
	SQLSMALLINT     BufferLength;
	SQLSMALLINT *   TextLengthPtr;

	SQLWCHAR   SQLStmt[MAX_CHAR];
	char      strSQL[MAX_CHAR];
	char      chrTemp;

	SQLVARCHAR rtnFirstName[50];
	SQLVARCHAR rtnLastName[50];
	SQLVARCHAR rtnAddress[30];
	SQLVARCHAR rtnCity[30];
	SQLVARCHAR rtnState[3];
	SQLDOUBLE  rtnSalary;
	SQLVARCHAR rtnGender[2];
	SQLINTEGER rtnAge;

	// Get a handle to the database

	SQLHENV EnvironmentHandle;
	RETCODE retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &EnvironmentHandle);

	// Set the SQL environment flags

	retcode = SQLSetEnvAttr(EnvironmentHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);

	// create handle to the SQL database

	SQLHDBC ConnHandle;
	retcode = SQLAllocHandle(SQL_HANDLE_DBC, EnvironmentHandle, &ConnHandle);

	// Open the database using a System DSN

	retcode = SQLDriverConnect(ConnHandle,
		NULL,
		(SQLWCHAR*)"DSN=PRG411;UID=myUser;PWD=myPass;",
		SQL_NTS,
		NULL,
		SQL_NTS,
		NULL,
		SQL_DRIVER_NOPROMPT);
	if (!retcode)
	{
		cout << "SQLConnect() Failed";
	}
	else
	{
		// create a SQL Statement variable

		SQLHSTMT StatementHandle;
		retcode = SQLAllocHandle(SQL_HANDLE_STMT, ConnHandle, &StatementHandle);

		// Hardcode records into the table

		/*do
		{
			cout << "Add records to the table? ";
			cin >> chrTemp;
		} while (cin.fail());

		if (chrTemp == 'y' || chrTemp == 'Y')
		{
			strcpy((char *)SQLStmt, "INSERT INTO employee([FirstName], [LastName], [Address], [City], [State], [Salary], [Gender],[Age]) VALUES ('Mike','Slentz','123 Torrey Dr.','North Clairmont','CA', 48000.00 ,'M',34)");
			retcode = SQLExecDirect(StatementHandle, SQLStmt, SQL_NTS);

			strcpy((char *)SQLStmt, "INSERT INTO employee([FirstName], [LastName], [Address], [City], [State], [Salary], [Gender],[Age]) VALUES ('Sue','Vander Hayden','46 East West St.','San Diego','CA', 36000.00 ,'F',28)");
			retcode = SQLExecDirect(StatementHandle, SQLStmt, SQL_NTS);

			strcpy((char *)SQLStmt, "INSERT INTO employee([FirstName], [LastName], [Address], [City], [State], [Salary], [Gender],[Age]) VALUES ('Sharon','Stonewall','756 West Olive Garden Way','Plymouth','MA', 56000.00 ,'F',58)");
			retcode = SQLExecDirect(StatementHandle, SQLStmt, SQL_NTS);

			strcpy((char *)SQLStmt, "INSERT INTO employee([FirstName], [LastName], [Address], [City], [State], [Salary], [Gender],[Age]) VALUES ('James','Bartholemew','777 Praying Way','Falls Church','VA', 51000.00 ,'M',45)");
			retcode = SQLExecDirect(StatementHandle, SQLStmt, SQL_NTS);

			strcpy((char *)SQLStmt, "INSERT INTO employee([FirstName], [LastName], [Address], [City], [State], [Salary], [Gender],[Age]) VALUES ('Joe','Smith','111 North 43rd Ave','Peoria','AZ', 44000.00 ,'M', 40)");
			retcode = SQLExecDirect(StatementHandle, SQLStmt, SQL_NTS);

			strcpy((char *)SQLStmt, "INSERT INTO employee([FirstName], [LastName], [Address], [City], [State], [Salary], [Gender],[Age]) VALUES ('Michael','Smith','20344 North Swan Park','Phoenix','AZ', 24000.00 ,'M', 40)");
			retcode = SQLExecDirect(StatementHandle, SQLStmt, SQL_NTS);

			strcpy((char *)SQLStmt, "INSERT INTO employee([FirstName], [LastName], [Address], [City], [State], [Salary], [Gender],[Age]) VALUES ('Jennifer','Jones','123 West North Ave','Flagstaff','AZ', 40000.00 ,'F', 40)");
			retcode = SQLExecDirect(StatementHandle, SQLStmt, SQL_NTS);

			strcpy((char *)SQLStmt, "INSERT INTO employee([FirstName], [LastName], [Address], [City], [State], [Salary], [Gender],[Age]) VALUES ('Cora','York','33rd Park Way Drive','Mayville','MI', 30000.00 ,'F', 61)");
			retcode = SQLExecDirect(StatementHandle, SQLStmt, SQL_NTS);

			strcpy((char *)SQLStmt, "INSERT INTO employee([FirstName], [LastName], [Address], [City], [State], [Salary], [Gender],[Age]) VALUES ('Tom','Jefferson','234 Friendship Way','Battle Creek','MI', 41000.00 ,'M', 31)");
			retcode = SQLExecDirect(StatementHandle, SQLStmt, SQL_NTS);
		}*/


		SQLFreeStmt(StatementHandle, SQL_CLOSE);
		SQLFreeHandle(SQL_HANDLE_STMT, StatementHandle);

		SQLDisconnect(ConnHandle);

		SQLFreeHandle(SQL_HANDLE_DBC, ConnHandle);
		SQLFreeHandle(SQL_HANDLE_ENV, EnvironmentHandle);
	}

	return 0;
}