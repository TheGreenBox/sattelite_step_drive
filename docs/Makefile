HELLO_MSG="Drafts for step motor student work"
PRODUCT_DIR='product'

PROJECT_LIST=math_model

all:
	@for path in $(PROJECT_LIST); do \
		cd $$path ; \
		make ; \
		cd ../ ; \
	done

rebuild:
	@for path in $(PROJECT_LIST); do \
		cd $$path ; \
		make rebuild; \
		cd ../ ; \
	done

clean:
	@rm -f ${PRODUCT_DIR}/*

