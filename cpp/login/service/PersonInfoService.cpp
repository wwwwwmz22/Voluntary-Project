#include "stdafx.h"
#include "PersonInfoService.h"
#include "../dao/PersonInfoDAO.h"
#include "../Macros.h"
#include "../domain/dto/PersonInfoDTO.h"



PersonInfoDTO::Wrapper PersonInfoServer::getByIdAndPasword(const PersonInfoQuery::Wrapper& schoolid)
{
	PersonInfoDAO dao;
	auto res = dao.selectByIdAndPasword(schoolid);
	if (!res) {
		cout << "no result" << endl;
		return nullptr;
	}
	
	auto dto = PersonInfoDTO::createShared();
	dto->school_id = res->getSchoolId().c_str();
	dto->pasword = res->getPasword().c_str();
	dto->pname = res->getpName().c_str();
	dto->phone_number = res->getPhoneNumber().c_str();
	dto->political_status = res->getPoliticalStatus().c_str();
	dto->voluntary_time = res->getVoluntaryTime();
	dto->voluntary_id = res->getVoluntaryId().c_str();
	return dto;
}

bool PersonInfoServer::updateData(const PersonBaseInfoDTO::Wrapper& dto)
{
	PersonInfoDO data;
	ZO_STAR_DOMAIN_DTO_TO_DO(data, dto, SchoolId,  school_id, Pasword, pasword, pName,pname,  PhoneNumber,phone_number,  VoluntaryId,voluntary_id,PoliticalStatus,  political_status);
	PersonInfoDAO dao;
	return dao.update(data) == 1;
}

bool PersonInfoServer::saveData(const PersonAllInfoDTO::Wrapper& dto)
{
	PersonInfoDO data;
	ZO_STAR_DOMAIN_DTO_TO_DO(data, dto, SchoolId, school_id,Pasword,pasword ,pName, pname, PhoneNumber, phone_number, VoluntaryId, voluntary_id, PoliticalStatus, political_status, College, college, VoluntaryTime, voluntary_time, Gender, gender, Grade, grade, EduBackground, edu_background);
	PersonInfoDAO dao;
	return dao.insert(data) == 1;
}
