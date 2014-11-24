GLOBAL_INCLUDE_LIBS = Point3D.o Matrix.o MatrixFunctions.o

SENSOR_INCLUDE_LIBS = NNRobot.o NNWorld.o NNGeometryFunctions.o


all: global_libraries sensor_libraries unit_tests

global_libraries: Point3D.o Matrix.o MatrixFunctions.o

sensor_libraries: NNRobot.o NNWorld.o NNGeometryFunctions.o

unit_tests: matrix_test algae_sensor_test collision_sensor_test world_test geometry_test


geometry_test: geometry_test.o NNGeometryFunctions.o $(GLOBAL_INCLUDE_LIBS)
	g++ -o geometry_test geometry_test.o NNGeometryFunctions.o $(GLOBAL_INCLUDE_LIBS)
	
geometry_test.o: geometry_test.cc NNGeometryFunctions.h
	g++ -c geometry_test.cc


matrix_test: matrix_test.o $(GLOBAL_INCLUDE_LIBS)
	g++ -o matrix_test matrix_test.o $(GLOBAL_INCLUDE_LIBS)
	
matrix_test.o: matrix_test.cc Matrix.h MatrixFunctions.h
	g++ -c matrix_test.cc


algae_sensor_test: algae_sensor_test.o NNAlgaeSensor.o $(SENSOR_INCLUDE_LIBS) $(GLOBAL_INCLUDE_LIBS)
	g++ -o algae_sensor_test algae_sensor_test.o NNAlgaeSensor.o $(SENSOR_INCLUDE_LIBS) $(GLOBAL_INCLUDE_LIBS)

algae_sensor_test.o: algae_sensor_test.cc NNAlgaeSensor.h Matrix.h
	g++ -c algae_sensor_test.cc
	

collision_sensor_test: collision_sensor_test.cc NNCollisionSensor.o $(SENSOR_INCLUDE_LIBS) $(GLOBAL_INCLUDE_LIBS)
	g++ -o collision_sensor_test collision_sensor_test.o NNCollisionSensor.o $(SENSOR_INCLUDE_LIBS) $(GLOBAL_INCLUDE_LIBS)

collision_sensor_test.o: collision_sensor_test.cc NNCollisionSensor.h Matrixh
	g++ -c collision_sensor_test.cc

	
world_test: world_test.o NNWorld.o NNGeometryFunctions.o $(INCLUDE_LIBS)
	g++ -o world_test world_test.o NNWorld.o NNGeometryFunctions.o $(INCLUDE_LIBS)
	
world_test.o: world_test.cc NNWorld.h
	g++ -c world_test.cc


NNAlgaeSensor.o: NNAlgaeSensor.cc NNAlgaeSensor.h NNSensorUtility.h Point3D.h
	g++ -c NNAlgaeSensor.cc
	
NNCollisionSensor.o: NNCollisionSensor.cc NNCollisionSensor.h NNSensorUtility.h Point3D.h
	g++ -c NNCollisioNSensor.cc

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