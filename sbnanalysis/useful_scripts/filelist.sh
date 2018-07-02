#! /bin/bash   


list1=`samweb list-definition-files zennamo_numi_prelim_100_6_26_2018`
i=1
for file in $list1
do
    fullpath=`samweb locate-file $file`
    cutpath=`echo "${fullpath%(*}"/$file`
    echo "${cutpath##*:}"
    let i=i+1
done