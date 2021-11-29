# php_toml
PHP C-Extension to parse a TOML formatted string, and return its equivalent array structure.
As a C-extension this is around 10x faster than the equivalent PHP script.

Supports UTF-8 documents.


```php

class TomlReader {
    public function read(string $s) : array {}
}


/** @generate-function-entries */
function toml_read(string $subject) : array {}
```


The TOML parser handles time and datetime by creating objects to store and format them.
Time only values require a "DayTime" class. This is is available a class using the php_daytime extension,
A similar implementation is included as a php script class in this repository, which should be OK in the absense of the php_daytime extension.
