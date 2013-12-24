# ============================================================================
#  Name	 : build_help.mk
#  Part of  : RS_Man
# ============================================================================
#  Name	 : build_help.mk
#  Part of  : RS_Man
#
#  Description: This make file will build the application help file (.hlp)
# 
# ============================================================================

do_nothing :
	@rem do_nothing

# build the help from the MAKMAKE step so the header file generated
# will be found by cpp.exe when calculating the dependency information
# in the mmp makefiles.

MAKMAKE : RS_Man_0xE2A1DCB7.hlp
RS_Man_0xE2A1DCB7.hlp : RS_Man.xml RS_Man.cshlp Custom.xml
	cshlpcmp RS_Man.cshlp
ifeq (WINSCW,$(findstring WINSCW, $(PLATFORM)))
	md $(EPOCROOT)epoc32\$(PLATFORM)\c\resource\help
	copy RS_Man_0xE2A1DCB7.hlp $(EPOCROOT)epoc32\$(PLATFORM)\c\resource\help
endif

BLD : do_nothing

CLEAN :
	del RS_Man_0xE2A1DCB7.hlp
	del RS_Man_0xE2A1DCB7.hlp.hrh

LIB : do_nothing

CLEANLIB : do_nothing

RESOURCE : do_nothing
		
FREEZE : do_nothing

SAVESPACE : do_nothing

RELEASABLES :
	@echo RS_Man_0xE2A1DCB7.hlp

FINAL : do_nothing
