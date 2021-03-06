#ifndef PHIZ_TOMP_H
#define PHIZ_TOMP_H

#include <stdint.h>
#include <uchar.h>

typedef struct _toml_stream {
	zend_string		*value; // string of current token
	uint64_t		start;  // view of current parse
	uint64_t        end; 
	zval            subpats; // captures from preg_match
	uint64_t        id;
	uint64_t        line;
	int        		is_single;
	char32_t   		code;
	int             error;
	zend_string*    errorMsg;
	zend_string*   	hold; // s
	char*		    sptr;
	uint64_t		slen;
	uint64_t	    index;
	int             lineBegin;
	int           	unknownid;
	int           	eolid;
	int           	eosid;
	int           	tokenLine;
	int           	flagLF;
	int*            expSet;

	//  regular expression strings by enum
	zend_string**	zs_map;

	// 	build up parsed data		
	HashTable*		root;
	HashTable*		table;
	HashTable*      table_parts;

	// table path string pointers to keep clean
	zend_string*	path;
	zend_string*	partkey;
}
toml_stream;


typedef struct _t_tomlreader* p_tomlreader;

typedef struct _t_tomlreader {
	toml_stream 		 ts;
	zend_object          std;
} t_tomlreader;

extern PHPAPI zend_class_entry *phiz_ce_Tomp;


static inline  p_tomlreader t_tomlreader_from_obj(zend_object *obj)
{
	return (p_tomlreader)((char*)(obj) - XtOffsetOf(t_tomlreader, std));
}

static inline  p_tomlreader ZT_TOML_P(zval *zv)
{
	return (p_tomlreader)((char*) Z_OBJ_P((zv)) - XtOffsetOf(t_tomlreader, std));
}

bool ts_match_integer(toml_stream* oo, zval* ret, bool* partial);
bool ts_match_floatexp(toml_stream* oo, zval* ret, bool* partial);
bool ts_match_floatdot(toml_stream* oo, zval* ret, bool* partial);
bool ts_match_datetime(toml_stream* oo, zval* ret, bool* partial);
bool ts_match_bool(toml_stream* oo, zval* ret, bool* partial);
bool ts_match_daytime(toml_stream* oo, zval* ret, bool* partial);
bool ts_match_base(toml_stream* oo, zval* ret, bool* partial);

void ts_parse_init(toml_stream* oo, zend_string* s);
HashTable* ts_parse_loop(toml_stream* oo);
void ts_parse_end(toml_stream* oo);


void ts_assign_value(toml_stream* oo, zend_string* val);
void ts_init_ts(toml_stream* oo);
void ts_destroy_ts(toml_stream* oo);
void ts_handle_error(toml_stream* oo);
void ts_partial_error(toml_stream* oo);
void ts_nomatch_error(toml_stream* oo);
void ts_value_error(toml_stream* oo, char* msg, zend_string* src);
void ts_clear_error(toml_stream* oo);

void ts_set_path(toml_stream* oo, zend_string* p);
void ts_set_partkey(toml_stream* oo, zend_string* p);



#endif