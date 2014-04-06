HELLO_MSG="Documentation for step motor sattelaite student work"
PRODUCT_DIR='product'
PARTIAL_DIR='src/partial_compiles'

help: hello
	@echo "----------------------------------------"
	@echo
	@echo "  * if you want to build the course 112 milestone documentation please get the /make c112/"
	@echo
	@echo "  * if you want to build full doc please get the /make full/"
	@echo
	@echo "  * if you want to build all docs please get the /make all/"
	@echo
	@echo "  * if you want to build workshop report (full plan) please get the /make plan/"
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

all: full c112 plan

full: hello prepare
	@latex -output-directory=${PRODUCT_DIR} -output-format=pdf src/main_full.tex

c112: hello prepare
	@latex -output-directory=${PRODUCT_DIR} -output-format=pdf ${PARTIAL_DIR}/main_c112.tex

plan: hello prepare
	@latex -output-directory=${PRODUCT_DIR} -output-format=pdf ${PARTIAL_DIR}/main_plan.tex

