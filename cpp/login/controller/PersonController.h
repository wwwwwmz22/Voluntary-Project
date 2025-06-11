#pragma once
/*

*/
#ifndef _PERSONCONTROLLER_H_
#define _PERSONCONTROLLER_H_

#include "oatpp-swagger/Types.hpp"
#include "../domain/vo/PersonInfoVO.h"
#include "../domain/query/PersonInfoQuery.h"
#include "../../lib-oatpp/include/domain/vo/BaseJsonVO.h"
using namespace oatpp;

#include OATPP_CODEGEN_BEGIN(ApiController)
class PersonController:public oatpp::web::server::api::ApiController{
	//��ӷ��ʶ���
	API_ACCESS_DECLARE(PersonController);
public:
	//�����ѯ�û���Ϣ�ӿڶ˵�����
	ENDPOINT_INFO(queryUser){ 
		//�������
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("person.query"));
		//������Ӧ������ʽ
		API_DEF_ADD_RSP_JSON_WRAPPER(PersonInfoJsonVO);
		//������������
		API_DEF_ADD_QUERY_PARAMS(String, "school_id", ZH_WORDS_GETTER("person.info.stuid"), "2023000000", false);
		API_DEF_ADD_QUERY_PARAMS(String, "password", ZH_WORDS_GETTER("person.info.psw"), "", false);
	}

	//�����ѯ�û���Ϣ�ӿڶ˵㴦��
	ENDPOINT(API_M_GET,"login/getUserInfo", queryUser,QUERIES(QueryParams,params)) {
		//������ѯ����
		auto query = PersonInfoQuery::createShared();
		query->school_id = params.get("school_id");
		query->pasword = params.get("password");
		//����ִ�к�����Ӧ���
		API_HANDLER_RESP_VO(executeQueryInfo(query));
	}


	//�����޸��û���Ϣ�ӿ�����
	API_DEF_ENDPOINT_INFO(ZH_WORDS_GETTER("person.update"), modifyInfo, StringJsonVO::Wrapper);
	//�����޸��û���Ϣ�ӿڴ���
	API_HANDLER_ENDPOINT(API_M_PUT, "login/modifyuserinfo", modifyInfo, BODY_DTO(PersonBaseInfoDTO::Wrapper, dto), execModifyInfo(dto));

	//���������û���Ϣ�ӿ�����
	API_DEF_ENDPOINT_INFO(ZH_WORDS_GETTER("person.add"), addInfo, StringJsonVO::Wrapper);
	//���������û���Ϣ�ӿڴ���
	API_HANDLER_ENDPOINT(API_M_POST, "login/adduserinfo", addInfo, BODY_DTO(PersonAllInfoDTO::Wrapper, dto), execAddUser(dto));

private:
	//��ѯ�û���Ϣ
	PersonInfoJsonVO::Wrapper executeQueryInfo(const PersonInfoQuery::Wrapper& query);

	//�޸��û���Ϣ
	StringJsonVO::Wrapper execModifyInfo(const PersonBaseInfoDTO::Wrapper& dto);

	//�����û���Ϣ
	StringJsonVO::Wrapper execAddUser(const PersonAllInfoDTO::Wrapper& dto);
};
#include OATPP_CODEGEN_END(ApiController)
#endif // !_PERSONCONTROLLER_H_