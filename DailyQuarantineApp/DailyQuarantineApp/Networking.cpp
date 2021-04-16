#include "Networking.h"

bool Networking::networkConnection_QuickMode() const
{
    if (InternetCheckConnection(L"http://www.google.com", FLAG_ICC_FORCE_CONNECTION, 0))
    {
        return true;
    }
    return false;
}

Networking::INTERNET_STATUS Networking::isConnectedToInternet() const
{
    INTERNET_STATUS connectedStatus = INTERNET_STATUS::CONNECTION_ERROR;
    HRESULT hr = S_FALSE;

    try
    {
        hr = CoInitialize(NULL);
        if (SUCCEEDED(hr))
        {
            INetworkListManager* pNetworkListManager;
            hr = CoCreateInstance(CLSID_NetworkListManager, NULL, CLSCTX_ALL, __uuidof(INetworkListManager), (LPVOID*)&pNetworkListManager);
            if (SUCCEEDED(hr))
            {
                NLM_CONNECTIVITY nlmConnectivity = NLM_CONNECTIVITY::NLM_CONNECTIVITY_DISCONNECTED;
                VARIANT_BOOL isConnected = VARIANT_FALSE;
                hr = pNetworkListManager->get_IsConnectedToInternet(&isConnected);
                if (SUCCEEDED(hr))
                {
                    if (isConnected == VARIANT_TRUE)
                        connectedStatus = INTERNET_STATUS::CONNECTED;
                    else
                        connectedStatus = INTERNET_STATUS::DISCONNECTED;
                }

                if (isConnected == VARIANT_FALSE && SUCCEEDED(pNetworkListManager->GetConnectivity(&nlmConnectivity)))
                {
                    if (nlmConnectivity & (NLM_CONNECTIVITY_IPV4_LOCALNETWORK | NLM_CONNECTIVITY_IPV4_SUBNET | NLM_CONNECTIVITY_IPV6_LOCALNETWORK | NLM_CONNECTIVITY_IPV6_SUBNET))
                    {
                        connectedStatus = INTERNET_STATUS::CONNECTED_TO_LOCAL;
                    }
                }

                pNetworkListManager->Release();
            }
        }

        CoUninitialize();
    }
    catch (...)
    {
        connectedStatus = INTERNET_STATUS::CONNECTION_ERROR;
    }

    return connectedStatus;
}

bool Networking::networkConnection_AdvancedMode() const
{
    INTERNET_STATUS connectedStatus = INTERNET_STATUS::CONNECTION_ERROR;
    connectedStatus = isConnectedToInternet();
    switch (connectedStatus)
    {
    case INTERNET_STATUS::CONNECTED:
        return true;
        break;
    case INTERNET_STATUS::DISCONNECTED:
        return false;
        break;
    case INTERNET_STATUS::CONNECTED_TO_LOCAL:
        return true;
        break;
    case INTERNET_STATUS::CONNECTION_ERROR:
    default:
        return false;
        break;
    }
    return false;
}
