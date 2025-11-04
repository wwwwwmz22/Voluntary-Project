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
		data.setSchoolId(resultSet->getString("school_id"));
		data.setQdate(resultSet->getString("qdate"));
		data.setBeginTime(resultSet->getString("begin_time"));
		data.setEndTime(resultSet->getString("end_time"));
		//data.setCnt(resultSet->getInt("cnt"));
		data.setSignIn(resultSet->getInt("sign_in"));
		data.setSignOut(resultSet->getInt("sign_out"));
		return data;
	}

};

class PtrDutyMapper :public Mapper<PtrDutyResultDO> {
public:
	PtrDutyResultDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<DutyResultDO>();
		//data->setId(resultSet->getInt(1));
		data->setSchoolId(resultSet->getString("school_id"));
		data->setQdate(resultSet->getString("qdate"));
		data->setBeginTime(resultSet->getString("begin_time"));
		data->setEndTime(resultSet->getString("end_time"));
		//data->setCnt(resultSet->getInt("cnt"));
		data->setSignIn(resultSet->getInt("sign_in"));
		data->setSignOut(resultSet->getInt("sign_out"));
		return data;
	}

};

#endif // !_DUTYMAPPER_H_