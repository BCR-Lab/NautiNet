all: AlgaeSensor

AlgaeSensor: NNAlgaeSensor.o NNAlgaeSensorUnitTest.o
	g++ -o AlgaeSensor NNAlgaeSensor.o NNAlgaeSensorUnitTest.o

NNAlgaeSensorUnitTest.o: NNalgaeSensorUnitTest.cc Point3D.h
	g++ -c NNAlgaeSensorUnitTest.cc

NNAlgaeSensor.o: NNAlgaeSensor.cc NNAlgaeSensor.h Point3D.h
	g++ -c NNAlgaeSensor.cc