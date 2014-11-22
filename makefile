INCLUDE_LIBS = Point3D.o Matrix.o MatrixFunctions.o


all: libraries unit_tests

libraries: Point3D.o Matrix.o MatrixFunctions.o

unit_tests: matrix_test algae_sensor_test world_test geometry_test


geometry_test: geometry_test.o NNGeometryFunctions.o $(INCLUDE_LIBS)
	g++ -o geometry_test geometry_test.o NNGeometryFunctions.o $(INCLUDE_LIBS)
	
geometry_test.o: geometry_test.cc NNGeometryFunctions.h
	g++ -c geometry_test.cc


matrix_test: matrix_test.o $(INCLUDE_LIBS)
	g++ -o matrix_test matrix_test.o $(INCLUDE_LIBS)
	
matrix_test.o: matrix_test.cc Matrix.h MatrixFunctions.h
	g++ -c matrix_test.cc


algae_sensor_test: algae_sensor_test.o NNAlgaeSensor.o NNRobot.o $(INCLUDE_LIBS)
	g++ -o algae_sensor_test algae_sensor_test.o NNAlgaeSensor.o NNRobot.o $(INCLUDE_LIBS)

algae_sensor_test.o: algae_sensor_test.cc NNAlgaeSensor.h Matrix.h
	g++ -c algae_sensor_test.cc
	
	
world_test: world_test.o NNWorld.o NNGeometryFunctions.o $(INCLUDE_LIBS)
	g++ -o world_test world_test.o NNWorld.o NNGeometryFunctions.o $(INCLUDE_LIBS)
	
world_test.o: world_test.cc NNWorld.h
	g++ -c world_test.cc


NNAlgaeSensor.o: NNAlgaeSensor.cc NNAlgaeSensor.h Point3D.h
	g++ -c NNAlgaeSensor.cc
	
NNRobot.o: NNRobot.cc NNRobot.h Matrix.h Point3D.h
	g++ -c NNRobot.cc
	
NNWorld.o: NNWorld.cc NNWorld.h Point3D.h
	g++ -c NNWorld.cc
	
NNGeometryFunctions.o: NNGeometryFunctions.cc Point3D.h Matrix.h MatrixFunctions.h
	g++ -c NNGeometryFunctions.cc

Matrix.o: Matrix.cc Matrix.h
	g++ -c Matrix.cc

MatrixFunctions.o: MatrixFunctions.cc MatrixFunctions.h
	g++ -c MatrixFunctions.cc

Point3D.o: Point3D.cc Point3D.h
	g++ -c Point3D.cc