#include "stdafx.h"
#include <sstream>
#include "PersonInfoDAO.h"
#include "PersonInfoMapper.h"
#include "../../lib-mysql/include/SqlSession.h"


std::string PersonInfoDAO::queryConditionBuilder(const PersonInfoQuery::Wrapper& query, SqlParams& params)
{
	stringstream sqlCondition;
	sqlCondition << " WHERE 1=1";
	if (query->school_id) {
		sqlCondition << " AND `school_id` =?";
		SQLPARAMS_PUSH(params, "s", std::string, query->school_id.getValue(""));
		
	}
	if (query->pasword)
	{
		sqlCondition << " AND `pasword`=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->pasword.getValue(""));
	}
	return sqlCondition.str();
}

PtrPersonInfoDO PersonInfoDAO::selectByIdAndPasword(const PersonInfoQuery::Wrapper& stuid)
{
	SqlParams params;
	string sql = "SELECT * FROM vp_login";
	sql += queryConditionBuilder(stuid, params);
	PtrPersonInfoMapper mapper;
	return sqlSession->executeQueryOne<PtrPersonInfoDO>(sql, mapper, params);
}

int PersonInfoDAO::update(const PersonInfoDO& obj)
{
	string sql = "UPDATE `vp_login` SET `pname`=?,`college`=?,`voluntary_id`=?, `political_status`=?,`phone_number`=?,`grade`=?,`edu_background`=? ,`dorm`=?,`roomid`=? WHERE `school_id` =?";
	return sqlSession->executeUpdate(sql, "%s%s%s%s%s%i%s%s%s%s",obj.getpName(),obj.getCollege(),obj.getVoluntaryId(),obj.getPoliticalStatus(),obj.getPhoneNumber(),obj.getGrade(),obj.getEduBackground(),  obj.getDorm(), obj.getRoomid(),obj.getSchoolId());
}

int PersonInfoDAO::updateScore(const PersonInfoDO& obj)
{
	string sql = "UPDATE `vp_login` SET `score`=? WHERE `school_id` =?";
	return sqlSession->executeUpdate(sql, "%i%s", obj.getScore(), obj.getSchoolId());
}

int PersonInfoDAO::insert(const PersonInfoDO& obj)
{
	string sql = "INSERT INTO `vp_login` (`school_id`,`pasword`,`pname`,`phone_number`,`voluntary_id`,`political_status`,`voluntary_time`,`college`,`gender`,`grade`,`edu_background`,`score`,`identity`,`dorm`,`roomid`) VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";

	return sqlSession->executeUpdate(sql, "%s%s%s%s%s%s%i%s%s%i%s%i%s%s%s",  obj.getSchoolId(),obj.getPasword(), obj.getpName(), obj.getPhoneNumber(), obj.getVoluntaryId(), obj.getPoliticalStatus(), obj.getVoluntaryTime(), obj.getCollege(), obj.getGender(), obj.getGrade(), obj.getEduBackground(),obj.getScore(),obj.getIdentity(),obj.getDorm(),obj.getRoomid());

}
