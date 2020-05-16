%.dvi: %.tex
	latex $<

%.ps :  %.dvi
	dvips $< -o $@

%.ps : %.dot
	dot -Tps $< -o $@

.PHONY: all
all: lefty.bbl lefty.dvi

lefty.bbl:
	latex lefty.tex
	bibtex lefty
	rm lefty.dvi

.PHONY: clean
clean:
	rm -f *.aux *.log *.bbl *.blg *.ps *.dvi
