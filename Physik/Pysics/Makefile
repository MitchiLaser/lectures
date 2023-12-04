.PHONY: pdf
.IGNORE: clean-aux
.SILENT: clean-aux

pdf: main.tex $(shell find ./include -type f)
	mkdir -p _build
	mkdir -p figs
	pdflatex main.tex
	pythontex main.tex
	pdflatex main.tex
	pdflatex main.tex
	cp main.pdf ./_build/

clean-aux:
	latexmk -C
	rm main.pytxcode
	rm main.tdo
	rm -rf ./pythontex-files-main/
	rm -r ./figs/

clean: clean-aux
	rm -rf ./_build/
