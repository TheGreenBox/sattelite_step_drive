DEFAULT_DOT_PARAMS=-Tpdf

A2_LANSCAPE='{59.4cm,42.05cm}'
A1_PORTRAIR='{59.4cm,84.1cm}'
A1_LANSCAPE='{84.1cm,59.4cm}'

arch:
	dot ${DEFAULT_DOT_PARAMS} -o product/tmp_soft_arch.pdf soft_arch.dot
	inkscape soft_arch_frame_A2.svg --export-pdf=product/tmp_arch_frame.pdf
	pdfjam product/tmp_arch_frame.pdf --papersize ${A2_LANSCAPE} -o product/tmp_arch_frame.1.pdf
	pdfjam product/tmp_soft_arch.pdf --papersize ${A2_LANSCAPE} --scale 0.97 --offset "8mm 5mm" -o product/tmp_soft_arch.1.pdf
	pdftk product/tmp_soft_arch.1.pdf background product/tmp_arch_frame.1.pdf output product/soft_arch.pdf

clean:
	rm -r -f product

prepare:
	mkdir -p product
