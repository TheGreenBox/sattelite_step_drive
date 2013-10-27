HELLO_MSG="Drafts for step motor student work"
PRODUCT_DIR='product'

all: hello create_build_dir main

hello: 
	@echo "----------------------------------------"
	@echo "    "${HELLO_MSG}
	@echo "========================================"

clean:
	@rm -f ${PRODUCT_DIR}/*

create_build_dir:
	@mkdir -p ${PRODUCT_DIR}/

main:
	@latex -output-directory=${PRODUCT_DIR} -output-format=pdf src/main.tex 

