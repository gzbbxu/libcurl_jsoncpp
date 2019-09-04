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
	cout << "getDeviceUUid" <<endl;
	if (deviceUUid == "") {
		char mac[30] = { 0 };
		int i,j;
		get_local_mac(mac,"eth0");
		string strMac(mac);
		cout << "mac = "<<strMac<<endl;
		string strUUIDbuffer(CONSNT_UUID);
		if(strMac.size()>0){
			//成功获取到mac地址
			for(i=0,j=0;i<CONSNT_UUID.size()&& j<strMac.size();i++){
				char c =strUUIDbuffer[i];
				if(c!='-'){
					strUUIDbuffer[i] =strMac[j];
					j++;
				}
			}
		}
		deviceUUid = strUUIDbuffer;
		cout << "deviceUUID  " << deviceUUid<<endl;
	}
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

int DeviceUtil::get_local_mac(char *mac_addr,const char *eth_inf) {
	int sock_mac;

	struct ifreq ifr_mac;
	sock_mac = socket( AF_INET, SOCK_STREAM, 0);
	if (sock_mac == -1) {
		perror("create socket falise...mac/n");
	}

	memset(&ifr_mac, 0, sizeof(ifr_mac));
	strncpy(ifr_mac.ifr_name, eth_inf, sizeof(ifr_mac.ifr_name) - 1);

	if ((ioctl(sock_mac, SIOCGIFHWADDR, &ifr_mac)) < 0) {
		printf("mac ioctl error/n");
	}

	sprintf(mac_addr, "%02x%02x%02x%02x%02x%02x",
			(unsigned char) ifr_mac.ifr_hwaddr.sa_data[0],
			(unsigned char) ifr_mac.ifr_hwaddr.sa_data[1],
			(unsigned char) ifr_mac.ifr_hwaddr.sa_data[2],
			(unsigned char) ifr_mac.ifr_hwaddr.sa_data[3],
			(unsigned char) ifr_mac.ifr_hwaddr.sa_data[4],
			(unsigned char) ifr_mac.ifr_hwaddr.sa_data[5]);


	close(sock_mac);
}
// 获取本机ip
int DeviceUtil::get_local_ip(const char *eth_inf, char *ip) {
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

