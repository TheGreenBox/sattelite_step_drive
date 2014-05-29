HELLO_MSG="Documentation for step motor sattelaite student work"
PRODUCT_DIR='product'

help: hello
	@echo "----------------------------------------"
	@echo
	@echo "List of available options:"
	@echo -e 	"\t full - full doc"
	@echo -e 	"\t c112 - course 112 milestone documentation"
	@echo -e 	"\t all - all docs"
	@echo -e 	"\t plan - workshop report (full plan)"
	@echo -e 	"\t ecology - only ecology part"
	@echo
	@echo "----------------------------------------"
	@echo

hello:
	@echo "========================================"
	@echo
	@echo ${HELLO_MSG}
	@echo "----------------------------------------"
	@echo

clean:
	@rm -f ${PRODUCT_DIR}/*

prepare:
	@mkdir -p ${PRODUCT_DIR}/

all: full c112 plan ecology pcb_develop economics

full: hello prepare
	@latex -output-directory=${PRODUCT_DIR} -output-format=pdf src/main_full.tex

c112: hello prepare
	@latex -output-directory=${PRODUCT_DIR} -output-format=pdf src/obsolete/main_c112.tex

plan: hello prepare
	@latex -output-directory=${PRODUCT_DIR} -output-format=pdf src/practice_report/main_plan.tex

ecology: hello prepare
	@latex -output-directory=${PRODUCT_DIR} -output-format=pdf src/ecology/main_ecology.tex

pcb_develop: hello prepare
	@latex -output-directory=${PRODUCT_DIR} -output-format=pdf src/pcb_develop/main_pcb_develop.tex

economics: hello prepare
	@latex -output-directory=${PRODUCT_DIR} -output-format=pdf src/economics/main_economics.tex
