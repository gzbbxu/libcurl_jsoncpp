/*
 * DeviceUtil.cpp
 *
 *  Created on: 2019年8月23日
 *      Author: zhouke
 */

#include "../include/DeviceUtil.h"
const string DeviceUtil::CONSNT_UUID = "7e283ebd-d501-45fc-b512-d13e557f14f9";
string DeviceUtil::deviceUUid = "";
DeviceUtil::DeviceUtil() {

}
string DeviceUtil::getDeviceUUid() {
	// todo open /sys/class/dmi/id/board_serial
	return CONSNT_UUID;
}
string DeviceUtil::getDeviceName() {
	//todo 设备名称
	return "linux ubuntu";
}
string DeviceUtil::getDeviceType() {
	//todo 设备类型
	return "linux ubuntu";
}

// 获取本机ip
int DeviceUtil:: get_local_ip(const char *eth_inf, char *ip) {
	int sd;
	struct sockaddr_in sin;
	struct ifreq ifr;

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == sd) {
		printf("socket error: %s\n", strerror(errno));
		return -1;
	}

	strncpy(ifr.ifr_name, eth_inf, IFNAMSIZ);
	ifr.ifr_name[IFNAMSIZ - 1] = 0;

// if error: No such device
	if (ioctl(sd, SIOCGIFADDR, &ifr) < 0) {
		printf("ioctl error: %s\n", strerror(errno));
		close(sd);
		return -1;
	}

	memcpy(&sin, &ifr.ifr_addr, sizeof(sin));
	snprintf(ip, IP_SIZE, "%s", inet_ntoa(sin.sin_addr));

	close(sd);
	return 0;
}
DeviceUtil::~DeviceUtil() {

}

