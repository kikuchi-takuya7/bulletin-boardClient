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
    if (ret != 0)
    {
        /*
            �G���[����
        */
    }

    // �\�P�b�g�f�B�X�N���v�^
    SOCKET sock;

    // UDP�\�P�b�g�쐬
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    // �ڑ���T�[�o��IP�A�h���X����͂�����
    string serverIpAddress = IP;
    //cout << "Input Server IPv4 address :";
    //cin >> serverIpAddress;
    
    //�T�[�o�[����AllOK������܂Ńv���C���[�̎�t���s���B
    int playerNum = 0;
    while (true)
    {

        playerNum++;

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
            /*
                �G���[����
            */
        }
        ret = recvfrom(sock, message, sizeof(message), 0, (SOCKADDR*)&fromAddr, &fromlen);

        if (ret == SOCKET_ERROR)
        {

        }
        else
        {
            std::cout << message << std::endl;
        }

        char test[MESSAGELENGTH] = "AllOK";
        if (message == test) {
            break;
        }

    }

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
            /*
                �G���[����
            */
        }

    }
    for (int i = 0; i < playerNum; i++) {


        char message[MESSAGELENGTH];	// �T�[�o���ƃT�C�Y�����킹�邱��
        SOCKADDR_IN fromAddr;
        int fromlen = sizeof(fromAddr);
        ret = recvfrom(sock, message, sizeof(message), 0, (SOCKADDR*)&fromAddr, &fromlen);

        if (ret == SOCKET_ERROR)
        {

        }
        else
        {
            std::cout << message << std::endl;
        }

        if (message == "AllOK") {
            break;
        }
    }

    ret = closesocket(sock);
    if (ret == SOCKET_ERROR)
    {
        /*
            �G���[����
        */
    }

    // WinSock�̏I������
    ret = WSACleanup();
    //if (ret == SOCKET_ERROR)
    if (ret != 0)
    {
        /*
            �G���[����
        */
    }

    return 0;
}