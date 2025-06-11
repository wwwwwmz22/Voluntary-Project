/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2024/04/08 11:02:33

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
#include <fstream>
#include "Macros.h"
#include "PdfComponent.h"

#include "gtest/gtest.h"

TEST(PdfTest, TestText) {
	// ����PDF���
	PdfComponent pdf;

	// ����һ��ҳ��
	pdf.getNewPage();
	// ��������
	pdf.drawTextCenterH(ZH_WORDS_GETTER("pdf.title"), pdf.getCurrPageHeight() - 20);
	pdf.drawTextCenter(ZH_WORDS_GETTER("pdf.content"));
	pdf.drawTextCenterH(ZH_WORDS_GETTER("pdf.foot"), 20);
	
	// �ٴ���һ��ҳ�棬ʹ��ttf����
	pdf.getNewPage(pdf.getTtFont("fonts/PenguinAttack.ttf"));
	// ��������
	pdf.drawTextCenterH("I am ttf title", pdf.getCurrPageHeight() - 20);
	pdf.drawTextCenter("I am ttf content");
	pdf.drawTextCenterH("I am ttf foot", 20);
	
	// ���浽�ļ�
	ASSERT_EQ(pdf.saveDocToFile("pdf-text.pdf"), true);
}

TEST(PdfTest, TestTpl) {
	// ����ע����Ⱦģ��
	PdfComponent::registerTplRender("test", [](YAML::Node* node, PdfComponent* pdf, void* realData) {
		// ����һ��ҳ��
		pdf->getNewPage();

		// ���ƾ�̬����
		auto title = (*node)["t"].as<std::string>();
		auto foot = (*node)["f"].as<std::string>();
		pdf->drawTextCenterH(title, pdf->getCurrPageHeight() - 20);
		pdf->drawTextCenterH(foot, 20);

		// ���ƶ�̬����
		std::string content = static_cast<std::string*>(realData)->c_str();
		pdf->drawTextCenter(content);
		});

	// ���Ի���
	PdfComponent pdf;
	auto content = ZH_WORDS_GETTER("pdf.content");
	pdf.drawWithTemplate("tpl/test.yaml", "test", &content);
	// ���浽�ļ�
	pdf.saveDocToFile("pdf-tpl.pdf");
}

// ͼ������Ԥ�� https://zxing-cpp.github.io/zxing-cpp/demo_writer.html
TEST(PdfTest, TestPictureCode) {
	// ����PDF���
	PdfComponent pdf;
	// ����һ��ҳ��
	pdf.getNewPage();
	// ͼ����ʱ����λ��
	std::string filepath = "tmp.jpg";
	// ���������е�����
	std::string input = "11223344";
	// �������뵽�ļ�
	bool success = PdfComponent::genPictureCodeToFile(filepath, 200, 30, input, "Code93");
	if (success)
	{
		// ����ͼƬ�ļ�
		HPDF_Image image = HPDF_LoadJpegImageFromFile(pdf.getDoc(), filepath.c_str());
		// ����ͼƬ��PDF��
		pdf.drawImage(image, 200, 500);
	}
	
	// ���ɶ�ά�뵽�ļ�
	std::string url = "www.baidu.com";
	success = PdfComponent::genPictureCodeToFile(filepath, 200, 150, url, "QRCode");
	if (success)
	{
		// ����ͼƬ�ļ�
		HPDF_Image image = HPDF_LoadJpegImageFromFile(pdf.getDoc(), filepath.c_str());
		// ����ͼƬ��PDF��
		pdf.drawImage(image, 200, 350);
	}
	// ���浽�ļ���������ʾʹ���ڴ����ݱ��浽�ļ��ķ�ʽ
	auto data = pdf.saveDocToMem();
	auto buff = reinterpret_cast<const char*>(data.data());
	std::ofstream fsWrite;
	fsWrite.open("pdf-picturecode.pdf", std::ios::out | std::ios::binary);
	fsWrite.write(buff, data.size());
	fsWrite.close();
}