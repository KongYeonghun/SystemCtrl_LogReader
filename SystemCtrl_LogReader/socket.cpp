//#pragma warning(disable:4996)
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <thread>
#include <WinSock2.h>
#include "struct.h"
#include "socket.hpp"

using namespace std;

SysCtrlSOCKET::SysCtrlSOCKET(void)
{
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		cout << "WSAStartup error" << endl;
        WSACleanup();
        exit(0);
	}
}

SysCtrlSOCKET::~SysCtrlSOCKET(void)
{
}

void SysCtrlSOCKET::UDP_SERVER_OPEN(string ServerIpAddr, string ClientIpAddr, int ServerPort, int ClientPort)
{
	memset( &ServerInfo, 0, sizeof(ServerInfo) ); 
    memset( &ClientInfo, 0, sizeof(ClientInfo) );

    ServerInfo.sin_family  = AF_INET; 
    ServerInfo.sin_addr.s_addr = inet_addr( ServerIpAddr.c_str() ); 
    ServerInfo.sin_port   = htons( ServerPort ); 

    ClientInfo.sin_family  = AF_INET; 
    ClientInfo.sin_addr.s_addr = inet_addr( ClientIpAddr.c_str() ); 
    ClientInfo.sin_port   = htons( ClientPort ); 

    ServerSocket = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP ); // udp. SOCK_DGRAM : UDP
    if( ServerSocket == INVALID_SOCKET ) 
    {
        cout<<"socket error."<<endl;
        closesocket( ServerSocket );
        WSACleanup();
        exit(0);
    }
     //DWORD recvTimeout = 5000;  // 5초.
     //setsockopt(ServerSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&recvTimeout, sizeof(recvTimeout));


    //ntohl : 리틀 엔디안 바이트 순서로 u_long 타입 반환
    //ntohs : 리틀 엔디안 바이트 순서로 u_short 타입 반환
    //htonl : 빅 엔디안 바이트 순서로 u_long 타입 반환
    //htons : 빅 엔디안 바이트 순서로 u_short 타입 반환
}

void SysCtrlSOCKET::UDP_SERVER_CLOSE()
{
    closesocket( ServerSocket );
}


void SysCtrlSOCKET::UDP_CLIENT_OPEN(string ServerIpAddr, string ClientIpAddr, int ServerPort, int ClientPort)
{
    memset( &ServerInfo, 0, sizeof( ServerInfo ));
    memset( &ClientInfo, 0, sizeof( ClientInfo ));
 
    ServerInfo.sin_family   = AF_INET;
    ServerInfo.sin_addr.s_addr = inet_addr( ServerIpAddr.c_str() ); 
    ServerInfo.sin_port   = htons( ServerPort ); // 포트번호

    ClientInfo.sin_family   = AF_INET;
    ClientInfo.sin_addr.s_addr = inet_addr( ClientIpAddr.c_str() ); 
    ClientInfo.sin_port   = htons( ClientPort ); // 포트번호

    ClientSocket = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );
    if( ClientSocket == INVALID_SOCKET )
    {
        cout<<"socket error."<<endl;
        closesocket( ClientSocket );
        WSACleanup();
        exit(0);
    }

    //DWORD recvTimeout = 5000;  // 5초.
    //setsockopt(ServerSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&recvTimeout, sizeof(recvTimeout));
}

void SysCtrlSOCKET::UDP_CLIENT_CLOSE()
{
	closesocket( ClientSocket ); //소켓 닫기
}

/*******************************************************************************************/
//FromServerToClient_Send
//FromServerToClient_Recv
//FromClientToServer_Send
//FromClientToServer_Recv
/*******************************************************************************************/
void SysCtrlSOCKET::ServerToClient_Send(char *Buffer, SysCtrlSOCKET mSysCtrlSOCKET, int Buffer_Size)//when this program are server., size of buffer size
{
    int Send_Size = sendto( mSysCtrlSOCKET.ServerSocket, Buffer, Buffer_Size, 0, (struct sockaddr*) &mSysCtrlSOCKET.ClientInfo, sizeof( mSysCtrlSOCKET.ClientInfo ) );

    if( Send_Size != Buffer_Size )
    { 
        // cout << "Send_Size : " << Send_Size << endl;
        memset(Buffer, 0, sizeof(Buffer));
        // cout << "ip : " << inet_ntoa(ntohl(mSysCtrlSOCKET.ClientInfo.sin_addr.s_addr)) << endl;
        // cout << "ServerToClient_Send was failed!" <<endl;
    }
}

void SysCtrlSOCKET::ServerToClient_Recv(char *Buffer, SysCtrlSOCKET mSysCtrlSOCKET)//when this program are server.
{
    int Client_size = sizeof( mSysCtrlSOCKET.ClientInfo );
    int cRecv_Size = recvfrom( mSysCtrlSOCKET.ServerSocket, Buffer, BUFFER_SIZE, 0, (struct sockaddr*) &(mSysCtrlSOCKET.ClientInfo), &Client_size );

    if( cRecv_Size <= 0 )
    { 
        // cout << "cRecv_Size : " << cRecv_Size << endl;
        memset(Buffer, 0, sizeof(Buffer));
        // cout << "ip : " << inet_ntoa(ntohl(mSysCtrlSOCKET.ClientInfo.sin_addr.s_addr)) << endl;
        // cout << "ServerToClient_Recv was failed!"<<endl;
    }
}

void SysCtrlSOCKET::ClientToServer_Send(char *Buffer, SysCtrlSOCKET mSysCtrlSOCKET, int Buffer_Size)//when this program are client.
{
    int Send_Size = sendto(mSysCtrlSOCKET.ClientSocket, Buffer, Buffer_Size,  0, (struct sockaddr*) &mSysCtrlSOCKET.ServerInfo, sizeof( mSysCtrlSOCKET.ServerInfo ) );

    if( Send_Size != Buffer_Size )
    { 
        // cout << "Send_Size : " << Send_Size << endl;
        memset(Buffer, 0, sizeof(Buffer));
        // cout << "ip : " << inet_ntoa(ntohl((mSysCtrlSOCKET.ServerInfo.sin_addr.s_addr)) << endl;
        // cout << "ClientToServer_Send was failed!" <<endl;
    }
}

void SysCtrlSOCKET::ClientToServer_Recv(char *Buffer, SysCtrlSOCKET mSysCtrlSOCKET)//when this program are client.
{
    int Server_Size = sizeof( mSysCtrlSOCKET.ServerInfo );
    int Recv_Size = recvfrom( mSysCtrlSOCKET.ClientSocket, Buffer, BUFFER_SIZE, 0, (struct sockaddr*) &(mSysCtrlSOCKET.ServerInfo), &Server_Size );

    if( Recv_Size <= 0 )
    { 
        // cout << "Recv_Size : " << Recv_Size << endl;
        memset(Buffer, 0, sizeof(Buffer));
        // cout << "ip : " << inet_ntoa(ntohl((mSysCtrlSOCKET.ServerInfo.sin_addr.s_addr)) << endl;
        // cout << "ClientToServer_Recv was failed!"<<endl;
    }
}

/*******************************************************************************************/
//MessageClassification
/*******************************************************************************************/

void SysCtrlSOCKET::MessageClassification(char* Buffer, ROSStatusInfo* mROSStatusInfo)
{
    char temp_buffer[COMM_BODY_SIZE];

	memset(temp_buffer, 0, sizeof(temp_buffer));
    memcpy(temp_buffer, Buffer + sizeof(Header), sizeof(*mROSStatusInfo));
    memcpy(mROSStatusInfo, (ROSStatusInfo*)&temp_buffer, sizeof(*mROSStatusInfo));
}

void SysCtrlSOCKET::MessageClassification(char* Buffer, USVModeCommand* mUSVModeCommand)
{
    char temp_buffer[COMM_BODY_SIZE];
    
    memset(temp_buffer, 0, sizeof(temp_buffer));
    memcpy(temp_buffer, Buffer + sizeof(Header), sizeof(*mUSVModeCommand));
    memcpy(mUSVModeCommand, (USVModeCommand*)&temp_buffer, sizeof(*mUSVModeCommand));
}

void SysCtrlSOCKET::MessageClassification(char* Buffer, MissionRecordInfo* mMissionRecordInfo)
{
    char temp_buffer[COMM_BODY_SIZE];
    
    memset(temp_buffer, 0, sizeof(temp_buffer));
    memcpy(temp_buffer, Buffer + sizeof(Header), sizeof(*mMissionRecordInfo));
    memcpy(mMissionRecordInfo, (MissionRecordInfo*)&temp_buffer, sizeof(*mMissionRecordInfo));
}

void SysCtrlSOCKET::MessageClassification(char* Buffer, PowerControl* mPowerControl)
{
    char temp_buffer[COMM_BODY_SIZE];
    
    memset(temp_buffer, 0, sizeof(temp_buffer));
    memcpy(temp_buffer, Buffer + sizeof(Header), sizeof(*mPowerControl));
    memcpy(mPowerControl, (PowerControl*)&temp_buffer, sizeof(*mPowerControl));
}

void SysCtrlSOCKET::MessageClassification(char* Buffer, EOCameraControlCommand* mEOCameraControlCommand)
{
    char temp_buffer[COMM_BODY_SIZE];
    
    memset(temp_buffer, 0, sizeof(temp_buffer));
    memcpy(temp_buffer, Buffer + sizeof(Header), sizeof(*mEOCameraControlCommand));
    memcpy(mEOCameraControlCommand, (EOCameraControlCommand*)&temp_buffer, sizeof(*mEOCameraControlCommand));
}

void SysCtrlSOCKET::MessageClassification(char* Buffer, PlatformControlCommand* mPlatformControlCommand)
{
    char temp_buffer[COMM_BODY_SIZE];
    
    memset(temp_buffer, 0, sizeof(temp_buffer));
    memcpy(temp_buffer, Buffer + sizeof(Header), sizeof(*mPlatformControlCommand));
    memcpy(mPlatformControlCommand, (PlatformControlCommand*)&temp_buffer, sizeof(*mPlatformControlCommand));
}

void SysCtrlSOCKET::MessageClassification(char* Buffer, USVStatusInfo* mUSVStatusInfo)
{
    char temp_buffer[COMM_BODY_SIZE];
    
    memset(temp_buffer, 0, sizeof(temp_buffer));
    memcpy(temp_buffer, Buffer + sizeof(Header), sizeof(*mUSVStatusInfo));
    memcpy(mUSVStatusInfo, (USVStatusInfo*)&temp_buffer, sizeof(*mUSVStatusInfo));
}

void SysCtrlSOCKET::MessageClassification(char* Buffer, NavigationStatusInfo* mNavigationStatusInfo)
{
    char temp_buffer[COMM_BODY_SIZE];
    
    memset(temp_buffer, 0, sizeof(temp_buffer));
    memcpy(temp_buffer, Buffer + sizeof(Header), sizeof(*mNavigationStatusInfo));
    memcpy(mNavigationStatusInfo, (NavigationStatusInfo*)&temp_buffer, sizeof(*mNavigationStatusInfo));
}

void SysCtrlSOCKET::MessageClassification(char* Buffer, NavigationInfo* mNavigationInfo)
{
    char temp_buffer[COMM_BODY_SIZE];
    
    memset(temp_buffer, 0, sizeof(temp_buffer));
    memcpy(temp_buffer, Buffer + sizeof(Header), sizeof(*mNavigationInfo));
    memcpy(mNavigationInfo, (NavigationInfo*)&temp_buffer, sizeof(*mNavigationInfo));
}

void SysCtrlSOCKET::MessageClassification(char* Buffer, AutoNaviStatusInfo* mAutoNaviStatusInfo)
{
    char temp_buffer[COMM_BODY_SIZE];
    
    memset(temp_buffer, 0, sizeof(temp_buffer));
    memcpy(temp_buffer, Buffer + sizeof(Header), sizeof(*mAutoNaviStatusInfo));
    memcpy(mAutoNaviStatusInfo, (AutoNaviStatusInfo*)&temp_buffer, sizeof(*mAutoNaviStatusInfo));
}

void SysCtrlSOCKET::MessageClassification(char* Buffer, RadarTargetInfo* mRadarTargetInfo)
{
    char temp_buffer[COMM_BODY_SIZE];
    
    memset(temp_buffer, 0, sizeof(temp_buffer));
    memcpy(temp_buffer, Buffer + sizeof(Header), sizeof(*mRadarTargetInfo));
    memcpy(mRadarTargetInfo, (RadarTargetInfo*)&temp_buffer, sizeof(*mRadarTargetInfo));
}

void SysCtrlSOCKET::MessageClassification(char* Buffer, LidarTargetInfo* mLidarTargetInfo)
{
    char temp_buffer[COMM_BODY_SIZE];
    
    memset(temp_buffer, 0, sizeof(temp_buffer));
    memcpy(temp_buffer, Buffer + sizeof(Header), sizeof(*mLidarTargetInfo));
    memcpy(mLidarTargetInfo, (LidarTargetInfo*)&temp_buffer, sizeof(*mLidarTargetInfo));
}

void SysCtrlSOCKET::MessageClassification(char* Buffer, FlexTargetInfo* mFlexTargetInfo)
{
    char temp_buffer[COMM_BODY_SIZE];
    
    memset(temp_buffer, 0, sizeof(temp_buffer));
    memcpy(temp_buffer, Buffer + sizeof(Header), sizeof(*mFlexTargetInfo));
    memcpy(mFlexTargetInfo, (FlexTargetInfo*)&temp_buffer, sizeof(*mFlexTargetInfo));
}

void SysCtrlSOCKET::MessageClassification(char* Buffer, PlatformControlState* mPlatformControlState)
{
    char temp_buffer[COMM_BODY_SIZE];
    
    memset(temp_buffer, 0, sizeof(temp_buffer));
    memcpy(temp_buffer, Buffer + sizeof(Header), sizeof(*mPlatformControlState));
    memcpy(mPlatformControlState, (PlatformControlState*)&temp_buffer, sizeof(*mPlatformControlState));
}

void SysCtrlSOCKET::MessageClassification(char* Buffer, PlatformStatusInfo* mPlatformStatusInfo)
{
    char temp_buffer[COMM_BODY_SIZE];
    
    memset(temp_buffer, 0, sizeof(temp_buffer));
    memcpy(temp_buffer, Buffer + sizeof(Header), sizeof(*mPlatformStatusInfo));
    memcpy(mPlatformStatusInfo, (PlatformStatusInfo*)&temp_buffer, sizeof(*mPlatformStatusInfo));
}

void SysCtrlSOCKET::MessageClassification(char* Buffer, PowerControlResult* mPowerControlResult)
{
    char temp_buffer[COMM_BODY_SIZE];
    
    memset(temp_buffer, 0, sizeof(temp_buffer));
    memcpy(temp_buffer, Buffer + sizeof(Header), sizeof(*mPowerControlResult));
    memcpy(mPowerControlResult, (PowerControlResult*)&temp_buffer, sizeof(*mPowerControlResult));
}

void SysCtrlSOCKET::MessageClassification(char* Buffer, AcousticCommInfo* mAcousticCommInfo)
{
    char temp_buffer[COMM_BODY_SIZE];
    
    memset(temp_buffer, 0, sizeof(temp_buffer));
    memcpy(temp_buffer, Buffer + sizeof(Header), sizeof(*mAcousticCommInfo));
    memcpy(mAcousticCommInfo, (AcousticCommInfo*)&temp_buffer, sizeof(*mAcousticCommInfo));
}

void SysCtrlSOCKET::MessageClassification(char* Buffer, EOTargetInfo* mEOTargetInfo)
{
    char temp_buffer[COMM_BODY_SIZE];
    
    memset(temp_buffer, 0, sizeof(temp_buffer));
    memcpy(temp_buffer, Buffer + sizeof(Header), sizeof(*mEOTargetInfo));
    memcpy(mEOTargetInfo, (EOTargetInfo*)&temp_buffer, sizeof(*mEOTargetInfo));
}

void SysCtrlSOCKET::MessageClassification(char* Buffer, MissionRecordInfoRes* mMissionRecordInfoRes)
{
    char temp_buffer[COMM_BODY_SIZE];
    
    memset(temp_buffer, 0, sizeof(temp_buffer));
    memcpy(temp_buffer, Buffer + sizeof(Header), sizeof(*mMissionRecordInfoRes));
    memcpy(mMissionRecordInfoRes, (MissionRecordInfoRes*)&temp_buffer, sizeof(*mMissionRecordInfoRes));
}

void SysCtrlSOCKET::MessageClassification(char* Buffer, IRCameraControlCommand* mIRCameraControlCommand)
{
    char temp_buffer[COMM_BODY_SIZE];
    
    memset(temp_buffer, 0, sizeof(temp_buffer));
    memcpy(temp_buffer, Buffer + sizeof(Header), sizeof(*mIRCameraControlCommand));
    memcpy(mIRCameraControlCommand, (IRCameraControlCommand*)&temp_buffer, sizeof(*mIRCameraControlCommand));
}

void SysCtrlSOCKET::MessageClassification(char* Buffer, SaeronEOTrackingCommand* mSaeronEOTrackingCommand)
{
    char temp_buffer[COMM_BODY_SIZE];
    
    memset(temp_buffer, 0, sizeof(temp_buffer));
    memcpy(temp_buffer, Buffer + sizeof(Header), sizeof(*mSaeronEOTrackingCommand));
    memcpy(mSaeronEOTrackingCommand, (SaeronEOTrackingCommand*)&temp_buffer, sizeof(*mSaeronEOTrackingCommand));
}

void SysCtrlSOCKET::MessageClassification(char* Buffer, EOCameraControlRes* mEOCameraControlRes)
{
    char temp_buffer[COMM_BODY_SIZE];
    
    memset(temp_buffer, 0, sizeof(temp_buffer));
    memcpy(temp_buffer, Buffer + sizeof(Header), sizeof(*mEOCameraControlRes));
    memcpy(mEOCameraControlRes, (EOCameraControlRes*)&temp_buffer, sizeof(*mEOCameraControlRes));
}

void SysCtrlSOCKET::MessageClassification(char* Buffer, IRCameraControlRes* mIRCameraControlRes)
{
    char temp_buffer[COMM_BODY_SIZE];
    
    memset(temp_buffer, 0, sizeof(temp_buffer));
    memcpy(temp_buffer, Buffer + sizeof(Header), sizeof(*mIRCameraControlRes));
    memcpy(mIRCameraControlRes, (IRCameraControlRes*)&temp_buffer, sizeof(*mIRCameraControlRes));
}

void SysCtrlSOCKET::MessageClassification(char* Buffer, SaeronEOTrackingCommandRes* mSaeronEOTrackingCommandRes)
{
    char temp_buffer[COMM_BODY_SIZE];
    
    memset(temp_buffer, 0, sizeof(temp_buffer));
    memcpy(temp_buffer, Buffer + sizeof(Header), sizeof(*mSaeronEOTrackingCommandRes));
    memcpy(mSaeronEOTrackingCommandRes, (SaeronEOTrackingCommandRes*)&temp_buffer, sizeof(*mSaeronEOTrackingCommandRes));
}

void SysCtrlSOCKET::MessageClassification(char* Buffer, LRFDisdanceRes* mLRFDisdanceRes)
{
    char temp_buffer[COMM_BODY_SIZE];
    
    memset(temp_buffer, 0, sizeof(temp_buffer));
    memcpy(temp_buffer, Buffer + sizeof(Header), sizeof(*mLRFDisdanceRes));
    memcpy(mLRFDisdanceRes, (LRFDisdanceRes*)&temp_buffer, sizeof(*mLRFDisdanceRes));
}

/*******************************************************************************************/
//MessageCombination
/*******************************************************************************************/

void SysCtrlSOCKET::MessageCombination(char* Buffer, Header mHeader, ROSStatusInfo mROSStatusInfo)
{
    memset(Buffer, 0, BUFFER_SIZE);
    memcpy(Buffer, (char*)&mHeader, sizeof(mHeader));
    memcpy(Buffer + sizeof(mHeader), (char*)&mROSStatusInfo, sizeof(mROSStatusInfo));
}

void SysCtrlSOCKET::MessageCombination(char* Buffer, Header mHeader, USVModeCommand mUSVModeCommand)
{
    memset(Buffer, 0, BUFFER_SIZE);
    memcpy(Buffer, (char*)&mHeader, sizeof(mHeader));
    memcpy(Buffer + sizeof(mHeader), (char*)&mUSVModeCommand, sizeof(mUSVModeCommand));
}

void SysCtrlSOCKET::MessageCombination(char* Buffer, Header mHeader, MissionRecordInfo mMissionRecordInfo)
{
    memset(Buffer, 0, BUFFER_SIZE);
    memcpy(Buffer, (char*)&mHeader, sizeof(mHeader));
    memcpy(Buffer + sizeof(mHeader), (char*)&mMissionRecordInfo, sizeof(mMissionRecordInfo));
}

void SysCtrlSOCKET::MessageCombination(char* Buffer, Header mHeader, PowerControl mPowerControl)
{
    memset(Buffer, 0, BUFFER_SIZE);
    memcpy(Buffer, (char*)&mHeader, sizeof(mHeader));
    memcpy(Buffer + sizeof(mHeader), (char*)&mPowerControl, sizeof(mPowerControl));
}

void SysCtrlSOCKET::MessageCombination(char* Buffer, Header mHeader, EOCameraControlCommand mEOCameraControlCommand)
{
    memset(Buffer, 0, BUFFER_SIZE);
    memcpy(Buffer, (char*)&mHeader, sizeof(mHeader));
    memcpy(Buffer + sizeof(mHeader), (char*)&mEOCameraControlCommand, sizeof(mEOCameraControlCommand));
}

void SysCtrlSOCKET::MessageCombination(char* Buffer, Header mHeader, PlatformControlCommand mPlatformControlCommand)
{
    memset(Buffer, 0, BUFFER_SIZE);
    memcpy(Buffer, (char*)&mHeader, sizeof(mHeader));
    memcpy(Buffer + sizeof(mHeader), (char*)&mPlatformControlCommand, sizeof(mPlatformControlCommand));
}

void SysCtrlSOCKET::MessageCombination(char* Buffer, Header mHeader, USVStatusInfo mUSVStatusInfo)
{
    memset(Buffer, 0, BUFFER_SIZE);
    memcpy(Buffer, (char*)&mHeader, sizeof(mHeader));
    memcpy(Buffer + sizeof(mHeader), (char*)&mUSVStatusInfo, sizeof(mUSVStatusInfo));
}

void SysCtrlSOCKET::MessageCombination(char* Buffer, Header mHeader, NavigationStatusInfo mNavigationStatusInfo)
{
    memset(Buffer, 0, BUFFER_SIZE);
    memcpy(Buffer, (char*)&mHeader, sizeof(mHeader));
    memcpy(Buffer + sizeof(mHeader), (char*)&mNavigationStatusInfo, sizeof(mNavigationStatusInfo));
}

void SysCtrlSOCKET::MessageCombination(char* Buffer, Header mHeader, NavigationInfo mNavigationInfo)
{
    memset(Buffer, 0, BUFFER_SIZE);
    memcpy(Buffer, (char*)&mHeader, sizeof(mHeader));
    memcpy(Buffer + sizeof(mHeader), (char*)&mNavigationInfo, sizeof(mNavigationInfo));
}

void SysCtrlSOCKET::MessageCombination(char* Buffer, Header mHeader, AutoNaviStatusInfo mAutoNaviStatusInfo)
{
    memset(Buffer, 0, BUFFER_SIZE);
    memcpy(Buffer, (char*)&mHeader, sizeof(mHeader));
    memcpy(Buffer + sizeof(mHeader), (char*)&mAutoNaviStatusInfo, sizeof(mAutoNaviStatusInfo));
}

void SysCtrlSOCKET::MessageCombination(char* Buffer, Header mHeader, RadarTargetInfo mRadarTargetInfo)
{
    memset(Buffer, 0, BUFFER_SIZE);
    memcpy(Buffer, (char*)&mHeader, sizeof(mHeader));
    memcpy(Buffer + sizeof(mHeader), (char*)&mRadarTargetInfo, sizeof(mRadarTargetInfo));
}

void SysCtrlSOCKET::MessageCombination(char* Buffer, Header mHeader, LidarTargetInfo mLidarTargetInfo)
{
    memset(Buffer, 0, BUFFER_SIZE);
    memcpy(Buffer, (char*)&mHeader, sizeof(mHeader));
    memcpy(Buffer + sizeof(mHeader), (char*)&mLidarTargetInfo, sizeof(mLidarTargetInfo));
}

void SysCtrlSOCKET::MessageCombination(char* Buffer, Header mHeader, FlexTargetInfo mFlexTargetInfo)
{
    memset(Buffer, 0, BUFFER_SIZE);
    memcpy(Buffer, (char*)&mHeader, sizeof(mHeader));
    memcpy(Buffer + sizeof(mHeader), (char*)&mFlexTargetInfo, sizeof(mFlexTargetInfo));
}

void SysCtrlSOCKET::MessageCombination(char* Buffer, Header mHeader, PlatformControlState mPlatformControlState)
{
    memset(Buffer, 0, BUFFER_SIZE);
    memcpy(Buffer, (char*)&mHeader, sizeof(mHeader));
    memcpy(Buffer + sizeof(mHeader), (char*)&mPlatformControlState, sizeof(mPlatformControlState));
}

void SysCtrlSOCKET::MessageCombination(char* Buffer, Header mHeader, PlatformStatusInfo mPlatformStatusInfo)
{
    memset(Buffer, 0, BUFFER_SIZE);
    memcpy(Buffer, (char*)&mHeader, sizeof(mHeader));
    memcpy(Buffer + sizeof(mHeader), (char*)&mPlatformStatusInfo, sizeof(mPlatformStatusInfo));
}

void SysCtrlSOCKET::MessageCombination(char* Buffer, Header mHeader, PowerControlResult mPowerControlResult)
{
    memset(Buffer, 0, BUFFER_SIZE);
    memcpy(Buffer, (char*)&mHeader, sizeof(mHeader));
    memcpy(Buffer + sizeof(mHeader), (char*)&mPowerControlResult, sizeof(mPowerControlResult));
}

void SysCtrlSOCKET::MessageCombination(char* Buffer, Header mHeader, AcousticCommInfo mAcousticCommInfo)
{
    memset(Buffer, 0, BUFFER_SIZE);
    memcpy(Buffer, (char*)&mHeader, sizeof(mHeader));
    memcpy(Buffer + sizeof(mHeader), (char*)&mAcousticCommInfo, sizeof(mAcousticCommInfo));
}

void SysCtrlSOCKET::MessageCombination(char* Buffer, Header mHeader, EOTargetInfo mEOTargetInfo)
{
    memset(Buffer, 0, BUFFER_SIZE);
    memcpy(Buffer, (char*)&mHeader, sizeof(mHeader));
    memcpy(Buffer + sizeof(mHeader), (char*)&mEOTargetInfo, sizeof(mEOTargetInfo));
}

void SysCtrlSOCKET::MessageCombination(char* Buffer, Header mHeader, MissionRecordInfoRes mMissionRecordInfoRes)
{
    memset(Buffer, 0, BUFFER_SIZE);
    memcpy(Buffer, (char*)&mHeader, sizeof(mHeader));
    memcpy(Buffer + sizeof(mHeader), (char*)&mMissionRecordInfoRes, sizeof(mMissionRecordInfoRes));
}

void SysCtrlSOCKET::MessageCombination(char* Buffer, Header mHeader, IRCameraControlCommand mIRCameraControlCommand)
{
    memset(Buffer, 0, BUFFER_SIZE);
    memcpy(Buffer, (char*)&mHeader, sizeof(mHeader));
    memcpy(Buffer + sizeof(mHeader), (char*)&mIRCameraControlCommand, sizeof(mIRCameraControlCommand));
}

void SysCtrlSOCKET::MessageCombination(char* Buffer, Header mHeader, SaeronEOTrackingCommand mSaeronEOTrackingCommand)
{
    memset(Buffer, 0, BUFFER_SIZE);
    memcpy(Buffer, (char*)&mHeader, sizeof(mHeader));
    memcpy(Buffer + sizeof(mHeader), (char*)&mSaeronEOTrackingCommand, sizeof(mSaeronEOTrackingCommand));
}

void SysCtrlSOCKET::MessageCombination(char* Buffer, Header mHeader, EOCameraControlRes mEOCameraControlRes)
{
    memset(Buffer, 0, BUFFER_SIZE);
    memcpy(Buffer, (char*)&mHeader, sizeof(mHeader));
    memcpy(Buffer + sizeof(mHeader), (char*)&mEOCameraControlRes, sizeof(mEOCameraControlRes));
}

void SysCtrlSOCKET::MessageCombination(char* Buffer, Header mHeader, IRCameraControlRes mIRCameraControlRes)
{
    memset(Buffer, 0, BUFFER_SIZE);
    memcpy(Buffer, (char*)&mHeader, sizeof(mHeader));
    memcpy(Buffer + sizeof(mHeader), (char*)&mIRCameraControlRes, sizeof(mIRCameraControlRes));
}

void SysCtrlSOCKET::MessageCombination(char* Buffer, Header mHeader, SaeronEOTrackingCommandRes mSaeronEOTrackingCommandRes)
{
    memset(Buffer, 0, BUFFER_SIZE);
    memcpy(Buffer, (char*)&mHeader, sizeof(mHeader));
    memcpy(Buffer + sizeof(mHeader), (char*)&mSaeronEOTrackingCommandRes, sizeof(mSaeronEOTrackingCommandRes));
}

void SysCtrlSOCKET::MessageCombination(char* Buffer, Header mHeader, LRFDisdanceRes mLRFDisdanceRes)
{
    memset(Buffer, 0, BUFFER_SIZE);
    memcpy(Buffer, (char*)&mHeader, sizeof(mHeader));
    memcpy(Buffer + sizeof(mHeader), (char*)&mLRFDisdanceRes, sizeof(mLRFDisdanceRes));
}

/*******************************************************************************************/
//Header
/*******************************************************************************************/

void SysCtrlSOCKET::HeaderSetting(Header* mHeader, unsigned char Source_Application_ID, unsigned char Destination_Application_ID, unsigned short Message_ID,unsigned int Payload_Length, unsigned int Sequence_Number)
{
    mHeader->Source_Application_ID = Source_Application_ID;
    mHeader->Destination_Application_ID = Destination_Application_ID;
    mHeader->Message_ID = Message_ID;
    mHeader->Payload_Length = Payload_Length;
    mHeader->Sequence_Number = Sequence_Number;
}
