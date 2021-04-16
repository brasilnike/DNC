#pragma once

#include <iostream>
#include <string>
#include <Windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include <wininet.h>
#include <ObjBase.h>
#include <Netlistmgr.h>
#pragma comment(lib,"Wininet.lib")

class Networking
{
public:
    enum class INTERNET_STATUS
    {
        CONNECTED,
        DISCONNECTED,
        CONNECTED_TO_LOCAL,
        CONNECTION_ERROR
    };

    INTERNET_STATUS isConnectedToInternet() const;

    bool networkConnection_QuickMode() const;
    bool networkConnection_AdvancedMode() const;
};

