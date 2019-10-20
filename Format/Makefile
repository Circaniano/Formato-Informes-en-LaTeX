all:
	pdflatex inform
	bibtex bibliografia
	pdflatex inform
clean: 
	rm -f *.aux *.bbl *.log *.blg *.dvi *.toc

cleanall: clean
	rm -f inform.pdf