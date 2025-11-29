#pragma once
/*

*/
#ifndef _PERSONINFOMAPPER_H_
#define _PERSONINFOMAPPER_H_

#include "Mapper.h"
#include "../domain/do/PersonInfoDO.h"

class PersonInfoMapper:public Mapper<PersonInfoDO>{

public:
	PersonInfoDO mapper(ResultSet* resultSet) const override
	{
		PersonInfoDO data;
		data.setSchoolId(resultSet->getString(3));
		data.setPasword(resultSet->getString(4));
		data.setpName(resultSet->getString(2));
		data.setPhoneNumber(resultSet->getString(8));
		data.setVoluntaryId(resultSet->getString(6));
		data.setPoliticalStatus(resultSet->getString(7));
		data.setVoluntaryTime(resultSet->getUInt64(9));
		data.setCollege(resultSet->getString(5));
		data.setGender(resultSet->getString(10));
		data.setGrade(resultSet->getUInt64(11));
		data.setIdentity(resultSet->getString(12));
		data.setEduBackground(resultSet->getString(13));
		data.setScore(resultSet->getUInt64(14));
		data.setDorm(resultSet->getString(15));
		data.setRoomid(resultSet->getString(16));
		return data;
	}

};

class PtrPersonInfoMapper :Mapper<PtrPersonInfoDO> {
public:
	PtrPersonInfoDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<PersonInfoDO>();
		data->setSchoolId(resultSet->getString(3));
		data->setPasword(resultSet->getString(4));
		data->setpName(resultSet->getString(2));
		data->setPhoneNumber(resultSet->getString(8));
		data->setVoluntaryId(resultSet->getString(6));
		data->setPoliticalStatus(resultSet->getString(7));
		data->setVoluntaryTime(resultSet->getUInt64(9));
		data->setCollege(resultSet->getString(5));
		data->setGender(resultSet->getString(10));
		data->setGrade(resultSet->getUInt64(11));
		data->setIdentity(resultSet->getString(12));
		data->setEduBackground(resultSet->getString(13));
		data->setScore(resultSet->getUInt64(14));
		data->setDorm(resultSet->getString(15));
		data->setRoomid(resultSet->getString(16));
		return data;
	}

};

#endif // !_PERSONINFOMAPPER_H_