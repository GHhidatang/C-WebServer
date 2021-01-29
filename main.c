#include <stdio.h>
#include <WinSock2.h> //���������̵�ͷ�ļ������뾲̬��
#pragma comment (lib, "ws2_32.lib")

void sendhtm1(SOCKET s, char * filename);

int merror(int redata, int  error, char * showinfo)
{
    if (redata == error)
    {
        perror(showinfo); // ������ַ�����ͬʱ�����ӡ������Ϣ
        getchar();
        return -1;
    }

    return 0;
}

int main()
{
    printf("��ӭʹ���ҵ�Wed������......\n ");
    WSADATA wsdata;
    int isok = WSAStartup(MAKEWORD(2, 2), &wsdata); // ȷ��socket�汾��Ϣ;

    merror(isok, WSAEINVAL, "����socketʧ��");

    /*
     * AF_INET: Э���壬 ����socket�ĵ�ַ����
     * SOCK_STREAM: �������ͣ� SOCK_STREAM������
     * IPPROTO_TCP: ָ���Ĵ���Э�飬 tcp
     * */
    SOCKET server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    merror(server, INVALID_SOCKET, "����socketʧ��");

    struct sockaddr_in seraddr;
    seraddr.sin_family = AF_INET; // �ʹ�����ʱ�����һ�� ipv4
    seraddr.sin_port = htons(80);
    seraddr.sin_addr.s_addr = INADDR_ANY; // ���������ַ

    isok = bind(server, &seraddr, sizeof(seraddr));
    merror(isok, SOCKET_ERROR, "��ʧ��...\n");

    isok = listen(server, 5);
    merror(isok, SOCKET_ERROR, "����ʧ��...\n");

    struct sockaddr_in claddr;
    int cllen = sizeof(claddr);
    while(1)
    {
        SOCKET client = accept(server, &claddr, &cllen); // ˭���ӽ�����
        merror(client, INVALID_SOCKET, "����ʧ��...\n");

        char revdata[1024] = "";
        recv(client, revdata, 1024, 0);
        printf("%s �����յ�%d�ֽ�����\n", revdata, strlen(revdata));

//        char sendata[1024] = "<h1 style = \"color:red;\">�������</h1>";
//        send(client, sendata, strlen(sendata), 0);
        char * filename = "E:\\website\\index.html";
        sendhtm1(client, filename);

        closesocket(client);
    }

    closesocket(server);
    WSACleanup();

    return 0;
}

void sendhtm1(SOCKET s, char * filename)
{
    FILE * fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("���ļ�ʧ��\n");
        return;
    }

    char temp[1024] = "";
    do
    {
        fgets(temp, 1024, fp);
        send(s, temp, strlen(temp), 0);
    }while (!feof(fp));
}