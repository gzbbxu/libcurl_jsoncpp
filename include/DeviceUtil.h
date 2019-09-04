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
	/**
	 * 获取设备唯一标志
	 * 当前采用默认uuid 和 mac 地址组合生成
	 */
	static string  getDeviceUUid();
	static string getDeviceName();
	static string getDeviceType();
	/**
	 * 获取指定网口的ip
	 * @param eth_inf 指定网口名称
	 * @ip 得到ip地址
	 */
	static  int get_local_ip(const char *eth_inf, /*out*/char *ip);
	/**
	 * 获取mac 地址
	 */
	static int get_local_mac(char * ma,const char *eth_inf);
	virtual ~DeviceUtil();
};

#endif /* DEVICEUTIL_H_ */
