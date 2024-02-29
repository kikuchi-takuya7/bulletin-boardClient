#include <iostream>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;

#pragma comment( lib, "ws2_32.lib" )

// �|�[�g�ԍ�
const unsigned short SERVERPORT = 8888;

// ����M���郁�b�Z�[�W�̍ő�l
const unsigned int MESSAGELENGTH = 1024;

const string IP = "192.168.42.32";

int main()
{

    int ret;
    // WinSock�̏�����	WinSock2.2
    WSADATA wsaData;
    ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
    // if (ret == SOCKET_ERROR)
    if (ret == SOCKET_ERROR)
    {
        std::cout << "InitoError" << WSAGetLastError() << std::endl;
        return 1;
    }

    // �\�P�b�g�f�B�X�N���v�^
    SOCKET sock;

    // UDP�\�P�b�g�쐬
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    // �ڑ���T�[�o��IP�A�h���X����͂�����
    string serverIpAddress;
    cout << "Input Server IPv4 address :";
    cin >> serverIpAddress;
    
    //�T�[�o�[����AllOK������܂Ńv���C���[�̎�t���s���B
    int playerNum = 0;
    while (true)
    {

        // �ڑ���T�[�o�̃\�P�b�g�A�h���X���i�[
        SOCKADDR_IN toAddr;
        const int tolen = sizeof(toAddr);
        memset(&toAddr, 0, sizeof(toAddr));
        toAddr.sin_family = AF_INET;
        toAddr.sin_port = htons(SERVERPORT);
        inet_pton(AF_INET, serverIpAddress.c_str(), &toAddr.sin_addr.s_addr);

        char message[MESSAGELENGTH];	// �T�[�o���ƃT�C�Y�����킹�邱��
        SOCKADDR_IN fromAddr;
        int fromlen = sizeof(fromAddr);
        cout << "���[�U�[���̓���:";
        cin >> message;
        ret = sendto(sock, message, sizeof(message), 0, (SOCKADDR*)&toAddr, tolen);
        if (ret == SOCKET_ERROR)
        {
            std::cout << "SendtoError" << WSAGetLastError() << std::endl;
            return 1;
        }
        ret = recvfrom(sock, message, sizeof(message), 0, (SOCKADDR*)&fromAddr, &fromlen);

        if (ret == SOCKET_ERROR)
        {
            std::cout << "ResvtoError" << WSAGetLastError() << std::endl;
            return 1;
        }
        else
        {
            std::cout << message << std::endl;
        }

        if (strcmp(message,"AllOK") == 0) {
            break;
        }

        playerNum++;

    }

    //���[���傫�ρ[�̎w�������炤
    //{
    //    char message[MESSAGELENGTH];	// �T�[�o���ƃT�C�Y�����킹�邱��
    //    SOCKADDR_IN fromAddr;
    //    int fromlen = sizeof(fromAddr);
    //    ret = recvfrom(sock, message, sizeof(message), 0, (SOCKADDR*)&fromAddr, &fromlen);

    //    if (ret == SOCKET_ERROR)
    //    {

    //    }
    //    else
    //    {
    //        std::cout << message << std::endl;
    //    }
    //}

    //�o��������
    for(int i=0;i<playerNum;i++)
    {
        // �ڑ���T�[�o�̃\�P�b�g�A�h���X���i�[
        SOCKADDR_IN toAddr;
        const int tolen = sizeof(toAddr);
        memset(&toAddr, 0, sizeof(toAddr));
        toAddr.sin_family = AF_INET;
        toAddr.sin_port = htons(SERVERPORT);
        inet_pton(AF_INET, serverIpAddress.c_str(), &toAddr.sin_addr.s_addr);

        char message[MESSAGELENGTH];	// �T�[�o���ƃT�C�Y�����킹�邱��
        SOCKADDR_IN fromAddr;
        int fromlen = sizeof(fromAddr);
        cout << "�v���C���[���ɏo����̓���:";
        cin >> message;
        ret = sendto(sock, message, sizeof(message), 0, (SOCKADDR*)&toAddr, tolen);
        if (ret == SOCKET_ERROR)
        {
            std::cout << "SendtoError" << WSAGetLastError() << std::endl;
            return 1;
        }

    }

    //���s�𕷂�
    for (int i = 0; i < playerNum; i++) {


        char message[MESSAGELENGTH];	// �T�[�o���ƃT�C�Y�����킹�邱��
        SOCKADDR_IN fromAddr;
        int fromlen = sizeof(fromAddr);
        ret = recvfrom(sock, message, sizeof(message), 0, (SOCKADDR*)&fromAddr, &fromlen);

        if (ret == SOCKET_ERROR)
        {
            std::cout << "initoError" << WSAGetLastError() << std::endl;
            return 1;
        }
        else
        {
            std::cout << message << std::endl;
        }

    }

    ret = closesocket(sock);
    if (ret == SOCKET_ERROR)
    {
        std::cout << "ClosetoError" << WSAGetLastError() << std::endl;
        return 1;
    }

    // WinSock�̏I������
    ret = WSACleanup();
    //if (ret == SOCKET_ERROR)
    if (ret != 0)
    {
        std::cout << "CleantoError" << WSAGetLastError() << std::endl;
        return 1;
    }

    return 0;
}