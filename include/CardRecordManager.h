/*
 * CardRecordManager.h
 *
 *  Created on: 2019年8月23日
 *      Author: zhouke
 */

#ifndef CARDRECORDMANAGER_H_
#define CARDRECORDMANAGER_H_
#include "modules.h"
#include "DeviceUtil.h"
using namespace modules;
namespace basemodule {

class CardRecordManager {
public:
	CardRecordManager();
	virtual ~CardRecordManager();
	CardRecordData * cardRecordData;
};

} /* namespace basemodule */

#endif /* CARDRECORDMANAGER_H_ */
