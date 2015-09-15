all: customer_app test_driver

customer_app: customer_app.o BSTree.o Customer.o Node.o
	g++ -o customer_app customer_app.o BSTree.o Customer.o Node.o

test_driver: test_driver.o BSTree.o Customer.o Node.o
	g++ -o test_driver test_driver.o BSTree.o Customer.o Node.o

customer_app.o: customer_app.cpp BSTree.h Customer.h Node.h
	g++ -c customer_app.cpp

test_driver.o: test_driver.cpp BSTree.h Customer.h Node.h
	g++ -c test_driver.cpp

BSTree.o: BSTree.cpp BSTree.h Customer.h Node.h
	g++ -c BSTree.cpp

Customer.o: Customer.cpp BSTree.h Customer.h Node.h
	g++ -c Customer.cpp

Node.o: Node.cpp BSTree.h Customer.h Node.h
	g++ -c Node.cpp

clean:
	rm -f *.o customer_app test_driver