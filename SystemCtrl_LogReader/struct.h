
/*******************************************************************************************/
//ICD version : 0.3.0
/*******************************************************************************************/

#pragma once

#include <stdint.h>
#include <thread>
#include <WinSock2.h>

#define COMM_HEADER_SIZE 12
#define COMM_BODY_SIZE 1300
#define BUFFER_SIZE COMM_HEADER_SIZE+COMM_BODY_SIZE

#define DEF_NUM_WP 15
#define DEF_NUM_TARGET 20
//#define SETTING_PATH ".\\..\\setting.txt" 
#define SETTING_PATH ".\\setting.txt" 
#define LOGGING_PATH ".\\SystemCtrl_Logging.bin"
#pragma pack(push,1)

/*******************************************************************************************/
//Header
/*******************************************************************************************/

typedef struct stHeader
{
	unsigned char Source_Application_ID;
	unsigned char Destination_Application_ID;
	unsigned short Message_ID;
	unsigned int Payload_Length;// body_length
	unsigned int Sequence_Number;
}Header;

typedef struct stCurrentTime
{
	int year;
	int month;
	int day;
	int hour;
	int min;
	int sec;
}CurrentTime;

/*******************************************************************************************/
//ROS -> SystemCtrl
/*******************************************************************************************/

typedef struct stROSStatusInfo
{
	double ROS_Latitude;
	double ROS_Longitude;
}ROSStatusInfo;


typedef struct stUSVModeCommand
{
	unsigned char	Mode;
	unsigned short	ModeDetail;
	unsigned char	AlgSelect;
	unsigned short	NavigationStartRecordID;
	double	Emergency_Return_Latitude;
	double	Emergency_Return_Longitude;
	unsigned char	reserved;

}USVModeCommand;

typedef struct stWaypoint
{
	unsigned short 	RecordID			;
	unsigned short 	Velocity			;
	double 			Latitude			;
	double 			Longitude			;
	unsigned char 	EngineSelect		;
	unsigned char 	AuvLauncher			;
	unsigned char 	SonarLauncher		;
	unsigned char 	AcousticCommLauncher;
}mWaypoint;

typedef struct stMissionRecordInfo
{
	char MissionName[50];
	unsigned short LateralError;
	unsigned short PathRange;	
	unsigned short MissionPointCount;
	mWaypoint Waypoint[DEF_NUM_WP];
}MissionRecordInfo;

typedef struct stMissionRecordInfoRes
{
	char			MissionName[50];
	unsigned short	MissionPointCount;
	unsigned short	Result;
}MissionRecordInfoRes;

typedef struct stEOCameraControlRes
{
	unsigned char	EOMode				;
	unsigned char	PanControl			;
	unsigned short	PanSpeed			;
	unsigned char	TiltControl			;
	unsigned short	TiltSpeed			;
	short			PanLocationControl	;
	unsigned char	PanMode				;
	short			TiltLocationControl	;
	unsigned char	TiltMode			;
	unsigned char	LRFControl			;
	unsigned char	TrakingControl		;
	unsigned char	TrakingID			;
	unsigned char	ZoomMode			;
	unsigned char	FocusMode			;
	unsigned char	EONightMode			;
	unsigned short	D_ZoomControl		;
	unsigned short	DISControl			;
}EOCameraControlRes;


typedef struct stIRCameraControlRes
{
	unsigned short	D_ZoomControl;
	unsigned short	NUCControl	;
	unsigned short	DISControl	;
	unsigned short	MIDEControl	;
}IRCameraControlRes;

typedef struct stSaeronEOTrackingCommandRes
{
	unsigned short	TrackingResult;
}SaeronEOTrackingCommandRes;


typedef struct stLRFDisdanceRes
{
	unsigned short LrfModeInfo;		
	unsigned short LrfMeasureDistanceInfo;		
}LRFDisdanceRes;

typedef struct stPowerControl
{
	unsigned char AutoSailingSBC1_2;
	unsigned char AutoSailingSBC3;
	unsigned char GPS_INS;
	unsigned char EthernetSwitch;
	unsigned char DigitalCompass;
	unsigned char CCTV;
	unsigned char Radar;
	unsigned char LiDAR;
	unsigned char EO;
	unsigned char PlatformControlSBC;
	unsigned char MissionControlSBC;
	unsigned char MultibeamSonar;
	unsigned char AcousticComm1;
	unsigned char AcousticComm2;
}PowerControl;

typedef struct stEOCameraControlCommand
{
	unsigned char	EOMode;
	unsigned char	PanControl;
	unsigned short	PanSpeed;
	unsigned char	TiltControl;
	unsigned short	TiltSpeed;
	short			PanLocationControl;
	unsigned char	PanMode;
	short			TiltLocationControl;
	unsigned char	TiltMode;
	unsigned char	LRFControl;
	unsigned char	TrakingControl;
	unsigned char	TrakingID;
	unsigned char	ZoomMode;
	unsigned char	FocusMode;
	unsigned char	EONightMode;
	unsigned short	D_ZoomControl;
	unsigned short	DISControl;
}EOCameraControlCommand;

typedef struct stIRCameraControlCommand
{
	unsigned short	D_ZoomControl;
	unsigned short	NUCControl	;
	unsigned short	DISControl	;
	unsigned short	MIDEControl	;
}IRCameraControlCommand;

typedef struct stSaeronEOTrackingCommand
{
	unsigned short TrackingCameraType;
	unsigned short PointX;
	unsigned short PointY;
	unsigned short Width;
	unsigned short Height;
	unsigned short TrackingMode;
	unsigned short TrackingAssist;
	unsigned short TrackingStartFlag;
}SaeronEOTrackingCommand;

typedef struct stPlatformControlCommand
{
	unsigned short ControlType;
	unsigned short RPMValue;
	short HandleAngle;
	unsigned short Heading;
	unsigned short Velocity;
	unsigned short Gear;
	unsigned char EngineSelect;
}PlatformControlCommand;

/*******************************************************************************************/
// SystemCtrl -> ROS
/*******************************************************************************************/

typedef struct stUSVStatusInfo
{
	unsigned char Mode;
	unsigned short ModeDetail;
	unsigned char NavigationConnectFlag;
	unsigned char PlatformConnectFlag;
	unsigned char EoCamDevConnectFlag;
	unsigned char reserved1;
	unsigned char reserved2;
}USVStatusInfo;

typedef struct stUSVStatusInfoConnectionFlag
{
	unsigned char NavigationConnectFlag;
	unsigned char PlatformConnectFlag;
	unsigned char EoCamDevConnectFlag;
	unsigned char reserved1;
	unsigned char reserved2;
}USVStatusInfoConnectionFlag;

typedef struct stNavigationStatusInfo
{
	unsigned char EOCameraBit;
	unsigned char RadarBit;
	unsigned char LidarBit;
	unsigned char GPSBit;
	unsigned char reserved;
}NavigationStatusInfo;

typedef struct stNavigationInfo
{
	double Latitude;
	double Longitude;
	unsigned short Heading;		
	unsigned short Velocity;	
	double Roll;
	double Pitch;
	double Yaw;
}NavigationInfo;
		
typedef struct stAutoNaviStatusInfo
{
	unsigned short DestinationPathID;
	unsigned short AutoNaviStatus;
	unsigned short Heading;
	unsigned short Velocity;
	unsigned short FailStatus;
}AutoNaviStatusInfo;


typedef struct stAllTargetInfo
{
	unsigned short  Object_ID	;	
	unsigned short  Course		;	
	unsigned short  Velocity	;	
	double          Latitude	;	
	double          Longitude	;	
}AllTargetInfo;

typedef struct stRadarTargetInfo
{
	unsigned short  TargetCount;
	AllTargetInfo	TargetInfo[DEF_NUM_TARGET];
}RadarTargetInfo;

typedef struct stLidarTargetInfo
{
	unsigned short  TargetCount;
	AllTargetInfo	TargetInfo[DEF_NUM_TARGET];
}LidarTargetInfo;

typedef struct stFlexTargetInfo
{
	unsigned short  TargetCount;
	AllTargetInfo	TargetInfo[DEF_NUM_TARGET];
}FlexTargetInfo;

typedef struct stPlatformControlState
{
	unsigned short ControlType;
	unsigned short RPMValue;
	unsigned short HandleAngle;
	unsigned short Heading;
	unsigned short Velocity;
	unsigned short Gear;
}PlatformControlState;

typedef struct stPlatformStatusInfo
{
	unsigned short BITState;
	unsigned short FuelState;
	unsigned short EngineStartStatus;
	unsigned char EngineSelectFlag;
}PlatformStatusInfo;

typedef struct stPowerControlResult
{
	unsigned char AutoSailingSBC1_2;
	unsigned char AutoSailingSBC3;
	unsigned char GPS_INS;
	unsigned char EthernetSwitch;
	unsigned char DigitalCompass;
	unsigned char CCTV;
	unsigned char Radar;
	unsigned char LiDAR;
	unsigned char EO;
	unsigned char PlatformControlSBC;
	unsigned char MissionControlSBC;
	unsigned char MultibeamSonar;
	unsigned char AcousticComm1;
	unsigned char AcousticComm2;
}PowerControlResult;

typedef struct stAcousticCommInfo
{
	unsigned char EquipmentSelect;
	unsigned char AuvID;
	double Latitude;
	double Longitude;	
	unsigned char Depth;			
}AcousticCommInfo;

typedef struct stAllEOMemberInfo
{
	unsigned short		Object_ID;
	unsigned short		Course;
	unsigned short		Velocity;
	double				Latitude;
	double				Longitude;
	unsigned short		BoundingBox_X_StartPoint;
	unsigned short		BoundingBox_Y_StartPoint;
	unsigned short		BoundingBox_X_Length;
	unsigned short		BoundingBox_Y_Length;
}AllEOMemberInfo;

typedef struct stEOTargetInfo
{
	unsigned short		TargetCount;
	AllEOMemberInfo		mEOMemberInfo[DEF_NUM_TARGET];
}EOTargetInfo;

/*******************************************************************************************/
// SystemCtrl -> AutoSailing
/*******************************************************************************************/

/*******************************************************************************************/
// AutoSailing -> SystemCtrl
/*******************************************************************************************/

/*******************************************************************************************/
// SystemCtrl -> PlatformCtrl
/*******************************************************************************************/

/*******************************************************************************************/
// PlatformCtrl-> SystemCtrl

/*******************************************************************************************/

/*******************************************************************************************/
// director ; kong yeong hun 
/*******************************************************************************************/

#define		NUM_WP				20
#define		DEF_NUM_TARGET		20	

#define		DEF_RAND_SEED		5

#define		DEF_DEG2RAD			3.1415926535897931/180.0
#define		DEF_RAD2DEG			180.0/3.1415926535897931
#define		PI					3.1415926535897931
#define     DEF_KTS2MPS         0.5144
#define     DEF_MPS2KTS         1/0.5144

typedef struct tWPInfo
{
	int stnWPnum;
	int stnWPsize;
	double stdWPUTMN[NUM_WP];
	double stdWPUTME[NUM_WP];
	double stdCOG[NUM_WP];
	double stdSOG[NUM_WP];
	double stdWPTime[NUM_WP];//wp 
	int stWPinfo[NUM_WP];//
	// 20171221 KAIST 
	double stdWPID[NUM_WP];
	double stdWPMaxVel[NUM_WP];// 
	double stdWPLeftTime[NUM_WP];
	double stdWPAcceptRadius[NUM_WP];
}stWPInfo;

typedef struct tUSVMotion
{
	double stdUTMN;
	double stdUTME;
	double stdSOG;// m/s
	double stdCOG;// degree
	double stdRoll;
	double stdPitch;
	double stdYaw;
	double stdVsurge;
	double stWVsway;
	double stWVHeave;
	double stWAccSurge;
	double stWAccSway;
	double stWAccHeave;
	double stErrCov_N;
	double stErrCov_NE;
	double stErrCov_E;
}stUSVMotion;

typedef struct tTargetMotion
{
	int stnNumObj;
	int stnMMSI[DEF_NUM_TARGET];
	double stdShipLOA[DEF_NUM_TARGET];
	double stdUTMN[DEF_NUM_TARGET];
	double stdUTME[DEF_NUM_TARGET];
	double stdSOG[DEF_NUM_TARGET];         // m/s
	double stdCOG[DEF_NUM_TARGET];         // degree, USV heading
	double stdDISTANCE[DEF_NUM_TARGET];
	double stErrCov_N[DEF_NUM_TARGET];     // m^2
	double stErrCov_NE[DEF_NUM_TARGET];	// m^2
	double stErrCov_E[DEF_NUM_TARGET];     // m^2
	double stErrCov_heading[DEF_NUM_TARGET]; // rad^2
}stTargetMotion;

typedef struct stUsvGoalHeadingNVelocity{
	double heading;
	double velocity;
}stUsvGoalHnV;

typedef struct PotentialFieldAlgorithmInit {
	double AVOIDANCE_RADIUS;//meter
	double PF_CONSTANT_PARAMETER;
	double HEADING_LIMIT;
	double COLEGS_RULE_RADIUS;
}PF_INIT;

#pragma pack(pop)