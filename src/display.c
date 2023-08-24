/*
 * display.c
 *
 *  Created on: Oct 25, 2021
 *      Author: Administrator
 */

#include <string.h>

#include "def.h"
#include <coredef.h>
#include <struct.h>
#include <poslib.h>



#define QRBMP "QRBMP.bmp"
#define LOGOBMP "LOGO.bmp"
#define KHQRBMP "/ext/3-0103.jpg"
#define USDQRBMP "/ext/USD_QR.bmp"

void QRlogo() {
    int ret;
//	ret = QREncodeString("www.baidu.com", 3, 3, LOGOBMP, 7);
//	TipAndWaitEx_Api("QREncodeString:%d", ret);
    ScrCls_Api();
    ScrDispImage_Api(LOGOBMP, 18, 38);
    WaitAnyKey_Api(60);
}


void QRCodeDisp() {
#ifdef __DISPLAY__
    u8 OutBuf[128];
    int ret;

    memset(OutBuf, 0, sizeof(OutBuf));
    strcpy(OutBuf, "https://www.acledabank.com.kh/");
    ret = QREncodeString(OutBuf, 3, 3, QRBMP, 7.0);
    TipAndWaitEx_Api("Welcome");

    ScrDispImage_Api(QRBMP, 5, 30);
    WaitAnyKey_Api(60);
#endif
}


void DispMainFace(void) {
//	playMp3Test();
    ScrCls_Api();
    LedLightOn_Api(0x01);
    ScrBackLight_Api(0xFFFF);

    CustomizedQR();

//	ScrDisp_Api(LINE4, 0, "Welcome to use", CDISP);
//	ScrDisp_Api(LINE5, 0, "Aisino Q161", CDISP);
}


int WaitEvent(void) {
    u8 Key;
    int TimerId;

    TimerId = TimerSet_Api();
    while (1) {
        if (TimerCheck_Api(TimerId, 30 * 1000) == 1) {
            SysPowerStand_Api();
            return 0xfe;
        }
        Key = GetKey_Api();
        if (Key != 0)
            return Key;
    }

    return 0;
}

#define        TIMEOUT            -2

int ShowMenuItem(char *Title, const char *menu[], u8 ucLines, u8 ucStartKey, u8 ucEndKey, int IsShowX, u8 ucTimeOut) {
    u8 IsShowTitle, cur_screen, OneScreenLines, Cur_Line, i, t;
    int nkey;
    char dispbuf[50];

    memset(dispbuf, 0, sizeof(dispbuf));

    if (Title != NULL) {
        IsShowTitle = 1;
        OneScreenLines = 12;
    } else {
        IsShowTitle = 0;
        OneScreenLines = 13;
    }
    IsShowX -= 1;
    cur_screen = 0;
    while (1) {
        ScrClsRam_Api();

        if (IsShowTitle)
            ScrDisp_Api(LINE1, 0, Title, CDISP);
        Cur_Line = LINE1 + IsShowTitle;
        for (i = 0; i < OneScreenLines; i++) {
            t = i + cur_screen * OneScreenLines;
            if (t >= ucLines || menu[t] == NULL)//
            {
                break;
            }
            memset(dispbuf, 0, sizeof(dispbuf));
            strcpy(dispbuf, menu[t]);
            ScrDispRam_Api(Cur_Line++, 0, dispbuf, FDISP);
        }
        ScrBrush_Api();
        MAINLOG_L1("after ScrBrush_Api");
        nkey = WaitAnyKey_Api(ucTimeOut);
        MAINLOG_L1("WaitAnyKey_Api aa:%d", nkey);
        switch (nkey) {
            case ESC:
            case TIMEOUT:
                return nkey;
            default:
                if ((nkey >= ucStartKey) && (nkey <= ucEndKey))
                    return nkey;
                break;
        }
    };
}

void MenuThread() {
    int Result = 0;
    while (1) {
        // When we don use DispMainFace(); it, when we click btn ESC it will not work(when we want to exit menu enter)
        DispMainFace();

        Result = WaitEvent();
        if (Result == 0xfe)
            continue;
        if (Result != 0) {
            switch (Result) {
                case ENTER:
//                    SelectMainMenu();
                    break;
                default:
                    break;
            }
        }
    }
}

int CustomizedQR() {
    int ret = 1;
    int key = 1;

    ScrCls_Api();
//	playMp3Test();
//	PlayMp3ListTest();

    ret = ScrDispImage_Api(KHQRBMP, 0, 0);
//    ScrFontSetEx_Api(2);
    ScrDisp_Api(10, 0, "City Bus State-07", CDISP);
    ScrDisp_Api(11, 0, "3-0103", CDISP);

    while (1) {
        key = WaitAnyKey_Api(60);
        switch (key) {
            case PGUP:
                if (G_sys_param.sound_level >= 5)

//                    AppPlayTip("This is the maximum volume");
                	PlayMP3File("Max_sound.mp3");
                else {
                    G_sys_param.sound_level++;
                    ttsSetVolume_lib(G_sys_param.sound_level);
//                    AppPlayTip("Increased");
                    PlayMP3File("Increase.mp3");
                    saveParam();
                }
                continue;
            case PGDWON:
                if (G_sys_param.sound_level <= 1)
//                    AppPlayTip("This is the minimum volume");
                	PlayMP3File("Min_sound.mp3");
                else {
                    G_sys_param.sound_level--;
                    ttsSetVolume_lib(G_sys_param.sound_level);
//                    AppPlayTip("Decreased");
                    PlayMP3File("Decrease.mp3");
                    saveParam();
                }
                continue;
            case ESC:
                return 0;
            default:
                break;
        }
    }

    return 0;
}

int CustomizedQR2() {
    int ret = 1;
    int key = 1;

    ScrCls_Api();

    ret = ScrDispImage_Api(USDQRBMP, 0, 0);

    while (1) {
        key = WaitAnyKey_Api(60);
        switch (key) {
            case PGUP:
                if (G_sys_param.sound_level >= 5)
//                    AppPlayTip("This is the maximum volume");
                	PlayMP3File("Max_sound_adr.mp3");
                else {
                    G_sys_param.sound_level++;
//                    AppPlayTip("Increased");
                    PlayMP3File("Increase_adr.mp3");
                    saveParam();
                }
                continue;
            case PGDWON:
                if (G_sys_param.sound_level <= 1)
//                    AppPlayTip("This is the minimum volume");
                	PlayMP3File("Min_sound_adr.mp3");
                else {
                    G_sys_param.sound_level--;
//                    AppPlayTip("Decreased");
                    PlayMP3File("Decrease_adr.mp3");
                    saveParam();
                }
                continue;
            case ESC:
                return 0;
            default:
                break;
        }
    }
    return 0;
}


void SelectMainMenu(void) {
    int nSelcItem = 1, ret;

    char *pszTitle = "Menu";
    const char *pszItems[] = {
            "1.Amount Display",
            "2.Switch QR to Khmer",
            "3.Switch QR to USD"
    };
    while (1) {
        nSelcItem = ShowMenuItem(pszTitle, pszItems, sizeof(pszItems) / sizeof(char *), DIGITAL1, DIGITAL3, 0, 60);
        MAINLOG_L1("ShowMenuItem = %d  %d  %d %d", nSelcItem, DIGITAL1, DIGITAL2, DIGITAL3);
        switch (nSelcItem) {
            case DIGITAL1:
#ifdef __DISPLAY__
                secscrOpen_lib();
                secscrCls_lib();
                secscrSetAttrib_lib(4,1);
                secscrPrint_lib(0, 0, 0, "114.00");
                WaitAnyKey_Api(60);
#endif
                break;
            case DIGITAL2:
//			PlayMP3File("Success_01.mp3");
//			PlayMp3ListTest();
                CustomizedQR();
                break;
            case DIGITAL3:
//			PlayMP3File("Fail_01.mp3");
                CustomizedQR2();
                break;

//		case DIGITAL2:
//			ret = wirelessPdpWriteParam_lib(NULL, NULL, NULL);
//			MAINLOG_L1("wirelessPdpWriteParam_lib NULL = %d", ret);
//			SysPowerReBoot_Api();
//			break;
//		case DIGITAL3:
//			ret = wirelessPdpWriteParam_lib("M2MISAFE", "", "");
//			MAINLOG_L1("wirelessPdpWriteParam_lib M2MISAFE = %d", ret);
//			SysPowerReBoot_Api();
//			break ;

            case ESC:
                return;

            default:
                break;
        }
    }
}

