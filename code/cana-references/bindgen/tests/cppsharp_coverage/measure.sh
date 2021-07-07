#!/bin/bash

TARGET_DIR=$1
shift

REDUCE_DIR=$1
shift

CONVERT_DIR=$1
shift

if [[ -z ${TARGET_DIR} || -z ${REDUCE_DIR} || -z ${CONVERT_DIR} ]]; then
  echo "USAGE: $0 [TARGET_DIR] [REDUCE_DIR] [CONVERT_DIR]"
  exit 255
fi

echo "PWD = `pwd`"

echo "TARGET_DIR = '${TARGET_DIR}'"
echo "REDUCE_DIR = '${REDUCE_DIR}'"
echo "CONVERT_DIR = '${CONVERT_DIR}'"

make -C ${REDUCE_DIR} &> /dev/null
make -C ${CONVERT_DIR} &> /dev/null

SOURCES=()

for ARG in $@; do
  echo "ADDED: ${ARG}"
  SOURCES+=("${TARGET_DIR}/${ARG}")
done

if [[ ${#SOURCES[@]} -eq 0 ]]; then
  SOURCES+=(`ls ${TARGET_DIR}/*.i`)
fi

for SRC in ${SOURCES[@]}; do
  UNIT=`basename ${SRC}`

  rm -f *.log
  rm -f toy.*

  REDUCE_EXITCODE=0
  REDUCE_LOG="reduce.log"

  rm -f ${REDUCE_LOG}

  SRC_FILENAME=toy.c
  OUT_FILENAME=toy.i

  cp ${TARGET_DIR}/${UNIT} ${SRC_FILENAME}
  (${REDUCE_DIR}/reduce ${SRC_FILENAME} -- 2> reduce.log > ${OUT_FILENAME}) || REDUCE_EXITCODE=$?

  if [[ ${REDUCE_EXITCODE} -ne 0 ]]; then
    echo "TEST ${UNIT}: REDUCE FAILED"
    continue
  fi

  sed -i 's/_Bool/int/g' ${OUT_FILENAME}

  GCC_EXITCODE=0
  GCC_LOG="gcc.log"

  rm -f ${GCC_LOG}

  (gcc -c ${OUT_FILENAME} 2> ${GCC_LOG}) || GCC_EXITCODE=$?

  if [[ ${GCC_EXITCODE} -ne 0 ]]; then
    echo "TEST ${UNIT}: GCC FAILED"
    continue
  fi

  CONVERT_EXITCODE=0
  CONVERT_LOG="convert.log"

  (MONO_PATH=${CONVERT_DIR}/lib mono --debug ${CONVERT_DIR}/convert.exe -l toy ${OUT_FILENAME} &> ${CONVERT_LOG}) || CONVERT_EXITCODE=$?

  if [[ ! -f toy.cs ]]; then
    echo "TEST ${UNIT}: CONVERT FAILED"
    continue
  fi

  MCS_EXITCODE=0
  MCS_LOG="mcs.log"
  
  (mcs -unsafe -t:library toy.cs &> ${MCS_LOG}) || MCS_EXITCODE=$?

  if [[ ${MCS_EXITCODE} -ne 0 ]]; then
    echo "TEST ${UNIT}: MCS FAILED"
    continue
  fi

  echo "TEST ${UNIT}: PASSED"
done
