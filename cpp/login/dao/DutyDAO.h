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
	// 统计数据条数
	//uint64_t count(const DutyQuery::Wrapper& query);
	//通过时间段查询人数
	std::list<DutyResultDO> selectOneDay(const DutyQuery::Wrapper& query);
	//修改数据
	int update(const DutyDO& obj);
	//保存数据
	uint64_t insert(const DutyDO& obj);
	//删除数据
	int deleteOne(const DeleteDutyDO& obj);
	//查询值班表
	std::list<ScheduleDO> selectSchedule(const DutyQuery::Wrapper& query);
};

#endif // !_DUTYDAO_H_