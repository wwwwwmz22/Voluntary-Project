#pragma once
#include "../domain/dto/PersonInfoDTO.h"
#include "../domain/query/PersonInfoQuery.h"
/*

*/
#ifndef _PERSONINFOSERVICE_H_
#define _PERSONINFOSERVICE_H_

class PersonInfoServer{
public:
	// ͨ��ѧ�Ų�ѯ��������
	PersonInfoDTO::Wrapper getByIdAndPasword(const PersonInfoQuery::Wrapper& schoolid);
	//�޸���Ϣ
	bool updateData(const PersonBaseInfoDTO::Wrapper& dto);
	//�����û���Ϣ
	bool saveData(const PersonAllInfoDTO::Wrapper& dto);
};

#endif // !_PERSONINFOSERVICE_H_