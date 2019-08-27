/*
 * FaceDao.cpp
 *
 *  Created on: 2019年8月23日
 *   人脸dao 数据库 操作
 *      Author: zhouke
 */

#include "../include/FaceDao.h"

FaceDao::FaceDao() {

}
string FaceDao::getOnlineDbVersion() {
	//todo
	return "0";
}
void FaceDao::resetOnlineDb() {
	//	todo 清理在线数据库
	//  todo 本地版本号置为 0
}

void FaceDao::deleteOnLineById(string uuid){

}

void FaceDao::setOnLineDbVersion(string version){

}


FaceDao::~FaceDao() {
	// TODO Auto-generated destructor stub
}

