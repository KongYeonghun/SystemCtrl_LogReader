#pragma warning(disable:4996)

#include "main.h"

int main(void)
{
	system("title SystemCtrl_LogReader")                                            ;
	cout << "SystemCtrl_LogReader Start.." << endl                                            ;

	Header							mHeader                                            ;
	CurrentTime						mCurrentTime                                            ;
	ROSStatusInfo					mROSStatusInfo                                            ;
	USVModeCommand					mUSVModeCommand                                            ;
	MissionRecordInfo				mMissionRecordInfo                                            ;
	PowerControl					mPowerControl                                            ;
	EOCameraControlCommand			mEOCameraControlCommand                                            ;
	PlatformControlCommand			mPlatformControlCommand                                            ;
	USVStatusInfo					mUSVStatusInfo                                            ;
	NavigationStatusInfo			mNavigationStatusInfo                                            ;
	NavigationInfo					mNavigationInfo                                            ;
	AutoNaviStatusInfo				mAutoNaviStatusInfo                                            ;
	RadarTargetInfo					mRadarTargetInfo                                            ;
	LidarTargetInfo					mLidarTargetInfo                                            ;
	FlexTargetInfo					mFlexTargetInfo                                            ;
	PlatformControlState			mPlatformControlState                                            ;
	PlatformStatusInfo				mPlatformStatusInfo                                            ;
	PowerControlResult				mPowerControlResult                                            ;
	AcousticCommInfo				mAcousticCommInfo                                            ;
	USVModeCommand					Emergency_USVModeCommand                                            ;
	MissionRecordInfo				Emergency_MissionRecordInfo                                            ;
	IRCameraControlCommand			mIRCameraControlCommand                                            ;
	SaeronEOTrackingCommand			mSaeronEOTrackingCommand                                            ;
	EOCameraControlRes				mEOCameraControlRes                                            ;
	IRCameraControlRes				mIRCameraControlRes                                            ;
	SaeronEOTrackingCommandRes 		mSaeronEOTrackingCommandRes                                            ;
	USVStatusInfoConnectionFlag		mUSVStatusInfoConnectionFlag                                            ;
	MissionRecordInfoRes			mMissionRecordInfoRes                                            ;
	EOTargetInfo					mEOTargetInfo                                            ;

	memset(&mHeader,						0, sizeof(mHeader))                                            ;
	memset(&mROSStatusInfo, 				0, sizeof(mROSStatusInfo))                                            ;
	memset(&mUSVModeCommand, 				0, sizeof(mUSVModeCommand))                                            ;
	memset(&mMissionRecordInfo, 			0, sizeof(mMissionRecordInfo))                                            ;
	memset(&mPowerControl, 					0, sizeof(mPowerControl))                                            ;
	memset(&mEOCameraControlCommand,		0, sizeof(mEOCameraControlCommand))                                            ;
	memset(&mPlatformControlCommand, 		0, sizeof(mPlatformControlCommand))                                            ;
	memset(&mUSVStatusInfo, 				0, sizeof(mUSVStatusInfo))                                            ;
	memset(&mNavigationStatusInfo, 			0, sizeof(mNavigationStatusInfo))                                            ;
	memset(&mNavigationInfo, 				0, sizeof(mNavigationInfo))                                            ;
	memset(&mAutoNaviStatusInfo, 			0, sizeof(mAutoNaviStatusInfo))                                            ;
	memset(&mRadarTargetInfo, 				0, sizeof(mRadarTargetInfo))                                            ;
	memset(&mLidarTargetInfo, 				0, sizeof(mLidarTargetInfo))                                            ;
	memset(&mFlexTargetInfo, 				0, sizeof(mFlexTargetInfo))                                            ;
	memset(&mPlatformControlState, 			0, sizeof(mPlatformControlState))                                            ;
	memset(&mPlatformStatusInfo, 			0, sizeof(mPlatformStatusInfo))                                            ;
	memset(&mPowerControlResult, 			0, sizeof(mPowerControlResult))                                            ;
	memset(&mAcousticCommInfo, 				0, sizeof(mAcousticCommInfo))                                            ;
	memset(&mIRCameraControlCommand, 		0, sizeof(mIRCameraControlCommand))                                            ;
	memset(&mSaeronEOTrackingCommand, 		0, sizeof(mSaeronEOTrackingCommand))                                            ;
	memset(&mEOCameraControlRes, 			0, sizeof(mEOCameraControlRes))                                            ;
	memset(&mIRCameraControlRes, 			0, sizeof(mIRCameraControlRes))                                            ;
	memset(&mSaeronEOTrackingCommandRes, 	0, sizeof(mSaeronEOTrackingCommandRes))                                            ;
	memset(&mUSVStatusInfoConnectionFlag, 	0, sizeof(mUSVStatusInfoConnectionFlag))                                            ;
	memset(&mMissionRecordInfoRes, 			0, sizeof(mMissionRecordInfoRes))                                            ;


	FILE *fp = fopen(LOGGING_PATH, "rb")                                            ;   // 파일을 쓰기/바이너리 모드(wb)로 열기
	
	timer = time(NULL)                                            ;
	t = localtime(&timer)                                            ;
	string test = "SystemCtrl_LogReader"                                            ;
	test += std::to_string(t->tm_year + 1900)                                            ;
	test += "_"                                            ;
	test += std::to_string(t->tm_mon + 1)                                            ;
	test += "_"                                            ;
	test += std::to_string(t->tm_mday + 1)                                            ;
	test += "_"                                            ;
	test += std::to_string(t->tm_hour)                                            ;
	test += "_"                                            ;
	test += std::to_string(t->tm_min)                                            ;
	test += "_"                                            ;
	test += std::to_string(t->tm_sec)                                            ;
	test += ".csv"                                            ;

	AlgLoggingFile.open(test)                                            ;
	AlgLoggingFile.setf(ios::fixed)                                            ;
	AlgLoggingFile.setf(ios::showpoint)                                            ;
	AlgLoggingFile.precision(6)                                            ;

	AlgLoggingFile <<
	"time													" 		<< "," <<
	"mROSStatusInfo.ROS_Latitude								" 		<< "," <<
	"mROSStatusInfo.ROS_Longitude							" 		<< "," << 
	"mUSVModeCommand.Mode									" 		<< "," << 
	"mUSVModeCommand.ModeDetail								" 		<< "," << 
	"mUSVModeCommand.AlgSelect								" 		<< "," << 
	"mUSVModeCommand.NavigationStartRecordID					" 		<< "," << 
	"mUSVModeCommand.Emergency_Return_Latitude				" 		<< "," << 
	"mUSVModeCommand.Emergency_Return_Longitude				" 		<< "," <<
	"mUSVModeCommand.reserved								" 		<< "," << 
	"mMissionRecordInfo.MissionName[0]						" 		<< "," << 
	"mMissionRecordInfo.LateralError							" 		<< "," << 
	"mMissionRecordInfo.PathRange							" 		<< "," << 
	"mMissionRecordInfo.MissionPointCount 					" 		<< "," << 
	"mMissionRecordInfo.Waypoint[0].RecordID					" 		<< "," << 
	"mMissionRecordInfo.Waypoint[0].Velocity					" 		<< "," <<
	"mMissionRecordInfo.Waypoint[0].Latitude					" 		<< "," << 
	"mMissionRecordInfo.Waypoint[0].Longitude				" 		<< "," << 
	"mMissionRecordInfo.Waypoint[0].EngineSelect				" 		<< "," << 
	"mMissionRecordInfo.Waypoint[0].AuvLauncher				" 		<< "," << 
	"mMissionRecordInfo.Waypoint[0].SonarLauncher			" 		<< "," << 
	"mMissionRecordInfo.Waypoint[0].AcousticCommLauncher		" 		<< "," <<
	"mMissionRecordInfoRes.MissionName[0]					" 		<< "," << 
	"mMissionRecordInfoRes.MissionPointCount					" 		<< "," << 
	"mMissionRecordInfoRes.Result							" 		<< "," << 
	"mEOCameraControlRes.EOMode								" 		<< "," << 
	"mEOCameraControlRes.PanControl							" 		<< "," << 
	"mEOCameraControlRes.PanSpeed							" 		<< "," << 
	"mEOCameraControlRes.TiltControl							" 		<< "," <<
	"mEOCameraControlRes.TiltSpeed							" 		<< "," << 
	"mEOCameraControlRes.PanLocationControl					" 		<< "," << 
	"mEOCameraControlRes.PanMode								" 		<< "," << 
	"mEOCameraControlRes.TiltLocationControl					" 		<< "," << 
	"mEOCameraControlRes.TiltMode							" 		<< "," << 
	"mEOCameraControlRes.LRFControl							" 		<< "," << 
	"mEOCameraControlRes.TrakingControl						" 		<< "," <<
	"mEOCameraControlRes.TrakingID							" 		<< "," << 
	"mEOCameraControlRes.ZoomMode							" 		<< "," << 
	"mEOCameraControlRes.FocusMode							" 		<< "," << 
	"mEOCameraControlRes.EONightMode							" 		<< "," << 
	"mEOCameraControlRes.D_ZoomControl						" 		<< "," << 
	"mEOCameraControlRes.DISControl							" 		<< "," << 
	"mIRCameraControlRes.D_ZoomControl						" 		<< "," <<
	"mIRCameraControlRes.NUCControl							" 		<< "," << 
	"mIRCameraControlRes.DISControl							" 		<< "," << 
	"mIRCameraControlRes.MIDEControl							" 		<< "," << 
	"mSaeronEOTrackingCommandRes.TrackingResult				" 		<< "," << 
	// "mPowerControl.AutoSailingSBC1_2							" 		<< "," << 
	// "mPowerControl.AutoSailingSBC3							" 		<< "," << 
	// "mPowerControl.GPS_INS									" 		<< "," <<
	// "mPowerControl.EthernetSwitch							" 		<< "," << 
	// "mPowerControl.DigitalCompass							" 		<< "," << 
	// "mPowerControl.CCTV										" 		<< "," << 
	// "mPowerControl.Radar										" 		<< "," << 
	// "mPowerControl.LiDAR										" 		<< "," << 
	// "mPowerControl.EO										" 		<< "," << 
	// "mPowerControl.PlatformControlSBC						" 		<< "," <<
	// "mPowerControl.MissionControlSBC							" 		<< "," << 
	// "mPowerControl.MultibeamSonaR							" 		<< "," << 
	// "mPowerControl.AcousticComm1								" 		<< "," << 
	// "mPowerControl.AcousticComm2								" 		<< "," << 
	"mEOCameraControlCommand.EOMode							" 		<< "," << 
	"mEOCameraControlCommand.PanControl						" 		<< "," << 
	"mEOCameraControlCommand.PanSpeed						" 		<< "," <<
	"mEOCameraControlCommand.TiltControl						" 		<< "," << 
	"mEOCameraControlCommand.TiltSpeed						" 		<< "," << 
	"mEOCameraControlCommand.PanLocationControl				" 		<< "," << 
	"mEOCameraControlCommand.PanMode							" 		<< "," << 
	"mEOCameraControlCommand.TiltLocationControl				" 		<< "," << 
	"mEOCameraControlCommand.TiltMode						" 		<< "," << 
	"mEOCameraControlCommand.LRFControl						" 		<< "," <<
	"mEOCameraControlCommand.TrakingControl					" 		<< "," << 
	"mEOCameraControlCommand.TrakingID						" 		<< "," << 
	"mEOCameraControlCommand.ZoomMode						" 		<< "," << 
	"mEOCameraControlCommand.FocusMode						" 		<< "," << 
	"mEOCameraControlCommand.EONightMode						" 		<< "," << 
	"mEOCameraControlCommand.D_ZoomControl					" 		<< "," << 
	"mEOCameraControlCommand.DISControl						" 		<< "," <<
	"mIRCameraControlCommand.D_ZoomControl					" 		<< "," << 
	"mIRCameraControlCommand.NUCControl						" 		<< "," << 
	"mIRCameraControlCommand.DISControl						" 		<< "," << 
	"mIRCameraControlCommand.MIDEControl						" 		<< "," << 
	"mSaeronEOTrackingCommand.TrackingCameraType				" 		<< "," << 
	"mSaeronEOTrackingCommand.PointX							" 		<< "," << 
	"mSaeronEOTrackingCommand.PointY							" 		<< "," <<
	"mSaeronEOTrackingCommand.Width							" 		<< "," << 
	"mSaeronEOTrackingCommand.Height							" 		<< "," << 
	"mSaeronEOTrackingCommand.TrackingMode					" 		<< "," << 
	"mSaeronEOTrackingCommand.TrackingAssist					" 		<< "," << 
	"mSaeronEOTrackingCommand.TrackingStartFlag				" 		<< "," << 
	"mPlatformControlCommand.ControlType                    	" 		<< "," << 
	"mPlatformControlCommand.RPMValue                       	" 		<< "," <<
	"mPlatformControlCommand.HandleAngle                    	" 		<< "," << 
	"mPlatformControlCommand.Heading                        	" 		<< "," << 
	"mPlatformControlCommand.Velocity                       	" 		<< "," << 
	"mPlatformControlCommand.Gear                           	" 		<< "," << 
	"mPlatformControlCommand.EngineSelect                   	" 		<< "," << 
	"mUSVStatusInfo.Mode                                    	" 		<< "," << 
	"mUSVStatusInfo.ModeDetail                              	" 		<< "," <<
	"mUSVStatusInfo.NavigationConnectFlag                   	" 		<< "," << 
	"mUSVStatusInfo.PlatformConnectFlag                     	" 		<< "," << 
	"mUSVStatusInfo.EoCamDevConnectFlag                     	" 		<< "," << 
	"mUSVStatusInfo.reserved1                               	" 		<< "," << 
	"mUSVStatusInfo.reserved2                               	" 		<< "," << 
	"mUSVStatusInfoConnectionFlag.NavigationConnectFlag  	" 		<< "," << 
	"mUSVStatusInfoConnectionFlag.PlatformConnectFlag    	" 		<< "," <<
	"mUSVStatusInfoConnectionFlag.EoCamDevConnectFlag    	" 		<< "," << 
	"mUSVStatusInfoConnectionFlag.reserved1              	" 		<< "," << 
	"mUSVStatusInfoConnectionFlag.reserved2              	" 		<< "," << 
	"mNavigationStatusInfo.EOCameraBit  						" 		<< "," << 
	"mNavigationStatusInfo.RadarBit     						" 		<< "," << 
	"mNavigationStatusInfo.LidarBit     						" 		<< "," << 
	"mNavigationStatusInfo.GPSBit       						" 		<< "," <<
	"mNavigationStatusInfo.reserved     						" 		<< "," << 
	"mNavigationInfo.Latitude           						" 		<< "," << 
	"mNavigationInfo.Longitude          						" 		<< "," << 
	"mNavigationInfo.Heading            						" 		<< "," << 
	"mNavigationInfo.Velocity           						" 		<< "," << 
	"mNavigationInfo.Roll               						" 		<< "," << 
	"mNavigationInfo.Pitch              						" 		<< "," <<
	"mNavigationInfo.Yaw                						" 		<< "," << 
	"mAutoNaviStatusInfo.DestinationPathID               	" 		<< "," << 
	"mAutoNaviStatusInfo.AutoNaviStatus                  	" 		<< "," << 
	"mAutoNaviStatusInfo.Heading                         	" 		<< "," << 
	"mAutoNaviStatusInfo.Velocity                        	" 		<< "," << 
	"mAutoNaviStatusInfo.FailStatus                      	" 		<< "," << 
	"mRadarTargetInfo.TargetCount                           " 		<< "," <<
	"mRadarTargetInfo.TargetInfo[0].Object_ID	            " 		<< "," << 
	"mRadarTargetInfo.TargetInfo[0].Course		            " 		<< "," << 
	"mRadarTargetInfo.TargetInfo[0].Velocity	            	" 		<< "," << 
	"mRadarTargetInfo.TargetInfo[0].Latitude	            	" 		<< "," << 
	"mRadarTargetInfo.TargetInfo[0].Longitude	            " 		<< "," << 
	"mLidarTargetInfo.TargetCount                           " 		<< "," << 
	"mLidarTargetInfo.TargetInfo[0].Object_ID	            " 		<< "," <<
	"mLidarTargetInfo.TargetInfo[0].Course		            " 		<< "," << 
	"mLidarTargetInfo.TargetInfo[0].Velocity	            	" 		<< "," << 
	"mLidarTargetInfo.TargetInfo[0].Latitude	            	" 		<< "," << 
	"mLidarTargetInfo.TargetInfo[0].Longitude	            " 		<< "," << 
	"mFlexTargetInfo.TargetCount                            " 		<< "," << 
	"mFlexTargetInfo.TargetInfo[0].Object_ID	            	" 		<< "," << 
	"mFlexTargetInfo.TargetInfo[0].Course		            " 		<< "," <<
	"mFlexTargetInfo.TargetInfo[0].Velocity	                " 		<< "," << 
	"mFlexTargetInfo.TargetInfo[0].Latitude	                " 		<< "," << 
	"mFlexTargetInfo.TargetInfo[0].Longitude	            	" 		<< "," << 
	"mPlatformControlState.ControlType                      " 		<< "," << 
	"mPlatformControlState.RPMValue                         " 		<< "," << 
	"mPlatformControlState.HandleAngle                      " 		<< "," <<
	"mPlatformControlState.Heading                          " 		<< "," << 
	"mPlatformControlState.Velocity                         " 		<< "," << 
	"mPlatformControlState.Gear                             " 		<< "," << 
	"mPlatformStatusInfo.BITState                           " 		<< "," << 
	"mPlatformStatusInfo.FuelState                          " 		<< "," << 
	"mPlatformStatusInfo.EngineStartStatus                  " 		<< "," << 
	"mPlatformStatusInfo.EngineSelectFlag                   " 		<< "," <<
	// "mPowerControlResult.AutoSailingSBC1_2                  " 		<< "," << 
	// "mPowerControlResult.AutoSailingSBC3                    " 		<< "," << 
	// "mPowerControlResult.GPS_INS                            " 		<< "," << 
	// "mPowerControlResult.EthernetSwitch                     " 		<< "," << 
	// "mPowerControlResult.DigitalCompass                     " 		<< "," << 
	// "mPowerControlResult.CCTV                               " 		<< "," << 
	// "mPowerControlResult.Radar                              " 		<< "," <<
	// "mPowerControlResult.LiDAR                              " 		<< "," << 
	// "mPowerControlResult.EO                                 " 		<< "," << 
	// "mPowerControlResult.PlatformControlSBC                 " 		<< "," << 
	// "mPowerControlResult.MissionControlSBC                  " 		<< "," << 
	// "mPowerControlResult.MultibeamSonar                     " 		<< "," << 
	// "mPowerControlResult.AcousticComm1                      " 		<< "," << 
	// "mPowerControlResult.AcousticComm2                      " 		<< "," <<
	"mAcousticCommInfo.EquipmentSelect                      " 		<< "," << 
	"mAcousticCommInfo.AuvID                                " 		<< "," << 
	"mAcousticCommInfo.Latitude                             " 		<< "," << 
	"mAcousticCommInfo.Longitude                            " 		<< "," << 
	"mAcousticCommInfo.Depth                                " 		<< "," << 
	"mEOTargetInfo.TargetCount                              " 		<< "," << 
	"mEOTargetInfo.mEOMemberInfo[0].Object_ID               " 		<< "," <<
	"mEOTargetInfo.mEOMemberInfo[0].Course                  " 		<< "," << 
	"mEOTargetInfo.mEOMemberInfo[0].Velocity                " 		<< "," << 
	"mEOTargetInfo.mEOMemberInfo[0].Latitude                " 		<< "," << 
	"mEOTargetInfo.mEOMemberInfo[0].Longitude               " 		<< "," << 
	"mEOTargetInfo.mEOMemberInfo[0].BoundingBox_X_StartPoint" 		<< "," << 
	"mEOTargetInfo.mEOMemberInfo[0].BoundingBox_Y_StartPoint" 		<< "," << 
	"mEOTargetInfo.mEOMemberInfo[0].BoundingBox_X_Length    " 		<< "," <<
	"mEOTargetInfo.mEOMemberInfo[0].BoundingBox_Y_Length    " 		<< "," << 

	"\n"                                            ;

	while(feof(fp) == 0)
	{
		// Sleep(1)                                            ;
		fread(&mCurrentTime,			sizeof(mCurrentTime)				, 1/*sizeof(mHeader)					*/	, fp)                                            ;       // 구조체의 내용을 파일에 저장
		fread(&mHeader,					sizeof(mHeader)						, 1/*sizeof(mHeader)					*/	, fp)                                            ;       // 구조체의 내용을 파일에 저장
		fread(&mROSStatusInfo, 			sizeof(mROSStatusInfo)				, 1/*sizeof(mROSStatusInfo)				*/	, fp)                                            ;       // 구조체의 내용을 파일에 저장
		fread(&mUSVModeCommand, 		sizeof(mUSVModeCommand)				, 1/*sizeof(mUSVModeCommand)			*/	, fp)                                            ;       // 구조체의 내용을 파일에 저장
		fread(&mMissionRecordInfo, 		sizeof(mMissionRecordInfo)			, 1/*sizeof(mMissionRecordInfo)			*/	, fp)                                            ;       // 구조체의 내용을 파일에 저장
		fread(&mPowerControl, 			sizeof(mPowerControl)				, 1/*sizeof(mPowerControl)				*/	, fp)                                            ;       // 구조체의 내용을 파일에 저장
		fread(&mEOCameraControlCommand,	sizeof(mEOCameraControlCommand)		, 1/*sizeof(mEOCameraControlCommand)	*/	, fp)                                            ;       // 구조체의 내용을 파일에 저장
		fread(&mPlatformControlCommand,	sizeof(mPlatformControlCommand)		, 1/*sizeof(mPlatformControlCommand)	*/	, fp)                                            ;       // 구조체의 내용을 파일에 저장
		fread(&mUSVStatusInfo, 			sizeof(mUSVStatusInfo)				, 1/*sizeof(mUSVStatusInfo)				*/	, fp)                                            ;       // 구조체의 내용을 파일에 저장
		fread(&mNavigationStatusInfo,	sizeof(mNavigationStatusInfo)		, 1/*sizeof(mNavigationStatusInfo)		*/	, fp)                                            ;       // 구조체의 내용을 파일에 저장
		fread(&mNavigationInfo,			sizeof(mNavigationInfo)				, 1/*sizeof(mNavigationInfo)			*/	, fp)                                            ;       // 구조체의 내용을 파일에 저장
		fread(&mAutoNaviStatusInfo,		sizeof(mAutoNaviStatusInfo)			, 1/*sizeof(mAutoNaviStatusInfo)		*/	, fp)                                            ;       // 구조체의 내용을 파일에 저장
		fread(&mRadarTargetInfo, 		sizeof(mRadarTargetInfo)			, 1/*sizeof(mRadarTargetInfo)			*/	, fp)                                            ;       // 구조체의 내용을 파일에 저장
		fread(&mLidarTargetInfo, 		sizeof(mLidarTargetInfo)			, 1/*sizeof(mLidarTargetInfo)			*/	, fp)                                            ;       // 구조체의 내용을 파일에 저장
		fread(&mFlexTargetInfo, 		sizeof(mFlexTargetInfo)				, 1/*sizeof(mFlexTargetInfo)			*/	, fp)                                            ;       // 구조체의 내용을 파일에 저장
		fread(&mPlatformControlState, 	sizeof(mPlatformControlState)		, 1/*sizeof(mPlatformControlState)		*/	, fp)                                            ;       // 구조체의 내용을 파일에 저장
		fread(&mPlatformStatusInfo,		sizeof(mPlatformStatusInfo)			, 1/*sizeof(mPlatformStatusInfo)		*/	, fp)                                            ;       // 구조체의 내용을 파일에 저장
		fread(&mPowerControlResult, 	sizeof(mPowerControlResult)			, 1/*sizeof(mPowerControlResult)		*/	, fp)                                            ;       // 구조체의 내용을 파일에 저장
		fread(&mAcousticCommInfo, 		sizeof(mAcousticCommInfo)			, 1/*sizeof(mAcousticCommInfo)			*/	, fp)                                            ;       // 구조체의 내용을 파일에 저장

		cout << endl                                            ;
		cout << "["                                            ;
		cout << std::to_string(mCurrentTime.year	) << "y-"                                            ;
		cout << std::to_string(mCurrentTime.month	) << "m-"                                            ;
		cout << std::to_string(mCurrentTime.day		) << "d]_[Current Time:"                                            ;
		cout << std::to_string(mCurrentTime.hour	) << ":"                                            ;
		cout << std::to_string(mCurrentTime.min		) << ":"                                            ;
		cout << std::to_string(mCurrentTime.sec		) << ""                                            ;
		cout << "]"                                            ;
		cout << endl                                            ;

		string time_for_record = "";
		time_for_record += "["                                            ;
		time_for_record += std::to_string(mCurrentTime.year	) ;
		time_for_record += "y-"                                            ;
		time_for_record += std::to_string(mCurrentTime.month	) ;
		time_for_record += "m-"                                            ;
		time_for_record += std::to_string(mCurrentTime.day		) ;
		time_for_record += "d]_[Current Time:"                                            ;
		time_for_record += std::to_string(mCurrentTime.hour	) ;
		time_for_record += ":"                                            ;
		time_for_record += std::to_string(mCurrentTime.min		) ;
		time_for_record += ":"                                            ;
		time_for_record += std::to_string(mCurrentTime.sec		) ;
		time_for_record += ""                                            ;
		time_for_record +="]"                                            ;
		//cout << "mROSStatusInfo.ROS_Latitude : " <<(double)mROSStatusInfo.ROS_Latitude << endl                                            ;
		//cout << "mROSStatusInfo.ROS_Longitude : " << (double)mROSStatusInfo.ROS_Longitude << endl                                            ;

		//cout << "mUSVModeCommand.Mode : " 	<<(int)mUSVModeCommand.Mode 									<< endl                                            ;
		//cout << "mUSVModeCommand.ModeDetail : " 	<<(int)mUSVModeCommand.ModeDetail 								<< endl                                            ;
		//cout << "mUSVModeCommand.NavigationStartRecordID : " 	<<(int)mUSVModeCommand.NavigationStartRecordID 					<< endl                                            ;
		//cout << "mUSVModeCommand.Emergency_Return_Latitude : " 	<<(double)mUSVModeCommand.Emergency_Return_Latitude 			<< endl                                            ;
		//cout << "mUSVModeCommand.Emergency_Return_Longitude : " 	<<(double)mUSVModeCommand.Emergency_Return_Longitude 			<< endl                                            ;

		//cout << "mMissionRecordInfo.MissionName : " << mMissionRecordInfo.MissionName						<< endl                                            ;																																																																																									
		//cout << "mMissionRecordInfo.LateralError : " << mMissionRecordInfo.LateralError						<< endl                                            ;																																																																																									
		//cout << "mMissionRecordInfo.PathRange : " << mMissionRecordInfo.PathRange							<< endl                                            ;																																																																																								
		//cout << "mMissionRecordInfo.MissionPointCount : " << mMissionRecordInfo.MissionPointCount					<< endl                                            ;																																																																																										
		//cout << "mMissionRecordInfo.Waypoint[0].RecordID : " << mMissionRecordInfo.Waypoint[0].RecordID				<< endl                                            ;																																								
		//cout << "mMissionRecordInfo.Waypoint[0].Velocity : " << mMissionRecordInfo.Waypoint[0].Velocity				<< endl                                            ;																																								
		//cout << "mMissionRecordInfo.Waypoint[0].Latitude : " << mMissionRecordInfo.Waypoint[0].Latitude				<< endl                                            ;																																								
		//cout << "mMissionRecordInfo.Waypoint[0].Longitude : " << mMissionRecordInfo.Waypoint[0].Longitude				<< endl                                            ;																																								
		//cout << "mMissionRecordInfo.Waypoint[0].EngineSelect : " << mMissionRecordInfo.Waypoint[0].EngineSelect			<< endl                                            ;																																									
		//cout << "mMissionRecordInfo.Waypoint[0].AuvLauncher	: " << mMissionRecordInfo.Waypoint[0].AuvLauncher			<< endl                                            ;																																									
		//cout << "mMissionRecordInfo.Waypoint[0].SonarLauncher : " << mMissionRecordInfo.Waypoint[0].SonarLauncher			<< endl                                            ;																																									
		//cout << "mMissionRecordInfo.Waypoint[0].AcousticCommLauncher : " << mMissionRecordInfo.Waypoint[0].AcousticCommLauncher	<< endl                                            ;																																											

		//cout << "mUSVStatusInfo" <<  endl                                            ;	
		//cout << "- mUSVStatusInfo.Mode : " << 	(int)mUSVStatusInfo.Mode						<< endl                                            ;																									
		//cout << "- mUSVStatusInfo.ModeDetail : " << 	(int)mUSVStatusInfo.ModeDetail				<< endl                                            ;																								
		//cout << "- mUSVStatusInfo.NavigationConnectFlag : " << 	(int)mUSVStatusInfo.NavigationConnectFlag	<< endl                                            ;																					
		//cout << "- mUSVStatusInfo.PlatformConnectFlag : " << 	(int)mUSVStatusInfo.PlatformConnectFlag		<< endl                                            ;																															
		//cout << "- mUSVStatusInfo.EoCamDevConnectFlag : " << 	(int)mUSVStatusInfo.EoCamDevConnectFlag		<< endl                                            ;																													
		//cout << "- mUSVStatusInfo.reserved1 : " << 	(int)mUSVStatusInfo.reserved1	<< endl                                            ;																											
		//cout << "- mUSVStatusInfo.reserved2 : " << 	(int)mUSVStatusInfo.reserved2				<< endl                                            ;

		cout << "mNavigationInfo.Latitude : "	<< mNavigationInfo.Latitude		<< endl                                            ;
		cout << "- mNavigationInfo.Longitude : "	<< mNavigationInfo.Longitude	<< endl                                            ;
		cout << "- mNavigationInfo.Heading : "	<< mNavigationInfo.Heading			<< endl                                            ;
		cout << "- mNavigationInfo.Velocity : "	<< mNavigationInfo.Velocity		<< endl                                            ;
		cout << "- mNavigationInfo.Roll : "		<< mNavigationInfo.Roll			<< endl                                            ;
		cout << "- mNavigationInfo.Pitch : "		<< mNavigationInfo.Pitch			<< endl                                            ;
		cout << "- mNavigationInfo.Yaw : "		<< mNavigationInfo.Yaw				<< endl                                            ;

		// cout << "mNavigationStatusInfo.EOCameraBi : "	<< (int)	mNavigationStatusInfo.EOCameraBit << endl                                            ;
		// cout << "mNavigationStatusInfo.RadarBit : "	<< (int)	mNavigationStatusInfo.RadarBit << endl                                            ;
		// cout << "mNavigationStatusInfo.LidarBit	: "	<< (int)	mNavigationStatusInfo.LidarBit << endl                                            ;
		// cout << "mNavigationStatusInfo.GPSBit : " << (int)	mNavigationStatusInfo.GPSBit << endl                                            ;
		// cout << "mNavigationStatusInfo.reserved	: "	<< (int)	mNavigationStatusInfo.reserved << endl                                            ;

		// cout << "mFlexTargetInfo.TargetCount : "	<< (int) mFlexTargetInfo.TargetCount 				<< endl                                            ;
		// cout << "mFlexTargetInfo.TargetInfo[0].Object_ID : " << (int)mFlexTargetInfo.TargetInfo[0].Object_ID 	<< endl                                            ;
		// cout << "mFlexTargetInfo.TargetInfo[0].Course : "	<< (int)mFlexTargetInfo.TargetInfo[0].Course 		<< endl                                            ;
		// cout << "mFlexTargetInfo.TargetInfo[0].Velocity : "	<< (int)mFlexTargetInfo.TargetInfo[0].Velocity 		<< endl                                            ;
		// cout << "mFlexTargetInfo.TargetInfo[0].Latitude : "	<< (double)mFlexTargetInfo.TargetInfo[0].Latitude 	<< endl                                            ;
		// cout << "mFlexTargetInfo.TargetInfo[0].Longitude : "	<< (double)mFlexTargetInfo.TargetInfo[0].Longitude 	<< endl                                            ;

		// cout << "(int) mRadarTargetInfo.TargetCount : "					<< (int) mRadarTargetInfo.TargetCount 				<< endl                                            ;
		// cout << "(int)mRadarTargetInfo.TargetInfo[0].Object_ID : " 		<< (int)mRadarTargetInfo.TargetInfo[0].Object_ID 	<< endl                                            ;
		// cout << "(int)mRadarTargetInfo.TargetInfo[0].Course : "			<< (int)mRadarTargetInfo.TargetInfo[0].Course 		<< endl                                            ;
		// cout << "(int)mRadarTargetInfo.TargetInfo[0].Velocity : "		<< (int)mRadarTargetInfo.TargetInfo[0].Velocity 		<< endl                                            ;
		// cout << "(double)mRadarTargetInfo.TargetInfo[0].Latitude : "	<< (double)mRadarTargetInfo.TargetInfo[0].Latitude 	<< endl                                            ;
		// cout << "(double)mRadarTargetInfo.TargetInfo[0].Longitude : "	<< (double)mRadarTargetInfo.TargetInfo[0].Longitude 	<< endl                                            ;

		// cout << "(int)mLidarTargetInfo.TargetCount : " 					<< (int) mLidarTargetInfo.TargetCount 					<< endl                                            ;
		// cout << "(int)mLidarTargetInfo.TargetInfo[0].Object_ID : " 		<< (int)mLidarTargetInfo.TargetInfo[0].Object_ID 		<< endl                                            ;
		// cout << "(int)mLidarTargetInfo.TargetInfo[0].Course : "			<< (int)mLidarTargetInfo.TargetInfo[0].Course 			<< endl                                            ;
		// cout << "(int)mLidarTargetInfo.TargetInfo[0].Velocity : "		<< (int)mLidarTargetInfo.TargetInfo[0].Velocity 		<< endl                                            ;
		// cout << "(double)mLidarTargetInfo.TargetInfo[0].Latitude : "	<< (double)mLidarTargetInfo.TargetInfo[0].Latitude 		<< endl                                            ;
		// cout << "(double)mLidarTargetInfo.TargetInfo[0].Longitude : "	<< (double)mLidarTargetInfo.TargetInfo[0].Longitude 	<< endl                                            ;

		// cout << "mPowerControl.AutoSailingSBC1_2 : " << (int) mPowerControl.AutoSailingSBC1_2	<< endl                                            ;	
		// cout << "mPowerControl.AutoSailingSBC3 : " << (int) mPowerControl.AutoSailingSBC3		<< endl                                            ;		
		// cout << "mPowerControl.GPS_INS : " << (int) mPowerControl.GPS_INS				<< endl                                            ;	
		// cout << "mPowerControl.EthernetSwitch : " << (int) mPowerControl.EthernetSwitch		<< endl                                            ;	
		// cout << "mPowerControl.DigitalCompass : " << (int) mPowerControl.DigitalCompass		<< endl                                            ;	
		// cout << "mPowerControl.CCTV : " << (int) mPowerControl.CCTV					<< endl                                            ;						
		// cout << "mPowerControl.Radar : " << (int) mPowerControl.Radar				<< endl                                            ;					
		// cout << "mPowerControl.LiDAR : " << (int) mPowerControl.LiDAR				<< endl                                            ;						
		// cout << "mPowerControl.EO : " << (int) mPowerControl.EO					<< endl                                            ;					
		// cout << "mPowerControl.PlatformControlSBC : " << (int) mPowerControl.PlatformControlSBC	<< endl                                            ;										
		// cout << "mPowerControl.MissionControlSBC : " << (int) mPowerControl.MissionControlSBC	<< endl                                            ;							
		// cout << "mPowerControl.MultibeamSonar : " << (int) mPowerControl.MultibeamSonar		<< endl                                            ;					
		// cout << "mPowerControl.AcousticComm1 : " << (int) mPowerControl.AcousticComm1		<< endl                                            ;								
		// cout << "mPowerControl.AcousticComm2 : " << (int) mPowerControl.AcousticComm2		<< endl                                            ;		

		// cout << "mPowerControlResult.AutoSailingSBC1_2 : " << (int) mPowerControlResult.AutoSailingSBC1_2		<< endl                                            ;	
		// cout << "mPowerControlResult.AutoSailingSBC3 : " << (int) mPowerControlResult.AutoSailingSBC3		<< endl                                            ;		
		// cout << "mPowerControlResult.GPS_INS : " << (int) mPowerControlResult.GPS_INS				<< endl                                            ;	
		// cout << "mPowerControlResult.EthernetSwitch	: " << (int) mPowerControlResult.EthernetSwitch			<< endl                                            ;	
		// cout << "mPowerControlResult.DigitalCompass	: " << (int) mPowerControlResult.DigitalCompass			<< endl                                            ;	
		// cout << "mPowerControlResult.CCTV : " << (int) mPowerControlResult.CCTV					<< endl                                            ;						
		// cout << "mPowerControlResult.Radar : " << (int) mPowerControlResult.Radar					<< endl                                            ;					
		// cout << "mPowerControlResult.LiDAR : " << (int) mPowerControlResult.LiDAR					<< endl                                            ;						
		// cout << "mPowerControlResult.EO : " << (int) mPowerControlResult.EO						<< endl                                            ;					
		// cout << "mPowerControlResult.PlatformControlSBC : " << (int) mPowerControlResult.PlatformControlSBC		<< endl                                            ;										
		// cout << "mPowerControlResult.MissionControlSBC : " << (int) mPowerControlResult.MissionControlSBC		<< endl                                            ;							
		// cout << "mPowerControlResult.MultibeamSonar : " << (int) mPowerControlResult.MultibeamSonar			<< endl                                            ;					
		// cout << "mPowerControlResult.AcousticComm1 : " << (int) mPowerControlResult.AcousticComm1			<< endl                                            ;								
		// cout << "mPowerControlResult.AcousticComm2 : " << (int) mPowerControlResult.AcousticComm2			<< endl                                            ;					

		cout << "mAutoNaviStatusInfo" << endl                                            ;
		cout << "- mAutoNaviStatusInfo.DestinationPathID : "<< mAutoNaviStatusInfo.DestinationPathID	<< endl                                            ;
		cout << "- mAutoNaviStatusInfo.AutoNaviStatus : "<< mAutoNaviStatusInfo.AutoNaviStatus		<< endl                                            ;
		cout << "- mAutoNaviStatusInfo.Heading : "	<< mAutoNaviStatusInfo.Heading				<< endl                                            ;
		cout << "- mAutoNaviStatusInfo.Velocity : "<< mAutoNaviStatusInfo.Velocity			<< endl                                            ;	
		cout << "- mAutoNaviStatusInfo.FailStatus : "<< mAutoNaviStatusInfo.FailStatus			<< endl                                            ;	

		// cout << "mUSVStatusInfo.Mode	: "<< (int) mUSVStatusInfo.Mode << endl		                                            ;
		// cout << "mUSVStatusInfo.ModeDetail : "<< (int) mUSVStatusInfo.ModeDetail << endl	                                            ;
		// cout << "mUSVStatusInfo.NavigationConnectFlag : "<< (int) mUSVStatusInfo.NavigationConnectFlag << endl		                                            ;
		// cout << "mUSVStatusInfo.PlatformConnectFlag : "<< (int) mUSVStatusInfo.PlatformConnectFlag << endl	                                            ;
		// cout << "mUSVStatusInfo.EoCamDevConnectFlag : "<< (int) mUSVStatusInfo.EoCamDevConnectFlag << endl		                                            ;



		AlgLoggingFile <<
		time_for_record													<< "," <<
		mROSStatusInfo.ROS_Latitude										<< "," <<
		mROSStatusInfo.ROS_Longitude									<< "," << 
		mUSVModeCommand.Mode											<< "," << 
		mUSVModeCommand.ModeDetail										<< "," << 
		mUSVModeCommand.AlgSelect										<< "," << 
		mUSVModeCommand.NavigationStartRecordID							<< "," << 
		mUSVModeCommand.Emergency_Return_Latitude						<< "," << 
		mUSVModeCommand.Emergency_Return_Longitude						<< "," <<
		mUSVModeCommand.reserved										<< "," << 
		mMissionRecordInfo.MissionName[0]								<< "," << 
		mMissionRecordInfo.LateralError									<< "," << 
		mMissionRecordInfo.PathRange									<< "," << 
		mMissionRecordInfo.MissionPointCount 							<< "," << 
		mMissionRecordInfo.Waypoint[0].RecordID							<< "," << 
		mMissionRecordInfo.Waypoint[0].Velocity							<< "," <<
		mMissionRecordInfo.Waypoint[0].Latitude							<< "," << 
		mMissionRecordInfo.Waypoint[0].Longitude						<< "," << 
		mMissionRecordInfo.Waypoint[0].EngineSelect						<< "," << 
		mMissionRecordInfo.Waypoint[0].AuvLauncher						<< "," << 
		mMissionRecordInfo.Waypoint[0].SonarLauncher					<< "," << 
		mMissionRecordInfo.Waypoint[0].AcousticCommLauncher				<< "," <<
		mMissionRecordInfoRes.MissionName[0]							<< "," << 
		mMissionRecordInfoRes.MissionPointCount							<< "," << 
		mMissionRecordInfoRes.Result									<< "," << 
		mEOCameraControlRes.EOMode										<< "," << 
		mEOCameraControlRes.PanControl									<< "," << 
		mEOCameraControlRes.PanSpeed									<< "," << 
		mEOCameraControlRes.TiltControl									<< "," <<
		mEOCameraControlRes.TiltSpeed									<< "," << 
		mEOCameraControlRes.PanLocationControl							<< "," << 
		mEOCameraControlRes.PanMode										<< "," << 
		mEOCameraControlRes.TiltLocationControl							<< "," << 
		mEOCameraControlRes.TiltMode									<< "," << 
		mEOCameraControlRes.LRFControl									<< "," << 
		mEOCameraControlRes.TrakingControl								<< "," <<
		mEOCameraControlRes.TrakingID									<< "," << 
		mEOCameraControlRes.ZoomMode									<< "," << 
		mEOCameraControlRes.FocusMode									<< "," << 
		mEOCameraControlRes.EONightMode									<< "," << 
		mEOCameraControlRes.D_ZoomControl								<< "," << 
		mEOCameraControlRes.DISControl									<< "," << 
		mIRCameraControlRes.D_ZoomControl								<< "," <<
		mIRCameraControlRes.NUCControl									<< "," << 
		mIRCameraControlRes.DISControl									<< "," << 
		mIRCameraControlRes.MIDEControl									<< "," << 
		mSaeronEOTrackingCommandRes.TrackingResult						<< "," << 
		// mPowerControl.AutoSailingSBC1_2									<< "," << 
		// mPowerControl.AutoSailingSBC3									<< "," << 
		// mPowerControl.GPS_INS											<< "," <<
		// mPowerControl.EthernetSwitch									<< "," << 
		// mPowerControl.DigitalCompass									<< "," << 
		// mPowerControl.CCTV												<< "," << 
		// mPowerControl.Radar												<< "," << 
		// mPowerControl.LiDAR												<< "," << 
		// mPowerControl.EO												<< "," << 
		// mPowerControl.PlatformControlSBC								<< "," <<
		// mPowerControl.MissionControlSBC									<< "," << 
		// mPowerControl.MultibeamSonaR									<< "," << 
		// mPowerControl.AcousticComm1										<< "," << 
		// mPowerControl.AcousticComm2										<< "," << 
		mEOCameraControlCommand.EOMode									<< "," << 
		mEOCameraControlCommand.PanControl								<< "," << 
		mEOCameraControlCommand.PanSpeed								<< "," <<
		mEOCameraControlCommand.TiltControl								<< "," << 
		mEOCameraControlCommand.TiltSpeed								<< "," << 
		mEOCameraControlCommand.PanLocationControl						<< "," << 
		mEOCameraControlCommand.PanMode									<< "," << 
		mEOCameraControlCommand.TiltLocationControl						<< "," << 
		mEOCameraControlCommand.TiltMode								<< "," << 
		mEOCameraControlCommand.LRFControl								<< "," <<
		mEOCameraControlCommand.TrakingControl							<< "," << 
		mEOCameraControlCommand.TrakingID								<< "," << 
		mEOCameraControlCommand.ZoomMode								<< "," << 
		mEOCameraControlCommand.FocusMode								<< "," << 
		mEOCameraControlCommand.EONightMode								<< "," << 
		mEOCameraControlCommand.D_ZoomControl							<< "," << 
		mEOCameraControlCommand.DISControl								<< "," <<
		mIRCameraControlCommand.D_ZoomControl							<< "," << 
		mIRCameraControlCommand.NUCControl								<< "," << 
		mIRCameraControlCommand.DISControl								<< "," << 
		mIRCameraControlCommand.MIDEControl								<< "," << 
		mSaeronEOTrackingCommand.TrackingCameraType						<< "," << 
		mSaeronEOTrackingCommand.PointX									<< "," << 
		mSaeronEOTrackingCommand.PointY									<< "," <<
		mSaeronEOTrackingCommand.Width									<< "," << 
		mSaeronEOTrackingCommand.Height									<< "," << 
		mSaeronEOTrackingCommand.TrackingMode							<< "," << 
		mSaeronEOTrackingCommand.TrackingAssist							<< "," << 
		mSaeronEOTrackingCommand.TrackingStartFlag						<< "," << 
		mPlatformControlCommand.ControlType                    			<< "," << 
		mPlatformControlCommand.RPMValue                       			<< "," <<
		mPlatformControlCommand.HandleAngle                    			<< "," << 
		mPlatformControlCommand.Heading                        			<< "," << 
		mPlatformControlCommand.Velocity                       			<< "," << 
		mPlatformControlCommand.Gear                           			<< "," << 
		mPlatformControlCommand.EngineSelect                   			<< "," << 
		mUSVStatusInfo.Mode                                    			<< "," << 
		mUSVStatusInfo.ModeDetail                              			<< "," <<
		mUSVStatusInfo.NavigationConnectFlag                   			<< "," << 
		mUSVStatusInfo.PlatformConnectFlag                     			<< "," << 
		mUSVStatusInfo.EoCamDevConnectFlag                     			<< "," << 
		mUSVStatusInfo.reserved1                               			<< "," << 
		mUSVStatusInfo.reserved2                               			<< "," << 
		mUSVStatusInfoConnectionFlag.NavigationConnectFlag  			<< "," << 
		mUSVStatusInfoConnectionFlag.PlatformConnectFlag    			<< "," <<
		mUSVStatusInfoConnectionFlag.EoCamDevConnectFlag    			<< "," << 
		mUSVStatusInfoConnectionFlag.reserved1              			<< "," << 
		mUSVStatusInfoConnectionFlag.reserved2              			<< "," << 
		mNavigationStatusInfo.EOCameraBit  								<< "," << 
		mNavigationStatusInfo.RadarBit     								<< "," << 
		mNavigationStatusInfo.LidarBit     								<< "," << 
		mNavigationStatusInfo.GPSBit       								<< "," <<
		mNavigationStatusInfo.reserved     								<< "," << 
		mNavigationInfo.Latitude           								<< "," << 
		mNavigationInfo.Longitude          								<< "," << 
		mNavigationInfo.Heading            								<< "," << 
		mNavigationInfo.Velocity           								<< "," << 
		mNavigationInfo.Roll               								<< "," << 
		mNavigationInfo.Pitch              								<< "," <<
		mNavigationInfo.Yaw                								<< "," << 
		mAutoNaviStatusInfo.DestinationPathID               			<< "," << 
		mAutoNaviStatusInfo.AutoNaviStatus                  			<< "," << 
		mAutoNaviStatusInfo.Heading                         			<< "," << 
		mAutoNaviStatusInfo.Velocity                        			<< "," << 
		mAutoNaviStatusInfo.FailStatus                      			<< "," << 
		mRadarTargetInfo.TargetCount                           		<< "," <<
		mRadarTargetInfo.TargetInfo[0].Object_ID	           			<< "," << 
		mRadarTargetInfo.TargetInfo[0].Course		           			<< "," << 
		mRadarTargetInfo.TargetInfo[0].Velocity	            			<< "," << 
		mRadarTargetInfo.TargetInfo[0].Latitude	            			<< "," << 
		mRadarTargetInfo.TargetInfo[0].Longitude	           			<< "," << 
		mLidarTargetInfo.TargetCount                           		<< "," << 
		mLidarTargetInfo.TargetInfo[0].Object_ID	           			<< "," <<
		mLidarTargetInfo.TargetInfo[0].Course		           			<< "," << 
		mLidarTargetInfo.TargetInfo[0].Velocity	            			<< "," << 
		mLidarTargetInfo.TargetInfo[0].Latitude	            			<< "," << 
		mLidarTargetInfo.TargetInfo[0].Longitude	           			<< "," << 
		mFlexTargetInfo.TargetCount                            		<< "," << 
		mFlexTargetInfo.TargetInfo[0].Object_ID	            			<< "," << 
		mFlexTargetInfo.TargetInfo[0].Course		           			<< "," <<
		mFlexTargetInfo.TargetInfo[0].Velocity	               			<< "," << 
		mFlexTargetInfo.TargetInfo[0].Latitude	               			<< "," << 
		mFlexTargetInfo.TargetInfo[0].Longitude	            			<< "," << 
		mPlatformControlState.ControlType                      		<< "," << 
		mPlatformControlState.RPMValue                         		<< "," << 
		mPlatformControlState.HandleAngle                      		<< "," <<
		mPlatformControlState.Heading                          		<< "," << 
		mPlatformControlState.Velocity                         		<< "," << 
		mPlatformControlState.Gear                             		<< "," << 
		mPlatformStatusInfo.BITState                           		<< "," << 
		mPlatformStatusInfo.FuelState                          		<< "," << 
		mPlatformStatusInfo.EngineStartStatus                  		<< "," << 
		mPlatformStatusInfo.EngineSelectFlag                   		<< "," <<
		// mPowerControlResult.AutoSailingSBC1_2                  		<< "," << 
		// mPowerControlResult.AutoSailingSBC3                    		<< "," << 
		// mPowerControlResult.GPS_INS                            		<< "," << 
		// mPowerControlResult.EthernetSwitch                     		<< "," << 
		// mPowerControlResult.DigitalCompass                     		<< "," << 
		// mPowerControlResult.CCTV                               		<< "," << 
		// mPowerControlResult.Radar                              		<< "," <<
		// mPowerControlResult.LiDAR                              		<< "," << 
		// mPowerControlResult.EO                                 		<< "," << 
		// mPowerControlResult.PlatformControlSBC                 		<< "," << 
		// mPowerControlResult.MissionControlSBC                  		<< "," << 
		// mPowerControlResult.MultibeamSonar                     		<< "," << 
		// mPowerControlResult.AcousticComm1                      		<< "," << 
		// mPowerControlResult.AcousticComm2                      		<< "," <<
		mAcousticCommInfo.EquipmentSelect                      		<< "," << 
		mAcousticCommInfo.AuvID                                		<< "," << 
		mAcousticCommInfo.Latitude                             		<< "," << 
		mAcousticCommInfo.Longitude                            		<< "," << 
		mAcousticCommInfo.Depth                                		<< "," << 
		mEOTargetInfo.TargetCount                              		<< "," << 
		mEOTargetInfo.mEOMemberInfo[0].Object_ID               		<< "," <<
		mEOTargetInfo.mEOMemberInfo[0].Course                  		<< "," << 
		mEOTargetInfo.mEOMemberInfo[0].Velocity                		<< "," << 
		mEOTargetInfo.mEOMemberInfo[0].Latitude                		<< "," << 
		mEOTargetInfo.mEOMemberInfo[0].Longitude               		<< "," << 
		mEOTargetInfo.mEOMemberInfo[0].BoundingBox_X_StartPoint		<< "," << 
		mEOTargetInfo.mEOMemberInfo[0].BoundingBox_Y_StartPoint		<< "," << 
		mEOTargetInfo.mEOMemberInfo[0].BoundingBox_X_Length    		<< "," <<
		mEOTargetInfo.mEOMemberInfo[0].BoundingBox_Y_Length    		<< "," << 

		"\n"                                            ;




	}


	return 0                                            ;
}