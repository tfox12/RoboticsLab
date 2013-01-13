uart_test: uart_test.cpp gpio.o uart.o
	g++ -o uart_test uart_test.cpp gpio.o uart.o
gpio.o: gpio.h gpio.cpp
	g++ -c gpio.cpp
uart.o: uart.h uart.cpp
	g++ -c uart.cpp
clean:
	rm uart_test
	rm gpio.o
	rm uart.o
