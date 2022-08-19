/*
 * cl.exe wslnet.cpp /std:c++latest /O2 /EHsc /FD /analyze /Fe: wslnet.exe
 */

#include <windows.h>
#include <computenetwork.h>

#pragma comment(lib, "computenetwork")

int main(void)
{
    HRESULT hRes;
    HCN_NETWORK hcnNetwork;
    PWSTR errRecord;
    const GUID netId = {
        0xB95D0C5E,
        0x57D4,
        0x412B,
        {0xB5, 0x71, 0x18, 0xA8, 0x1A, 0x16, 0xE0, 0x05}};

    // Flags = EnableDnsProxy + IsolateVSwitch
    // Type = Static
    PCWSTR netSettings = LR"(
    {
        "Name" : "WSL",
        "Type" : "ICS",
        "IsolateSwitch" : true,
        "Flags" : 9,
        "Subnets": [
            {
                "AddressPrefix":"192.168.50.0/24"
            }
        ]
    })";

    hRes = HcnCreateNetwork(netId, netSettings, &hcnNetwork, &errRecord);
    hRes = HcnCloseNetwork(hcnNetwork);

    return 0;
}