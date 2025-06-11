#pragma once
/*

*/
#ifndef _DUTYDAO_H_
#define _DUTYDAO_H_
#include "BaseDAO.h"
#include "../domain/query/DutyQuery.h"
#include "../domain/do/DutyDO.h"
#include "../domain/do/DutyResultDO.h"

class DutyDAO:public BaseDAO {
private:
	inline std::string queryConditionBuilder(const DutyQuery::Wrapper& query, SqlParams& params);

public:
	// ͳ����������
	//uint64_t count(const DutyQuery::Wrapper& query);
	//ͨ��ʱ��β�ѯ����
	std::list<DutyResultDO> selectOneDay(const DutyQuery::Wrapper& query);
	//�޸�����
	int update(const DutyDO& obj);
	//��������
	uint64_t insert(const DutyDO& obj);
	//ɾ������
	int deleteOne(const DeleteDutyDO& obj);
	//��ѯֵ���
	std::list<ScheduleDO> selectSchedule(const DutyQuery::Wrapper& query);
};

#endif // !_DUTYDAO_H_