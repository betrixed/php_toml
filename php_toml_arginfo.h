/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 7a9127b5c6a6ab63fed93edcdddca92688d13909 */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_toml_read, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, subject, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_TomlReader_read, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, s, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_TomlReader_matchBase, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, s, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_TomlReader_matchTime, 0, 1, DayTime, 0)
	ZEND_ARG_TYPE_INFO(0, s, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_TomlReader_matchInt arginfo_class_TomlReader_matchBase

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_TomlReader_matchDateTime, 0, 1, DateTime, 0)
	ZEND_ARG_TYPE_INFO(0, s, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_TomlReader_matchBool, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, s, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_TomlReader_matchFloatDot, 0, 1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, s, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_TomlReader_matchFloatExp arginfo_class_TomlReader_matchFloatDot


ZEND_FUNCTION(toml_read);
ZEND_METHOD(TomlReader, read);
ZEND_METHOD(TomlReader, matchBase);
ZEND_METHOD(TomlReader, matchTime);
ZEND_METHOD(TomlReader, matchInt);
ZEND_METHOD(TomlReader, matchDateTime);
ZEND_METHOD(TomlReader, matchBool);
ZEND_METHOD(TomlReader, matchFloatDot);
ZEND_METHOD(TomlReader, matchFloatExp);


static const zend_function_entry ext_functions[] = {
	ZEND_FE(toml_read, arginfo_toml_read)
	ZEND_FE_END
};


static const zend_function_entry class_TomlReader_methods[] = {
	ZEND_ME(TomlReader, read, arginfo_class_TomlReader_read, ZEND_ACC_PUBLIC)
	ZEND_ME(TomlReader, matchBase, arginfo_class_TomlReader_matchBase, ZEND_ACC_PUBLIC)
	ZEND_ME(TomlReader, matchTime, arginfo_class_TomlReader_matchTime, ZEND_ACC_PUBLIC)
	ZEND_ME(TomlReader, matchInt, arginfo_class_TomlReader_matchInt, ZEND_ACC_PUBLIC)
	ZEND_ME(TomlReader, matchDateTime, arginfo_class_TomlReader_matchDateTime, ZEND_ACC_PUBLIC)
	ZEND_ME(TomlReader, matchBool, arginfo_class_TomlReader_matchBool, ZEND_ACC_PUBLIC)
	ZEND_ME(TomlReader, matchFloatDot, arginfo_class_TomlReader_matchFloatDot, ZEND_ACC_PUBLIC)
	ZEND_ME(TomlReader, matchFloatExp, arginfo_class_TomlReader_matchFloatExp, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};
