CXX = g++
LIBS = -I/usr/include/mysql++ -I/usr/include/mysql -lmysqlpp -lldns
 
all: 
	$(CXX) --std=c++11 *.cpp -o dpt $(LIBS)

clean:
	rm dpt
