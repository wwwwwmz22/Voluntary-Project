#pragma once
/*

*/
#ifndef _SCHEDULEMAPPER_H_
#define _SCHEDULEMAPPER_H_

#include "Mapper.h"
#include "../domain/do/DutyDO.h"


class ScheduleMapper :public Mapper<ScheduleDO> {
public:
	ScheduleDO mapper(ResultSet* resultSet) const override
	{
		ScheduleDO data;
		data.setQdate(resultSet->getString("qdate"));
		data.setBeginTime(resultSet->getString("begin_time"));
		data.setEndTime(resultSet->getString("end_time"));
		data.setpNamelist(resultSet->getString("pname_list"));
		return data;
	}

};

class PtrScheduleMapper :public Mapper<PtrScheduleDO> {
public:
	PtrScheduleDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<ScheduleDO>();
		data->setQdate(resultSet->getString("qdate"));
		data->setBeginTime(resultSet->getString("begin_time"));
		data->setEndTime(resultSet->getString("end_time"));
		data->setpNamelist(resultSet->getString("pname_list"));
		return data;
	}

};


#endif // !_SCHEDULEMAPPER_H_