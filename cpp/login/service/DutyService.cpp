#include "DutyService.h"
#include "../domain/query/DutyQuery.h"
#include "../dao/DutyDAO.h"
#include "../domain/do/DutyResultDO.h"
#include "../Macros.h"




DutyListDTO::Wrapper DutyService::getOneInfo(const DutyQuery::Wrapper& query)
{
	auto result = DutyListDTO::createShared();
	result->list = oatpp::List<DutyCountDTO::Wrapper>::createShared();

	DutyDAO dao;
	std::list<DutyResultDO> res = dao.selectOneDayById(query);


	for (auto sub : res) {
		auto dto = DutyCountDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub,school_id,SchoolId, qdate, Qdate, begin_time, BeginTime, end_time, EndTime,sign_in,SignIn,sign_out,SignOut);
		result->list->push_back(dto);
	}
	return result;
}

DutyListDTO::Wrapper DutyService::getOneDayInfo(const DutyOneDayQuery::Wrapper& query)
{
	auto result = DutyListDTO::createShared();
	result->list = oatpp::List<DutyCountDTO::Wrapper>::createShared();

	DutyDAO dao;
	std::list<DutyResultDO> res = dao.selectOneDay(query);


	for (auto sub : res) {
		auto dto = DutyCountDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, school_id, SchoolId, qdate, Qdate, begin_time, BeginTime, end_time, EndTime, sign_in, SignIn, sign_out, SignOut);
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


DutyInsertResultDTO::Wrapper DutyService::saveData(oatpp::List<DutyDTO::Wrapper>& dtolist)
{
	DutyDAO dao;
	auto result = DutyInsertResultDTO::createShared();
	for (DutyDTO::Wrapper& dto : (*dtolist) ) {
		DutyDO data;
		ZO_STAR_DOMAIN_DTO_TO_DO(data, dto, SchoolId, school_id, Qdate, qdate, BeginTime, begin_time, EndTime, end_time, SignIn, sign_in, SignOut, sign_out);
		//待添加判断  不能重复报名同一时间段&人数不超过三个  

		  // ① 检查是否重复报名
		if (dao.existsSameVolunteer(dto->school_id, dto->qdate, dto->begin_time, dto->end_time)) {
			result->success = false;
			result->message = u8"该志愿者已报名该时间段";
			return result;
		}

		// ② 检查该时间段人数是否已满
		int count = dao.countByTimeRange(dto->qdate, dto->begin_time, dto->end_time);
		if (count >= 3) {
			result->success = false;
			result->message = u8"该时间段报名人数已满";
			return result;
		}

		// ③ 插入记录
		bool subres = dao.insert(data);
		if (!subres) {
			OATPP_LOGE("DutyService", "Insert failed for school_id:%s qdate:%s begin_time:%s end_time:%s",
				dto->school_id->c_str(), dto->qdate->c_str(),
				dto->begin_time->c_str(), dto->end_time->c_str());

			result->success = false;
			result->message = u8"数据库插入失败";
			return result;
		}
	}

	// 全部成功
	result->success = true;
	result->message = u8"报名成功";
	return result;
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

DutyExportListDTO::Wrapper DutyService::exportDuty(const DutyExportQuery::Wrapper& query)
{
	auto result = DutyExportListDTO::createShared();
	result->list = oatpp::List<DutyExportDTO::Wrapper>::createShared();
	DutyDAO dao;
	
	std::list<DutyExportDO> res = dao.selectDutyExport(query);
	for (auto one : res) {
		auto dto = DutyExportDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, one,voluntary_id,VoluntaryId, name, Name,date,Date,begin_time, BeginTime, end_time, EndTime,total_time,TotalTime);
		result->list->push_back(dto);
	}
	return result;
}
