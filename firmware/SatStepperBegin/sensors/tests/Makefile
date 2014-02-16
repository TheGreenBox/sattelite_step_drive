CC=gcc
FLAGS=-B ../ -std=c99 -DSAT_STEPPER___TEST
UNITS=../encoder.c
WORK_DIR=product

all: prepare
	@echo '/********************************************************/'
	@echo '/********************************************************/'
	${CC} ${FLAGS} ${UNITS} test.c -o ${WORK_DIR}/test
	@echo '/********************************************************/'

prepare:
	mkdir -p ${WORK_DIR}

clean:
	rm -r -f ${WORK_DIR}
