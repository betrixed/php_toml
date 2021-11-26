/* php_toml extension for PHP */

#ifndef PHP_PHP_TOML_H
# define PHP_PHP_TOML_H

extern zend_module_entry php_toml_module_entry;
# define phpext_php_toml_ptr &php_toml_module_entry

# define PHP_PHP_TOML_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_PHP_TOML)
ZEND_TSRMLS_CACHE_EXTERN()
# endif


PHP_MINIT_FUNCTION(php_toml);

#endif	/* PHP_PHP_TOML_H */
