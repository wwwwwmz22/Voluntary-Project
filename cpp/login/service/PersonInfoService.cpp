#include "stdafx.h"
#include "PersonInfoService.h"
#include "../dao/PersonInfoDAO.h"
#include "../domain/dto/PersonInfoDTO.h"
#include "../Macros.h"



PersonAllInfoDTO::Wrapper PersonInfoServer::getByIdAndPasword(const PersonInfoQuery::Wrapper& schoolid)
{
	PersonInfoDAO dao;
	auto res = dao.selectByIdAndPasword(schoolid);
	if (!res) {
		cout << "no result" << endl;
		return nullptr;
	}
	
	auto dto = PersonAllInfoDTO::createShared();
	dto->school_id = res->getSchoolId().c_str();
	dto->pasword = res->getPasword().c_str();
	dto->pname = res->getpName().c_str();
	dto->college = res->getCollege().c_str();
	dto->phone_number = res->getPhoneNumber().c_str();
	dto->political_status = res->getPoliticalStatus().c_str();
	dto->voluntary_time = res->getVoluntaryTime();
	dto->voluntary_id = res->getVoluntaryId().c_str();
	dto->gender = res->getGender().c_str();
	dto->grade = res->getGrade();
	dto->identity = res->getIdentity().c_str();
	dto->edu_background = res->getEduBackground().c_str();
	dto->score = res->getScore();
	dto->dorm = res->getDorm();
	dto->roomid = res->getRoomid();
	return dto;
}

bool PersonInfoServer::updateData(const PersonUpdateInfoDTO::Wrapper& dto)
{
	PersonInfoDO data;
	ZO_STAR_DOMAIN_DTO_TO_DO(data, dto, SchoolId,  school_id, pName,pname, College, college, VoluntaryId,voluntary_id,PhoneNumber,phone_number, PoliticalStatus,  political_status , Grade, grade, EduBackground, edu_background,Dorm,dorm,Roomid,roomid );
	PersonInfoDAO dao;
	return dao.update(data) == 1;
}

bool PersonInfoServer::updateScore(const PersonUpdateScoreDTO::Wrapper& dto)
{
	PersonInfoDO data;
	ZO_STAR_DOMAIN_DTO_TO_DO(data, dto, SchoolId, school_id, Score, score);
	PersonInfoDAO dao;
	return dao.updateScore(data) == 1;
}

bool PersonInfoServer::saveData(const PersonAllInfoDTO::Wrapper& dto)
{
	PersonInfoDO data;
	ZO_STAR_DOMAIN_DTO_TO_DO(data, dto, SchoolId, school_id, Pasword, pasword, pName, pname, PhoneNumber, phone_number, VoluntaryId, voluntary_id, PoliticalStatus, political_status, College, college, VoluntaryTime, voluntary_time, Gender, gender, Grade, grade, EduBackground, edu_background, Score, score,Identity, identity, Dorm, dorm, Roomid, roomid);
	PersonInfoDAO dao;
	return dao.insert(data) == 1;
}
