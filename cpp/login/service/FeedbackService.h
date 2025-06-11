#pragma once
#include "../domain/dto/FeedbackDTO.h"
#include "../domain/query/FeedbackQuery.h"
/*

*/
#ifndef _FEEDBACKSERVICE_H_
#define _FEEDBACKSERVICE_H_

class FeedbackService{
public:
	//��ҳ��ѯ������־��Ϣ
	FeedbackListDTO::Wrapper listAll(const FeedbackQuery::Wrapper& query);
	//������־��Ϣ
	bool saveData(const FeedbackDTO::Wrapper& dto);
};

#endif // !_FEEDBACKSERVICE_H_