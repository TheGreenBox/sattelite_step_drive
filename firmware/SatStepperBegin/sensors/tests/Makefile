CC=gcc
FLAGS=-std=c99 -I ..
UNITS=../gray_code_decoder.c
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
