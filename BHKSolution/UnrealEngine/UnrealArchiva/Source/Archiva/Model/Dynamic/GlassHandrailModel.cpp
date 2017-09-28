// Fill out your copyright notice in the Description page of Project Settings.

#include "Archiva.h"
#include "GlassHandrailModel.h"

AGlassHandrailModel::AGlassHandrailModel()
{
	H_length = 200;
	H_width = 10;
	H_height = 7;

	P_length = 6;
	P_width = H_width -2;
	P_height = 100;

	G_length = 50;
	G_width = 1;
	G_height = 80;

}

void AGlassHandrailModel::Create(FModelData data)
{
	model->ClearAllMeshSections();
	meshNum = 0;
	SavedMaterial = data.materials;
	//data���� �Է¹޾� �����ϴ� ����
	H_length = data.size.X;
	P_height = data.height - H_height;
	angle = data.pitch;
	G_length = data.interval;
	G_height = P_height - 20;

	float trig_x = CalcTrigX(H_length);
	float trig_y = CalcTrigY(H_length);

	/*������*/
	FVector cordinate[8];
	cordinate[0] = FVector(0, H_width / 2, P_height);
	cordinate[1] = FVector(trig_x, H_width / 2, P_height + trig_y);
	cordinate[2] = FVector(trig_x, H_width / 2, P_height + H_height + trig_y);
	cordinate[3] = FVector(0, H_width / 2, P_height + H_height);

	cordinate[4] = FVector(0, -(H_width / 2), P_height);
	cordinate[5] = FVector(trig_x, -(H_width / 2), P_height + trig_y);
	cordinate[6] = FVector(trig_x, -(H_width / 2), P_height + H_height + trig_y);
	cordinate[7] = FVector(0, -(H_width / 2), P_height + H_height);

	//���� side
	CreateQuad(cordinate[4], cordinate[0], cordinate[3], cordinate[7], "handle", FVector(-1, 0, 0));
	//���� side
	CreateQuad(cordinate[3], cordinate[2], cordinate[6], cordinate[7], "handle", FVector(0, 0, 1));
	//������ side
	CreateQuad(cordinate[1], cordinate[5], cordinate[6], cordinate[2], "handle", FVector(1, 0, 0));
	//�Ʒ��� side
	CreateQuad(cordinate[4], cordinate[5], cordinate[1], cordinate[0], "handle", FVector(0, 0, -1));
	//�ո�
	CreateQuad(cordinate[0], cordinate[1], cordinate[2], cordinate[3], "handle", FVector(0, 1, 0));
	//�޸�
	CreateQuad(cordinate[7], cordinate[6], cordinate[5], cordinate[4], "handle", FVector(0, -1, 0));
	
	/*ù��° ���*/
	CreatePillar(FVector(P_length / 2 + 2, 0, 0));
	/*������ ���*/
	CreatePillar(FVector(trig_x - P_length/2 - 2, 0, trig_y));

	/*�ݺ��Ǵ� �κ� ����*/
	float startP = P_length / 2 + (P_length + G_length);
	float endP = H_length - P_length / 2;
	while(startP < endP)
	{ 
		CreatePillar(FVector(CalcTrigX(startP), 0, CalcTrigY(startP)));
		//glass �����!
		CreateGlass(startP);

		startP += (P_length + G_length);
	} 

	//������ ����κ��� Glass
	CreateQuad(
		FVector(CalcTrigX(startP - (P_length + G_length)), G_width, CalcTrigY(startP - (P_length + G_length)) + G_height + 10),
		FVector(CalcTrigX(endP), G_width, CalcTrigY(endP) + G_height + 10),
		FVector(CalcTrigX(endP), G_width, CalcTrigY(endP) + 10),
		FVector(CalcTrigX(startP - (P_length + G_length)), G_width, CalcTrigY(startP - (P_length + G_length)) + 10),
		"glass", FVector(0, 1, 0));
	CreateQuad(
		FVector(CalcTrigX(startP - (P_length + G_length)), -G_width, CalcTrigY(startP - (P_length + G_length)) + 10),
		FVector(CalcTrigX(endP), -G_width, CalcTrigY(endP) + 10),
		FVector(CalcTrigX(endP), -G_width, CalcTrigY(endP) + G_height + 10),
		FVector(CalcTrigX(startP - (P_length + G_length)), -G_width, CalcTrigY(startP - (P_length + G_length)) + G_height + 10),
		"glass", FVector(0, -1, 0));
	//material�� �����ϴ� �Լ�
	ApplyMaterial(data.materials);
}

void AGlassHandrailModel::CreatePillar(FVector std)
{
	float l = P_length / 2;
	float w = P_width / 2;
	float h = P_height + H_height/2;

	FVector cordinate[8];
	cordinate[0] = FVector(std.X - l, std.Y + w, std.Z);
	cordinate[1] = FVector(std.X + l, std.Y + w, std.Z);
	cordinate[2] = FVector(std.X + l, std.Y + w, std.Z + h);
	cordinate[3] = FVector(std.X - l, std.Y + w, std.Z + h);

	cordinate[4] = FVector(std.X - l, std.Y - w, std.Z);
	cordinate[5] = FVector(std.X + l, std.Y - w, std.Z);
	cordinate[6] = FVector(std.X + l, std.Y - w, std.Z + h);
	cordinate[7] = FVector(std.X - l, std.Y - w, std.Z + h);

	//���� side
	CreateQuad(cordinate[4], cordinate[0], cordinate[3], cordinate[7], "pillar", FVector(-1, 0, 0));
	//���� side
	CreateQuad(cordinate[3], cordinate[2], cordinate[6], cordinate[7], "pillar", FVector(0, 0, 1));
	//������ side
	CreateQuad(cordinate[1], cordinate[5], cordinate[6], cordinate[2], "pillar", FVector(1, 0, 0));
	//�Ʒ��� side
	CreateQuad(cordinate[4], cordinate[5], cordinate[1], cordinate[0], "pillar", FVector(0, 0, -1));
	//�ո�
	CreateQuad(cordinate[0], cordinate[1], cordinate[2], cordinate[3], "pillar", FVector(0, 1, 0));
	//�޸�
	CreateQuad(cordinate[7], cordinate[6], cordinate[5], cordinate[4], "pillar", FVector(0, -1, 0));
}

void AGlassHandrailModel::CreateGlass(float startP)
{
	FVector glassCord[8];
	glassCord[0] = FVector(CalcTrigX(startP - (P_length + G_length)), G_width, CalcTrigY(startP - (P_length + G_length)) + 10);
	glassCord[1] = FVector(CalcTrigX(startP), G_width, CalcTrigY(startP) + 10);
	glassCord[2] = FVector(CalcTrigX(startP), G_width, CalcTrigY(startP) + G_height + 10);
	glassCord[3] = FVector(CalcTrigX(startP - (P_length + G_length)), G_width, CalcTrigY(startP - (P_length + G_length)) + G_height + 10);

	glassCord[4] = FVector(CalcTrigX(startP - (P_length + G_length)), -G_width, CalcTrigY(startP - (P_length + G_length)) + 10);
	glassCord[5] = FVector(CalcTrigX(startP), -G_width, CalcTrigY(startP) + 10);
	glassCord[6] = FVector(CalcTrigX(startP), -G_width, CalcTrigY(startP) + G_height + 10);
	glassCord[7] = FVector(CalcTrigX(startP - (P_length + G_length)), -G_width, CalcTrigY(startP - (P_length + G_length)) + G_height + 10);

	CreateQuad(glassCord[0], glassCord[1], glassCord[2], glassCord[3], "glass", FVector(0, 1, 0));
	CreateQuad(glassCord[7], glassCord[6], glassCord[5], glassCord[4], "glass", FVector(0, -1, 0));
}

float AGlassHandrailModel::CalcTrigX(float length)
{
	return length * cos(angle*PI / 180);
}

float AGlassHandrailModel::CalcTrigY(float length)
{
	return length * sin(angle*PI / 180);
}
