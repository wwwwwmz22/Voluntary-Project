#include "FeedbackDAO.h"
#include "stdafx.h"
#include <sstream>
#include "../../lib-mysql/include/SqlSession.h"
#include "FeedbackMapper.h"



std::string FeedbackDAO::queryConditionBuilder(const FeedbackQuery::Wrapper& query, SqlParams& params)
{
	stringstream sqlCondition;
	sqlCondition << "WHERE 1=1";
	if (query->qdate)
	{
		sqlCondition << " AND qdate=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->qdate.getValue(""));
	}
	return sqlCondition.str();
}

//uint64_t FeedbackDAO::count(const FeedbackQuery::Wrapper& query)
//{
//	SqlParams params;
//	string sql = "SELECT COUNT(*) FROM feedback_recording ";
//	sql += queryConditionBuilder(query, params);
//	return sqlSession->executeQueryNumerical(sql, params);
//}

std::list<FeedbackDO> FeedbackDAO::selectWithPage(const FeedbackQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT school_id,pname,qdate,isclean,isnoise,isfood,isseat,isother FROM feedback_recording ";
	sql += queryConditionBuilder(query, params);

	FeedbackMapper mapper;
	return sqlSession->executeQuery<FeedbackDO>(sql, mapper, params);
}

int FeedbackDAO::insert(const FeedbackDO& obj)
{
	string sql = "INSERT INTO `feedback_recording` (`school_id`,`pname`,`qdate`,`isclean`,`isnoise`,`isfood`,`isseat`,`isother`) VALUES(?,?,?,?,?,?,?,?) ";

	return sqlSession->executeUpdate(sql, "%s%s%s%s%s%s%s%s", obj.getSchoolId(),  obj.getpName(),obj.getQdate(),obj.getisClean(),obj.getisNoise(),obj.getisFood(),obj.getisSeat(),obj.getisOther());

}
