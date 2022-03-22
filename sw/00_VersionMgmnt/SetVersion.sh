# Shell-Skript zum Inkrementieren der Versions-Nummer
# im File Version.H

VersionFile="version.h"
Datum=` TZ=UTC-1 date +"%d.%m.%Y"`
DatumD=` TZ=UTC-1 date +"%d"`
DatumM=` TZ=UTC-1 date +"%m"`
DatumY=` TZ=UTC-1 date +"%Y"`
TimeB=` TZ=UTC-1 date +"%H:%M:%S"`
TimeH=` TZ=UTC-1 date +"%H"`
TimeM=` TZ=UTC-1 date +"%M"`
TimeS=` TZ=UTC-1 date +"%S"`
wait

DSP_Ver=0
DSP_Txt1=1449489011  # "Vers"
DSP_Txt2=1768910368  # "ion "

# echo "Anzahl der Params " $#
if [ $# -ne 3 ]; then
#  Version lesen
   if [ -r $VersionFile ]; then
      read Comment Major Minor Micro Rest < $VersionFile

      if [ $# -ne 1 ]; then
#        Version erh?he
         Micro=`expr $Micro + 1`
         if [ $Micro -eq 255 ]; then
            Micro=1
            Minor=`expr $Minor + 1`
         fi
         if [ $Minor -eq 100 ]; then
            Minor=1
            Major=`expr $Major + 1`
         fi
         DSP_Ver=`expr $Major \* 65536 + $Minor \* 256 + $Micro`
         echo "Version $Major.$Minor.$Micro"
      else
         if [ $1 == "s" ]; then
#           Version anzeigen
            printf "%s.%02s.%03s\r\n" $Major $Minor $Micro
            exit # Hier ist Ende. Ausgabe ist nicht notwendig
         else
#           Version vermindern
            Micro=`expr $Micro - 1`
            if [ $Micro -eq -1 ]; then
               Micro=99
               Minor=`expr $Minor - 1`
            fi
            if [ $Minor -eq -1 ]; then
               Minor=99
               Major=`expr $Major - 1`
            fi
            printf "%s.%02s.%03s\r\n" $Major $Minor $Micro
         fi
      fi
   else
#     Neues File mit 0.0.1
      Major=0
      Minor=0
      Micro=1
   fi

else
#  Version aus den Aufrufparametern ?bernehmen
   Major=$1
   Minor=$2
   Micro=$3
fi

# VersioFile neu erzeugen
printf "//  %s %s %s   %s  %s\r\n\
#define MAJOR  \"%2s\"\r\n\
#define MINOR  \"%2s\"\r\n\
#define MICRO  \"%4s\"\r\n\
#define MAJOR2 \"%s\"\r\n\
#define MINOR2 \"%s\"\r\n\
#define MICRO2 \"%s\"\r\n\
#define MAJOR_INT %s\r\n\
#define MINOR_INT %s\r\n\
#define MICRO_INT %s\r\n\
#define VERSION_DSP  %s,%s,%s,0\r\n\
#define VERSION_TXT  \"%s.%02s.%02s\"\r\n\
#define VERSION_TXT2 \"%s.%s%02s\"\r\n\
#define VERSION_TXT3 \"%s.%s.%02s\"\r\n\
#define VERSION_TXT4 0x%02x%02x\r\n\
#define VERSION_TXT5 \"%s.%02s Build %02s\"\r\n\
#define VERSION_TXT6 0x%02x%02x%04x\r\n\
#define BUILD_DATE_TIME \"%s  %s\"\r\n\
#define BUILD_DATE   \"%s\"\r\n\
#define BUILD_TIME   \"%s\"\r\n\
#define BUILD_TIME_H \"%s\"\r\n\
#define BUILD_TIME_M \"%s\"\r\n\
#define BUILD_TIME_S \"%s\"\r\n\
#define BUILD_TIME_H_INT %s\r\n\
#define BUILD_TIME_M_INT %s\r\n\
#define BUILD_TIME_S_INT %s\r\n\
#define BUILD_DATE_D_INT %s\r\n\
#define BUILD_DATE_M_INT %s\r\n\
#define BUILD_DATE_Y_INT %s\r\n" \
$Major $Minor $Micro $Datum $TimeB \
$Major $Minor $Micro \
$Major $Minor $Micro \
$Major $Minor $Micro \
$DSP_Txt1 $DSP_Txt2 $DSP_Ver \
$Major $Minor $Micro \
$Major $Minor $Micro \
$Major $Minor $Micro \
`expr $Major + 48` \
`expr $Minor + 48` \
$Major $Minor $Micro \
$Major $Minor $Micro \
$Datum $TimeB \
$Datum $TimeB $TimeH $TimeM $TimeS \
`expr $TimeH + 0` `expr $TimeM + 0` `expr $TimeS + 0` \
`expr $DatumD + 0` `expr $DatumM + 0` $DatumY > $VersionFile

# Hinweis: Letztes #define: Zwischen dem abschliessendem " und \ muss ein Blank sein !!!

#-----------------------------------------------------------------------
# End of File