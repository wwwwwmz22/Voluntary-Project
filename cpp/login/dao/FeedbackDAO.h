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
	//ͳ����������
	//uint64_t count(const FeedbackQuery::Wrapper& query);
	//��ѯ
	std::list<FeedbackDO> selectWithPage(const FeedbackQuery::Wrapper& query);
	//��������
	int insert(const FeedbackDO& obj);
};

#endif // !_FEEDBACKDAO_H_