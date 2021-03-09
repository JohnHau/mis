#!/usr/bin/awk  -f
BEGIN{
	FS=",";
	ORS=" "

}
{
	print $1 " " $2	
	if (NR%2)
	{
		ORS="\n"
#	print $1
#printf("%s",$1) 
#		print("%s",$1) 
	}
	else
	{
		ORS=" ";
	}



}
