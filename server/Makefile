##############################################################################
# keye Makefile. Requires GNU Make.
# Copyright (C) 2005-2012 Keye Leo.
##############################################################################

NAME=    keye
MAJVER=  1
MINVER=  0
RELVER=  0
VERSION= $(MAJVER).$(MINVER).$(RELVER)

##############################################################################
# Change the installation path as needed. Note: PREFIX must be an absolute path!
#
export PREFIX= builds
SRC=foo
##############################################################################

INSTALL_BIN=   $(PREFIX)/bin
INSTALL_LIB=   $(PREFIX)/lib
INSTALL_SHARE= $(PREFIX)/share
INSTALL_INC=   $(PREFIX)/include/$(NAME)-$(MAJVER).$(MINVER)

INSTALL_TNAME= $(NAME)
INSTALL_ANAME= lib$(NAME)-$(ABIVER).a
INSTALL_SONAME= lib$(NAME)-$(ABIVER).so

INSTALL_T= $(INSTALL_BIN)/$(INSTALL_TNAME)
INSTALL_STATIC= $(INSTALL_LIB)/$(INSTALL_ANAME)
INSTALL_DYN= $(INSTALL_LIB)/$(INSTALL_SONAME)

INSTALL_DIRS= $(INSTALL_BIN) $(INSTALL_LIB) $(INSTALL_INC)
UNINSTALL_DIRS= $(INSTALL_INC)

RM= rm -f
MKDIR= mkdir -p
RMDIR= rmdir 2>/dev/null
SYMLINK= ln -sf
INSTALL_X= install -m 0755
INSTALL_F= install -m 0644
UNINSTALL= $(RM)
LDCONFIG= ldconfig -n
SED_PC= sed -e "s|^prefix=.*|prefix=$(PREFIX)|"

FILE_T= $(NAME)
FILE_A= lib$(NAME).a
FILE_SO= lib$(NAME).so
FILES_INC= $(wildcard $(SRC)/*.h)

ifeq (,$(findstring Windows,$(OS)))
  ifeq (Darwin,$(shell uname -s))
    LDCONFIG= :
  endif
endif

##############################################################################

# Target flags and source option.
MAKE_CMD=$(MAKE) -C $(SRC)
MAKE_CLEAN_CMD=$(MAKE) -C $(SRC) clean
include Makefile.dep

default all:
	@echo "==== Building $(NAME) $(VERSION) ===="
	$(MAKE_CMD)
	@echo "==== Successfully built $(NAME) $(VERSION) ===="

install:
	@echo "==== Installing $(NAME) $(VERSION) to $(PREFIX) ===="
	$(MKDIR) $(INSTALL_DIRS)
	cd $(SRC) && $(INSTALL_X) $(FILE_T) $(INSTALL_T)
	cd $(SRC) && test -f $(FILE_A) && $(INSTALL_F) $(FILE_A) $(INSTALL_STATIC) || :
	$(RM) $(INSTALL_DYN)
	cd $(SRC) && test -f $(FILE_SO) && \
	  $(INSTALL_X) $(FILE_SO) $(INSTALL_DYN) && \
	  $(LDCONFIG) $(INSTALL_LIB)
	cd $(SRC) && $(INSTALL_F) $(FILES_INC) $(INSTALL_INC)
	@echo "==== Successfully installed $(NAME) $(VERSION) to $(PREFIX) ===="

uninstall:
	@echo "==== Uninstalling $(NAME) $(VERSION) from $(PREFIX) ===="
	$(UNINSTALL) $(INSTALL_T) $(INSTALL_STATIC) $(INSTALL_DYN)
	for file in $(FILES_INC); do \
	  $(UNINSTALL) $(INSTALL_INC)/$$file; \
	  done
	$(LDCONFIG) $(INSTALL_LIB)
	$(RMDIR) $(UNINSTALL_DIRS) || :
	@echo "==== Successfully uninstalled $(NAME) $(VERSION) from $(PREFIX) ===="

clean:
	$(MAKE_CLEAN_CMD)
#	$(MAKE) -C $(SRC) clean

echo:
	@echo Start make ...

.PHONY: all install uninstall clean echo

##############################################################################
