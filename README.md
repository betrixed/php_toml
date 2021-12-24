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
DateTime values are converted to PHP datetime objects.
Time only values have been given "DayTime" class.  This is in the [php_daytime](https://github.com/betrixed/php_daytime) extension,
A DayTime PHP class can be used with same functions, is in this repository as DayTime.php.
