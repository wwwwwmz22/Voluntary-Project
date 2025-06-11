#pragma once
/*

*/
#ifndef _PERSONINFODAO_H_
#define _PERSONINFODAO_H_
#include "BaseDAO.h"
#include "../domain/do/PersonInfoDO.h"
#include "../domain/query/PersonInfoQuery.h"

class PersonInfoDAO:public BaseDAO{
private:
	inline std::string queryConditionBuilder(const PersonInfoQuery::Wrapper& query, SqlParams& params);

public:
	//通过学号查询个人信息
	PtrPersonInfoDO selectByIdAndPasword(const PersonInfoQuery::Wrapper& stuid);
	//修改数据
	int update(const PersonInfoDO& obj);
	//保存数据
	int insert(const PersonInfoDO& obj);

};

#endif // !_PERSONINFODAO_H_