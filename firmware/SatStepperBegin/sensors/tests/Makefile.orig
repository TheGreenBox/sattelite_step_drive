CC=gcc
<<<<<<< HEAD
FLAGS=-std=c99 -I ..
UNITS=../gray_code_decoder.c
=======
FLAGS=-B ../ -std=c99 -DSAT_STEPPER___TEST
UNITS=../encoder.c
>>>>>>> 170f72a015767210695d26cad8e63195b5a5ed06
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
