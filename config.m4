dnl config.m4 for extension toml


PHP_ARG_ENABLE([toml],
  [whether to enable toml support],
  [AS_HELP_STRING([--enable-toml],
    [Enable toml support])],
  [no])

if test "$TOML" != "no"; then
  AC_DEFINE(HAVE_TOML, 1, [ Have toml support ])
  PHP_ADD_INCLUDE([toml])
  PHP_NEW_EXTENSION(toml, \
    src/ucode8.c src/tom_p.c \
     php_toml.c \
    , $ext_shared)
  PHP_SUBST(TOML_SHARED_LIBADD)
  CFLAGS="$CFLAGS -std=c17"
fi
