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
	//查询一个人数据
	DutyListDTO::Wrapper getOneInfo(const DutyQuery::Wrapper& query);
	//修改信息
	bool updateData(const DutyDTO::Wrapper& dto);
	//增加信息
	DutyInsertResultDTO::Wrapper saveData(oatpp::List<DutyDTO::Wrapper>& dtolist);
	//删除信息
	bool deleteData(const DeleteDutyDTO::Wrapper& dto);
	//查询值班表
	ScheduleListDTO::Wrapper getSchedule(const DutyQuery::Wrapper& query);
	//导出表
	DutyExportListDTO::Wrapper exportDuty(const DutyExportQuery::Wrapper& query);
};

#endif // !_DUTYSERVICE_H_