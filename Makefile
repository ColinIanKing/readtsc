BINDIR=/usr/bin

LDFLAGS += -static
CFLAGS += -O3

readtsc: readtsc.o
	$(CC) readtsc.o -o readtsc
	strip readtsc

clean:
	rm -f readtsc readtsc.o readtsc*snap

install: readtsc
	mkdir -p ${DESTDIR}${BINDIR}
	cp readtsc ${DESTDIR}${BINDIR}

