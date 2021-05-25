.PHONY=clean all

all: tcpEchoClientTest tcpEchoAddrinfo udpTest tcpProxy
clean:	
	- rm -f *.o  tcpEchoClient tcpEchoServer udpTest tcpProxy tcpEchoClientTest tcpEchoAddrinfo

COMMON =  logger.o addressUtility.o
tcpEchoClientTest:      tcpEchoClientTest.o  tcpClientUtil.o    $(COMMON)
tcpEchoAddrinfo:      tcpEchoAddrinfo.o  tcpServerUtil.o    $(COMMON)
udpTest:	    UDPTest.o logger.o	    
tcpProxy: tcpProxy.o buffer.o tcpServerUtil.o $(COMMON)