all: AlgaeSensor

AlgaeSensor: NNAlgaeSensor.o NNAlgaeSensorUnitTest.o
	g++ -o AlgaeSensor NNAlgaeSensor.o NNAlgaeSensorUnitTest.o

NNAlgaeSensorUnitTest.o: NNalgaeSensorUnitTest.cc Point3D.h
	g++ -c NNAlgaeSensorUnitTest.cc

NNAlgaeSensor.o: NNAlgaeSensor.cc NNAlgaeSensor.h Point3D.h
	g++ -c NNAlgaeSensor.cc
	
matrix_test: matrix_test.o Matrix.o
	g++ -o matrix_test matrix_test.o Matrix.o
	
matrix_test.o: matrix_test.cc Matrix.h
	g++ -c matrix_test.cc

Matrix.o: Matrix.cc Matrix.h
	g++ -c Matrix.cc
