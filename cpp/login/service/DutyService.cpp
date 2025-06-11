#include "DutyService.h"
#include "../domain/query/DutyQuery.h"
#include "../dao/DutyDAO.h"
#include "../domain/do/DutyResultDO.h"
#include "../Macros.h"




DutyListDTO::Wrapper DutyService::getInfo(const DutyQuery::Wrapper& query)
{
	auto result = DutyListDTO::createShared();
	result->list = oatpp::List<DutyCountDTO::Wrapper>::createShared();

	DutyDAO dao;
	std::list<DutyResultDO> res = dao.selectOneDay(query);


	for (auto sub : res) {
		auto dto = DutyCountDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, cnt, Cnt, qdate, Qdate, begin_time, BeginTime, end_time, EndTime);
		result->list->push_back(dto);
	}
	return result;
}

bool DutyService::updateData(const DutyDTO::Wrapper& dto)
{
	DutyDO data;
	ZO_STAR_DOMAIN_DTO_TO_DO(data, dto, SchoolId, school_id, Qdate, qdate, BeginTime, begin_time, EndTime, end_time, SignIn, sign_in, SignOut, sign_out);
	DutyDAO dao;
	return dao.update(data) == 1;
}

//bool DutyService::saveData(const AddDutyDTO::Wrapper& dtolist)
//{
//	DutyDO data;
//	ZO_STAR_DOMAIN_DTO_TO_DO(data, dto, SchoolId, school_id, Qdate, qdate, BeginTime, begin_time, EndTime, end_time, SignIn, sign_in, SignOut, sign_out);
//	DutyDAO dao;
//	return dao.insert(data) == 1;
//}

bool DutyService::saveData(oatpp::List<DutyDTO::Wrapper>& dtolist)
{
	DutyDAO dao;
	bool flag = true;
	for (DutyDTO::Wrapper& dto : (*dtolist) ) {
		DutyDO data;
		ZO_STAR_DOMAIN_DTO_TO_DO(data, dto, SchoolId, school_id, Qdate, qdate, BeginTime, begin_time, EndTime, end_time, SignIn, sign_in, SignOut, sign_out);
		bool subres= dao.insert(data);
		if (!subres) {
			OATPP_LOGE("DutyService", "Insert failed for school_id:%s qdate:%s begin_time:%s, end_time:%s", dto->school_id, dto->qdate, dto->begin_time, dto->end_time);
		}
		
		flag &= subres;
	}
	return flag;
}

bool DutyService::deleteData(const DeleteDutyDTO::Wrapper& dto)
{
	DeleteDutyDO data;
	ZO_STAR_DOMAIN_DTO_TO_DO(data, dto, SchoolId, school_id, Qdate, qdate, BeginTime, begin_time, EndTime, end_time);
	DutyDAO dao;
	return dao.deleteOne(data) == 1;
}

ScheduleListDTO::Wrapper DutyService::getSchedule(const DutyQuery::Wrapper& query)
{
	auto result = ScheduleListDTO::createShared();
	result->list = oatpp::List<ScheduleDTO::Wrapper>::createShared();

	DutyDAO dao;
	std::list<ScheduleDO> res = dao.selectSchedule(query);


	for (auto sub : res) {
		auto dto = ScheduleDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, pname_list, pNamelist, qdate, Qdate, begin_time, BeginTime, end_time, EndTime);
		result->list->push_back(dto);
	}
	return result;
}
