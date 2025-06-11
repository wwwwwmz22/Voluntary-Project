#pragma once
/*

*/
#ifndef _FEEDBACKCONTROLLER_H_
#define _FEEDBACKCONTROLLER_H_
#include "oatpp-swagger/Types.hpp"
#include "../../../lib-oatpp/include/ApiHelper.h"
#include "../../domain/dto/FeedbackDTO.h"
#include "../../domain/query/FeedbackQuery.h"
#include "../../../lib-oatpp/include/domain/vo/BaseJsonVO.h"
#include "../../domain/vo/FeedbackVO.h"
using namespace oatpp;
#include OATPP_CODEGEN_BEGIN(ApiController)

class FeedbackController :public oatpp::web::server::api::ApiController {
	API_ACCESS_DECLARE(FeedbackController);
public:
	//��ѯΥ�����
	ENDPOINT_INFO(queryFeedback) {
		//�������
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("feedback.query"));
		//������Ӧ������ʽ
		API_DEF_ADD_RSP_JSON_WRAPPER(FeedbackJsonVO);
		//������������
		API_DEF_ADD_QUERY_PARAMS(String, "qdate", ZH_WORDS_GETTER("duty.info.date"), "2025-05-15", false);
	}
	//�����ѯΥ������ӿڶ˵㴦��
	ENDPOINT(API_M_GET, "feedback/getFeedbackInfo", queryFeedback, QUERIES(QueryParams, qdate)) {
		//������ѯ����
		API_HANDLER_QUERY_PARAM(querydate, FeedbackQuery, qdate);
		//����ִ�к�����Ӧ���
		API_HANDLER_RESP_VO(executeQueryInfo(querydate));
	}

	//��������������Ϣ�ӿ�����
	API_DEF_ENDPOINT_INFO(ZH_WORDS_GETTER("feedback.add"), addInfo, Uint64JsonVO::Wrapper);
	//��������������Ϣ�ӿڴ���
	API_HANDLER_ENDPOINT(API_M_POST, "feedback/addFeedbackInfo", addInfo, BODY_DTO(FeedbackDTO::Wrapper, dto), execAdd(dto));

private:
	//��ѯ������Ϣ
	FeedbackJsonVO::Wrapper executeQueryInfo(const FeedbackQuery::Wrapper& query);
	//����������Ϣ
	Uint64JsonVO::Wrapper execAdd(const FeedbackDTO::Wrapper& dto);
};

#include OATPP_CODEGEN_END(ApiController)
#endif // !_FEEDBACKCONTROLLER_H_