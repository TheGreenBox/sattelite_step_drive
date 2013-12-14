HELLO_MSG="Documentation for step motor sattelaite  student work"
PRODUCT_DIR='product'

help: hello 
	@echo "----------------------------------------"
	@echo 
	@echo "  * if you want to build the course 112 milestone documentation please get the /make c112/"
	@echo 
	@echo "  * if you want to build full doc please get the /make all/"
	@echo 
	@echo "----------------------------------------"
	@echo 

hello: 
	@echo "========================================"
	@echo 
	@echo "    "${HELLO_MSG}
	@echo "----------------------------------------"
	@echo 

clean:
	@rm -f ${PRODUCT_DIR}/*

prepare:
	@mkdir -p ${PRODUCT_DIR}/

all: hello prepare 
	@latex -output-directory=${PRODUCT_DIR} -output-format=pdf src/main.tex 

c112: hello prepare 
	@latex -output-directory=${PRODUCT_DIR} -output-format=pdf src/c112.tex 

