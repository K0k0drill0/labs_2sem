if [ -n "$1" ]
then
  if [ "$1" == "?" ]
  then
    echo "this program will copy all files that are write protected for all users with a prefix you can specify."
    exit
  else
    echo "Can not identify your parameter."
    exit
  fi
fi
echo "Write your prefix:"
cat > pr
pref=`cat pr`
rm pr
for f in *
do
  permissions=`ls -l $f`
  sub_str="w"
  #if [ -w $f ]
  if [ `expr index "$permissions" "$sub_str"` == "0" ]
  then
    name="$pref$f"
    cp $f $name
    chmod u+w,g+w,o+w $name
    echo "File $f has been copied successfully!"
  fi
done
