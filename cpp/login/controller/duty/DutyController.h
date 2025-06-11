#pragma once
/*

*/
#ifndef _DUTYCONTROLLER_H_
#define _DUTYCONTROLLER_H_
#include "oatpp-swagger/Types.hpp"
#include "../../../lib-oatpp/include/ApiHelper.h"
#include "../../domain/vo/DutyVO.h"
#include "../../domain/query/DutyQuery.h"
#include "../../domain/dto/DutyDTO.h"
#include "../../../lib-oatpp/include/domain/vo/BaseJsonVO.h"
#include "../../domain/vo/ScheduleVO.h"

using namespace oatpp;

#include OATPP_CODEGEN_BEGIN(ApiController)
class DutyController :public oatpp::web::server::api::ApiController {
	API_ACCESS_DECLARE(DutyController);
public:
	//�����ѯ������Ϣ�ӿڶ˵�����
	ENDPOINT_INFO(queryDuty) {
		//�������
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("duty.query"));
		//������Ӧ������ʽ
		API_DEF_ADD_RSP_JSON_WRAPPER(DutyJsonVO);
		//������������
		API_DEF_ADD_QUERY_PARAMS(String, "qdate", ZH_WORDS_GETTER("duty.info.date"), "2025-05-15", false);
	}

	//�����ѯ������Ϣ�ӿڶ˵㴦��
	ENDPOINT(API_M_GET, "duty/getDutyInfo", queryDuty, QUERIES(QueryParams, qdate)) {
		//������ѯ����
		API_HANDLER_QUERY_PARAM(querydate, DutyQuery, qdate);
		//����ִ�к�����Ӧ���
		API_HANDLER_RESP_VO(executeQueryInfo(querydate));
	}

	//��������������Ϣ�ӿ�����
	API_DEF_ENDPOINT_INFO(ZH_WORDS_GETTER("duty.add"), addInfo, Uint64JsonVO::Wrapper);
	//��������������Ϣ�ӿڴ���
	API_HANDLER_ENDPOINT(API_M_POST, "duty/addInfo", addInfo, BODY_DTO(AddDutyDTO::Wrapper, dtolist), execAdd(dtolist));


	//�����޸ı�����Ϣ�ӿ�����
	API_DEF_ENDPOINT_INFO(ZH_WORDS_GETTER("duty.update"), updateInfo, Uint64JsonVO::Wrapper);
	//�����޸ı�����Ϣ�ӿڴ���
	API_HANDLER_ENDPOINT(API_M_PUT, "duty/updateInfo", updateInfo, BODY_DTO(DutyDTO::Wrapper, dto), execUpdate(dto));

	//����ɾ��������Ϣ�ӿ�����
	API_DEF_ENDPOINT_INFO(ZH_WORDS_GETTER("duty.delete"), removeInfo, Uint64JsonVO::Wrapper);
	//����ɾ��������Ϣ�ӿڴ���
	API_HANDLER_ENDPOINT(API_M_DEL, "duty/deleteInfo", removeInfo, BODY_DTO(DeleteDutyDTO::Wrapper, dto), execRemove(dto));

	//��ѯֵ���
	ENDPOINT_INFO(querySchedule) {
		//�������
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("duty.queryschedule"));
		//������Ӧ������ʽ
		API_DEF_ADD_RSP_JSON_WRAPPER(ScheduleJsonVO);
		//������������
		API_DEF_ADD_QUERY_PARAMS(String, "qdate", ZH_WORDS_GETTER("duty.info.date"), "2025-05-15", false);
	}

	//�����ѯ������Ϣ�ӿڶ˵㴦��
	ENDPOINT(API_M_GET, "duty/getSehedule", querySchedule, QUERIES(QueryParams, qdate)) {
		//������ѯ����
		API_HANDLER_QUERY_PARAM(queryschedule, DutyQuery, qdate);
		//����ִ�к�����Ӧ���
		API_HANDLER_RESP_VO(executeQuerySchedule(queryschedule));
	}

private:
	//��ѯ������Ϣ
	DutyJsonVO::Wrapper executeQueryInfo(const DutyQuery::Wrapper& query);
	//����������Ϣ
	Uint64JsonVO::Wrapper execAdd(const AddDutyDTO::Wrapper& dtolist);
	//�޸���Ϣ
	Uint64JsonVO::Wrapper execUpdate(const DutyDTO::Wrapper& dto);
	//ȡ��������Ϣ
	Uint64JsonVO::Wrapper execRemove(const DeleteDutyDTO::Wrapper& dto);
	//��ѯֵ���
	ScheduleJsonVO::Wrapper executeQuerySchedule(const DutyQuery::Wrapper& query);
};

#include OATPP_CODEGEN_END(ApiController)
#endif // !_DUTYCONTROLLER_H_