#include <stdio.h>
#include <string.h>

#include "def.h"

#include <coredef.h>
#include <struct.h>
#include <poslib.h>

const APP_MSG App_Msg = {
        "Demo",
        "Demo-App",
        "V220913",
        "VANSTONE",
        __DATE__ " " __TIME__,
        "",
        0,
        0,
        0,
        "00001001140616"
};


void MenuThread();


/*
*******************************Connect Wifi*******************************
*/


#define COMMPARAMFILE   "CommParamFile"
//struct COMMPARASTRUC G_CommPara;

void SaveCommParam(void) {
    u8 result;

    do {
        result = WriteFile_Api(COMMPARAMFILE, (u8 * ) & G_CommPara, 0, sizeof(struct _COMMPARASTRUC_));
    } while (result != 0);
}


/*
*******************************End Connect Wifi*******************************
*/

void InitSys(void) {

    int ret;
    unsigned char bp[32];

    // Turn on debug output to serial COM
    SetApiCoreLogLevel(5);

    // Load parameters
    initParam();

    //initializes device type
    initDeviceType();

    // Turn off WIFI and turn on 4G network
    NetModuleOper_Api(WIFI, 0);
    NetModuleOper_Api(GPRS, 1);


    // Network initialization
    net_init();

    // MQTT client initialization
    initMqttOs();


    memset(bp, 0, sizeof(bp));
    ret = sysReadBPVersion_lib(bp);
    MAINLOG_L1("Firmware Version == %d, version: %s", ret, bp);

    memset(bp, 0, sizeof(bp));
    ret = sysReadVerInfo_lib(4, bp);
    MAINLOG_L1("lib Version == %d, version: %s", ret, bp);
    MAINLOG_L1("APP Version == version: %s", App_Msg.Version);

    ret = fibo_thread_create(MenuThread, "mainMenu", 14 * 1024, NULL, 1);
    MAINLOG_L1("fibo_thread_create: %d", ret);

    //check if any app to update
    ret = checkAppUpdate();
    if (ret < 0)
        set_tms_download_flag(1);
}

int AppMain(int argc, char **argv) {
    int ret;
    int wif;
    int signal_lost_count;
    int mobile_network_registered;

    SystemInit_Api(argc, argv);

//	QRlogo();

    InitSys();

    signal_lost_count = 0;
    mobile_network_registered = 0;


    while (1) {

        // Check mobile network status
        ret = NetLinkCheck_Api(GPRS);
        MAINLOG_L1("*******************4G status:%d", ret);

        wif = NetLinkCheck_Api(WIFI);
        MAINLOG_L1("*******************WIFI status:%d", wif);


		if (ret == 2) {
			PlayMP3File("Insert sim.mp3");
			Delay_Api(60000);
//			SysPowerReBoot_Api();
		}
		else if (ret == 1) {
			if (signal_lost_count > 10) {
				Delay_Api(60000);
//				SysPowerReBoot_Api();
			}

			AppPlayTip("Mobile network registration in progress");

			Delay_Api(3000);
			signal_lost_count++;
			mobile_network_registered = 0;
			continue;
		}
		else {
			signal_lost_count = 0;

			if (mobile_network_registered == 0) {
				mobile_network_registered = 1;
				//AppPlayTip("Mobile network registered");
			}
		}

        mQTTMainThread();
        PlayMP3File("IoT_Server_down.mp3");
    }

    return 0;
}





