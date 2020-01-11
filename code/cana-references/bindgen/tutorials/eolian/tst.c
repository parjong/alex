
Eina_Bool _tst_activate(Eo *obj, Tst_Data *pd, int number, const char *string);

EOAPI EO_FUNC_BODYV(tst_activate, Eina_Bool, 0, EO_FUNC_CALL(number, string), int number, const char *string);

void _tst_disable(Eo *obj, Tst_Data *pd, int level);

EOAPI EO_VOID_FUNC_BODYV(tst_disable, EO_FUNC_CALL(level), int level);

static const Eo_Op_Description _tst_op_desc[] = {
     EO_OP_FUNC(tst_activate, _tst_activate),
     EO_OP_FUNC(tst_disable, _tst_disable),
};

static const Eo_Class_Description _tst_class_desc = {
     EO_VERSION,
     "Tst",
     EO_CLASS_TYPE_REGULAR,
     EO_CLASS_DESCRIPTION_OPS(_tst_op_desc),
     NULL,
     sizeof(Tst_Data),
     NULL,
     NULL
};

EO_DEFINE_CLASS(tst_class_get, &_tst_class_desc, EO_BASE_CLASS, NULL);