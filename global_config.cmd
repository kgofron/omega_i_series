dbLoadRecords("db/alarm_summary.db","Sys=${Sys}")
set_savefile_path("${TOP}/as","/save")
set_requestfile_path("${TOP}/as","/req")
set_pass1_restoreFile("info_settings.sav")
iocInit()
#system("install -m 777 -d ${TOP}/as/save")
#system("install -m 777 -d ${TOP}/as/req")
dbl > ${TOP}/records.dbl
system "cp ${TOP}/records.dbl /cf-update/$HOSTNAME.$IOCNAME.dbl"
#makeAutosaveFiles()
makeAutosaveFileFromDbInfo("as/req/info_settings.req", "autosaveFields");
makeAutosaveFileFromDbInfo("as/req/info_positions.req", "autosaveFields_pass0");
create_monitor_set("info_positions.req",30)
create_monitor_set("info_settings.req",30)
