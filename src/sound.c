/*
 * sound.c
 *
 *  Created on: 2021Äê10ÔÂ15ÈÕ
 *      Author: vanstone
 */
#include "def.h"

#include <coredef.h>
#include <struct.h>
#include <poslib.h>

void AppPlayTip(char *tip)
{
	PlaySound_Api((unsigned char *)tip, G_sys_param.sound_level, 9);
}

void PlayMP3File(char *audioFileName){
	int ret;
	char filePath[16];

	memset(filePath,0,sizeof(filePath));
//	sprintf(filePath,"/app/ufs/%s",audioFileName);
	sprintf(filePath,"/ext/%s",audioFileName);
	MAINLOG_L1("MP3 Path is %s",filePath);

	while(1){
//		ttsSetVolume_lib(5);
		ret = audioFilePlayPath_lib(filePath);

		if (ret==0){
			MAINLOG_L1("test==0");
			break;
		}
		else if (ret==-1) {
			MAINLOG_L1("Play failed, please check if the file is damaged");
			break;
		}
		else if (ret==-2) {
			MAINLOG_L1("File is not present");
//			audioFilePlayPath_lib("/ext/Success_01.mp3");
			break;
		}
		else if (ret==-3) {
			MAINLOG_L1("TSS is occupied");
		}
	}


}
void playMp3Test()
{
	audioFilePlayPath_lib("/ext/Success_01.mp3");
}

void PlayMp3ListTest()
{
	int ret;

	unsigned char fnametmp[4][128];
	memset(fnametmp, 0, sizeof(fnametmp));
	strcpy(fnametmp[0], "/ext/Fail_01.mp3");
//	strcpy(fnametmp[1], "/ext/bb.mp3");
//	strcpy(fnametmp[2], "/ext/cc.mp3");
//	strcpy(fnametmp[3], "/ext/dd.mp3");
//	ret = audioPlayList_lib(fnametmp,4);
	ret = audioFilePlayPath_lib("/ext/Success_01.mp3");
	MAINLOG_L1("audioPlayList_lib:%d",ret);
}

