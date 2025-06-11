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
	//��ѯ����
	DutyListDTO::Wrapper getInfo(const DutyQuery::Wrapper& query);
	//�޸���Ϣ
	bool updateData(const DutyDTO::Wrapper& dto);
	//������Ϣ
	bool saveData(oatpp::List<DutyDTO::Wrapper>& dtolist);
	//ɾ����Ϣ
	bool deleteData(const DeleteDutyDTO::Wrapper& dto);
	//��ѯֵ���
	ScheduleListDTO::Wrapper getSchedule(const DutyQuery::Wrapper& query);
};

#endif // !_DUTYSERVICE_H_