#pragma once
/*

*/
#ifndef _DUTYMAPPER_H_
#define _DUTYMAPPER_H_
#include "Mapper.h"
#include "../domain/do/DutyDO.h"
#include "../domain/do/DutyResultDO.h"

class DutyMapper:public Mapper<DutyResultDO>{
public:
	DutyResultDO mapper(ResultSet* resultSet) const override
	{
		DutyResultDO data;
		//data.setId(resultSet->getInt(1));
		//data.setSchoolId(resultSet->getString(2));
		data.setQdate(resultSet->getString("qdate"));
		data.setBeginTime(resultSet->getString("begin_time"));
		data.setEndTime(resultSet->getString("end_time"));
		data.setCnt(resultSet->getInt("cnt"));
		//data.setSignIn(resultSet->getInt(6));
		//data.setSignOut(resultSet->getInt(7));
		return data;
	}

};

class PtrDutyMapper :public Mapper<PtrDutyResultDO> {
public:
	PtrDutyResultDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<DutyResultDO>();
		//data->setId(resultSet->getInt(1));
		//data->setSchoolId(resultSet->getString(2));
		data->setQdate(resultSet->getString("qdate"));
		data->setBeginTime(resultSet->getString("begin_time"));
		data->setEndTime(resultSet->getString("end_time"));
		data->setCnt(resultSet->getInt("cnt"));
		//data->setSignIn(resultSet->getInt(6));
		//data->setSignOut(resultSet->getInt(7));
		return data;
	}

};

#endif // !_DUTYMAPPER_H_