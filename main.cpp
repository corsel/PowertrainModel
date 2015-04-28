#include <iostream>
#include "Utilities.h"
#include "Engine.h"
#include "Test.h"

int main()
{
	EngineDescriptor desc;
	//Tork egrisinin data noktaları
	desc.appendTorqueDataPoint(0.0f, 0.1f);
	desc.appendTorqueDataPoint(4.0f, 8.0f);
	desc.appendTorqueDataPoint(2.0f, 3.0f);
	desc.appendTorqueDataPoint(5.0f, 2.0f);
	desc.appendTorqueDataPoint(1.0f, 2.0f);
	desc.appendTorqueDataPoint(3.0f, 5.0f);
	//Rolanti
	desc.idleThrottle = 0.1f;
	//Volan tekeri eylemsizligi
	desc.inertia = 6.0f;
	//Motordaki surtunme kayiplari (rpm ile carpilip net torku dusurur)
	desc.internalLossFactor = 0.3f;

	//Verilen tork egrisi kontrol noktalarinin ara degerlerini hesaplayip 
	//"./PowertrainModel/Test/Interpolate_Test_Output.txt" dosyasına yazar.
	Test::interpolateTest(desc, 0.0f, 6.0f, 0.1f);

	//Motorun 0.02 ms zaman araligi, 20.0 birim yuk ve 0.03 sabit gaza basma ile zamana gore tork ciktisi 
	//ve rpm'ini, "./PowertrainModel/Test/Interpolate_Test_Output.txt" dosyasina yazar.
	Engine engine(desc, 0.02f); //50 fps
	Test::engineTest(engine, 20.0f, 0.03f);
	/*
	//Matematik araclari henuz tam calismiyor
	float **testMatrix = new float*[4];
	for (int i = 0; i < 4; i++)
	{
		testMatrix[i] = new float[4];
		for (int j = 0; j < 4; j++)
		{
			testMatrix[i][j] = 4 * i + j + 1;
		}
	}
	
	Test::print4x4Matrix(testMatrix);
	MathTools::getUpperTriangleMatrix(testMatrix);
	Test::print4x4Matrix(testMatrix);
	*/
	int a; std::cin >> a;

	return 0;
}