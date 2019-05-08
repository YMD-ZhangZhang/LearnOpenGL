#include "Demo1.h"
#include "Demo2.h"
#include "Demo3.h"

int main(void)
{
	// 一个箱子
	//Demo1* d1 = new Demo1();
	//delete d1;

	// 2D示例
	//Demo2* d2 = new Demo2();
	//delete d2;
	
	// 3D场景和相机示例
	Demo3* d3 = new Demo3();
	delete d3;

	//
	return 0;
}