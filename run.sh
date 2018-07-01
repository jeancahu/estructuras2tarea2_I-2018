#!/bin/bash

declare -l EJER="$*"

function compile_exec ()
{
    [ -d ./bin ] || mkdir ./bin
    cd ./src
    make
    cd -
    ln ./src/*.x ./bin
    if (( $? ))
    then	
	ln -s ./src/*.x ./bin
    fi
}

if [ -d ./bin ]
then
    :
else
    echo "Es necesario compilar el código:"
    compile_exec
fi

case $EJER in
    e*1)
	if [ ! -x ./bin/E1.x ] ; then compile_exec ; fi
	mpiexec ./bin/E1.x
	;;
    e*2)
	if [ ! -x ./bin/E2.x ] ; then compile_exec ; fi
	mpiexec ./bin/E2.x
	;;
    e*3)
	if [ ! -x ./bin/E3.x ] ; then compile_exec ; fi
	FILE_LOG=$( mktemp primos.XXXX )
	mpiexec -n 4 ./bin/E3.x 2>/dev/null 1>$FILE_LOG
	if (( $? ))
	then
	    mpiexec -n 2 ./bin/E3.x 2>/dev/null 1>$FILE_LOG
	fi
	tail -n 1 $FILE_LOG
	echo "Los números se encuentran en le fichero $FILE_LOG"
	;;
    o*1)
	if [ ! -x ./bin/EOpc1.x ] ; then compile_exec ; fi
	mpiexec ./bin/EOpc1.x
	;;
    o*2)
	if [ ! -x ./bin/EOpc2.x ] ; then compile_exec ; fi
	mpiexec ./bin/EOpc2.x
	;;
    o*3)
	if [ ! -x ./bin/EOpc3.x ] ; then compile_exec ; fi
	mpiexec ./bin/EOpc3.x
	;;
    o*4)
	echo "Ejecutar el programa con MPI_Gather:"
	if [ ! -x ./bin/prom_scatter_plus_gather.x ] ; then compile_exec ; fi
	mpiexec ./bin/prom_scatter_plus_gather.x
	echo "Ejecutar el programa con MPI_Reduce:"
	if [ ! -x ./bin/prom_scatter_plus_reduce.x ] ; then compile_exec ; fi
	mpiexec ./bin/prom_scatter_plus_reduce.x
	;;
    clean)
	cd ./bin
	rm *.x
	cd ../src
	make clean
	cd -
	;;
    *)
	echo "Error: sub comando no reconocido."
	exit 1
    ;;
    esac

exit 0
