#include "stdafx.h"
#include "DutyDAO.h"
#include<sstream>
#include <ctime>
#include "DutyMapper.h"
#include "ScheduleMapper.h"
#include "DutyExportMapper.h"


std::string DutyDAO::queryConditionBuilder(const DutyQuery::Wrapper& query, SqlParams& params)
{
	stringstream sqlCondition;
	sqlCondition << "WHERE 1=1";
	if (query->qdate) {
		sqlCondition << " AND `qdate`=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->qdate.getValue(""));
	}
	return sqlCondition.str();
}


//uint64_t DutyDAO::count(const DutyQuery::Wrapper& query)
//{
//	return 99;
//}

std::list<DutyResultDO> DutyDAO::selectOneDayById(const DutyQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT school_id,qdate,begin_time,end_time,sign_in,sign_out FROM duty_recording ";
	sql += "WHERE `school_id` = ? AND  `qdate`= ? ";
	sql += " GROUP BY qdate,begin_time, end_time ORDER BY begin_time";
	SQLPARAMS_PUSH(params, "s", std::string, query->school_id.getValue(""));
	SQLPARAMS_PUSH(params, "s", std::string,query->qdate.getValue(""));
	//查询
	DutyMapper mapper;
	return sqlSession->executeQuery<DutyResultDO>(sql,mapper, params);
}

int DutyDAO::update(const DutyDO& obj)
{
	string sql = "UPDATE `duty_recording` SET `sign_in`=?,`sign_out`=? WHERE `school_id`=? AND `qdate`=? AND `begin_time`=? AND `end_time`=?";
	return sqlSession->executeUpdate(sql, "%i%i%s%s%s%s", obj.getSignIn(), obj.getSignOut(), obj.getSchoolId(), obj.getQdate(), obj.getBeginTime(), obj.getEndTime());
}

uint64_t DutyDAO::insert(const DutyDO& obj)
{
	string sql = "INSERT INTO `duty_recording`(`school_id`,`qdate`,`begin_time`,`end_time`,`sign_in`,`sign_out`) VALUES(?,?,?,?,?,?) ";
	return sqlSession->executeInsert(sql, "%s%s%s%s%i%i", obj.getSchoolId(), obj.getQdate(), obj.getBeginTime(), obj.getEndTime(), obj.getSignIn(), obj.getSignOut());
}

int DutyDAO::deleteOne(const DeleteDutyDO& obj)
{
	string sql = "DELETE FROM `duty_recording` WHERE `school_id`=? AND `qdate`=? AND `begin_time`=? AND `end_time`=?";
	return sqlSession->executeUpdate(sql, "%s%s%s%s", obj.getSchoolId(), obj.getQdate(), obj.getBeginTime(), obj.getEndTime());
}

std::list<ScheduleDO> DutyDAO::selectSchedule(const DutyQuery::Wrapper& query)
{
	SqlParams params;
	string sql = R"(
		SELECT 
			r.qdate,
			r.begin_time,
			r.end_time,
			GROUP_CONCAT(DISTINCT p.pname) AS pname_list 
		FROM duty_recording  r
		JOIN vp_login p ON r.school_id = p.school_id   
	)";
	if (query->qdate)
	{
		std::string startDate = query->qdate.getValue("");
		std::string endDate = startDate;

		std::tm tm{};
		std::istringstream ss(startDate);
		ss >> std::get_time(&tm, "%Y-%m-%d");
		if (!ss.fail()) {
			tm.tm_mday += 6;
			std::mktime(&tm);
			std::ostringstream oss;
			oss << std::put_time(&tm, "%Y-%m-%d");
			endDate = oss.str();
		}
		sql += " WHERE r.qdate BETWEEN ? AND ? ";
		SQLPARAMS_PUSH(params, "s", std::string, startDate);
		SQLPARAMS_PUSH(params, "s", std::string, endDate);
	}
	sql += R"(
		GROUP BY r.qdate,r.begin_time,r.end_time
		ORDER BY r.qdate ASC, LPAD(r.begin_time,5,'0') ASC
	)";
	//查询
	ScheduleMapper mapper;
	return sqlSession->executeQuery<ScheduleDO>(sql, mapper,params);
}

std::list<DutyExportDO> DutyDAO::selectDutyExport(const DutyExportQuery::Wrapper& query)
{
	SqlParams params;
	string sql = R"(
        SELECT
            l.voluntary_id,
            l.pname AS `name`,
            d.qdate AS `date`,
            d.begin_time,
            d.end_time,
            -- 计算 total_time 为小时数（保留两位小数）
            ROUND(TIME_TO_SEC(TIMEDIFF(d.end_time, d.begin_time)) / 3600, 2) AS `total_time`
        FROM
            duty_recording d
        INNER JOIN
            vp_login l ON d.school_id = l.school_id
        WHERE
            d.qdate >= ? AND d.qdate <= ?
        ORDER BY
            d.qdate ASC, d.begin_time ASC
    )";

	SQLPARAMS_PUSH(params, "s", std::string, query->begin_date.getValue(""));
	SQLPARAMS_PUSH(params, "s", std::string, query->end_date.getValue(""));
	DutyExportMapper mapper;
	return sqlSession->executeQuery<DutyExportDO>(sql, mapper, params);
}

int DutyDAO::countByTimeRange(const oatpp::String& qdate, const oatpp::String& begin_time, const oatpp::String& end_time)
{
	SqlSession sqlSession ;
	std::string sql = R"(
        SELECT COUNT(*) AS cnt
        FROM duty_recording
        WHERE qdate = ? AND begin_time = ? AND end_time = ?
    )";

	SqlParams params;
	SQLPARAMS_PUSH(params, "s", std::string, qdate.getValue(""));
	SQLPARAMS_PUSH(params, "s", std::string, begin_time.getValue(""));
	SQLPARAMS_PUSH(params, "s", std::string, end_time.getValue(""));

	auto result = sqlSession.executeQueryNumerical(sql, params);
	return result;
}

bool DutyDAO::existsSameVolunteer(const oatpp::String& school_id, const oatpp::String& qdate, const oatpp::String& begin_time, const oatpp::String& end_time)
{
	SqlSession sqlSession ;
	std::string sql = R"(
        SELECT COUNT(*) AS cnt
        FROM duty_recording
        WHERE school_id = ? AND qdate = ? AND begin_time = ? AND end_time = ?
    )";

	SqlParams params;
	SQLPARAMS_PUSH(params, "s", std::string, school_id.getValue(""));
	SQLPARAMS_PUSH(params, "s", std::string, qdate.getValue(""));
	SQLPARAMS_PUSH(params, "s", std::string, begin_time.getValue(""));
	SQLPARAMS_PUSH(params, "s", std::string, end_time.getValue(""));
	
	auto result = sqlSession.executeQueryNumerical(sql, params);
	return result > 0;
}
