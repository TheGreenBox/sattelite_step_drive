HELLO_MSG="Documentation for step motor sattelaite student work"
PRODUCT_DIR='product'
PARTIAL_DIR='src/partial_compiles'

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

all: full c112 plan ecology

full: hello prepare
	@latex -output-directory=${PRODUCT_DIR} -output-format=pdf src/main_full.tex

c112: hello prepare
	@latex -output-directory=${PRODUCT_DIR} -output-format=pdf ${PARTIAL_DIR}/main_c112.tex

plan: hello prepare
	@latex -output-directory=${PRODUCT_DIR} -output-format=pdf ${PARTIAL_DIR}/main_plan.tex

ecology: hello prepare
	@latex -output-directory=${PRODUCT_DIR} -output-format=pdf ${PARTIAL_DIR}/only_ecology.tex
