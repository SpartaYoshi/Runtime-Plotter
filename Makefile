TARGET		:=	$(notdir runtime-plot)
BUILD		:=	build
SRCDIR		:=	src
INCLDIR	    :=	include

export INCLUDE	:=	$(foreach dir,$(INCLDIR),-I$(CURDIR)/$(dir)) # -I$(CURDIR)/$(BUILD)
export SOURCE   :=  $(foreach dir,$(SRCDIR),$(wildcard $(dir)/*))

CFLAGS	:= -g -Wall -O2 $(INCLUDE)

$(BUILD): $(SOURCE)
	[ -d $@ ] || mkdir -p $@
	$(foreach srcfile,$(SOURCE),gcc $(CFLAGS) -c $(srcfile) -o $(patsubst %.c,$(BUILD)/%.o,$(notdir $(srcfile)) ;))
#	gcc $(CFLAGS) -c $^ -o $(patsubst %.c,$(BUILD)/%.o,$(notdir $(SOURCE)))


plotter:
	gcc $(CFLAGS) $(wildcard $(BUILD)/*) -o $(TARGET)

clean:
	rm -rf $(BUILD) $(TARGET)