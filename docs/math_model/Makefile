HELLO_MSG="Math model latex building"
PRODUCT_DIR='../product'

all: hello create_build_dir pdf

rebuild: hello
	latex -output-directory=${PRODUCT_DIR} -output-format=pdf src/math_model.tex 
	latex -output-directory=${PRODUCT_DIR} -output-format=pdf src/math_model.tex 

hello: 
	@echo "---------------------------"
	@echo " "${HELLO_MSG}
	@echo "==========================="

clean:
	@rm -f ${PRODUCT_DIR}/*

create_build_dir:
	@mkdir -p ${PRODUCT_DIR}/

pdf:
	latex -output-directory=${PRODUCT_DIR} -output-format=pdf src/math_model.tex 

