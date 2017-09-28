// Fill out your copyright notice in the Description page of Project Settings.

#include "Archiva.h"
#include "WallModel.h"


// Sets default values
AWallModel::AWallModel()
{
}

void AWallModel::Create(FModelData data)
{
	//������ �ִ� Mesh ���¸� �ı�
	model->ClearAllMeshSections();

	meshNum = 0;
	SavedMaterial = data.materials;

	//�Էµ� ���� ���� ��ǥ���� �ٽ� ���
	length = data.size.X;
	width = data.size.Y / 2;
	height = data.size.Z;

	cordOutline[0] = FVector(0, width, 0);
	cordOutline[1] = FVector(length, width, 0);
	cordOutline[2] = FVector(length, width, height);
	cordOutline[3] = FVector(0, width, height);

	cordOutline[4] = FVector(0, -width, 0);
	cordOutline[5] = FVector(length, -width, 0);
	cordOutline[6] = FVector(length, -width, height);
	cordOutline[7] = FVector(0, -width, height);

	//���������� �����Ǵ� �κ� �����
	
	//Start Point�� �ִ� ��
	CreateQuad(cordOutline[4], cordOutline[0], cordOutline[3], cordOutline[7], "out", FVector(-1, 0, 0));

	//���� ��
	CreateQuad(cordOutline[3], cordOutline[2], cordOutline[6], cordOutline[7], "side", FVector(0, 0, 1));

	//End Point�� �ִ� ��
	CreateQuad(cordOutline[1], cordOutline[5], cordOutline[6], cordOutline[2], "out", FVector(1, 0, 0));

	//�Էµ� Hole�� �ִٸ�!
	if (data.holes.Num() > 0) {

		//��߰� ���� �޴���� ������ �Ѵ�...

		//��ߺκ�
		float hole_X = data.holes[0].position.X;
		float hole_Y = data.holes[0].position.Y;

		float hole_Length = data.holes[0].length/2;
		float hole_height = data.holes[0].height;

		cordHole[0] = FVector((hole_X - hole_Length),	width,	hole_Y					);
		cordHole[1] = FVector((hole_X + hole_Length),	width,	hole_Y					);
		cordHole[2] = FVector((hole_X + hole_Length),	width,	hole_Y + hole_height	);
		cordHole[3] = FVector((hole_X - hole_Length),	width,	hole_Y + hole_height	);

		cordHole[4] = FVector((hole_X - hole_Length),	-width,	hole_Y					);
		cordHole[5] = FVector((hole_X + hole_Length),	-width,	hole_Y					);
		cordHole[6] = FVector((hole_X + hole_Length),	-width,	hole_Y + hole_height	);
		cordHole[7] = FVector((hole_X - hole_Length),	-width,	hole_Y + hole_height	);

		//ù��° hole�� ��ġ���� �� ����!
		
		//���� ��
		CreateQuad(cordOutline[7], FVector(cordHole[7].X, cordHole[7].Y, height), FVector(cordHole[4].X, cordHole[4].Y, 0), cordOutline[4], "in", FVector(0, -1, 0));
		
		//�ܺ� ��
		CreateQuad(cordOutline[0], FVector(cordHole[0].X, cordHole[0].Y, 0), FVector(cordHole[3].X, cordHole[3].Y, height), cordOutline[3], "out", FVector(0, 1, 0));
		
		//�ٴ� ��

		//�ݺ������� �κ�!
		for (int i = 0; i < data.holes.Num(); i++) {
			MakeHole(data.holes[i]);
			//���� Hole�� �����Ѵٸ�!
			if (data.holes.IsValidIndex(i+1)) {
				MakeConnection(data.holes[i], data.holes[i + 1]);
			}
			//������ Hole�̾��ٸ�!
			else {
				//���� ��
				CreateQuad(cordOutline[5], FVector(data.holes[i].position.X + (data.holes[i].length / 2), -width, 0), FVector(data.holes[i].position.X + (data.holes[i].length / 2), -width, height), cordOutline[6], "in", FVector(0, -1, 0));
				//�ܺ� ��
				CreateQuad(FVector(data.holes[i].position.X + (data.holes[i].length / 2), width, 0), cordOutline[1], cordOutline[2], FVector(data.holes[i].position.X + (data.holes[i].length / 2), width, height), "out", FVector(0,1,0));
			}
		}
	}
	//�Էµ� Hole�� ���ٸ�!
	else {
		//���� ��
		CreateQuad(cordOutline[5], cordOutline[4], cordOutline[7], cordOutline[6], "in", FVector(0,-1,0));
		//�ܺ� ��
		CreateQuad(cordOutline[0], cordOutline[1], cordOutline[2], cordOutline[3], "out", FVector(0, 1, 0));
	}

	//material�� �����ϴ� �Լ�
	ApplyMaterial(data.materials);

}

void AWallModel::MakeHole(FHole hole) 
{
	//���� ���� hole�� �µ��� ���� ����
	float hole_X = hole.position.X;
	float hole_Y = hole.position.Y;

	float hole_Length = hole.length / 2;
	float hole_height = hole.height;

	cordHole[0] = FVector((hole_X - hole_Length), width, hole_Y);
	cordHole[1] = FVector((hole_X + hole_Length), width, hole_Y);
	cordHole[2] = FVector((hole_X + hole_Length), width, hole_Y + hole_height);
	cordHole[3] = FVector((hole_X - hole_Length), width, hole_Y + hole_height);

	cordHole[4] = FVector((hole_X - hole_Length), -width, hole_Y);
	cordHole[5] = FVector((hole_X + hole_Length), -width, hole_Y);
	cordHole[6] = FVector((hole_X + hole_Length), -width, hole_Y + hole_height);
	cordHole[7] = FVector((hole_X - hole_Length), -width, hole_Y + hole_height);
	//hole�� Door Ÿ������ Window Ÿ������ ��������!

	//���̰� 0�̹Ƿ� Door Ÿ���̴�!
	if (hole_Y == 0) {

		//���� side�� ����!
		CreateQuad(cordHole[7], cordHole[3], cordHole[0], cordHole[4], "side", FVector(1, 0, 0));
		CreateQuad(cordHole[7], cordHole[6], cordHole[2], cordHole[3], "side", FVector(0, 0, -1));
		CreateQuad(cordHole[2], cordHole[6], cordHole[5], cordHole[1], "side", FVector(-1, 0, 0));

		//���� ���� �κ��� ������!

		//���� �κ��� ���κ�
		CreateQuad(FVector(cordHole[7].X, cordHole[7].Y, height), FVector(cordHole[6].X, cordHole[6].Y, height), cordHole[6], cordHole[7], "in", FVector(0, -1, 0));

		//���� �κ��� �ܺκ�
		CreateQuad(cordHole[3], cordHole[2], FVector(cordHole[2].X, cordHole[2].Y, height), FVector(cordHole[3].X, cordHole[3].Y, height), "out", FVector(0, 1, 0));
	}
	//���̰� 0�� �ƴϹǷ� Window Ÿ���̴�!
	else
	{
		//Window�� side�� ����!
		CreateQuad(cordHole[7], cordHole[3], cordHole[0], cordHole[4], "side", FVector(1, 0, 0));
		CreateQuad(cordHole[7], cordHole[6], cordHole[2], cordHole[3], "side", FVector(0, 0, -1));
		CreateQuad(cordHole[2], cordHole[6], cordHole[5], cordHole[1], "side", FVector(-1, 0, 0));
		CreateQuad(cordHole[0], cordHole[1], cordHole[5], cordHole[4], "side", FVector(0, 0, -1));
		//���� �Ʒ� �κ��� ���κ�
		//��
		CreateQuad(FVector(cordHole[7].X, cordHole[7].Y, height), FVector(cordHole[6].X, cordHole[6].Y, height), cordHole[6], cordHole[7], "in", FVector(0 ,-1, 0));
		//�Ʒ�
		CreateQuad(cordHole[4], cordHole[5], FVector(cordHole[5].X, cordHole[5].Y, 0), FVector(cordHole[4].X, cordHole[4].Y, 0), "in", FVector(0, -1, 0));
		
		//���� �Ʒ� �κ��� �ܺκ�
		//��
		CreateQuad(cordHole[3], cordHole[2], FVector(cordHole[2].X, cordHole[2].Y, height), FVector(cordHole[3].X, cordHole[3].Y, height), "out", FVector(0, 1, 0));
		//�Ʒ�
		CreateQuad(FVector(cordHole[0].X, cordHole[0].Y, 0), FVector(cordHole[1].X, cordHole[1].Y, 0), cordHole[1], cordHole[0], "out", FVector(0, 1, 0));
	}

}

void AWallModel::MakeConnection(FHole pre, FHole post)
{
	//���� ��
	CreateQuad(FVector(pre.position.X + (pre.length / 2), -width, height), FVector(post.position.X - (post.length / 2), -width, height), FVector(post.position.X - (post.length / 2), -width, 0), FVector(pre.position.X + (pre.length / 2), -width, 0), "in", FVector(0,-1,0));

	//�ܺ� ��
	CreateQuad(FVector(pre.position.X + (pre.length / 2), width, 0), FVector(post.position.X - (post.length / 2), width, 0), FVector(post.position.X - (post.length / 2), width, height), FVector(pre.position.X + (pre.length / 2), width, height), "out", FVector(0, 1, 0));
}

