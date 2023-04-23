CXX ?= g++

DEBUG ?= 1
ifeq ($(DEBUG), 1)
    CXXFLAGS += -g
else
    CXXFLAGS += -O2

endif

carpark: main.cpp ./CarPark.cpp ./Log/Log.cpp 
	$(CXX) -o carpark  $^ $(CXXFLAGS) -lpthread

carParkCapTest: ./test/carParkCapTest.cpp ./CarPark.cpp ./Log/Log.cpp 
	$(CXX) -o ./test/carParkCapTest  $^ $(CXXFLAGS) -lpthread

idCardTest: ./test/idCardTest.cpp ./CarPark.cpp ./Log/Log.cpp 
	$(CXX) -o ./test/idCardTest  $^ $(CXXFLAGS) -lpthread

modeChangeTest: ./test/modeChangeTest.cpp ./CarPark.cpp ./Log/Log.cpp 
	$(CXX) -o ./test/modeChangeTest  $^ $(CXXFLAGS) -lpthread


clean:
	rm  -r carpark
