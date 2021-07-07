#ifndef _TST_H_
#define _TST_H_

#ifndef _TST_EO_CLASS_TYPE
#define _TST_EO_CLASS_TYPE

typedef Eo Tst;

#endif

#ifndef _TST_EO_TYPES
#define _TST_EO_TYPES


#endif
#define TST_CLASS tst_class_get()

EAPI const Eo_Class *tst_class_get(void) EINA_CONST;

EOAPI Eina_Bool  tst_activate(int number, const char *string);

EOAPI void  tst_disable(int level);


#endif
