#!/bin/bash
echo "Simulando..."
if [ $# -lt 7 -o  $# -gt 9 ]
then
	echo "Quantidade incorreta de parametros" && exit
fi
LEVEL=$3
THRESHOLD=$4
PASSO_LEVEL=$5
PASSO_THRESHOLD=$6
RESULTADOS=$7
echo
if [ -d $RESULTADOS ]
then
	echo "Folder "$RESULTADOS" already exist, proceeding..."
else
	mkdir "$RESULTADOS" && echo "Criando a pasta "$RESULTADOS"..."
fi
while [ $LEVEL -le 10000 ]
do
	THRESHOLD=$4
	while [ $THRESHOLD -le 10000 ]
	do
#		if [ -d ""$RESULTADOS"/"$2"_"$(./bashcalc.sh $LEVEL/10000)"_"$(./bashcalc.sh $THRESHOLD/10000)"" ] 
#		then
#			echo "Folder ""$RESULTADOS"/"$2"_"$(./bashcalc.sh $LEVEL/10000)"_"$(./bashcalc.sh $THRESHOLD/10000)"" already exist, proceeding..."
#		else
#			mkdir ""$RESULTADOS"/"$2"_"$(./bashcalc.sh $LEVEL/10000)"_"$(./bashcalc.sh $THRESHOLD/10000)""\
#				 && echo "Criando a pasta ""$RESULTADOS"/"$2"_"$(./bashcalc.sh $LEVEL/10000)"_"$(./bashcalc.sh $THRESHOLD/10000)""..."
#		fi
		echo "Executando..."
 		echo "Path "$RESULTADOS"/"$2"_"$(./bashcalc.sh $LEVEL/10000)"_"$(./bashcalc.sh $THRESHOLD/10000)""
		echo "Level="$(./bashcalc.sh $LEVEL/10000)" Threshold="$(./bashcalc.sh $THRESHOLD/10000)""
		./watershed "$1" "$RESULTADOS"/"$2"_"$(./bashcalc.sh $LEVEL/10000)"_"$(./bashcalc.sh $THRESHOLD/10000)" "$(./bashcalc.sh $LEVEL/10000)" "$(./bashcalc.sh $THRESHOLD/10000)"
		echo
		THRESHOLD=$(($THRESHOLD+$PASSO_THRESHOLD))
	done
	LEVEL=$(($LEVEL+$PASSO_LEVEL))
done
echo "Finalizou com sucesso!"
echo
