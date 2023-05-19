/* php_toml extension for PHP */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_php_toml.h"
#include "php_toml_arginfo.h"
#include "src/tom_p.h"

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif





zend_object_handlers 	zt_handler_toml;
PHPAPI zend_class_entry *zt_ce_Toml;


static void t_tomlreader_copy_ctor( p_tomlreader to, p_tomlreader from)
{

}
static zend_object *t_tomlreader_new_ex(zend_class_entry *class_type,
									zend_object *orig, bool clone_orig)
{
	p_tomlreader 		  	   intern;
	zend_class_entry      *parent = class_type;
	bool                   inherited = false;

	intern = zend_object_alloc(sizeof(t_tomlreader), class_type);

	ts_init_ts(&intern->ts);

	zend_object_std_init(&intern->std, class_type);

	object_properties_init(&intern->std, class_type);

	if (orig && clone_orig) {
		p_tomlreader other = t_tomlreader_from_obj(orig);
		t_tomlreader_copy_ctor(intern, other);
	}
	while(parent) {
		if (parent == zt_ce_Toml) {
			intern->std.handlers = &zt_handler_toml;
			break;
		}
		parent = parent->parent;
		inherited = true;
	}

	ZEND_ASSERT(parent);

	return &intern->std;
	
}


static zend_object *t_tomlreader_new(zend_class_entry *class_type)
{
	return t_tomlreader_new_ex(class_type, NULL, 0);
}

static void t_tomlreader_free_storage(zend_object *object)
{
	p_tomlreader intern = t_tomlreader_from_obj(object);
	
	ts_destroy_ts(&intern->ts);
	zend_object_std_dtor(&intern->std);
}

static zend_object *t_tomlreader_clone(zend_object *old_object)
{
	zend_object *new_object = t_tomlreader_new_ex(old_object->ce, old_object, 1);

	zend_objects_clone_members(new_object, old_object);

	return new_object;
}
PHPAPI void 
t_register_std_class(zend_class_entry ** ppce, 
	char * class_name,  const zend_function_entry* function_list)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY_EX(ce, class_name, strlen(class_name), function_list);
	*ppce = zend_register_internal_class(&ce);
}

PHPAPI void 
t_register_child_class(zend_class_entry ** ppce, 
	zend_class_entry *parent, 
	char * class_name, const zend_function_entry* function_list)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY_EX(ce, class_name, strlen(class_name), function_list);
	*ppce = zend_register_internal_class_ex(&ce, parent);
}

PHP_MINIT_FUNCTION(toml)
{
	t_register_std_class(&zt_ce_Toml, "TomlReader", class_TomlReader_methods);

	zt_ce_Toml->create_object = t_tomlreader_new;


	memcpy(&zt_handler_toml, &std_object_handlers, sizeof(zend_object_handlers));

	zt_handler_toml.offset = XtOffsetOf(t_tomlreader, std);
	zt_handler_toml.clone_obj = t_tomlreader_clone;
	zt_handler_toml.dtor_obj  = zend_objects_destroy_object;
	zt_handler_toml.free_obj  = t_tomlreader_free_storage;
}

PHP_METHOD(TomlReader, matchInt)
{

	zval *object = ZEND_THIS;
	zend_string*   subject;

	p_tomlreader	   intern = ZT_TOML_P(object);

	ZEND_PARSE_PARAMETERS_START(1, 1)
			Z_PARAM_STR(subject)
	ZEND_PARSE_PARAMETERS_END();

	bool isPartial = false;
	toml_stream* oo = &intern->ts;
	
	//printf("subject refct = %d interned=%d\n", subject->gc, ZSTR_IS_INTERNED(subject));
	//ZVAL_LONG(return_value,101);
	
	ts_parse_init(oo,NULL);
	ts_assign_value(oo, subject);

	if (!ts_match_integer(oo, return_value, &isPartial)) {
		ts_nomatch_error(oo);
	}
	else if (isPartial) {
		ts_partial_error(oo);
	}

	ts_parse_end(oo);
}

PHP_METHOD(TomlReader, read)
{
	zval *object = ZEND_THIS;
	zend_string*   subject;

	p_tomlreader	   intern = ZT_TOML_P(object);

	ZEND_PARSE_PARAMETERS_START(1, 1)
			Z_PARAM_STR(subject)
	ZEND_PARSE_PARAMETERS_END();
	toml_stream* oo = &intern->ts;

	ts_parse_init(oo, subject);
	HashTable* root = ts_parse_loop(oo);
	
    ZVAL_ARR(return_value, root);
    ts_parse_end(oo);
}


PHP_METHOD(TomlReader, matchBase)
{
	zval *object = ZEND_THIS;
	zend_string*   subject;

	p_tomlreader	   intern = ZT_TOML_P(object);

	ZEND_PARSE_PARAMETERS_START(1, 1)
			Z_PARAM_STR(subject)
	ZEND_PARSE_PARAMETERS_END();
	bool isPartial = false;
	toml_stream* oo = &intern->ts;

	ts_parse_init(oo,NULL);
	ts_assign_value(oo, subject);

	if (!ts_match_base(oo, return_value, &isPartial)) {
		ts_nomatch_error(oo);
	}
	else if (isPartial) {
		ts_partial_error(oo);
	}
	ts_parse_end(oo);

}

PHP_METHOD(TomlReader, matchBool)
{
	zval *object = ZEND_THIS;
	zend_string*   subject;

	p_tomlreader	   intern = ZT_TOML_P(object);

	ZEND_PARSE_PARAMETERS_START(1, 1)
			Z_PARAM_STR(subject)
	ZEND_PARSE_PARAMETERS_END();
	bool isPartial = false;
	toml_stream* oo = &intern->ts;
	
	ts_parse_init(oo,NULL);
	ts_assign_value(oo, subject);

	if (!ts_match_bool(oo, return_value, &isPartial)) {
		ts_nomatch_error(oo);
	}
	else if (isPartial) {
		ts_partial_error(oo);
	}
	ts_parse_end(oo);
}


PHP_METHOD(TomlReader, matchTime)
{
	zval *object = ZEND_THIS;
	zend_string*   subject;

	p_tomlreader	   intern = ZT_TOML_P(object);

	ZEND_PARSE_PARAMETERS_START(1, 1)
			Z_PARAM_STR(subject)
	ZEND_PARSE_PARAMETERS_END();
	bool isPartial = false;
	toml_stream* oo = &intern->ts;
	
	ts_parse_init(oo,NULL);
	ts_assign_value(oo, subject);

	if (!ts_match_daytime(oo, return_value, &isPartial)) {
		ts_nomatch_error(oo);
	}
	else if (isPartial) {
		ts_partial_error(oo);
	}
	ts_parse_end(oo);
}

PHP_METHOD(TomlReader, matchDateTime)
{
	zval *object = ZEND_THIS;
	zend_string*   subject;

	p_tomlreader	   intern = ZT_TOML_P(object);

	ZEND_PARSE_PARAMETERS_START(1, 1)
			Z_PARAM_STR(subject)
	ZEND_PARSE_PARAMETERS_END();
	bool isPartial = false;
	toml_stream* oo = &intern->ts;
	
	ts_parse_init(oo,NULL);
	ts_assign_value(oo, subject);

	if (!ts_match_datetime(oo, return_value, &isPartial)) {
		ts_nomatch_error(oo);
	}
	else if (isPartial) {
		ts_partial_error(oo);
	}
	ts_parse_end(oo);
}
PHP_METHOD(TomlReader, matchFloatExp)
{
	zval *object = ZEND_THIS;
	zend_string*   subject;

	p_tomlreader	   intern = ZT_TOML_P(object);

	ZEND_PARSE_PARAMETERS_START(1, 1)
			Z_PARAM_STR(subject)
	ZEND_PARSE_PARAMETERS_END();
	bool isPartial = false;
	toml_stream* oo = &intern->ts;
	
	ts_parse_init(oo,NULL);
	ts_assign_value(oo, subject);

	if (!ts_match_floatexp(oo, return_value, &isPartial)) {
		ts_nomatch_error(oo);
	}
	else if (isPartial) {
		ts_partial_error(oo);
	}
	ts_parse_end(oo);
}


PHP_METHOD(TomlReader, matchFloatDot)
{
	zval *object = ZEND_THIS;
	zend_string*   subject;

	

	ZEND_PARSE_PARAMETERS_START(1, 1)
			Z_PARAM_STR(subject)
	ZEND_PARSE_PARAMETERS_END();
	bool isPartial = false;
	
	p_tomlreader	   intern = ZT_TOML_P(object);
	toml_stream* oo = &intern->ts;

	ts_parse_init(oo,NULL);
	ts_assign_value(oo, subject);

	if (!ts_match_floatdot(oo, return_value, &isPartial)) {
		ts_nomatch_error(oo);
	}
	else if (isPartial) {
		ts_partial_error(oo);
	}
	ts_parse_end(oo);

}


ZEND_FUNCTION(toml_read) 
{
	zend_string *stream;
	toml_stream  soo;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_STR(stream)
	ZEND_PARSE_PARAMETERS_END();

	ts_init_ts(&soo);
	ts_parse_init(&soo,stream);
	HashTable* root = ts_parse_loop(&soo);
	
    ZVAL_ARR(return_value, root);
    ts_destroy_ts(&soo);
}

/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION(toml)
{
#if defined(ZTS) && defined(COMPILE_DL_PHP_TOML)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(toml)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "toml support", "enabled");
	php_info_print_table_end();
}
/* }}} */


/* {{{ pdo_mysql_deps[] */
static const zend_module_dep toml_deps[] = {
	ZEND_MOD_REQUIRED("daytime")
	ZEND_MOD_END
};

/* {{{ toml_module_entry */
zend_module_entry toml_module_entry = {
	STANDARD_MODULE_HEADER_EX, NULL,
	toml_deps,
	"toml",					/* Extension name */
	ext_functions,					/* zend_function_entry */
	PHP_MINIT(toml),							/* PHP_MINIT - Module initialization */
	NULL,							/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(toml),			/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(toml),			/* PHP_MINFO - Module info */
	PHP_PHP_TOML_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_TOML
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(toml)
#endif