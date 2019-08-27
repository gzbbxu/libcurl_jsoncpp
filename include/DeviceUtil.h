/*
 * DeviceUtil.h
 *
 *  Created on: 2019年8月23日
 *      Author: zhouke
 */

#ifndef DEVICEUTIL_H_
#define DEVICEUTIL_H_
#include <iostream>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include<string.h>
#include <unistd.h>
#include <stdio.h>
#define IP_SIZE 16
using namespace std;
class DeviceUtil {
public:
	static const string CONSNT_UUID;
	static string deviceUUid ;
	DeviceUtil();
	static string  getDeviceUUid();
	static string getDeviceName();
	static string getDeviceType();
	static  int get_local_ip(const char *eth_inf, char *ip);
	virtual ~DeviceUtil();
};

#endif /* DEVICEUTIL_H_ */
