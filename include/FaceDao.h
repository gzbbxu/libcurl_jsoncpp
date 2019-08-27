/*
 * FaceDao.h
 *
 *  Created on: 2019年8月23日
 *      Author: zhouke
 */

#ifndef FACEDAO_H_
#define FACEDAO_H_
#include <iostream>
#include <string>
using namespace std;
class FaceDao {
public:
	FaceDao();
	/**
	 * 获取当前数线上据库版本号 作为同步人脸传参
	 */
	string getOnlineDbVersion();
	/**
	 * 下发人脸数据库
	 */
	void disposeFaceToDb();
	/**
	 * 清理数据库之后，重设线上据库版本号为0
	 */
	void resetOnlineDb();
	/**
	 * 根据id 删除 数据
	 * @uuid 人脸在数据库中 唯一标志
	 */
	void deleteOnLineById(string uuid);

	/**
	 * 设置数线上据库版本号
	 * @version 同步完成后，设置为服务器版本号
	 */
	void setOnLineDbVersion(string version);

	virtual ~FaceDao();
};

#endif /* FACEDAO_H_ */
