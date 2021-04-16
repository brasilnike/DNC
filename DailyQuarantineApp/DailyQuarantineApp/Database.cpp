#include "Database.h"
#include "Networking.h"

#define SQL_RETURN_CODE_LEN 1000

bool CheckNetworkConnection()
{
	Networking networking;
	return (networking.networkConnection_QuickMode() || networking.networkConnection_AdvancedMode());
}

Database::Database()
{
	m_isConnected = false;
	m_sqlConnHandle = NULL;
	m_sqlStmtHandle = NULL;
	m_sqlEnvHandle = NULL;

	if (CheckNetworkConnection())
	{
		connectToDatabase();
	}
	else
	{

	}
}

void Database::connectToDatabase()
{
	SQLWCHAR retconstring[SQL_RETURN_CODE_LEN];

	//allocations
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_sqlEnvHandle))
	{
		disconnectDatabase();
		return;
	}
	if (SQL_SUCCESS != SQLSetEnvAttr(m_sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
	{
		disconnectDatabase();
		return;
	}
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, m_sqlEnvHandle, &m_sqlConnHandle))
	{
		disconnectDatabase();
		return;
	}

	
	//connect to SQL Server  
	switch (SQLDriverConnect(m_sqlConnHandle,
		NULL,
		(SQLWCHAR*)L"DRIVER={SQL Server};SERVER=localhost;DATABASE=QuarantineDatabase;UID=Elev;PWD=Elev;Trusted=true;",
		SQL_NTS,
		retconstring,
		1024,
		NULL,
		SQL_DRIVER_NOPROMPT)) {
	case SQL_SUCCESS:
		m_isConnected = true;
		break;
	case SQL_SUCCESS_WITH_INFO:
		m_isConnected = true;
		break;
	case SQL_INVALID_HANDLE:
		disconnectDatabase();
		break;
	case SQL_ERROR:
		disconnectDatabase();
		break;
	default:
		break;
	}

	//if there is a problem connecting then exit application
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, m_sqlConnHandle, &m_sqlStmtHandle))
	{
		disconnectDatabase();
		return;
	}
}

void Database::disconnectDatabase()
{
	m_isConnected = false;
	SQLFreeHandle(SQL_HANDLE_STMT, m_sqlStmtHandle);
	SQLDisconnect(m_sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, m_sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, m_sqlEnvHandle);
}

Database::~Database()
{
	disconnectDatabase();
}

SQLHANDLE Database::getConnHandle() const
{
	return m_sqlConnHandle;
}

SQLHANDLE Database::getStmtHandle() const
{
	return m_sqlStmtHandle;
}

SQLHANDLE Database::getEnvHandle() const
{
	return m_sqlEnvHandle;
}

bool Database::getIsConnected() const
{
	return m_isConnected;
}

void Database::setStmtHandle(const SQLHANDLE& handle)
{
	m_sqlStmtHandle = handle;
}
