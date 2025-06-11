#pragma once

/*

*/
#ifndef _DUTYSERVICE_H_
#define _DUTYSERVICE_H_
#include "../domain/dto/DutyDTO.h"
#include "../domain/query/DutyQuery.h"
#include "../domain/dto/ScheduleDTO.h"

class DutyService{
public:
	//查询数据
	DutyListDTO::Wrapper getInfo(const DutyQuery::Wrapper& query);
	//修改信息
	bool updateData(const DutyDTO::Wrapper& dto);
	//增加信息
	bool saveData(oatpp::List<DutyDTO::Wrapper>& dtolist);
	//删除信息
	bool deleteData(const DeleteDutyDTO::Wrapper& dto);
	//查询值班表
	ScheduleListDTO::Wrapper getSchedule(const DutyQuery::Wrapper& query);
};

#endif // !_DUTYSERVICE_H_