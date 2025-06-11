#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2024/11/18 10:26:47

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

	  https://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#ifndef _UUIDFACADE_H_
#define _UUIDFACADE_H_
#include <string>
#include <memory>
#include "stduuid/uuid.h"

/**
 * ��װһ������UUID��������
 * �����ӣ�https://github.com/mariusbancila/stduuid
 */
class UuidFacade final
{
private:
	// ʹ������������ 0 random 1 system
	int type;
	// ����UUID������
	uuids::uuid_random_generator* random_gen;
#ifdef UUID_SYSTEM_GENERATOR
	uuids::uuid_system_generator* system_gen;
#endif
	// ��ʼ��
	void init();
public:
	//************************************
	// Method:      UuidFacade
	// FullName:    UuidFacade::UuidFacade
	// Access:      public 
	// Returns:     
	// Parameter:   int type ʹ�����������ͣ�0 random 1 system
	// Description: �����ʼ��
	//************************************
	UuidFacade(int type);
	// ����ϵͳ�����Զ�ѡ��������
	UuidFacade();
	~UuidFacade();

	//************************************
	// Method:      genUuid
	// FullName:    UuidFacade::genUuid
	// Access:      public 
	// Returns:     std::string ����ʧ�ܷ��ؿ��ַ���
	// Description: ����һ��UUID
	//************************************
	std::string genUuid();
};

#endif // !_UUIDFACADE_H_