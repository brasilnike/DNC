#pragma once

#include <iostream>
#include <string>
#include <Windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>

class Database
{
public:
	Database();

	void connectToDatabase();
	void disconnectDatabase();

	~Database();

public:
	SQLHANDLE getConnHandle() const;
	SQLHANDLE getStmtHandle() const;
	SQLHANDLE getEnvHandle() const;
	bool getIsConnected() const;

	void setStmtHandle(const SQLHANDLE& handle);

private:
	SQLHANDLE m_sqlConnHandle;
	SQLHANDLE m_sqlStmtHandle;
	SQLHANDLE m_sqlEnvHandle;
	bool m_isConnected;
};
