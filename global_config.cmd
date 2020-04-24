set_savefile_path("${TOP}/as","/save")
set_requestfile_path("${TOP}/as","/req")
iocInit()
dbl > ${TOP}/records.dbl
system "cp ${TOP}/records.dbl /cf-update/$HOSTNAME.$IOCNAME.dbl"
#system("install -m 777 -d ${TOP}/as/save")
#system("install -m 777 -d ${TOP}/as/req")
makeAutosaveFiles()
