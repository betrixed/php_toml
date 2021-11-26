# php_toml
PHP C-Extension to parse a TOML formatted string, and return its equivalent array structure.
As a C-extension this about 10x faster than the equivalent PHP script.

Supports UTF-8 documents.


```php

class TomlReader {
    public function read(string $s) : array {}
}


/** @generate-function-entries */
function toml_read(string $subject) : array {}
```
