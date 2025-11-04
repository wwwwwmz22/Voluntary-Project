#pragma once
/*

*/
#ifndef _DUTYEXPORTMAPPER_H_
#define _DUTYEXPORTMAPPER_H_
#include "Mapper.h"
#include "../domain/do/DutyDO.h"
#include "../domain/do/DutyResultDO.h"

class DutyExportMapper :public Mapper<DutyExportDO> {
public:
	DutyExportDO mapper(ResultSet* resultSet) const override
	{
		DutyExportDO data;
		//data.setId(resultSet->getInt(1));
		data.setVoluntaryId(resultSet->getString("voluntary_id"));
		data.setName(resultSet->getString("name"));
		data.setDate(resultSet->getString("date"));
		data.setBeginTime(resultSet->getString("begin_time"));
		data.setEndTime(resultSet->getString("end_time"));
		data.setTotalTime(resultSet->getDouble("total_time"));
		return data;
	}

};

class PtrDutyExportMapper :public Mapper<PtrDutyExportDO> {
public:
	PtrDutyExportDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<DutyExportDO>();
		data->setVoluntaryId(resultSet->getString("voluntary_id"));
		data->setName(resultSet->getString("name"));
		data->setDate(resultSet->getString("date"));
		data->setBeginTime(resultSet->getString("begin_time"));
		data->setEndTime(resultSet->getString("end_time"));
		data->setTotalTime(resultSet->getDouble("total_time"));
		return data;
	}

};

#endif // !_DUTYEXPORTMAPPER_H_