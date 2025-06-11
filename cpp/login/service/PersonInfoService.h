#pragma once
#include "../domain/dto/PersonInfoDTO.h"
#include "../domain/query/PersonInfoQuery.h"
/*

*/
#ifndef _PERSONINFOSERVICE_H_
#define _PERSONINFOSERVICE_H_

class PersonInfoServer{
public:
	// 通过学号查询单个数据
	PersonInfoDTO::Wrapper getByIdAndPasword(const PersonInfoQuery::Wrapper& schoolid);
	//修改信息
	bool updateData(const PersonBaseInfoDTO::Wrapper& dto);
	//保存用户信息
	bool saveData(const PersonAllInfoDTO::Wrapper& dto);
};

#endif // !_PERSONINFOSERVICE_H_