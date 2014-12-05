# Utility classes and functions used by many parts of the program.
GLOBAL_INCLUDE_LIBS = Point3D.o Matrix.o MatrixFunctions.o

# The robot and all its components.
ROBOT_INCLUDE_LIBS = NNRobot.o NNAlgaeSensorArray.o NNAlgaeSensor.o NNCollisionSensor.o NNProximitySensor.o NNSensorUtility.o NNLocomotion.o

# The simulated world and the utility functions it uses.
WORLD_INCLUDE_LIBS = NNWorld.o NNGeometryFunctions.o


COMPILER = g++


all: global_libraries robot_libraries world_libraries unit_tests


clean:
	rm *.o *_test
	
getversion:
	$(COMPILER) --version
	

global_libraries: $(GLOBAL_INCLUDE_LIBS)

robot_libraries: $(ROBOT_INCLUDE_LIBS)

world_libraries: $(WORLD_INCLUDE_LIBS)

unit_tests: matrix_test geometry_test algae_sensor_test collision_sensor_test proximity_sensor_test world_test robot_test


geometry_test: geometry_test.o NNGeometryFunctions.o $(GLOBAL_INCLUDE_LIBS)
	$(COMPILER) -o geometry_test geometry_test.o NNGeometryFunctions.o $(GLOBAL_INCLUDE_LIBS)
	
geometry_test.o: geometry_test.cc NNGeometryFunctions.h
	$(COMPILER) -c geometry_test.cc


matrix_test: matrix_test.o $(GLOBAL_INCLUDE_LIBS)
	$(COMPILER) -o matrix_test matrix_test.o $(GLOBAL_INCLUDE_LIBS)
	
matrix_test.o: matrix_test.cc Matrix.h MatrixFunctions.h
	$(COMPILER) -c matrix_test.cc


algae_sensor_test: algae_sensor_test.o $(WORLD_INCLUDE_LIBS) $(ROBOT_INCLUDE_LIBS) $(GLOBAL_INCLUDE_LIBS)
	$(COMPILER) -o algae_sensor_test algae_sensor_test.o $(WORLD_INCLUDE_LIBS) $(ROBOT_INCLUDE_LIBS)  $(GLOBAL_INCLUDE_LIBS)

algae_sensor_test.o: algae_sensor_test.cc NNAlgaeSensor.h Matrix.h
	$(COMPILER) -c algae_sensor_test.cc
	

collision_sensor_test: collision_sensor_test.o $(WORLD_INCLUDE_LIBS) $(ROBOT_INCLUDE_LIBS) $(GLOBAL_INCLUDE_LIBS)
	$(COMPILER) -o collision_sensor_test collision_sensor_test.o $(WORLD_INCLUDE_LIBS) $(ROBOT_INCLUDE_LIBS) $(GLOBAL_INCLUDE_LIBS)

collision_sensor_test.o: collision_sensor_test.cc NNCollisionSensor.h Matrix.h
	$(COMPILER) -c collision_sensor_test.cc
	
	
proximity_sensor_test: proximity_sensor_test.o $(WORLD_INCLUDE_LIBS) $(ROBOT_INCLUDE_LIBS) $(SENSOR_INCLUDE_LIBS) $(GLOBAL_INCLUDE_LIBS)
	$(COMPILER) -o proximity_sensor_test proximity_sensor_test.o $(WORLD_INCLUDE_LIBS) $(ROBOT_INCLUDE_LIBS)  $(SENSOR_INCLUDE_LIBS) $(GLOBAL_INCLUDE_LIBS)
	
proximity_sensor_test.o: proximity_sensor_test.cc NNProximitySensor.h
	$(COMPILER) -c proximity_sensor_test.cc

	
world_test: world_test.o $(WORLD_INCLUDE_LIBS) $(GLOBAL_INCLUDE_LIBS)
	$(COMPILER) -o world_test world_test.o $(WORLD_INCLUDE_LIBS) $(GLOBAL_INCLUDE_LIBS)
	
world_test.o: world_test.cc NNWorld.h
	$(COMPILER) -c world_test.cc
	
robot_test: robot_test.o $(ROBOT_INCLUDE_LIBS) $(WORLD_INCLUDE_LIBS) $(GLOBAL_INCLUDE_LIBS)
	$(COMPILER) -o robot_test robot_test.o $(ROBOT_INCLUDE_LIBS) $(WORLD_INCLUDE_LIBS) $(GLOBAL_INCLUDE_LIBS)
	
robot_test.o: robot_test.cc NNRobot.h NNAlgaeSensor.h NNWorld.h
	$(COMPILER) -c robot_test.cc


NNAlgaeSensor.o: NNAlgaeSensor.cc NNAlgaeSensor.h NNSensorUtility.h Matrix.h Point3D.h
	$(COMPILER) -c NNAlgaeSensor.cc
	
NNAlgaeSensorArray.o: NNAlgaeSensorArray.cc NNAlgaeSensorArray.h NNAlgaeSensor.h Point3D.h
	$(COMPILER) -c NNAlgaeSensorArray.cc
		
NNCollisionSensor.o: NNCollisionSensor.cc NNCollisionSensor.h NNSensorUtility.h Matrix.h Point3D.h
	$(COMPILER) -c NNCollisionSensor.cc
	
NNProximitySensor.o: NNProximitySensor.cc NNProximitySensor.h Matrix.h Point3D.h
	$(COMPILER) -c NNProximitySensor.cc
	
NNSensorUtility.o: NNSensorUtility.cc NNSensorUtility.h
	$(COMPILER) -c NNSensorUtility.cc
	
NNLocomotion.o: NNLocomotion.cc NNLocomotion.h Matrix.h Point3D.h
	$(COMPILER) -c NNLocomotion.cc

NNRobot.o: NNRobot.cc NNRobot.h Matrix.h Point3D.h NNAlgaeSensorArray.h
	$(COMPILER) -c NNRobot.cc
	
NNWorld.o: NNWorld.cc NNWorld.h Point3D.h
	$(COMPILER) -c NNWorld.cc
	
NNGeometryFunctions.o: NNGeometryFunctions.cc Point3D.h Matrix.h MatrixFunctions.h
	$(COMPILER) -c NNGeometryFunctions.cc

Matrix.o: Matrix.cc Matrix.h
	$(COMPILER) -c Matrix.cc

MatrixFunctions.o: MatrixFunctions.cc MatrixFunctions.h
	$(COMPILER) -c MatrixFunctions.cc

Point3D.o: Point3D.cc Point3D.h
	$(COMPILER) -c Point3D.cc