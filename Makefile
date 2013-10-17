PKGNAME := $(shell sed -n "s/Package: *\([^ ]*\)/\1/p" DESCRIPTION)
PKGVERS := $(shell sed -n "s/Version: *\([^ ]*\)/\1/p" DESCRIPTION)
PKGSRC  := $(shell basename `pwd`)

all: install

build:
	cd ..;\
	R CMD build $(PKGSRC)

install: 
	cd ..;\
	R CMD INSTALL $(PKGNAME)

check: build
	cd ..;\
	R CMD check $(PKGNAME)_$(PKGVERS).tar.gz --as-cran
	
test: 
	Rscript -e "library('testthat',quietly=TRUE);library('mirt',quietly=TRUE);options(warn=2);test_package('mirt')"

clean:
	$(RM) src/*.o
	$(RM) src/*.so
	$(RM) ../$(PKGNAME)_$(PKGVERS).tar.gz 
	$(RM) -r ../$(PKGNAME).Rcheck/
	

