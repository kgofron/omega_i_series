#!../../bin/linux-x86_64/omegaCNi32

## You may have to change omegaCNi32 to something else
## everywhere it appears in this file

< envPaths

epicsEnvSet("ENGINEER", "Engineer's name x5555")
epicsEnvSet("LOCATION", "XF:xxIDA{RG:A2}")
epicsEnvSet("EPICS_CA_AUTO_ADDR_LIST","NO")
epicsEnvSet("EPICS_CA_ADDR_LIST","10.xx.0.255")

cd ${TOP}

## Register all support components
dbLoadDatabase("dbd/omegaCNi32.dbd",0,0)
omegaCNi32_registerRecordDeviceDriver(pdbbase) 

## Streamdevice Protocol Path

epicsEnvSet ("STREAM_PROTOCOL_PATH", "protocols")

drvAsynIPPortConfigure("tsrv1-p16","10.xx.2.51:4016")
#asynSetTraceMask("tsrv1-p16",0,0x09)
#asynSetTraceIOMask("tsrv1-p16",0,0x02)

## Load record instances
dbLoadRecords("db/omegaCNi32_temp.db","Sys=XF:xxIDA-CT,Dev={RG:A1},Chan=01,N_T=,N_GAIN=,PORT=tsrv1-p16")
# N_T and N_GAIN macros used if there are multiple temperature controllers in a rack. Leading ':' required on N_T, no leading ':' required on N_GAIN.
#dbLoadRecords("db/omegaCNi32_temp.db","Sys=XF:xxIDA-CT,Dev={RG:A1},Chan=01,N_T=:1,N_GAIN=1,PORT=tsrv1-p16")

iocInit()

dbl > ${TOP}/records.dbl
system "cp ${TOP}/records.dbl /cf-update/$HOSTNAME.$IOCNAME.dbl"


