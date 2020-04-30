dbLoadRecords("db/alarm_summary.db","Sys=${Sys}")
epicsEnvSet("AS", "${TOP}/../as")
set_savefile_path("${AS}","/save")
set_requestfile_path("${AS}","/req")
set_pass0_restoreFile("info_positions.sav")
set_pass1_restoreFile("info_settings.sav")
iocInit()
#system("install -m 777 -d ${TOP}/as/save")
#system("install -m 777 -d ${TOP}/as/req")
dbl > ${TOP}/records.dbl
system "cp ${TOP}/records.dbl /cf-update/$HOSTNAME.$IOCNAME.dbl"
#makeAutosaveFiles()
makeAutosaveFileFromDbInfo("${AS}/req/info_settings.req", "autosaveFields");
makeAutosaveFileFromDbInfo("${AS}/req/info_positions.req", "autosaveFields_pass0");
create_monitor_set("info_positions.req",30)
create_monitor_set("info_settings.req",30)
