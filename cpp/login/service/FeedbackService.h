#pragma once
#include "../domain/dto/FeedbackDTO.h"
#include "../domain/query/FeedbackQuery.h"
/*

*/
#ifndef _FEEDBACKSERVICE_H_
#define _FEEDBACKSERVICE_H_

class FeedbackService{
public:
	//分页查询所有日志信息
	FeedbackListDTO::Wrapper listAll(const FeedbackQuery::Wrapper& query);
	//增加日志信息
	bool saveData(const FeedbackDTO::Wrapper& dto);
};

#endif // !_FEEDBACKSERVICE_H_