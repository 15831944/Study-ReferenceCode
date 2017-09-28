// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"

//����� �� �ִ� ��� Procedural Mesh �� ������ ���Խ�Ų��.
#include "Model/MyModel.h"

#include "Model/StaticModel.h"
#include "Model/DynamicModel.h"
/*
#include "Model/Dynamic/WallModel.h"
#include "Model/Dynamic/FloorModel.h"
#include "Model/Dynamic/HipRoofModel.h"
#include "Model/Dynamic/FullStairModel.h"
#include "Model/Dynamic/HollowStairModel.h"
#include "Model/Dynamic/FixedWindowModel.h"
#include "Model/Dynamic/SlideWindowModel.h"
#include "Model/Dynamic/GlassHandrailModel.h"
#include "Model/Dynamic/BarhandrailModel.h"

#include "Model/Static/WindowModel.h"
#include "Model/Static/DoorModel.h"
#include "Model/Static/ColumnModel.h"
*/
#include "Model/Light/PointLightModel.h"
#include "Model/Light/SkyLightModel.h"
#include "Model/Light/SpotLightModel.h"

#include "ArchivaCamera.h"
#include "Xml/ArchivaXmlReader.h"


/**
* \brief �׽�Ʈ�� ���� �α� ī�װ� ����
*
* ������Ʈ�� �׽�Ʈ�ϱ� ����, �ʿ��� �α� ī�װ��� �����ؼ� ����Ѵ�.
*/

//�⺻���� �α� ī�װ�
DECLARE_LOG_CATEGORY_EXTERN(MyLog, Log, All);

//���� ���� ��, �߻��ϴ� �α� ī�װ�
DECLARE_LOG_CATEGORY_EXTERN(MyInit, Log, All);

//�ݵ�� Ȯ���ؾ� �� ġ������ ���� �α� ī�װ�
DECLARE_LOG_CATEGORY_EXTERN(MyError, Log, All);