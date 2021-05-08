TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application

PROD_IOC = omegaCNi32
# omegaCNi32.dbd will be created and installed
DBD += omegaCNi32.dbd

# omegaCNi32.dbd will be made up from these files:
#omegaCNi32_DBD += base.dbd
omegaCNi32_DBD += base.dbd
omegaCNi32_DBD += asyn.dbd
omegaCNi32_DBD += calc.dbd
omegaCNi32_DBD += stream.dbd
omegaCNi32_DBD += drvAsynIPPort.dbd
omegaCNi32_DBD += drvAsynSerialPort.dbd
omegaCNi32_DBD += system.dbd
omegaCNi32_DBD += devIocStats.dbd
omegaCNi32_DBD += system.dbd
omegaCNi32_DBD += caPutLog.dbd
omegaCNi32_DBD += asSupport.dbd # for autosave/restore

# Include dbd files from all support applications:
#omegaCNi32_DBD += xxx.dbd
omegaCNi32_DBD += asubFunctions.dbd

# Add all the support libraries needed by this IOC
omegaCNi32_LIBS += asyn calc stream autosave devIocStats caPutLog

# omegaCNi32_registerRecordDeviceDriver.cpp derives from omegaCNi32.dbd
omegaCNi32_SRCS += omegaCNi32_registerRecordDeviceDriver.cpp
omegaCNi32_SRCS += asubFunctions.c

# Build the main IOC entry point on workstation OSs.
omegaCNi32_SRCS_DEFAULT += omegaCNi32Main.cpp
omegaCNi32_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#omegaCNi32_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

# Finally link to the EPICS Base libraries
omegaCNi32_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

