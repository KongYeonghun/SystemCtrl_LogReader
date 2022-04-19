
#pragma once
#ifndef SOCKET_HPP
#define SOCKET_HPP
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <thread>
#include <WinSock2.h>
#include "struct.h"

using namespace std;

class SysCtrlSOCKET
{
public:
	SysCtrlSOCKET(void);
	~SysCtrlSOCKET(void);
	void UDP_SERVER_OPEN(string ServerIpAddr, string ClientIpAddr, int ServerPort, int ClientPort);
	void UDP_SERVER_CLOSE();
	void UDP_CLIENT_OPEN(string ServerIpAddr, string ClientIpAddr, int ServerPort, int ClientPort);
	void UDP_CLIENT_CLOSE();

	void ServerToClient_Send(char *nBuffer, SysCtrlSOCKET nSysCtrlSOCKET, int Buffer_Size);//when this program are server.
	void ServerToClient_Recv(char *nBuffer, SysCtrlSOCKET nSysCtrlSOCKET);//when this program are server.
	void ClientToServer_Send(char *nBuffer, SysCtrlSOCKET nSysCtrlSOCKET, int Buffer_Size);//when this program are client.
	void ClientToServer_Recv(char *nBuffer, SysCtrlSOCKET nSysCtrlSOCKET);//when this program are client.

	void MessageClassification(char* Buffer, ROSStatusInfo* mROSStatusInfo);
	void MessageClassification(char* Buffer, USVModeCommand* mUSVModeCommand);
	void MessageClassification(char* Buffer, MissionRecordInfo* mMissionRecordInfo);
	void MessageClassification(char* Buffer, PowerControl* mPowerControl);
	void MessageClassification(char* Buffer, EOCameraControlCommand* mEOCameraControlCommand);
	void MessageClassification(char* Buffer, PlatformControlCommand* mPlatformControlCommand);
	void MessageClassification(char* Buffer, USVStatusInfo* mUSVStatusInfo);
	void MessageClassification(char* Buffer, NavigationStatusInfo* mNavigationStatusInfo);
	void MessageClassification(char* Buffer, NavigationInfo* mNavigationInfo);
	void MessageClassification(char* Buffer, AutoNaviStatusInfo* mAutoNaviStatusInfo);
	void MessageClassification(char* Buffer, RadarTargetInfo* mRadarTargetInfo);
	void MessageClassification(char* Buffer, LidarTargetInfo* mLidarTargetInfo);
	void MessageClassification(char* Buffer, FlexTargetInfo* mFlexTargetInfo);
	void MessageClassification(char* Buffer, PlatformControlState* mPlatformControlState);
	void MessageClassification(char* Buffer, PlatformStatusInfo* mPlatformStatusInfo);
	void MessageClassification(char* Buffer, PowerControlResult* mPowerControlResult);
	void MessageClassification(char* Buffer, AcousticCommInfo* mAcousticCommInfo);
	void MessageClassification(char* Buffer, EOTargetInfo* mEOTargetInfo);
	void MessageClassification(char* Buffer, MissionRecordInfoRes* mMissionRecordInfoRes);
	void MessageClassification(char* Buffer, IRCameraControlCommand* mIRCameraControlCommand);
	void MessageClassification(char* Buffer, SaeronEOTrackingCommand* mSaeronEOTrackingCommand);
	void MessageClassification(char* Buffer, EOCameraControlRes* mEOCameraControlRes);
	void MessageClassification(char* Buffer, IRCameraControlRes* mIRCameraControlRes);
	void MessageClassification(char* Buffer, SaeronEOTrackingCommandRes* mSaeronEOTrackingCommandRes);
	void MessageClassification(char* Buffer, LRFDisdanceRes* mLRFDisdanceRes);

	void MessageCombination(char* Buffer, Header mHeader, ROSStatusInfo mROSStatusInfo);
	void MessageCombination(char* Buffer, Header mHeader, USVModeCommand mUSVModeCommand);
	void MessageCombination(char* Buffer, Header mHeader, MissionRecordInfo mMissionRecordInfo);
	void MessageCombination(char* Buffer, Header mHeader, PowerControl mPowerControl);
	void MessageCombination(char* Buffer, Header mHeader, EOCameraControlCommand mEOCameraControlCommand);
	void MessageCombination(char* Buffer, Header mHeader, PlatformControlCommand mPlatformControlCommand);
	void MessageCombination(char* Buffer, Header mHeader, USVStatusInfo mUSVStatusInfo);
	void MessageCombination(char* Buffer, Header mHeader, NavigationStatusInfo mNavigationStatusInfo);
	void MessageCombination(char* Buffer, Header mHeader, NavigationInfo mNavigationInfo);
	void MessageCombination(char* Buffer, Header mHeader, AutoNaviStatusInfo mAutoNaviStatusInfo);
	void MessageCombination(char* Buffer, Header mHeader, RadarTargetInfo mRadarTargetInfo);
	void MessageCombination(char* Buffer, Header mHeader, LidarTargetInfo mLidarTargetInfo);
	void MessageCombination(char* Buffer, Header mHeader, FlexTargetInfo mFlexTargetInfo);
	void MessageCombination(char* Buffer, Header mHeader, PlatformControlState mPlatformControlState);
	void MessageCombination(char* Buffer, Header mHeader, PlatformStatusInfo mPlatformStatusInfo);
	void MessageCombination(char* Buffer, Header mHeader, PowerControlResult mPowerControlResult);
	void MessageCombination(char* Buffer, Header mHeader, AcousticCommInfo mAcousticCommInfo);
	void MessageCombination(char* Buffer, Header mHeader, EOTargetInfo mEOTargetInfo);
	void MessageCombination(char* Buffer, Header mHeader, MissionRecordInfoRes mMissionRecordInfoRes);
	void MessageCombination(char* Buffer, Header mHeader, IRCameraControlCommand mIRCameraControlCommand);
	void MessageCombination(char* Buffer, Header mHeader, SaeronEOTrackingCommand mSaeronEOTrackingCommand);
	void MessageCombination(char* Buffer, Header mHeader, EOCameraControlRes mEOCameraControlRes);
	void MessageCombination(char* Buffer, Header mHeader, IRCameraControlRes mIRCameraControlRes);
	void MessageCombination(char* Buffer, Header mHeader, SaeronEOTrackingCommandRes mSaeronEOTrackingCommandRes);
	void MessageCombination(char* Buffer, Header mHeader, LRFDisdanceRes mLRFDisdanceRes);

	void HeaderSetting(Header* mHeader, unsigned char Source_Application_ID, unsigned char Destination_Application_ID, unsigned short Message_ID,unsigned int Payload_Length, unsigned int Sequence_Number);

	WSADATA wsaData; 

	//udp server
	SOCKET ServerSocket;
	SOCKET ClientSocket;
	SOCKADDR_IN ServerInfo;
    SOCKADDR_IN ClientInfo; 
	
};

#endif
