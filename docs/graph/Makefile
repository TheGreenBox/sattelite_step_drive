DEFAULT_DOT_PARAMS=-Tpdf

A2_LANSCAPE='{594mm,420mm}'
A1_PORTRAIR='{594mm,841mm}'
A1_LANSCAPE='{841mm,594mm}'

help:
	@echo "For build you have to install few pkgs:"
	@echo "sudo apt-get install texlive-extra-utils"
	@echo "sudo apt-get install pdftk"
	@echo "sudo apt-get install graphviz"

all: arch pcbassembly

arch: _arch_build
	rm product/tmp_soft_arch*

pcbassembly: _pcbassembly_build
	rm product/tmp_assembly_map*

update_arch_in_doc: _arch_build
	cp product/tmp_soft_arch.pdf ../src/pictures/soft_arch.pdf

_arch_build:
	dot ${DEFAULT_DOT_PARAMS} -o product/tmp_soft_arch.pdf soft_arch.dot
	inkscape soft_arch_frame_A2.svg --export-pdf=product/tmp_soft_arch_frame.pdf
	pdfjam product/tmp_soft_arch_frame.pdf --papersize ${A2_LANSCAPE} -o product/tmp_soft_arch_frame.1.pdf
	pdfjam product/tmp_soft_arch.pdf --papersize ${A2_LANSCAPE} --scale 0.97 --offset "8mm 5mm" -o product/tmp_soft_arch.1.pdf
	pdftk product/tmp_soft_arch.1.pdf background product/tmp_soft_arch_frame.1.pdf output product/soft_arch_a2.pdf

_pcbassembly_build:
	dot ${DEFAULT_DOT_PARAMS} assembly_map.dot -oproduct/tmp_assembly_map.pdf
	inkscape assembly_map_frame_A1.svg --export-pdf=product/tmp_assembly_map_frame.pdf
	pdfjam product/tmp_assembly_map_frame.pdf --papersize ${A1_LANSCAPE} -o product/tmp_assembly_map_frame.1.pdf
	pdfjam product/tmp_assembly_map.pdf --papersize ${A1_LANSCAPE} --scale 0.97 --offset "8mm 5mm" -o product/tmp_assembly_map.1.pdf
	pdftk product/tmp_assembly_map.1.pdf background product/tmp_assembly_map_frame.1.pdf output product/assembly_map_a1.pdf

clean:
	rm -r -f product

prepare:
	mkdir -p product
