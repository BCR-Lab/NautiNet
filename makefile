unit_tests: matrix_test algae_sensor_test


matrix_test: matrix_test.o Matrix.o MatrixFunctions.O
	g++ -o matrix_test matrix_test.o Matrix.o MatrixFunctions.o
	
matrix_test.o: matrix_test.cc Matrix.h MatrixFunctions.h
	g++ -c matrix_test.cc


algae_sensor_test: algae_sensor_test.o NNAlgaeSensor.o Matrix.o MatrixFunctions.o
	g++ -o algae_sensor_test algae_sensor_test.o NNAlgaeSensor.o Matrix.o MatrixFunctions.o

algae_sensor_test.o: algae_sensor_test.cc NNAlgaeSensor.h Matrix.h
	g++ -c algae_sensor_test.cc


NNAlgaeSensor.o: NNAlgaeSensor.cc NNAlgaeSensor.h Point3D.h
	g++ -c NNAlgaeSensor.cc
	
Matrix.o: Matrix.cc Matrix.h
	g++ -c Matrix.cc

MatrixFunctions.o: MatrixFunctions.cc MatrixFunctions.h
	g++ -c MatrixFunctions.cc