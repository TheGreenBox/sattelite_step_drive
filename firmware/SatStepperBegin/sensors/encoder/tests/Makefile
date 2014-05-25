CC=gcc
UNITS=../gray_code_decoder.c
FLAGS=-B ../ -std=c99 -DSAT_STEPPER___TEST
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
