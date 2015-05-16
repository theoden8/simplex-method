[ -z "$(compgen -abc | grep ^highlight$ | head -1)" ] && echo "Please, install highlight utility (brew install highlight)" && return
separator="==============================================================================================\n"
DIR=$1
files="."

name="HIGHLIGHT.html"
css="highlight.css"

for hfiles in *.hpp; do
	printf "$separator\t$hfiles\n$separator"
	cat "$hfiles"
	cfiles=$(echo $hfiles | sed 's/hpp/cpp/g')
	printf "$separator\t$cfiles\n$separator"
	cat $cfiles
done | highlight --syntax=c++ -o "$name"

cp "$DIR/$files/colorscheme.css" "$css"
open "$name"
sleep 1; rm "$name"; rm "$css" &
