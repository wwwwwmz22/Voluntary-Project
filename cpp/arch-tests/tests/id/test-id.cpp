/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2024/11/18 10:12:22

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
#include <iostream>
#include "id/SnowFlake.h"
#include "id/UuidFacade.h"

#include "gtest/gtest.h"

// ����ѩ��ID
TEST(IdTest, TestSnowFlake) {
	// ���������� ��һ������ͳһ��1���ڶ���������С����
	SnowFlake sf(1, 1);
	// ����10��ID
	for (int i = 0; i < 10; i++)
		std::cout << sf.nextId() << std::endl;
}

// ����UUID
TEST(IdTest, TestUuid) {
	// ����������
	UuidFacade uf(1);
	// ����10��ID
	for (int i = 0; i < 10; i++)
		std::cout << uf.genUuid() << std::endl;
}

