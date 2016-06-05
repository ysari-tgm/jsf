OUTDIR = build
SOURCES = $(wildcard *.cpp)
OBJECTS = $(addprefix $(OUTDIR)/,$(notdir $(SOURCES:.cpp=.o)))

CREATE = create
READ = read

LFLAGS = -lpqxx -lpq

PG_ENVIRONMENT = PGHOST=vmdebian PGUSER=accounting PGPASSWORD=accounting PGDATABASE=company
CREATE_ARGS = testing 1

CPP = g++
RM = rm -rf
MKDIR = mkdir -p

$(OUTDIR):
	$(MKDIR) $(OUTDIR)

$(OBJECTS): $(SOURCES) | $(OUTDIR)
	@echo -e "Compiling\t"$(CYAN)$(filter %$(subst .o,.c,$(@F)), $(SOURCES))$(NORMAL)
	@$(CPP) -c $(LFLAGS) -o $@ $(filter %$(subst .o,.cpp,$(@F)), $(SOURCES))

$(OUTDIR)/$(CREATE): $(OUTDIR)/create_employee.o
	@echo -e "Linking\t\t"$(CYAN)$^$(NORMAL)
	@$(CPP) $(LFLAGS) -o $@ $^

$(OUTDIR)/$(READ): $(OUTDIR)/read_employee.o
	@echo -e "Linking\t\t"$(CYAN)$^$(NORMAL)
	@$(CPP) $(LFLAGS) -o $@ $^

create: $(OUTDIR)/$(CREATE)
	@$(PG_ENVIRONMENT) $(OUTDIR)/$(CREATE) $(CREATE_ARGS)

read: $(OUTDIR)/$(READ)
	@$(PG_ENVIRONMENT) $(OUTDIR)/$(READ)

update:
delete:
all: $(OUTDIR)/$(CREATE) $(OUTDIR)/$(READ)

clean:
	-$(RM) $(OUTDIR)/*

.PHONY: all clean
