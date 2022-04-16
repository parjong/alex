#!/bin/bash

TARGET_DIR=$1
shift

REDUCE_DIR=$1
shift

if [[ -z ${TARGET_DIR} || -z ${REDUCE_DIR} ]]; then
  echo "USAGE: $0 [TARGET_DIR] [REDUCE_DIR]"
  exit 255
fi

echo "PWD = `pwd`"

echo "TARGET_DIR = '${TARGET_DIR}'"
echo "REDUCE_DIR = '${REDUCE_DIR}'"

make -C ${REDUCE_DIR}

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

  SRC_FILENAME="toy.c"
  OUT_FILENAME="toy.i"

  rm -f ${SRC_FILENAME} ${OUT_FILENAME}

  #
  # Copy
  #
  cp ${TARGET_DIR}/${UNIT} ${SRC_FILENAME}

  #
  # Massage
  #
  sed -i 's/_Bool/int/g' ${SRC_FILENAME}

  #
  # Reduce
  #
  REDUCE_EXITCODE=0

  (${REDUCE_DIR}/reduce ${SRC_FILENAME} -- 2> reduce.log > ${OUT_FILENAME}) || REDUCE_EXITCODE=$?
  
  if [[ ${REDUCE_EXITCODE} -ne 0 ]]; then
    echo "${UNIT}, REDUCE FAILED"
    continue
  fi

  #
  # Check Union
  # 
  UNION_LINES=`grep union ${OUT_FILENAME} | wc -l`

  #
  # Compile
  #
  GCC_EXITCODE=0

  (gcc -c ${OUT_FILENAME} 2> /dev/null) || GCC_EXITCODE=$?
  
  if [[ ${GCC_EXITCODE} -ne 0 ]]; then
    echo "${UNIT}, GCC FAILED"
    continue
  fi

  echo "`basename ${UNIT}`, PASSED (${UNION_LINES})"
done
