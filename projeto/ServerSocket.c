#include "TCPIPConfig.h"
#include "TCPIP Stack/TCPIP.h"
#include "ServerSocket.h"

//maximo de conexeoes simultaneas
#define SERVER_CONNS 4

//maquina de estado servidor socket TCP
void ServerSocketTCP(void)
{
    WORD lenA;
    BYTE i;
    static DWORD timeout[SERVER_CONNS];
    static TCP_SOCKET	MySocket[SERVER_CONNS];
    unsigned char buf[10];
    static enum _TCPServerState
    {
        SM_HOME = 0,
        SM_LISTENING,
                
    }maquina_estado_servidor = SM_HOME;

    //maquina de estado
    switch(maquina_estado_servidor)
    {
        //----------------------------------------------------------------------
        case SM_HOME:
            for(i=0; i<SERVER_CONNS; i++)
            {
                //faz alocação de de buffer para os sockets
                MySocket[i] = TCPOpen(0, TCP_OPEN_SERVER, SERVER_PORT, TCP_PURPOSE_GENERIC_TCP_SERVER);
                timeout[i] = TickGet();
            }
            maquina_estado_servidor = SM_LISTENING;
        break;
        //----------------------------------------------------------------------
        case SM_LISTENING:
            for(i=0; i<SERVER_CONNS; i++)
            {
                if(TCPIsConnected(MySocket[i]))
                {
                    lenA=TCPIsGetReady(MySocket[i]);

                    if(lenA==2)
                    {
                        // Pega os dados da FIFO RX
                        TCPGetArray(MySocket[i], buf, lenA);
                        
                        //trata dados das conexoes
                        if((buf[0]=='O')&&(buf[1]=='I'))
                        {
                            TCPPut(MySocket[i], 'O');
                            TCPPut(MySocket[i], 'L');
                            TCPPut(MySocket[i], 'A');
                            TCPFlush(MySocket[i]);
                            timeout[i] = TickGet();
                        }
                        else
                            TCPDisconnect(MySocket[i]);
                    }
                    else
                    {
                        if(lenA>2)
                            TCPDiscard(MySocket[i]);
                    }
                    //se passou 15 segundos e nao recebeu nada desconecta
                    if(TickGet() - timeout[i] >= TICK_SECOND*15)
                    {
                        TCPDisconnect(MySocket[i]);
                    }
                }
                else
                {
                    timeout[i] = TickGet();
                }
            }
        break;
        //----------------------------------------------------------------------
    }
}