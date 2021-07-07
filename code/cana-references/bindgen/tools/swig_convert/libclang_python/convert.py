#!/usr/bin/env python

import os
import sys
import clang

from clang.cindex import Index
from clang.cindex import CursorKind
from clang.cindex import TypeKind

from sets import Set
from pprint import pprint

#clang.cindex.Config.set_library_path('/home/parjong/tools/svace-packages/svace-2.1.26-preprocess-x64-linux/compilers/clang-3.4-x64-linux/lib')
#clang.cindex.Config.set_library_file('/home/parjong/tools/svace-packages/svace-2.1.26-preprocess-x64-linux/compilers/clang-3.4-x64-linux/lib/libclang.so')
clang.cindex.Config.set_library_file('libclang-3.5.so')

def is_invalid_cursor(cursor):
    return cursor.kind == CursorKind.NO_DECL_FOUND

def is_candidate_function(cursor):
    return cursor.kind == CursorKind.FUNCTION_DECL and cursor.is_definition()

def is_unexposed_typedef(cursor):
    return cursor.kind == CursorKind.TYPEDEF_DECL and cursor.underlying_typedef_type.kind == TypeKind.UNEXPOSED

#
#
#
effective = Set()

def set_effective(cursor): 
    effective.add(cursor.get_usr())

def is_effective(cursor):
    return cursor.get_usr() in effective

# 
#
#
invisible = Set()

def set_invisible(cursor):
    invisible.add(cursor.get_usr())
 
def is_invisible(cursor):
    return cursor.get_usr() in invisible

 
#
#
#
def traverse_type(ty):  
    if ty.kind == TypeKind.INVALID:
        return
  
    traverse_type(ty.get_pointee())
    traverse_type(ty.get_array_element_type()) 
    traverse_type(ty.get_result())
    traverse_cursor(ty.get_declaration())

def traverse_cursor(cursor): 
    if is_effective(cursor) or is_invalid_cursor(cursor):
        return

    set_effective(cursor)

    for child in cursor.get_children():
        traverse_type(child.type)
        traverse_cursor(child)

#
#
#
typ_base = {
    TypeKind.BOOL: '_Bool',
    TypeKind.CHAR_S: 'char',
    TypeKind.CHAR16: 'char',
    TypeKind.INT: 'int',
    TypeKind.ULONGLONG: 'unsigned long long',
    TypeKind.UINT: 'unsigned int',
    TypeKind.VOID: 'void'
}

def is_pointer_type(ty):
    return ty.kind == TypeKind.POINTER

def is_typedef_type(ty):
    return ty.kind == TypeKind.TYPEDEF

def is_unexposed_type(ty):
    return ty.kind == TypeKind.UNEXPOSED

def spelling_of_type(ty):    
    if is_pointer_type(ty):
        return string_of_type(ty.get_pointee()) + ' *'
    elif is_typedef_type(ty):
        return ty.spelling

    elif is_unexposed_type(ty):
        return ty.spelling

    return typ_base[ty.kind]

def string_of_type(ty):
    base = spelling_of_type(ty) 

    if ty.is_restrict_qualified():
        base += ' __restrict'

    return base

def string_of_cursor(cursor):
    return ' '.join([token.spelling for token in cursor.get_tokens()])

def string_of_param(cursor):
    return string_of_type(cursor.type) + ' ' + cursor.spelling
    
#
#
#
def print_raw(cursor):
    print string_of_cursor(cursor)

def print_other(cursor):
    if is_invisible(cursor):
        return
    print_raw(cursor)

def print_function_impl(cursor):
    ret = cursor.result_type.spelling
    name = cursor.spelling

    args = ', '.join([string_of_param(arg) for arg in cursor.get_arguments()])

    print "%s %s(%s);" % (ret, name, args)
 
def print_function(cursor):
    print "%{"
    print_function_impl(cursor)
    print "%}"

    print "%callback(\"%s_cb\");"
    print_function_impl(cursor)
    print "%nocallback;"

def print_record_impl(cursor):
    fields = []

    for child in cursor.get_children():
        fields.append(string_of_cursor(child))
        
    if len(fields) is 0:
        print "struct %s;" % cursor.spelling
        return
       
    print "struct %s {" % cursor.spelling

    for field in fields:
        print "  %s" % field
        
    print "};"        

def print_record(cursor):
    print "%inline %{"
    print_record_impl(cursor)
    print "%}"

def print_typedef(cursor):
    print "%inline %{"
    print_other(cursor)
    print "%}"

def print_cursor(cursor): 
    if is_invisible(cursor):
        print        
    elif cursor.kind == CursorKind.FUNCTION_DECL:
        print_function(cursor)        
    elif cursor.kind == CursorKind.STRUCT_DECL:
        print_record(cursor)
    elif cursor.kind == CursorKind.TYPEDEF_DECL:
        print_typedef(cursor)
    else:
        print_other(cursor)
#
#
#
def process(filename):
    index = clang.cindex.Index.create()

    #tu = clang.cindex.TranslationUnit.from_ast_file(index, filename)
    tu = index.read(filename)

    top = tu.cursor

    # Traverse    
    for cursor in top.get_children():
        #print cursor.translation_unit.spelling, cursor.extent

        if is_unexposed_typedef(cursor):
            set_invisible(cursor.underlying_typedef_type.get_declaration())

        if is_candidate_function(cursor):
            set_effective(cursor)

            traverse_type(cursor.result_type)

            for child in cursor.get_children():
                if child.kind == CursorKind.PARM_DECL:
                    traverse_cursor(child) 

    # Print
    for decl in [decl for decl in top.get_children() if decl.get_usr() in effective]:
        print_cursor(decl)

#
#
#
filenames = []

if len(sys.argv) is 1:
    filenames.append('sample.i')
else:
    for i in range(1, len(sys.argv)):    
        filenames.append(sys.argv[i])

for filename in filenames:
    process(filename)
