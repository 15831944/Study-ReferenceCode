// Fill out your copyright notice in the Description page of Project Settings.

#include "Archiva.h"

IMPLEMENT_PRIMARY_GAME_MODULE(FDefaultGameModuleImpl, Archiva, "Archiva");

/**
* \brief �׽�Ʈ�� ���� �α� ī�װ� ����
*
* ������Ʈ�� �׽�Ʈ�ϱ� ����, �ʿ��� �α� ī�װ��� �����ؼ� ����Ѵ�.
*/

//�⺻���� �α� ī�װ�
DEFINE_LOG_CATEGORY(MyLog);

//���� ���� ��, �߻��ϴ� �α� ī�װ�
DEFINE_LOG_CATEGORY(MyInit);

//�ݵ�� Ȯ���ؾ� �� ġ������ ���� �α� ī�װ�
DEFINE_LOG_CATEGORY(MyError);

/*
* <C++�� Unreal�� ����>
*	<��>
*	���� ������ Dynamic�� Static�� �ִ�. ��� ���� MyModel�� ��ӹ޴´�.
*	Dynamic�� �ٽ����� �κ��� ����ϰ� ������, ��� Dynamic ���� DynamicModel�� ��ӹ޴´�.
*	Light�� ������ ���� Static�� ���� ���������� �ɵ������� ��ġ�ϱ� ����, Ư���� ���¸� ������.
*
*		<�� �߰��� ���ǻ���>
*		���� �߰��� ���� XmlReader, ModelData, Blueprint �� MaterialList, ArchivaGameMode ��
*		�����Ǿ� �ִ� ���� ���� ���Ǹ� ���Ѵ�.
*
*	<XML>
*	XmlReader�� Ȱ���Ͽ�, XML�� �а� ModelData�� �𵨰� XML ���̿� �����͸� �����ϴ� ������ �Ѵ�.
*
*	<���� ������ ���� ���ǻ���>
*	BP_SunControl�� ��ġ�ؾ� Sun�� ������ �� �ִ�.
*	NavMeshBoundVolume�� ��ġ�ؾ� Ŭ���� �̵��� �� �� �ִ�.
*	PlayerStart�� ��ġ�ؾ� Home�� �̿��� �� �ִ�.
*
*/

/*
*	TODO:
*	<���׸��>
*	1. Camera�� XML���� �߰��Ǹ� ��ȯ�� �̻������� ������ �ִ�. >> XML���� �߰� �� ��, ��ȣ�� ������ 0���� ���������� ����Ǿ�� �Ѵ�.
*	2. BirdView���� CharacterView�� ��ȯ�� ��, ���ڿ������� ���� �ִ�. >> BirdView�� LandScape�� Collision�� ������ �Ѵ�.
*	3. Camera������ ��ȯ���� ����Ŭ���� �ؾ� �۵��ϴ� ���װ� �ִ�. >> ���� �Ҹ�
*	4. Floor�� ǥ���� ���������� ���װ� �߻��Ѵ�. >> Floor�� �����ϴ� ��Ģ�� ����� �����ϸ�(y������ ���� �̵�), �� ��ȯ������ �ٵ��ǰ� ���� ��ǥ�� �߰��Ǿ�� �Ѵ�.
*	5. Present ����� ��� �Ŀ�, Tab & Go�� ���� �ִ�. >> ���� �Ҹ�
*	6. NavMesh�� SelectModel�� ������ Input�� ����Ͽ� �켱���� ��Ż�� ���� ���װ� �ִ�. >> Shift + Left Mouse�� SelectModel��, NavMesh�� Left Mouse��
*/