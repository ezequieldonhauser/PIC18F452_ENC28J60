#include "TCPIPConfig.h"

#if defined(STACK_USE_TCP_CLIENT)

#include "TCPIP Stack/TCPIP.h"
#include "ServerSocket.h"

//maquina de estado onde trabalha com socket cliente
void ClientSocketTCP(void)
{
    static DWORD            Timer;
    static TCP_SOCKET       MySocket = INVALID_SOCKET;

    static enum generic_client
    {
        INICIA=0,
        AGUARDA_BOTAO,
        CONECTA,
        AGUARDA_CONEXAO,
        ENVIA_DADOS,
        DESCONECTA,
        
    }maquina_estado_cliente = INICIA;

    //toda maquina de estado roda aki
    switch(maquina_estado_cliente)
    {
        ////////////////////////////////////////////////////////////////////////
        case INICIA:
            Timer = TickGet();
            maquina_estado_cliente = AGUARDA_BOTAO;
        break;

        ////////////////////////////////////////////////////////////////////////
        case AGUARDA_BOTAO:
            //pisca o led para informar a pilha rodando
            //if(TickGet() - Timer >= TICK_SECOND*3)
            if(!BUTTON0_IO)
            {
                if(TickGet() - Timer >= TICK_SECOND)
                {
                    Timer = TickGet();
                    maquina_estado_cliente = CONECTA;
                }
            }
            else
            {
                Timer = TickGet();
            }
        break;

        ////////////////////////////////////////////////////////////////////////
        case CONECTA:
            MySocket = TCPOpen((DWORD)&ServerName[0], 1, ServerPort, 0);
            if(MySocket == INVALID_SOCKET)
            break;
            maquina_estado_cliente=AGUARDA_CONEXAO;
            Timer = TickGet();
        break;

        ////////////////////////////////////////////////////////////////////////
        case AGUARDA_CONEXAO:
            if(!TCPIsConnected(MySocket))
            {
                //agurda o tick...
                if(TickGet()-Timer > 5*TICK_SECOND)
                {
                    //fecha a porta senao consegir conecta durante um tempo
                    TCPDisconnect(MySocket);
                    MySocket = INVALID_SOCKET;
                    maquina_estado_cliente=AGUARDA_BOTAO;
                }
                break;
            }
            Timer = TickGet();
            maquina_estado_cliente=ENVIA_DADOS;
        break;

        ////////////////////////////////////////////////////////////////////////
        case ENVIA_DADOS:
            if(TCPIsConnected(MySocket))
            {
                TCPPutROMString(MySocket,(ROM BYTE*)"E ai Server\r\n");
                TCPFlush(MySocket);
                maquina_estado_cliente = DESCONECTA;
            }
            else{maquina_estado_cliente = DESCONECTA;}
        break;

        ////////////////////////////////////////////////////////////////////////
        case DESCONECTA:
            TCPDisconnect(MySocket);
            MySocket = INVALID_SOCKET;
            maquina_estado_cliente = AGUARDA_BOTAO;
        break;
    }
}

#endif
