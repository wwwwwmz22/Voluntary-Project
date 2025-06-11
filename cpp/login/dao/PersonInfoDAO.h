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
	//ͨ��ѧ�Ų�ѯ������Ϣ
	PtrPersonInfoDO selectByIdAndPasword(const PersonInfoQuery::Wrapper& stuid);
	//�޸�����
	int update(const PersonInfoDO& obj);
	//��������
	int insert(const PersonInfoDO& obj);

};

#endif // !_PERSONINFODAO_H_