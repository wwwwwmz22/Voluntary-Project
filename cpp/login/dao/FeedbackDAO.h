#pragma once
/*

*/
#ifndef _FEEDBACKDAO_H_
#define _FEEDBACKDAO_H_
#include "BaseDAO.h"
#include "../domain/query/FeedbackQuery.h"
#include "../domain/do/FeedbackDO.h"

class FeedbackDAO :public BaseDAO {
private:
	inline std::string queryConditionBuilder(const FeedbackQuery::Wrapper& query, SqlParams& params);
public:
	//统计数据条数
	//uint64_t count(const FeedbackQuery::Wrapper& query);
	//查询
	std::list<FeedbackDO> selectWithPage(const FeedbackQuery::Wrapper& query);
	//保存数据
	int insert(const FeedbackDO& obj);
};

#endif // !_FEEDBACKDAO_H_