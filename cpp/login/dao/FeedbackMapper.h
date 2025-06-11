#pragma once
#include "../domain/do/FeedbackDO.h"
/*

*/
#ifndef _FEEDBACKMAPPER_H_
#define _FEEDBACKMAPPER_H_

class FeedbackMapper:Mapper<FeedbackDO>{
public:
	FeedbackDO mapper(ResultSet* resultSet) const override
	{
		FeedbackDO data;
		data.setSchoolId(resultSet->getString(1));
		data.setpName(resultSet->getString(2));
		data.setQdate(resultSet->getString(3));
		data.setisClean(resultSet->getString(4));
		data.setisNoise(resultSet->getString(5));
		data.setisFood(resultSet->getString(6));
		data.setisSeat(resultSet->getString(7));
		data.setisOther(resultSet->getString(8));
		return data;
	}

};

class PtrFeedbackMapper :Mapper<PtrFeedbackDO> {
public:
	PtrFeedbackDO mapper(ResultSet* resultSet) const override
	{
		PtrFeedbackDO data;
		data->setSchoolId(resultSet->getString(1));
		data->setpName(resultSet->getString(2));
		data->setQdate(resultSet->getString(3));
		data->setisNoise(resultSet->getString(5));
		data->setisFood(resultSet->getString(6));
		data->setisSeat(resultSet->getString(7));
		data->setisOther(resultSet->getString(8));
		return data;
	}

};

#endif // !_FEEDBACKMAPPER_H_